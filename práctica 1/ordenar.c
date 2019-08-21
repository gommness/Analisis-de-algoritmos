/**
 *
 * Descripcion: Implementacion de funciones de ordenacion 
 *
 * Fichero: ordenar.c
 * Autor:Javier Gómez Martínez y Carlos Li Hu 
 * Version: 1.0
 * Fecha: 22-09-2011
 *
 */

/* flag para poder usar clock es -lrt. poner luego en el makefile que nos dan
 -std=gnu99
 * 
 * LIBS = -lm -lrt
 * 
 * #define _POSIX_C_SOURCE 200112L      <-- define el clockgettime sin tener que usar -ltr en el makefile
 */

#define _POSIX_C_SOURCE 200112L
#include "ordenar.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/***************************************************/
/* Funcion: aleat_num Fecha:                       */
/* Autores:                                        */
/*                                                 */
/* Rutina que genera un numero aleatorio           */
/* entre dos numeros dados                         */
/*                                                 */
/* Entrada:                                        */
/* int inf: limite inferior                        */
/* int sup: limite superior                        */
/* Salida:                                         */
/* int: numero aleatorio                           */
/***************************************************/
int aleat_num(int inf, int sup)
{
    return (inf + (int)(((double)(sup-inf+1)*rand())/(RAND_MAX+1.0)));
}

/***************************************************/
/* Funcion: genera_perm Fecha:                     */
/* Autores:                                        */
/*                                                 */
/* Rutina que genera una permutacion               */
/* aleatoria                                       */
/*                                                 */
/* Entrada:                                        */
/* int n: Numero de elementos de la                */
/* permutacion                                     */
/* Salida:                                         */
/* int *: puntero a un array de enteros            */
/* que contiene a la permutacion                   */
/* o NULL en caso de error                         */
/***************************************************/
int* genera_perm(int n)
{
    int * perm;
    int aux1, aux2;
    int i;
    
    perm = (int*)malloc(n*sizeof(int));
    if(!perm)return NULL;
    
    for(i=1;i<=n;i++)
    {
        perm[i-1]=i;
    }
    for(i=1;i<=n;i++)
    {
        aux1 = perm[i-1];
        aux2 = aleat_num(i-1,n-1);
        perm[i-1] = perm[aux2];
        perm[aux2] = aux1;
    }
    return perm;
}

/***************************************************/
/* Funcion: genera_permutaciones Fecha:            */
/* Autores:                                        */
/*                                                 */
/* Funcion que genera n_perms permutaciones        */
/* aleatorias de tamanio elementos                 */
/*                                                 */
/* Entrada:                                        */
/* int n_perms: Numero de permutaciones            */
/* int tamanio: Numero de elementos de cada        */
/* permutacion                                     */
/* Salida:                                         */
/* int**: Array de punteros a enteros              */
/* que apuntan a cada una de las                   */
/* permutaciones                                   */
/* NULL en caso de error                           */
/***************************************************/
int** genera_permutaciones(int n_perms, int tamanio)
{
    int ** out;
    int i;
    out = (int**)malloc(n_perms * sizeof(int*));
    if(!out)return NULL;
    
    for(i=0;i<n_perms;i++)
        out[i]=genera_perm(tamanio);
    return out;
}

/***************************************************/
/* Funcion: SelectSort    Fecha:                   */
/* Vuestro comentario                              */
/***************************************************/
int BubbleSort(int* tabla, int ip, int iu)
{
    int flag=1, i, cont=0,j,aux;
        if(!tabla||ip<0||iu<ip)
        return -1;
    for(i=iu;flag==1 && i>ip;i--)
    {
     flag=0;
     for(j=ip;j<i;j++)
     {
         if(tabla[j]>tabla[j+1]){
             flag=1;
             cont++;
             aux= tabla[j];
             tabla[j]=tabla[j+1];
             tabla[j+1]=aux;
         }
     }
     
    }
    return cont;
    
}

/***************************************************/
/* Funcion: SelectSortInv    Fecha:                   */
/* Vuestro comentario                              */
/***************************************************/
int BubbleSortInv(int* tabla, int ip, int iu)
{
int flag=1, i, cont=0,j,aux;
        if(!tabla||ip<0||iu<ip)
        return -1;
    for(i=iu;flag==1 && i>ip;i--)
    {
     flag=0;
     for(j=ip;j<i;j++)
     {
         if(tabla[j]<tabla[j+1]){
             flag=1;
             cont++;
             aux= tabla[j];
             tabla[j]=tabla[j+1];
             tabla[j+1]=aux;
         }
     }
     
    }
    return cont;
}


