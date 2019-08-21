/**
 *
 * Descripcion: Implementacion funciones para busqueda 
 *
 * Fichero: busqueda.c
 * Autor: 
 * Version: 1.0
 * Fecha: 11-11-2011
 *
 */

#include "busqueda.h"

/**
 *  Funciones de geracion de claves
 *
 *  Descripcion: Recibe el numero de claves que hay que generar
 *               en el parametro n_claves. Las claves generadas
 *               iran de 1 a max. Las claves se devuelven en 
 *               el parametro claves que se debe reservar externamente
 *               a la funcion.
 */

/**
 *  Funcion: generador_claves_uniforme
 *               Esta fucnion genera todas las claves de 1 a max de forma 
 *               secuencial. Si n_claves==max entonces se generan cada clave
 *               una unica vez.
 */

void generador_claves_uniforme(int *claves, int n_claves, int max) {
    int i;

    for (i = 0; i < n_claves; i++) claves[i] = 1 + (i % max);

    return;
}

/**
 *  Funcion: generador_claves_potencial
 *               Esta funcion genera siguiendo una distribucion aproximadamente
 *               potencial. Siendo los valores mas pequenos mucho mas probables
 *               que los mas grandes. El valor 1 tiene una probabilidad del 50%,
 *               el dos del 17%, el tres el 9%, etc.
 */
void generador_claves_potencial(int *claves, int n_claves, int max) {
    int i;

    for (i = 0; i < n_claves; i++) {
        claves[i] = (1 + max) / (1 + max * ((double) rand() / RAND_MAX));
    }

    return;
}

PDICC ini_diccionario(int tamanio, char orden) {
    PDICC dick;
    dick = (PDICC) malloc(sizeof (DICC));
    if (dick == NULL)
        return NULL;
    dick->tamanio = tamanio;
    dick->orden = orden;
    dick->n_datos = 0;
    dick->tabla = (int*) malloc(sizeof (int)*tamanio);

    return dick;
}

void libera_diccionario(PDICC pdicc) {
    if (pdicc->tabla != NULL)
        free(pdicc->tabla);
    if (pdicc != NULL)
        free(pdicc);
}

int inserta_diccionario(PDICC pdicc, int clave) {
    int A, j, OB = 0;

    if (pdicc == NULL)
        return -1;
    if (pdicc->n_datos >= pdicc->tamanio)
        return -1;

    if (pdicc->orden == NO_ORDENADO) {
        pdicc->tabla[pdicc->n_datos] = clave;
        pdicc->n_datos++;
        OB++;
    } else if (pdicc->orden == ORDENADO) {
        pdicc->tabla[pdicc->n_datos] = clave;
        A = pdicc->tabla[pdicc->n_datos];
        for (j = pdicc->n_datos - 1; j >= 0 && pdicc->tabla[j] > A; j--) {
            OB++;
            swap(pdicc->tabla + (j + 1), pdicc->tabla + j);
        }
        pdicc->n_datos++;
    }
    return OB;
}

int insercion_masiva_diccionario(PDICC pdicc, int *claves, int n_claves) {
    int i, k = 0, OB = 0;
    if (pdicc == NULL || claves == NULL)
        return -1;
    for (i = 0; i < n_claves; i++) {
        k = inserta_diccionario(pdicc, claves[i]);
        if (k == -1)return -1;
        OB += k;
    }
	/*for(i=0;i<pdicc->tamanio;i++)
		printf("%d\n",pdicc->tabla[i]);
	printf("%d\n", pdicc->tamanio);*/
    return OB;
}

int busca_diccionario(PDICC pdicc, int clave, int *ppos, pfunc_busqueda metodo) {
    if(!pdicc)return -1;;
    return metodo(pdicc->tabla, 0, pdicc->n_datos-1, clave, ppos);
}

void imprime_diccionario(PDICC pdicc) {
    int i;
    if(!pdicc)
        return;
    for(i=0;i<pdicc->n_datos;i++)
        printf("%d ",pdicc->tabla[i]);
    printf("\n");
}

/* Funciones de busqueda del TAD Diccionario */
int bbin(int *tabla, int P, int U, int clave, int *ppos) {
    int OB = 0;
    if (!tabla || !ppos)
        return -1;
    while (P <= U) {
        OB++;
        *ppos = (P + U) / 2;
        if (tabla[*ppos] == clave)
            return OB;
        else if (clave < tabla[*ppos])
            U = (*ppos) - 1;
        else
            P = (*ppos) + 1;
    }
    return NO_ENCONTRADO;
}

int blin(int *tabla, int P, int U, int clave, int *ppos) {
    int OB = 0, i;
    if (!tabla || !ppos)
        return -1;
    for (i = P; i <= U; i++){
		OB++;        
		if (clave == tabla[i]) {
            *ppos = i;
            return OB;
        }
	}

    return NO_ENCONTRADO;
}

int blin_auto(int *tabla, int P, int U, int clave, int *ppos) {
    int OB = 0, i;
    if (!tabla || !ppos)
        return -1;
    for (i = P; i <= U; i++){
		OB++;
        if (clave == tabla[i]) {
            *ppos = i;
			if(i!=0)
				{
            	swap(tabla+i,tabla+(i-1));
				(*ppos)--;
				}
            return OB;
        }
	}

    return NO_ENCONTRADO;
}


