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
  int **perms = NULL, i = 0, num = 0;
  clock_t start, end;
  double total_time = 0.0;
  
  ptime->N = N;
  ptime->n_elems = n_perms;
  ptime->average_ob = 0;

  perms = generate_permutations(n_perms, N);
  if (perms == NULL) return ERR; /*Comprobación si falla generate_permutations??*/

  num = method(perms[0], 0, N);
  ptime->average_ob += num;
  ptime->min_ob = num;
  ptime->max_ob = num;

  start = clock();
  for (i = 0; i < n_perms; i++)
  {
    num = method(perms[i], 0, N);
    ptime->average_ob += num;
    if(ptime->min_ob > num) ptime->min_ob = num;
    if(ptime->max_ob < num) ptime->max_ob = num;
  }
  end = clock();

  ptime->time = (double)(end - start) / CLOCKS_PER_SEC;

  ptime->average_ob = ptime->average_ob / n_perms;

  for (i = 0; i < n_perms; i++)
    free(perms[i]);
  free(perms);

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
  int i = 0, j = 0, n_times;
  short res;

  n_times = (((num_max - num_min)) / incr) + 1;

  ptime = malloc(n_times * sizeof(TIME_AA));

  if(!ptime) return ERR;

  for (j = num_min; j <= num_max; j += incr, i++)
  {
    if(average_sorting_time(method, n_perms, j, ptime+i) != OK) {     /*Necesario comprobar si lo que devuelve average_sorting es correcto*/
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
/* Your documentation                              */
/***************************************************/
short save_time_table(char* file, PTIME_AA ptime, int n_times)
{
  FILE *f = fopen(file, "w");
  int i;

  if(!f) return ERR;

  fprintf(f, "\tN\tTime(s)\tAverage_OB\tMax_OB\tMin_OB\n");
  
  for (i = 0; i < n_times; i++)
    fprintf(f, "\t%d\t%f\t%f\t%d\t%d\n", ptime[i].N, ptime[i].time, ptime[i].average_ob, ptime[i].max_ob, ptime[i].min_ob);
  
  fclose(f);

  return OK;
}

