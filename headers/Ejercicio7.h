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

#ifndef EJERCICIO7_H_
#define EJERCICIO7_H_

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>
#include <semaphore.h>
#include <commons/collections/queue.h>

#define TAMAN_COLA 10

void  trabajar_PC(void*);
void  procesar_cola_impresion(void*);
void  mandar_a_imprimir(t_queue*, const char*);
char* crear_data();

typedef struct {
	const char* pc; //PC que hizo el pedido de impresion
	char* data; 	//Datos a imprimir
} t_print_job;
void destroy_t_print_job(void*);

void queue_synced_push(t_queue*, t_print_job*);
void* queue_synced_pop(t_queue*);

#endif /* EJERCICIO7_H_ */
