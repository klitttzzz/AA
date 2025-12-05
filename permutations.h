/**
 *
 * Descripcion: Header for functions for permutations generation
 *
 * Fichero: permutations.h
 * Autor: Carlos Aguirre 
 * Version: 1.1
 * Fecha: 16-09-2019
 *
 */

#ifndef PERMUTATIONS_H
#define PERMUTATIONS_H

/* constants */

#ifndef ERR
  #define ERR -1
  #define OK (!(ERR))
#endif

int random_num(int inf, int sup);
int* generate_perm(int N);
int** generate_permutations(int n_perms, int N);
void swap(int *orig, int *dest);
void build_worst_case_recursive(int* S, int* T, int low, int high);
int *generate_worst_case_mergesort(int N);

#endif

