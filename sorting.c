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
#include <stdlib.h>
#include <stdio.h>

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
      } else break;
    }
    array[j + 1] = key;
    
}

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
  int flag, num = 0, i, j;

  if (!array || ip > iu) return ERR;

  for (i = ip; i < iu - 1; i++)
  {
    flag = 0;
    for (j = ip; j < iu - i - 1 ; j++)
    {
      num++;
      if (array[j] > array[j + 1]) {
        swap_(array+j, array+j+1);
        
        flag = 1;
      }
    }
    if(flag == 0) return num;
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

int mergesort(int *tabla, int ip, int iu) {
  int imedio = (ip + iu) / 2, num = 0;
  if (!tabla) {
    return ERR;
  }

  if(ip >= iu) {
    return 0;
  }

  num = mergesort(tabla, ip, imedio) + mergesort(tabla, imedio + 1, iu) + merge(tabla, ip, iu, imedio);
  
  return num;
}

int merge(int* tabla, int ip, int iu, int imedio) {
  int *tabaux = NULL, i = ip, j = imedio + 1, k = 0, num = 0;

  tabaux = (int*) malloc((iu - ip + 1)*sizeof(int));
  if(!tabaux) {
    return ERR;
  }


  while(i <= imedio && j <= iu) {
    if(tabla[i] < tabla[j]) 
    {
      tabaux[k] = tabla[i];
      i++;
    }
    else  {
      tabaux[k] = tabla[j];
      j++;
    }
    k++;
    num++;
  }

  if(i > imedio) {
    while(j <= iu) {
      tabaux[k] = tabla[j];
      j++, k++;
    }
  }
  else if (j > iu) {  
    while(i <= imedio) {
      tabaux[k] = tabla[i];
      i++, k++;
    }
  }

  for(i = 0; i < (iu - ip + 1); i++)
    tabla[ip + i] = tabaux[i];
  free(tabaux);
  return num;

  
}

int quicksort(int *tabla, int ip, int iu) {
  int M = 0, ob = 0;
  if(ip > iu) {
    return ERR;
  }

  if(ip == iu) 
    return 0;
  else {
    partition(tabla, ip, iu, &M);
    if (ip < M - 1)
      ob = quicksort(tabla, ip, M - 1);
    
    if(M + 1 < iu) 
      ob = quicksort(tabla, M + 1, iu);
  }

  return ob;
}

int partition(int* tabla, int ip, int iu,int *pos) {
  int pivot = 0, i = 0;
  median_stat(tabla, ip, iu, pos);
  
  pivot = tabla[*pos];
  swap_(tabla+ip, tabla +(*pos));
  *pos = ip;
  for(i = ip + 1; i <= iu; i++) {
    if(tabla[i]< pivot) {
      (*pos)++;
      swap_(tabla+i, tabla+(*pos));
    }
  }
  swap_(tabla+ip, tabla+(*pos));
  return 0;


}
int median(int *tabla,int ip, int iu,int *pos){
  *pos = ip;
  return 0;
}
int median_avg(int *tabla, int ip, int iu, int *pos) {
  *pos = (ip + iu) /2;
  return 0;
}
int median_stat(int *tabla, int ip, int iu, int *pos) {
  if(ip < iu && ip > ((ip+iu)/2)) *pos = ip;
  else if(ip > iu && iu > ((ip+iu)/2)) *pos = iu;
  else *pos = (ip + iu) /2;
  return 0;
}
