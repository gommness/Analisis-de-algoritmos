/********************************************************/
/* Programa: ejercicio2      Fecha:                     */
/* Autores:Javier Gómez Martínez y Carlos Li Hu                                             */
/*                                                      */
/* Programa que genera permutaciones                    */
/* aleatorias                                           */
/*                                                      */
/* Entrada: Linea de comandos                           */
/* -tamanio: numero elementos permutacion               */
/* -numP: numero de permutaciones                       */
/* Salida: 0: OK, -1: ERR                               */
/********************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "ordenar.h"

int main(int argc, char** argv)
{
  FILE* f;
  int i;
  unsigned int num, tamanio, j, k;
  int* perm = NULL;

  srand(time(NULL));

  if (argc != 5) {
    fprintf(stderr, "Error en los parametros de entrada:\n\n");
    fprintf(stderr, "%s -tamanio <int> -numP <int>\n", argv[0]);
    fprintf(stderr, "Donde:\n");
    fprintf(stderr, " -tamanio : numero elementos permutacion.\n");
    fprintf(stderr, " -numP : numero de permutaciones.\n");
    exit(-1);
  }

  printf("Practica numero 1, apartado 2\n");
  printf("Realizada por: Javier Gómez Martínez y Carlos Li Hu\n");
  printf("Grupo: 1201\n");

  /* comprueba la linea de comandos */
  for(i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-tamanio") == 0) {
      tamanio = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-numP") == 0) {
      num = atoi(argv[++i]);
    } else {
      fprintf(stderr, "Parametro %s es incorrecto\n", argv[i]);
    }
  }
  f=fopen("prueba2.txt","w");
  /* imprimimos el resultado */
  for(j = 0; j < num; j++) { 
    perm = genera_perm(tamanio);
    if (perm == NULL) { /* error */
      printf("Error: No hay memoria\n");
      fclose(f);
      exit(-1);
    } else {
      for(k = 0; k < tamanio; k++) { /* imprimimos cada elemento */
        fprintf(f,"%d ", perm[k]);
      }
      fprintf(f,"\n");
      free(perm); /* liberamos la permutacion */
    }
  }
  fclose(f);
  return 0;
}

