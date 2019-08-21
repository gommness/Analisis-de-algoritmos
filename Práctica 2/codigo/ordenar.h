/**
 *
 * Descripcion: Funciones de cabecera para ordenacion 
 *
 * Fichero: ordenar.h
 * Autor: 
 * Version: 1.0
 * Fecha: 22-09-2011
 *
 */

#ifndef ORDENA_H
#define ORDENA_H
/* constantes */

#define ERR -1
#define OK (!(ERR))

/* definiciones de tipos */

typedef struct tiempo {
  int n_perms;     /* numero de permutaciones */
  int tamanio;     /* tamanio de las permutaciones */
  double tiempo;   /* tiempo promedio */
  double medio_ob; /* numero premedio de veces que se ejecuta la OB */
  int min_ob;      /* minimo de ejecuciones de la OB */
  int max_ob;      /* maximo de ejecuciones de la OB */
} TIEMPO, *PTIEMPO;

typedef int (* pfunc_ordena)(int*, int, int);

/* Funciones */

int aleat_num(int inf, int sup);
int* genera_perm(int n);
int** genera_permutaciones(int n_perms, int tamanio);
int BubbleSort(int* tabla, int ip, int iu);
int BubbleSortInv(int* tabla, int ip, int iu);
short tiempo_medio_ordenacion(pfunc_ordena metodo, int n_perms,int tamanio, PTIEMPO ptiempo);
short genera_tiempos_ordenacion(pfunc_ordena metodo, char* fichero, int num_min, int num_max, int incr, int n_perms);
short guarda_tabla_tiempos(char* fichero, PTIEMPO tiempo, int N);
int mergesort(int* tabla, int ip, int iu);
int quicksort(int* tabla, int ip, int iu);
int quicksort_src(int* tabla, int ip, int iu);
#endif
