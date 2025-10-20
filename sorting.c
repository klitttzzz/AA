/**
 *
 * Descripcion: Implementation of sorting functions
 *
 * Fichero: sorting.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#include "sorting.h"
#include <string.h>

/***************************************************/
/* Function: InsertSort Date:  12/10/25            */
/* Authors: Pablo Plaza y Ernest Çelo              */
/*                                                 */
/* Sorts an array using the insertion sort method  */
/*                                                 */
/* Input:                                          */
/* int* array: array to sort                       */
/* int ip: initial position                        */
/* int iu: final position                          */
/* Output:                                         */
/* int:number of OB executions or ERR              */
/* in case of error                                */
/***************************************************/
int InsertSort(int* array, int ip, int iu)
{
  int i, j, key;
  int num = 0;

  if(!array || ip > iu) return ERR;

  for (i = ip + 1; i <= iu; i++) 
  {
    key = array[i];
    j = i - 1;

    while(j >=ip ) 
    {
      num++;
      if(array[j] > key) 
      {
        array[j + 1] = array[j];
        j--;
      } else 
      {
        break;
      }
      
    }
    array[j + 1] = key;
    
}

return num;


  return num;
}

/***************************************************/
/* Function: BubbleSort Date: 12/10/25             */
/* Authors: Pablo Plaza y Ernest Çelo              */
/*                                                 */
/* Sorts an array using the bubble sort method     */
/*                                                 */
/* Input:                                          */
/* int* array: array to sort                       */
/* int ip: initial position                        */
/* int iu: final position                          */
/* Output:                                         */
/* int: number of swaps or ERR in case of error    */
/***************************************************/
int BubbleSort(int* array, int ip, int iu)
{
  int num = 0, i, j;
  int swapped = 0;

  if (!array || ip > iu) return ERR;

  for (i = ip; i < iu; i++) 
  {
    for (j = ip; j < iu - (i - ip); j++)
    {
      num++;   
      if (array[j] > array[j + 1]) {
        swap_(&array[j], &array[j+ 1]);
        swapped = 1;                               /*Comprobación de si el primero esta ordenado o no*/
      } 
    }
    if (swapped == 0) {
      break;
    }
}

  return num;
}

/***************************************************/
/* Function: swap_ Date: 12/10/25                  */
/* Authors: Pablo Plaza y Ernest Çelo              */
/*                                                 */
/* Swaps the values of two integers                */
/*                                                 */
/* Input:                                          */
/* int *orig: pointer to first integer             */
/* int *dest: pointer to second integer            */
/* Output:                                         */
/* None                                            */
/***************************************************/
void swap_(int *orig, int *dest) {
    int aux = *orig;
    *orig = *dest;
    *dest = aux;
}