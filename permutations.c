/**
 *
 * Descripcion: Implementation of function that generate permutations
 *
 * File: permutations.c
 * Autor: Carlos Aguirre
 * Version: 1.1
 * Fecha: 21-09-2019
 *
 */

#include "permutations.h"
#include <stdio.h>
#include <stdlib.h>

/***************************************************/
/* Function: random_num Date:                      */
/* Authors:                                        */
/*                                                 */
/* Rutine that generates a random number           */
/* between two given numbers                       */
/*                                                 */
/* Input:                                          */
/* int inf: lower limit                            */
/* int sup: upper limit                            */
/* Output:                                         */
/* int: random number                              */
/***************************************************/
int random_num(int inf, int sup)
{
  return inf + rand() % (sup - inf + 1);
}

/***************************************************/
/* Function: generate_perm Date:                   */
/* Authors:                                        */
/*                                                 */
/* Rutine that generates a random permutation      */
/*                                                 */
/* Input:                                          */
/* int n: number of elements in the permutation    */
/* Output:                                         */
/* int *: pointer to integer array                 */
/* that contains the permitation                   */
/* or NULL in case of error                        */
/***************************************************/
int *generate_perm(int N)
{
  int i = 0, *perm = NULL, j = 0;

  perm = (int *)malloc(N * sizeof(perm[0]));
  if (perm == NULL)
    return NULL;

  for (i = 0; i < N; i++)
    perm[i] = i + 1;

  for (i = 0; i < N; i++)
  {
    j = random_num(0, N - 1);
    swap(&perm[i], &perm[j]);
  }

  return perm;
}

/***************************************************/
/* Function: generate_permutations Date:           */
/* Authors:                                        */
/*                                                 */
/* Function that generates n_perms random          */
/* permutations with N elements                    */
/*                                                 */
/* Input:                                          */
/* int n_perms: Number of permutations             */
/* int N: Number of elements in each permutation   */
/* Output:                                         */
/* int**: Array of pointers to integer that point  */
/* to each of the permutations                     */
/* NULL en case of error                           */
/***************************************************/
int **generate_permutations(int n_perms, int N)
{
  int i = 0, **perm = NULL;

  perm = (int **)malloc(n_perms * sizeof(perm[0]));
  if (perm == NULL)
    return NULL;

  for (i = 0; i < n_perms; i++)
  {
    perm[i] = generate_perm(N);
    if (!perm[i])
    {
      for (--i; i >= 0; i--)
        free(perm[i]);
      free(perm);
      return NULL;
    }
  }
  return perm;
}

void swap(int *orig, int *dest)
{
  int aux = *dest;
  *dest = *orig;
  *orig = aux;
}