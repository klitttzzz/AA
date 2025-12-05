/**
 *
 * Description: Implementation of functions for search
 *
 * File: search.c
 * Author: Carlos Aguirre and Javier Sanz-Cruzado
 * Version: 1.0
 * Date: 14-11-2016
 *
 */

#include "search.h"

#include <stdlib.h>
#include <math.h>
#include <string.h>

/**
 *  Key generation functions
 *
 *  Description: Receives the number of keys to generate in the n_keys
 *               parameter. The generated keys go from 1 to max. The
 * 				 keys are returned in the keys parameter which must be
 *				 allocated externally to the function.
 */

/**
 *  Function: uniform_key_generator
 *               This function generates all keys from 1 to max in a sequential
 *               manner. If n_keys == max, each key will just be generated once.
 */
void uniform_key_generator(int *keys, int n_keys, int max)
{
  int i;

  for (i = 0; i < n_keys; i++)
    keys[i] = 1 + (i % max);

  return;
}

/**
 *  Function: potential_key_generator
 *               This function generates keys following an approximately
 *               potential distribution. The smaller values are much more
 *               likely than the bigger ones. Value 1 has a 50%
 *               probability, value 2 a 17%, value 3 the 9%, etc.
 */
void potential_key_generator(int *keys, int n_keys, int max)
{
  int i;

  for (i = 0; i < n_keys; i++)
  {
    keys[i] = .5 + max / (1 + max * ((double)rand() / (RAND_MAX)));
  }

  return;
}

/***************************************************/
/* Function: init_dictionary Date: 21/11/25        */
/* Authors: Pablo Plaza y Ernest Çelo              */
/*                                                 */
/* Allocates memory for the Dictionary ADT         */
/*                                                 */
/* Input:                                          */
/* int size: size of the dictionary table          */
/* char order: organization (SORTED/NOT_SORTED)    */
/* Output:                                         */
/* PDICT: pointer to the initialized dictionary    */
/***************************************************/
PDICT init_dictionary(int size, char order)
{
  PDICT pdict = NULL;
  int i = 0;

  pdict = malloc(sizeof(DICT));
  if (pdict == NULL)
    return NULL;

  pdict->size = size;
  pdict->order = order;
  pdict->n_data = 0;

  pdict->table = malloc(size * sizeof(int));
  if (pdict->table == NULL)
  {
    free(pdict);
    return NULL;
  }

  for (i = 0; i < size; i++)
  {
    pdict->table[i] = 0;
  }

  return pdict;
}

/***************************************************/
/* Function: free_dictionary Date: 21/11/25        */
/* Authors: Pablo Plaza y Ernest Çelo              */
/*                                                 */
/* Frees the memory allocated for the dictionary   */
/* structure and its internal data table           */
/*                                                 */
/* Input:                                          */
/* PDICT pdict: pointer to the dictionary          */
/* Output:                                         */
/* void                                            */
/***************************************************/
void free_dictionary(PDICT pdict)
{
  if (pdict == NULL)
    return;

  if (pdict->table)
    free(pdict->table);
  free(pdict);
}

/***************************************************/
/* Function: insert_dictionary Date: 21/11/25      */
/* Authors: Pablo Plaza y Ernest Çelo              */
/*                                                 */
/* Inserts a key into the dictionary               */
/* (Keeps order if initialized as SORTED)          */
/*                                                 */
/* Input:                                          */
/* PDICT pdict: pointer to the dictionary          */
/* int key: key to insert                          */
/* Output:                                         */
/* int: 0 if OK, error code otherwise              */
/***************************************************/
int insert_dictionary(PDICT pdict, int key)
{
  int A = 0, j = 0;
  if (pdict->n_data >= pdict->size)
    return ERR;
  pdict->table[pdict->n_data] = key;
  pdict->n_data++;

  A = pdict->table[pdict->n_data - 1];
  j = pdict->n_data - 2;

  if (pdict->order == SORTED)
  {
    while (j >= 0 && pdict->table[j] > A)
    {
      pdict->table[j + 1] = pdict->table[j];
      j--;
    }
    pdict->table[j + 1] = A;
  }

  return OK;
}

