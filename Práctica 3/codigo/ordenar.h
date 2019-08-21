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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* definiciones de tipos */
typedef struct diccionario {
  int tamanio; /* tamano de la tabla */
  int n_datos; /* numero de datos en la tabla */
  char orden;  /* tabla ordenada o desordenada */
  int *tabla;  /* tabla de datos */
} DICC, *PDICC;

typedef int (* pfunc_busqueda)(int*, int, int, int, int*);

typedef struct tiempo {
  int n_perms;     /* numero de permutaciones */
  int tamanio;    /* tamanio de las permutaciones */
  double tiempo;   /* tiempo promedio */
  double medio_ob; /* numero premedio de veces que se ejecuta la OB */
  int min_ob;      /* minimo de ejecuciones de la OB */
  int max_ob;      /* maximo de ejecuciones de la OB */
} TIEMPO, *PTIEMPO;

/* definiciones de tipos */
typedef int (* pfunc_ordena)(int*, int, int);
typedef void (* pfunc_generador_claves)(int*, int, int);

/*typedef struct tiempo {*/
/*  int n_perms;*/     /* numero de permutaciones */
/*  int tamanio;*/     /* tamanio de las permutaciones */
/*  double tiempo;*/   /* tiempo promedio */
/*  double medio_ob;*/ /* numero premedio de veces que se ejecuta la OB */
/*  int min_ob; */     /* minimo de ejecuciones de la OB */
/*  int max_ob;  */    /* maximo de ejecuciones de la OB */
/*} TIEMPO, *PTIEMPO;*/

/* Funciones */
void swap(int* a, int* b);
int aleat_num(int inf, int sup);
int* genera_perm(int n);
int** genera_permutaciones(int n_perms, int tamanio);
int BubbleSort(int* tabla, int ip, int iu);
int BubbleSortInv(int* tabla, int ip, int iu);
int mergesort(int* tabla, int ip, int iu);
int quicksort(int* tabla, int ip, int iu);
int quicksort_src(int* tabla, int ip, int iu);
#endif
