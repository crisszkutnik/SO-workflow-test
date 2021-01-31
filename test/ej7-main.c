#include "../headers/Ejercicio7.h"

//////////// Sincronización (Ejercicio7.c) ////////////
extern pthread_t h1, h2, h3, h4;
extern sem_t sem_size_cola;
extern sem_t sem_cola_vacia;
extern pthread_mutex_t mutex_impresion;

// Cola
extern t_queue* job_queue;

int main() {

	// Comentado porque dice que tiene LEAKS, pero es porque
	// no termina de ejecutar (porque siempre queda escuchando),
	// entonces nunca retorna, ni mucho menos hace el free! Fun

	// Probar de ejecutar localmente
	// gcc ej7-main.c ../lib/Ejercicio7.c -lpthread -lcommons -g -o main


	/*job_queue = queue_create();					// Cola vacía

	pthread_mutex_init(&mutex_impresion, NULL);	// Mutex común y corriente
	sem_init(&sem_size_cola, 0, TAMAN_COLA);	// Semáforo inicializado en TAMAN_COLA (ver queue_synced_*)
	sem_init(&sem_cola_vacia, 0, 0);			// Semáforo inicializado en 0 (ver queue_synced_*)

	// Ejecución

	pthread_create(&h1, NULL, (void*) trabajar_PC, "P-Cristobal");
	pthread_create(&h2, NULL, (void*) trabajar_PC, "P-LucasSpig");
	pthread_create(&h3, NULL, (void*) trabajar_PC, "P-GuidoDipi");
	pthread_create(&h4, NULL, (void*) procesar_cola_impresion, NULL);

	// Terminación (espera a que todos los hilos terminen para recién después retornar main)

	pthread_join(h1, (void**) NULL);
	pthread_join(h2, (void**) NULL);
	pthread_join(h3, (void**) NULL);
	pthread_join(h4, (void**) NULL);

	// Free stuff!!

	queue_destroy_and_destroy_elements(job_queue, &destroy_t_print_job);*/

	return EXIT_SUCCESS;
}