/***************************************************/
/* Funcion: tiempo_medio_ordenacion Fecha:         */
/*                                                 */
/* Vuestra documentacion (formato igual            */
/* que en el primer apartado):                     */
/***************************************************/
short tiempo_medio_ordenacion(pfunc_ordena metodo, 
                              int n_perms,
                              int tamanio, 
                              PTIEMPO ptiempo)
{
	/*FILE * f;*/
    int i, max, min;
    int** L;
    double sum, OB/*,start,end*/;
    double segundos;
    double t_medio=0;
    struct timespec time, aux;

	/*f = fopen("test.txt","w");*/
    OB=0;
    min = (int)ceil(((double)tamanio/2.0)*(tamanio-1));
    max = 0;
    
    /*ptiempo = (PTIEMPO)malloc(sizeof(TIEMPO));*/

    sum = 0;
    ptiempo->n_perms=n_perms;
    ptiempo->tamanio=tamanio;
    
    L = genera_permutaciones(n_perms,tamanio);

    for(i=0;i<n_perms;i++){
        clock_gettime(CLOCK_REALTIME,&time);
        
        sum = metodo(L[i],0,tamanio-1);
        clock_gettime(CLOCK_REALTIME,&aux);
		segundos = aux.tv_nsec-time.tv_nsec;
        t_medio += segundos*0.000000001;
	
        OB += sum;
        if(min > (int)sum)min = (int)sum;
        if(max < (int)sum)max = (int)sum;
    }
	for(i=0;i<n_perms;i++)
		free(L[i]);
	free(L);
    sum = OB;
    ptiempo->tiempo = (double)t_medio/i;
    ptiempo->medio_ob = (double)OB/i;
    ptiempo->max_ob=max;
    ptiempo->min_ob=min;
    /*fprintf(f,"%d\t\t",ptiempo->tamanio);
    fprintf(f,"%f\t",(double)ptiempo->tiempo);
    fprintf(f,"%f\t",(double)ptiempo->medio_ob);
    fprintf(f,"%d\t\t",ptiempo->max_ob);
    fprintf(f,"%d\n",ptiempo->min_ob);
	fclose(f);*/
	return OK;
}

/***************************************************/
/* Funcion: genera_tiempos_ordenacion Fecha:       */
/*                                                 */
/* Vuestra documentacion                           */
/***************************************************/
short genera_tiempos_ordenacion(pfunc_ordena metodo, char* fichero, int num_min, int num_max, int incr, int n_perms)
{
    FILE* f;
    int i,k,N;
    PTIEMPO tiempo;
    
    /*f = fopen(fichero,"w");
    if(!f)return ERR;*/
    N = (int)ceil(((double)num_max-(double)num_min)/(double)incr);
    tiempo = (PTIEMPO)malloc(sizeof(TIEMPO)*(N));
    if(!tiempo)return ERR;
    f=fopen(fichero,"w");
    fprintf(f, "tam perm\tt_ejec (s)\tpromedioOB\tmaximoOB\tminimoOB\n");
    fclose(f);
    for(k=0,i=num_max;k<N && i>=num_min;i-=incr,k++){
        tiempo_medio_ordenacion(metodo,n_perms,i,&(tiempo[k]));
    }
    guarda_tabla_tiempos(fichero,tiempo,N);
    /*for(i=0;i<N;i++)
	free(ptiempo[i]);
    free(ptiempo);*/
	free(tiempo);
    return OK;
}

/***************************************************/
/* Funcion: guarda_tabla_tiempos Fecha:            */
/*                                                 */
/* Vuestra documentacion (formato igual            */
/* que en el primer apartado):                     */
/***************************************************/
short guarda_tabla_tiempos(char* fichero, PTIEMPO tiempo, int N)
{
    FILE* f;
    int i;
    f=fopen(fichero,"a");
    for(i=0;i<N;i++){
    fprintf(f,"%d\t\t",tiempo[i].tamanio);
    fprintf(f,"%f\t",(double)tiempo[i].tiempo);
    fprintf(f,"%f\t",(double)tiempo[i].medio_ob);
    fprintf(f,"%d\t\t",tiempo[i].max_ob);
    fprintf(f,"%d\n",tiempo[i].min_ob);
    }
    fclose(f);
    return OK;
}


