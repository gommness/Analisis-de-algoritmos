
#include "tiempos.h"
#include <math.h>

short tiempo_medio_ordenacion(pfunc_ordena metodo,
        int n_perms,
        int tamanio,
        PTIEMPO ptiempo) {

    int i, max, min;
    int** L;
    double sum, OB;
    double t_medio = 0;
    struct timespec time, aux;

    OB = 0;
    min = (int) ceil(((double) tamanio / 2.0)*(tamanio));
    max = 0;


    sum = 0;
    ptiempo->n_perms = n_perms;
    ptiempo->tamanio = tamanio;

    L = genera_permutaciones(n_perms, tamanio);

    for (i = 0; i < n_perms; i++) {
        clock_gettime(CLOCK_REALTIME, &time);

        sum = metodo(L[i], 0, tamanio-1);
        clock_gettime(CLOCK_REALTIME, &aux);
        t_medio += (aux.tv_nsec - time.tv_nsec) * 0.000000001;

        OB += sum;
        if (min > (int) sum)min = (int) sum;
        if (max < (int) sum)max = (int) sum;
    }
    for (i = 0; i < n_perms; i++)
        free(L[i]);
    free(L);
    sum = OB;
    ptiempo->tiempo = (double) t_medio / i;
    ptiempo->medio_ob = (double) OB / i;
    ptiempo->max_ob = max;
    ptiempo->min_ob = min;
    return OK;
}

short genera_tiempos_ordenacion(pfunc_ordena metodo, char* fichero, int num_min, int num_max, int incr, int n_perms) {
    int i, k, N;
    PTIEMPO tiempo;

    N = (int) ceil(1 + ((double) num_max - (double) num_min) / (double) incr);
    tiempo = (PTIEMPO) malloc(sizeof (TIEMPO)*(N));
    if (!tiempo)return -1;

    for (k = 0, i = num_max; k < N && i >= num_min; k++, i -= incr) {
        tiempo_medio_ordenacion(metodo, n_perms, i, &(tiempo[k]));
    }
    guarda_tabla_tiempos(fichero, tiempo, N);
    free(tiempo);
    return OK;
}

short guarda_tabla_tiempos(char* fichero, PTIEMPO tiempo, int N) {
    FILE* f;
    int i;
    f = fopen(fichero, "w");
    fprintf(f, "tam perm\tt_ejec (s)\tpromedioOB\tmaximoOB\tminimoOB\n");
    for (i = 0; i < N; i++) {
        fprintf(f, "%d\t\t", tiempo[i].tamanio);
        fprintf(f, "%f\t", (double) tiempo[i].tiempo);
        fprintf(f, "%f\t", (double) tiempo[i].medio_ob);
        fprintf(f, "%d\t\t", tiempo[i].max_ob);
        fprintf(f, "%d\n", tiempo[i].min_ob);
    }
    fclose(f);
    return OK;
}

short genera_tiempos_busqueda(pfunc_busqueda metodo, pfunc_generador_claves generador, 
                                int orden, char* fichero, 
                                int num_min, int num_max, 
                                int incr, double fclaves, int n_ciclos){
	int i, k, N;
    PTIEMPO tiempo;

    N = (int) ceil(1 + ((double) num_max - (double) num_min) / (double) incr);
    tiempo = (PTIEMPO) malloc(sizeof (TIEMPO)*(N));
    if (!tiempo)return -1;

    for (k = 0, i = num_max; k < N && i >= num_min; k++, i -= incr) {
        tiempo_medio_busqueda(metodo, generador, orden, i, fclaves, n_ciclos, &(tiempo[k]));
    }
    guarda_tabla_tiempos(fichero, tiempo, N);
    free(tiempo);
    return OK;
}

short tiempo_medio_busqueda(pfunc_busqueda metodo, pfunc_generador_claves generador,
                              int orden,
                              int tamanio, 
                              double fclaves,
                              int n_ciclos,
                              PTIEMPO ptiempo){
	int flag, *max, *min, i, k;
	int *claves, ppos;
	int **L;
    PDICC dic;
    double sum, OB = 0;
    double megamax = 0, megamin = 0;
    double t_medio = 0;
    struct timespec time, aux;

	min = (int*)malloc(sizeof(int)*n_ciclos);
	max = (int*)malloc(sizeof(int)*n_ciclos);
	claves = (int*)malloc(sizeof(int) * fclaves*tamanio);
	if(claves == NULL)
		return -1;
	generador(claves,fclaves*tamanio,tamanio);
	L = genera_permutaciones(n_ciclos,tamanio);
	if(L == NULL)
		return -1;

	for(i = 0; i < n_ciclos; i++)
	{
		dic = ini_diccionario(tamanio,orden);
		if(dic == NULL)
			return -1;
		flag = insercion_masiva_diccionario(dic,L[i],tamanio);
		if(flag == -1)
			return -1;
		max[i] = 0;
		min[i] = tamanio;
		clock_gettime(CLOCK_REALTIME, &aux); 
		for(k = 0; k < fclaves*tamanio; k++)
			{
			sum=busca_diccionario(dic, claves[k], &ppos, metodo);
			/*sum = metodo(dic->tabla, 0, (dic->tamanio)-1, claves[k],&ppos);*/
			OB += sum;
			if (min[i] > (int)sum)min[i] = (int)sum;
        	if (max[i] < (int)sum)max[i] = (int)sum;
			}
		clock_gettime(CLOCK_REALTIME, &time);

		t_medio += (time.tv_nsec - aux.tv_nsec) * 0.000000001;
		megamax += max[i];
		megamin += min[i];
		free(L[i]);
		libera_diccionario(dic);
	}
	free(L);
	megamax /= i;
	megamin /= i;
	ptiempo->n_perms = n_ciclos;
	ptiempo->tiempo = (double) t_medio / i;
    ptiempo->medio_ob = (double) OB / (i*k);
    ptiempo->max_ob = megamax;
    ptiempo->min_ob = megamin;
	ptiempo->tamanio = tamanio;
	free(min);
	free(max);
	free(claves);
    return OK;
	
}





