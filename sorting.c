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
/* Function: InsertSort    Date:                   */
/* Your comment                                    */
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

    while(j >=ip && array[j] > key) 
    {
        swap_(&array[j], &array[j + 1]);
        j--;
        num++;
    }
}

return num;


}


/***************************************************/
/* Function: SelectSort    Date:                   */
/* Your comment                                    */
/***************************************************/
int BubbleSort(int* array, int ip, int iu)
{
  int num = 0, i, j;

  if (!array || ip > iu) return ERR;

  for (i = ip; i < iu; i++) 
    for (j = ip; j < iu - i ; j++) 
      if (array[j] > array[j + 1]) {
        swap_(array+j, array+j+1);
        num++;
      }

  return num;
}

void swap_(int *orig, int *dest) {
    int aux = *orig;
    *orig = *dest;
    *dest = aux;
}






