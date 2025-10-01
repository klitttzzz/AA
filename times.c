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

/***************************************************/
/* Function: average_sorting_time Date:            */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short average_sorting_time(pfunc_sort method, int n_perms, int N, PTIME_AA ptime)
{
  int **perms = NULL, i, num = 0;
  
  ptime->time = (double) clock();
  ptime->time = ptime->time / CLOCKS_PER_SEC;
  ptime->N = N;
  ptime->n_elems = n_perms;

  perms = generate_permutations(n_perms, N);

  num = method(perms[0], 0, N);
  ptime->average_ob += num;
  ptime->min_ob = num;
  ptime->max_ob = num;

  for (i = 1; i < n_perms; i++)
  {
    num = method(perms[i], 0, N);
    ptime->average_ob += num;
    if(ptime->min_ob > num) ptime->min_ob = num;
    if(ptime->max_ob < num) ptime->max_ob = num;
  }
  
   ptime->average_ob = ptime->average_ob / n_perms;

  return OK;
}

/***************************************************/
/* Function: generate_sorting_times Date:          */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short generate_sorting_times(pfunc_sort method, char* file, int num_min, int num_max, int incr, int n_perms)
{
  TIME_AA *ptime = NULL;
  int i, j, n_times;

  n_times = (((num_max - num_min)) / incr) + 1;

  ptime = malloc(n_times * sizeof(TIME_AA));

  if(!ptime) return ERR;

  for (j = num_min; j <= num_max; j += incr, i++)
  {
    average_sorting_time(method, n_perms, j, ptime+i);
  }

  save_time_table(file, ptime, n_times);

  return OK;
  
}

/***************************************************/
/* Function: save_time_table Date:                 */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short save_time_table(char* file, PTIME_AA ptime, int n_times)
{
  FILE *f = fopen(file, "w");
  int i;

  if(!f) return ERR;

  fprintf(f, "\tN\tTime(s)\tAverage_OB\tMax_OB\tMin_OB\n");
  
  for (i = 0; i < n_times; i++)
    fprintf(f, "\t%d\t%f\t%f\t%d\t%d\n", ptime->N, ptime->time, ptime->average_ob, ptime->max_ob, ptime->min_ob);
  
  fclose(f);

  return OK;
}


