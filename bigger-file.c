#include <commons/collections/list.h>
#include <commons/log.h>
#include <commons/string.h>
#include <commons/txt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Type used to store persons

typedef struct Persona {
  char *region;
  char *nya;
  int edad;
  char *num_tel;
  char *dni;
  int saldo;
} Persona;

void free_persona(void *p) {
  Persona *pers = (Persona *)p;
  free(pers->region);
  free(pers->nya);
  free(pers->num_tel);
  free(pers->dni);
  free(pers);
}

// p1 and p2 are of type void* to avoid
// warning caused by list_sort prototype
bool comp_persona(void *p1, void *p2) {
  Persona *pers1 = (Persona *)p1, *pers2 = (Persona *)p2;
  char strcmp_result;
  if (!(strcmp_result = strcmp(pers1->region, pers2->region)))
    return (pers1->edad < pers2->edad)

        ;
  return (strcmp_result < 0);
}

int main()

{

  // Logger
  t_log *logger = log_create("log.txt", "main.c", false, LOG_LEVEL_TRACE);

  // Input file

#define N_FIELDS 6
  FILE *fin = fopen("in.txt", "r");
  // Región; Nombre y Apellido; Edad; Número Telefónico; DNI; Saldo
  char buf[1000];
  char **lista_datos = NULL;

  ////////////
  // File content to list of Persona*

  t_list *lista_personas = list_create();

  while (fgets(buf, 1000, fin)) {
    lista_datos = string_split(buf, ";"); // split read line by ;

    // Create Persona* and populate
    Persona *persona = calloc(1, sizeof(Persona));
    persona->region = strdup(lista_datos[0]);
    persona->nya = strdup(lista_datos[1]);
    persona->edad = atoi(lista_datos[2]);
    persona->num_tel = strdup(lista_datos[3]);
    persona->dni = strdup(lista_datos[4]);
    persona->saldo = atoi(lista_datos[5]);

    // Espacios que sobran
    string_trim(&(persona->region));
    string_trim(&(persona->nya));
    string_trim(&(persona->num_tel));
    string_trim(&(persona->dni));

    list_add(lista_personas, persona); // push to list
    // Free lista_datos
    for (int i = 0; lista_datos[i] != NULL; free(lista_datos[i++]))
      ;
    free(lista_datos);
  }

  fclose(fin);
  list_sort(lista_personas, &comp_persona);

  log_info(logger, "lista_personas size: %d\n", list_size(lista_personas));

  ////////////
  // Parse data and dump to output file

  FILE *fout = fopen("out.txt", "w");

  Persona *temp_p = NULL; // Persona* buffer to read from list

  char *str_out = NULL;
  for (int i = 0; i < list_size(lista_personas); i++) {
    temp_p = list_get(lista_personas, i);

    if (temp_p->edad >= 18 || temp_p->saldo < 100) {
      // Región | Edad | DNI | Nombre y Apellido (30 chars máximo) | Número
      // telefónico
      temp_p->nya = realloc(temp_p->nya, 32 * sizeof(char));
      temp_p->nya[31] = '\0';
      str_out = string_from_format("%s | %d | %s | %s | %s\n", temp_p->region,
                                   temp_p->edad, temp_p->dni, temp_p->nya,
                                   temp_p->num_tel);
      if (temp_p->edad >= 18)
        txt_write_in_file(fout, str_out);
      if (temp_p->saldo < 100)
        log_info(logger, str_out);

      free(str_out); // really important thing right here
    }
  }
  // doesnt work if you put free(str_out) here, you get L E A K S

  fclose(fout);
  list_destroy_and_destroy_elements(lista_personas, &free_persona);
  log_destroy(logger);
  return 0;
}

/*
==105== Memcheck, a memory error detector
==105== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==105== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==105== Command: ./main.out
==105==
==105==
==105== HEAP SUMMARY:
==105==     in use at exit: 0 bytes in 0 blocks
==105==   total heap usage: 324 allocs, 324 frees, 27,184 bytes allocated
==105==
==105== All heap blocks were freed -- no leaks are possible
==105==
==105== For lists of detected and suppressed errors, rerun with: -s
==105== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
*/