/**
 *
 * Descripcion: Implementation of time measurement functions
 *
 * Fichero: times.c
 * Autor: Carlos Aguirre Maeso
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "times.h"
#include "sorting.h"
#include "permutations.h"
#include "search.h"

/***************************************************/ 
/* Function: average_sorting_time Date:15/10/25    */ 
/* Authors: Pablo Plaza y Ernest Çelo              */ 
/*                                                 */ 
/* Computes average, min, max and time for         */ 
/* sorting n_perms permutations of N elements      */ 
/*                                                 */ 
/* Input:                                          */ 
/* pfunc_sort method: sorting function             */ 
/* int n_perms: number of permutations             */ 
/* int N: number of elements per permutation       */ 
/* PTIME_AA ptime: pointer to result struct        */ 
/* Output:                                         */ 
/* short: OK or ERR                                */ 
/***************************************************/ 
short average_sorting_time(pfunc_sort method, int n_perms, int N, PTIME_AA ptime)
{
  int **perms = NULL, i = 0, num = 0, j = 0;
  clock_t start, end;
  
  ptime->N = N;
  ptime->n_elems = n_perms;
  ptime->average_ob = 0;

  perms = generate_permutations(n_perms, N);
  if (perms == NULL) return ERR; 

  start = clock();
  for (i = 0; i < n_perms; i++)
  {
    num = method(perms[i], 0, N - 1); 
    if(num == ERR)                    
    {
      for(j = 0; j < n_perms; j++)
        free(perms[j]);                      
      free(perms);
      return ERR;
    }
    ptime->average_ob += num;
    if(i==0) {
      ptime->min_ob = num;
      ptime->max_ob = num;
    }
    if(ptime->min_ob > num) ptime->min_ob = num;
    if(ptime->max_ob < num) ptime->max_ob = num;
  }
  end = clock();

  ptime->time = ((double)(end - start) / CLOCKS_PER_SEC) / n_perms;

  ptime->average_ob = ptime->average_ob / n_perms;

  for (i = 0; i < n_perms; i++)
    free(perms[i]); 
  free(perms);

  return OK;
}

/***************************************************/ 
/* Function: generate_sorting_times Date:15/10/25  */ 
/* Authors: Pablo Plaza y Ernest Çelo              */ 
/*                                                 */ 
/* Measures and saves sorting times for            */ 
/* different input sizes to a file                 */ 
/*                                                 */ 
/* Input:                                          */ 
/* pfunc_sort method: sorting function             */ 
/* char* file: output filename                     */ 
/* int num_min: min input size                     */ 
/* int num_max: max input size                     */ 
/* int incr: increment of input size               */ 
/* int n_perms: permutations per size              */ 
/* Output:                                         */ 
/* short: OK or ERR                                */ 
/***************************************************/ 
short generate_sorting_times(pfunc_sort method, char* file, int num_min, int num_max, int incr, int n_perms)
{
  TIME_AA *ptime = NULL;
  int i = 0, j = 0, n_times;
  short res;

  n_times = (((num_max - num_min)) / incr) + 1;

  ptime = malloc(n_times * sizeof(TIME_AA));

  if(!ptime) return ERR;

  for (j = num_min; j <= num_max; j += incr, i++)
  {
    if(average_sorting_time(method, n_perms, j, ptime+i) != OK) {     
      free(ptime);
      return ERR;
    }
  }

  res = save_time_table(file, ptime, n_times);
  free(ptime);

  return res;
  
}

