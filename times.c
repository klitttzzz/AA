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

/***************************************************/
/* Function: average_sorting_time Date:            */
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
    num = method(perms[i], 0, N - 1); /*Cambio, de N a N - 1*/
    if(num == ERR)                    /*Comprobación por si falla el method*/
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

  ptime->time = ((double)(end - start) / CLOCKS_PER_SEC) / n_perms; /*Añadido la división entre n_perms*/

  ptime->average_ob = ptime->average_ob / n_perms;

  for (i = 0; i < n_perms; i++)
    free(perms[i]);
  free(perms);

  return OK;
}

/***************************************************/
/* Function: generate_sorting_times Date:          */
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
/* Function: save_time_table Date:                 */
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
    fprintf(f, "\t%d\t%f\t%.2f\t%d\t%d\n", ptime[i].N, ptime[i].time, ptime[i].average_ob, ptime[i].max_ob, ptime[i].min_ob);
  
  fclose(f);

  return OK;
}

