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
int* generate_perm(int N)
{
  int i = 0, *array = NULL;

  array = (int*) malloc(N *sizeof(int));
  if(!array) {
    return NULL;
  }

  for(i = 0; i < N; i++) {
    array[i] = i + 1;
  }

  for(i = 0; i < N; i++) {
    int j = random_num(0, N - 1);
    int aux = array[i];
    array[i] = array[j];
    array[j] = aux;
  }

  return array;
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
int** generate_permutations(int n_perms, int N)
{
  int i = 0, **array = NULL;

  array = (int**) malloc(n_perms *sizeof(int*));
  if(!array) {
    return NULL;
  }

  for(i = 0; i < n_perms; i++) {
    array[i] = generate_perm(N);
    if(!array[i]) {
      for(--i; i >= 0; i--) {
        free(array[i]);
      }
      free(array);
      return NULL;
    }
  }
  return array;
}