/***************************************************/
/* Function: massive_insertion_dictionary Date:..  */
/* Authors: Pablo Plaza y Ernest Çelo              */
/*                                                 */
/* Inserts multiple keys from an array             */
/*                                                 */
/* Input:                                          */
/* PDICT pdict: pointer to the dictionary          */
/* int *keys: array of keys to insert              */
/* int n_keys: number of keys in the array         */
/* Output:                                         */
/* int: 0 if OK, ERR otherwise                     */
/***************************************************/
int massive_insertion_dictionary(PDICT pdict, int *keys, int n_keys)
{
  int i = 0;

  if (keys == NULL || n_keys < 0 || pdict == NULL)
    return ERR;

  for (i = 0; i < n_keys; i++)
  {
    if(insert_dictionary(pdict, keys[i]) == ERR) return ERR;
  }

  return OK;
}

/***************************************************/
/* Function: search_dictionary Date: 21/11/25      */
/* Authors: Pablo Plaza y Ernest Çelo              */
/*                                                 */
/* Wrapper function to search a key in the dict    */
/* using a specific search method                  */
/*                                                 */
/* Input:                                          */
/* PDICT pdict: pointer to the dictionary          */
/* int key: key to search                          */
/* int *ppos: pointer to store the position found  */
/* pfunc_search method: search function to use     */
/* Output:                                         */
/* int: Number of basic ops (OB) or NOT_FOUND      */
/***************************************************/
int search_dictionary(PDICT pdict, int key, int *ppos, pfunc_search method)
{
  return method(pdict->table, 0, pdict->n_data - 1, key, ppos);
}

/***************************************************/
/* Function: bin_search Date: 21/11/25             */
/* Authors: Pablo Plaza y Ernest Çelo              */
/*                                                 */
/* Performs binary search (logarithmic time)       */
/* Requires a sorted table                         */
/*                                                 */
/* Input:                                          */
/* int *table: data array                          */
/* int F: first index                              */
/* int L: last index                               */
/* int key: key to search                          */
/* int *ppos: pointer to store position found      */
/* Output:                                         */
/* int: Number of basic ops (OB) or NOT_FOUND      */
/***************************************************/
int bin_search(int *table, int F, int L, int key, int *ppos)
{
  int m = 0, ob = 0;
  while (F <= L)
  {
    m = (F + L) / 2;
    ob++;
    if (table[m] == key)
    {
      *ppos = m;
      return ob;
    }
    else if (key < table[m])
    {
      L = m - 1;
    }
    else
      F = m + 1;
  }
  *ppos = NOT_FOUND;
  return ob;
}

/***************************************************/
/* Function: lin_search Date: 21/11/25             */
/* Authors: Pablo Plaza y Ernest Çelo              */
/*                                                 */
/* Performs linear search (linear time)            */
/*                                                 */
/* Input:                                          */
/* int *table: data array                          */
/* int F: first index                              */
/* int L: last index                               */
/* int key: key to search                          */
/* int *ppos: pointer to store position found      */
/* Output:                                         */
/* int: Number of basic ops (OB) or NOT_FOUND      */
/***************************************************/
int lin_search(int *table, int F, int L, int key, int *ppos)
{
  int i = 0, ob = 0;
  for (i = F; i <= L; i++)
  {
    ob++;
    if (table[i] == key)
    {
      *ppos = i;
      return ob;
    }
  }
  *ppos = NOT_FOUND;
  return ob;
}

/***************************************************/
/* Function: lin_auto_search Date: 21/11/25        */
/* Authors: Pablo Plaza y Ernest Çelo              */
/*                                                 */
/* Performs linear search with auto-organization   */
/* using the Transposition method                  */
/*                                                 */
/* Input:                                          */
/* int *table: data array                          */
/* int F: first index                              */
/* int L: last index                               */
/* int key: key to search                          */
/* int *ppos: pointer to store position found      */
/* Output:                                         */
/* int: Number of basic ops (OB) or NOT_FOUND      */
/***************************************************/
int lin_auto_search(int *table, int F, int L, int key, int *ppos)
{
  int i = 0, ob = 0, aux = 0;
  for (i = F; i <= L; i++)
  {
    ob++;
    if (table[i] == key)
    {

      if (i == 0)
      {
        *ppos = i;
        return ob;
      }
      aux = table[i];
      table[i] = table[i - 1];
      table[i - 1] = aux;
      *ppos = i;
      return ob;
    }
  }

  *ppos = NOT_FOUND;
  return ob;
}