/***************************************************/ 
/* Function: save_time_table Date:15/10/25         */ 
/*Authors: Pablo Plaza y Ernest Çelo               */ 
/*                                                 */ 
/* Saves timing results to a file                  */ 
/*                                                 */ 
/* Input:                                          */ 
/* char* file: output filename                     */ 
/* PTIME_AA ptime: array of results                */ 
/* int n_times: number of results                  */ 
/* Output:                                         */ 
/* short: OK or ERR                                */ 
/***************************************************/ 
short save_time_table(char* file, PTIME_AA ptime, int n_times)
{
  FILE *f = fopen(file, "w");
  int i;

  if(!f) return ERR;

  fprintf(f, "\tN\tTime(s)\tAverage_OB\tMax_OB\tMin_OB\n");
  
  for (i = 0; i < n_times; i++)
    fprintf(f, "\t%d\t%f\t%.0f\t%d\t%d\n", ptime[i].N, ptime[i].time, ptime[i].average_ob, ptime[i].max_ob, ptime[i].min_ob);
  
  fclose(f);

  return OK;
}
/***************************************************/ 
/* Function: average_search_time Date: 21/11/25    */ 
/* Authors: Pablo Plaza y Ernest Çelo              */ 
/*                                                 */ 
/* Calculates the average time and basic ops for   */ 
/* searching keys in a dictionary of size N        */ 
/*                                                 */ 
/* Input:                                          */ 
/* pfunc_search metodo: search function pointer    */ 
/* pfunc_key_generator generator: key gen. pointer */ 
/* int order: sort order (SORTED/NOT_SORTED)       */ 
/* int N: size of the dictionary                   */ 
/* int n_times: repetitions per key search         */ 
/* PTIME_AA ptime: structure to store results      */ 
/* Output:                                         */ 
/* short: OK or ERR                                */ 
/***************************************************/
short average_search_time(pfunc_search metodo, pfunc_key_generator generator, int order, int N, int n_times, PTIME_AA ptime)
{
  int  i = 0, num = 0, *keys=NULL, *perm=NULL, ppos = 0;
  PDICT pdict = NULL;
  clock_t start, end;
  
  ptime->N = N;
  ptime->n_elems = N * n_times;
  ptime->average_ob = 0;

  pdict = init_dictionary(N,order);
  if (pdict == NULL) return ERR;

  perm = generate_perm(N);
  if (perm == NULL){
    free_dictionary(pdict);
    return ERR;
  }

  if(massive_insertion_dictionary(pdict, perm, N) == ERR) {
    free_dictionary(pdict);
    free(perm);
    return ERR;
  }

  keys = calloc(ptime->n_elems, sizeof(int));

  if (keys == NULL){
    free_dictionary(pdict);
    free(perm);
    return ERR;
  }

  generator(keys, ptime->n_elems, N);

  start = clock();
  for (i = 0; i < ptime->n_elems; i++)
  {
    num = search_dictionary(pdict, keys[i], &ppos, metodo); 
    if(num == ERR)                    
    {
      free_dictionary(pdict);
      free(perm);
      free(keys);
      return ERR;
    }
    ptime->average_ob += num;
    if(i==0) {
      ptime->min_ob = num;
      ptime->max_ob = num;
    }
    if(ptime->min_ob > num) ptime->min_ob = num;
    if(ptime->max_ob < num) ptime->max_ob = num;
  }
  end = clock();

  ptime->time = ((double)(end - start) / CLOCKS_PER_SEC) / ptime->n_elems;

  ptime->average_ob = ptime->average_ob / ptime->n_elems;

  free(perm);
  free(keys);
  free_dictionary(pdict);

  return OK;
}

/***************************************************/ 
/* Function: generate_search_times Date: 21/11/25  */ 
/* Authors: Pablo Plaza y Ernest Çelo              */ 
/*                                                 */ 
/* Generates a file with performance statistics    */ 
/* for the search algorithm over a range of sizes  */ 
/*                                                 */ 
/* Input:                                          */ 
/* pfunc_search method: search function pointer    */ 
/* pfunc_key_generator generator: key gen. pointer */ 
/* int order: sort order (SORTED/NOT_SORTED)       */ 
/* char* file: output filename                     */ 
/* int num_min: minimum dictionary size            */ 
/* int num_max: maximum dictionary size            */ 
/* int incr: increment step for size               */ 
/* int n_times: repetitions per key search         */ 
/* Output:                                         */ 
/* short: OK or ERR                                */ 
/***************************************************/
short generate_search_times(pfunc_search method, pfunc_key_generator generator, int order, char* file, int num_min, int num_max, int incr, int n_times)
{
  TIME_AA *ptime = NULL;
  int i = 0, j = 0;
  short res;
  int num_steps = 0;

  num_steps = (((num_max - num_min)) / incr) + 1;

  ptime = malloc(num_steps * sizeof(TIME_AA));

  if(ptime == NULL) return ERR;

  for (j = num_min; j <= num_max; j += incr, i++)
  {
    if(average_search_time(method, generator, order, j, n_times, ptime+i) != OK) {     
      free(ptime);
      return ERR;
    }
  }

  res = save_time_table(file, ptime, num_steps);
  free(ptime);

  return res;
  
}