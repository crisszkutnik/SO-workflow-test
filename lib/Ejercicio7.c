/*
 * Copyright (C) 2012 Sistemas Operativos - UTN FRBA. All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// Resuelto por Guidito

#include "../headers/Ejercicio7.h"

// Global variables are evil
// But I need them

//////////// Sincronización ////////////
pthread_t h1, h2, h3, h4;

// Estas dos: ver queue_synced_* al final
sem_t sem_size_cola;  // La cola tiene un tamaño máximo de 10
sem_t sem_cola_vacia; // Cuando la cola está vacía la impresora espera

pthread_mutex_t
    mutex_impresion; // Para que no hagan push o pop más de una PC a la vez
////////////////////////////////////////

// Cola
t_queue* job_queue;

void destroy_t_print_job(void* innocent_job) {
    t_print_job* job = (t_print_job*)innocent_job;
    // sorry job :((
    // free(job->pc);
    free(job->data);
    free(job); // noooo
}

// PC envía 10 trabajos a la cola
void trabajar_PC(void* args) {
    // t_queue* job_queue = (t_queue*) args; -> parece que job_queue tiene que
    // ser global
    //										   para que todos los hilos la puedan
    //usar. 										   Antes se estaba pasando como parámetro a esta func
    char* nombre = (char*)args; // Un mejor argumento!
    for (int i = 0; i < 10; i++) {
        mandar_a_imprimir(job_queue, nombre);
        usleep((unsigned int)1); // Ni idea por qué pero usan (unsigned int)
                                 // para esto
    }
}

// Func usada en trabajar_PC()
void mandar_a_imprimir(t_queue* job_queue, const char* nombre) {
    // Creación de t_print_job falopa inventado
    t_print_job* job = malloc(sizeof(t_print_job));
    job->data = crear_data(); // string[9] inventado
    job->pc = nombre;         // arg

    // Enviar a la cola
    printf("PC \"%s\" enviando [%s] a la cola...\n", job->pc, job->data);
    queue_synced_push(job_queue, job);
}

// La impresora procesa todo lo que haya en la cola
void procesar_cola_impresion(void* args) {
    // t_queue * job_queue = (t_queue*) args; // Lo mismo que trabajar()
    t_print_job* job = NULL; // NO UNINITIALIZED POINTERS!! aunque da igual

    for (;;) { // sexy
        job = (t_print_job*)queue_synced_pop(job_queue);
        printf("Imprimiendo trabajo de PC \"%s\", "
               "datos a imprimir: [%s]\n",
               job->pc, job->data);
        usleep((unsigned int)500); // De nuevo el casteo rarísimo
    }
}

// String[9] random
char* crear_data() {
    static const char alphanum[] =
        "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    char* out = malloc(10);
    for (int i = 0; i < 9; i++)
        out[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    out[9] = '\0';

    return out;
}

//////////// queue_synced_* ////////////

// Ejecutan queue_push y queue_pop pero
// utilizando la sincronización con los dos semáforos
// y el mutex inicializados al comienzo

void* queue_synced_pop(t_queue* job_queue) {
    sem_wait(&sem_cola_vacia); // espera mientras no tenga nada que popear!

    pthread_mutex_lock(&mutex_impresion);
    void* elem = queue_pop(job_queue);
    pthread_mutex_unlock(&mutex_impresion);

    sem_post(
        &sem_size_cola); // Señala que ahora hay 1 espacio más para hacer push

    return elem;
}

void queue_synced_push(t_queue* job_queue, t_print_job* job) {
    sem_wait(
        &sem_size_cola); // si está en 0, no tiene más espacio, impresora espera

    pthread_mutex_lock(&mutex_impresion);
    queue_push(job_queue, (void*)job);
    pthread_mutex_unlock(&mutex_impresion);

    sem_post(&sem_cola_vacia); // Le indica que ya se puede hacer pop, la cola
                               // no está más vacía
}

// Works like a charm!
