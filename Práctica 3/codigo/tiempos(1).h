/**
 *
 * Descripcion: Funciones de cabecera para medicion de tiempos 
 *
 * Fichero: tiempos.h
 * Autor: 
 * Version: 1.0
 * Fecha: 11-11-2011
 *
 */

#ifndef TIEMPOS_H
#define TIEMPOS_H

#define _POSIX_C_SOURCE 200112L
/*#define _POSIX_C_SOURCE 199309L*/
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ordenar.h"
#include "busqueda.h"

short tiempo_medio_ordenacion(pfunc_ordena metodo, int n_perms, int tamanio, PTIEMPO ptiempo);

short genera_tiempos_ordenacion(pfunc_ordena metodo, char* fichero, 
                                int num_min, int num_max, int incr, int n_perms);

short guarda_tabla_tiempos(char* fichero, PTIEMPO tiempo, int N);

short genera_tiempos_busqueda(pfunc_busqueda metodo, pfunc_generador_claves generador, 
                                int orden, char* fichero, 
                                int num_min, int num_max, 
                                int incr, double fclaves, int n_ciclos);

short tiempo_medio_busqueda(pfunc_busqueda metodo, pfunc_generador_claves generador,
                              int orden,
                              int tamanio, 
                              double fclaves,
                              int n_ciclos,
                              PTIEMPO ptiempo);


#endif

