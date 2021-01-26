#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <time.h> 
#include "astronum.h"

#define MOSTRAR_GRUPOS_LINEAS 3 //se usa en Mostrar()

// Macros caracter a int y viceversa
#define can(c) (c-'0')
#define nac(n) (n+'0')

//////////// Creación ////////////

// todos sus caracteres son numéricos? 1 : 0
static int cadenaNumerica(char* cadena){
    for (int out=0; cadena[out]!='\0'; out++)
        if (!isdigit(cadena[out])) return 0;
    return 1;
}

// Crea un puntero a NumeroAstronomico desde cadena
// Considera los errores: cadena invalida, cadena vacía, cadena muy larga, errores de malloc
// Si la cadena dada solamente tiene "0"s el comportamiento es indefinido.
NumeroAstronomico* CrearDesdeCadena(char* cadena){
    ////// MALLOC //////
    NumeroAstronomico *num = malloc(sizeof(NumeroAstronomico));
    if (num==NULL) return NULL; // si falla
    ////// END MALLOC //////

    for(int i=0; cadena[i]=='0'; *(cadena)++);

    // Caso cadena muy larga (>100 caracteres)
    if (strlen(cadena)>100) {
        num->longitudError = Overflow;
    }
    // Caso todo bien (o cadena nula)
    else if (cadenaNumerica(cadena)){
        num->entero = cadena;
        num->longitudError = strlen(cadena);
    }
    // Caso cadena inválida
    else {
        num->longitudError = CadenaInvalida;
    }
    return num;
}

// Precondiciones:
// La longitud del número que se creará no debe exceder los 100 dígitos.
// Ejemplo de error: CrearDesdeCifraSeguidaDeCeros(1427, 98); -> 102 dígitos, error
// En todos los casos, la cantidad de ceros no puede superar los 99
// En casos de error retorna NULL
NumeroAstronomico* CrearDesdeCifraSeguidaDeCeros(int num, int ceros){
    // Evaluación de precondiciones
    if (ceros>99) return NULL;
    int longitud_num = (int) log10(num) + 1;    // cantidad de digitos de num
    int longitud_total =  longitud_num + ceros;
    if (longitud_total > 100) return NULL;

    // Creación de la cadena
    char* cadena = malloc(longitud_total);
    if(cadena==NULL) return NULL; // fallo malloc
    sprintf(cadena, "%d", num);
    // itoa(num, cadena, 10); // copia num

    for(int i=0; i<ceros; i++) cadena[i+longitud_num]='0'; // llena el resto con 0

    cadena[longitud_total] = '\0'; // fin de cadena
    
    return CrearDesdeCadena(cadena); // para evitar repetir el código del malloc
}

// Si el programa se ejecuta más de una vez por segundo, el resultado generado es el mismo
NumeroAstronomico* CrearAleatorio(){
    srand(time(NULL)); // seeding para mayor aleatoriedad

    int longitud = 1 + rand() % 100; // entre 1 y 100

    char* cadena = malloc(longitud+1);
    if(cadena==NULL) return NULL; // fallo malloc

    // Creación de cadena
    for(int i=0; i<longitud; i++){
        char cifra_aleatoria = nac(rand()%10);
        cadena[i] = cifra_aleatoria;
    }
    cadena[longitud] = '\0';

    return CrearDesdeCadena(cadena); // para evitar repetir el código del malloc
}

// Libera memoria
void* FreeNumeroAstronomico(NumeroAstronomico* a)

{free(a->entero);free(a);}

//////////// Errores ////////////

int EsSecuenciaNula(NumeroAstronomico* a){
    return a->longitudError == CadenaNula;
}

int EsSecuenciaInvalida(NumeroAstronomico* a){
    return a->longitudError == CadenaInvalida;
}

int EsOverflow(NumeroAstronomico* a){
    return a->longitudError == Overflow;
}

int EsPunteroNulo(NumeroAstronomico* a){
    return a->longitudError == PunteroNulo;
}

int EsError(NumeroAstronomico* a){
    return EsSecuenciaInvalida(a) || EsOverflow(a) || EsSecuenciaNula(a) || EsPunteroNulo(a);
}

//////////// Salida ////////////

// Muestra N grupos de 3 cifras a partir de un índice dado (caracter a caracter)
// El índice se pasa como puntero por el uso que se le da en Mostrar()
static void mostrarNGrupos(NumeroAstronomico* a, int cant, int *ind){
    int tope = (*ind) + cant*3; //hasta qué índice mostrar
    int comienzo = (*ind); //en cuál se empezó

    for (*ind; (((*ind) < tope) && (a->entero[*ind] != '\0')); (*ind)++){
        // se ve medio imposible este 'for'
        // pero lo único que hace es contar la cantidad de digitos según 'cant'
        // y tiene una condicion adicional que rompe si terminó la cadena (!='\0')
        putchar(a->entero[(*ind)]);
        if ((*ind - comienzo)%3 == 2) putchar('.');
    }
    putchar('\n');
}

// PRECONDICIONES:
// "grupos" debe ser positivo (es evidente)
void Mostrar(NumeroAstronomico* a, int grupos){
    // Si hay algun error en el número
    // es más fácil hacerlo así que usando las funciones EsTipoError()...
    if(a == NULL) { fprintf(stderr, "Puntero nulo\n\n"); return; }
    switch(a->longitudError){
        case Overflow: fprintf(stderr, "Overflow\n\n"); return;
        case PunteroNulo: fprintf(stderr, "Puntero nulo\n\n"); return;
        case CadenaInvalida: fprintf(stderr, "Cadena invalida\n\n"); return;
        case CadenaNula: fprintf(stderr, "Cadena nula\n\n"); return;
    }
    // end errores //

    // primer grupo primera línea
    int espacios = (3-(a->longitudError % 3)) % 3;
    int i = 0-espacios;
    for (i; i<3-espacios; i++) 
        (i<0)? putchar(' ') : putchar(a->entero[i]);
    putchar('.');
    // terminar de mostrar primera línea
    mostrarNGrupos(a, grupos-1, &i);
    // muestra el resto
    // (indentado para que quede debajo del 2do grupo de la primera linea)
    while(i < a->longitudError){
        printf("    ");
        mostrarNGrupos(a, MOSTRAR_GRUPOS_LINEAS, &i);
    }

    putchar('\n');
}

//////////// Aritmética ////////////

// auxiliares //

// Retorna la longitud del número más grande, dados dos Numeros Astronomicos
static int longmax(NumeroAstronomico* a, NumeroAstronomico* b){
    return (a->longitudError > b->longitudError? a->longitudError : b->longitudError);
}

// Suma dos cadenas como si fueran enteros (sin atoi, atof, nada de eso)
// Retorna NULL si la cadena tiene más de 100 caracteres (overflow)
static char* sumaCadenas(const char* a, int lena, const char* b, int lenb){
    // Longitud máxima, cadena larga, cadena corta
    int longmax = lena>lenb? lena : lenb;
    longmax++; // la longitud máxima de la suma es 1 más que la cadena más larga
    char* corta = lena<lenb? strdup(a) : strdup(b);
    char* larga = lena<lenb? strdup(b) : strdup(a);
    char* salida = malloc(1+longmax); // lo que se retornará
    // Diferencia entre la larga y la corta (para rellenar con 0s)
    int diff = longmax - strlen(corta);

    // A sumar!
    int buffer;                     // auxiliar para carries
    int carries;                    // auxiliar para carries parte 2
    salida[0] = '0';                // primera cifra en 0
    // Suma caracter a caracter (de izquierda a derecha)
    for(int i=1; i<longmax; i++){
        // Suma dígitos de ambas cadenas (la mas corta rellenada con ceros a la izquierda)
        char padding_or_num = i<diff? '0' : corta[i-diff]; // 0 o dígito (cadena corta)
        int cifra = can(padding_or_num) + can(larga[i-1]); // dígito (cadena larga)

        // asigna el valor char de esa cifra (solo las unidades)
        salida[i] = nac(cifra%10);

        // arregla los carries (suma 1 para atrás con cada carry que surja)
        buffer = cifra; // variable auxiliar para un poco de claridad
        carries = 1;
        while(buffer > 9){
            buffer = can(salida[i-carries]+1);  // El dígito N (carries) lugares a la izquierda + 1
            salida[i-carries] = nac(buffer%10); // Se escribe en salida el valor de la unidad de eso
            carries++;                          // Repetir con dígitos más a la izquierda si el while itera
        }
    }
    salida[longmax] = '\0'; // Fin de cadena

    if (salida[0]=='0') *(salida)++; //Si empieza en 0 movemos el puntero 1 lugar para que no lo haga
    // Este caso sucede cuando la longitud máxima se sobreestimó

    return salida;
}
// end auxiliares //

// Suma dos números astronómicos!
// Avisa si alguno de los números tiene error
// Si uno de los números es secuencia nula, se cuenta como cero (si son nulos los dos retorna nulo)
// Si ocurre un error de algún otro tipo, retorna NULL
NumeroAstronomico* Sumar(NumeroAstronomico* a, NumeroAstronomico* b){
    if(a==NULL || b==NULL) return NULL;
    // Manejo de errores individuales
    if (EsSecuenciaInvalida(a) || EsSecuenciaInvalida(b)){
        fprintf(stderr, "Alguno de los numeros sumados es invalido.\n");
        NumeroAstronomico* invalido = malloc(sizeof(NumeroAstronomico));
        invalido->longitudError = CadenaInvalida;
        return invalido;
    }
    if (EsSecuenciaNula(a) && !EsError(b)) return CrearDesdeCadena(b->entero); // se toma como sumar 0
    if (EsSecuenciaNula(b) && !EsError(a)) return CrearDesdeCadena(a->entero); // lo mismo
    if (EsSecuenciaNula(a) && EsSecuenciaNula(b)) return CrearDesdeCadena(""); // si los dos son nulos retorna nulo
    // end manejo de errores individuales //

    if (!EsError(a) && !EsError(b)){ // todo en orden
        char* suma = sumaCadenas(a->entero, a->longitudError, b->entero, b->longitudError);
        // Si hubo Overflow (>100 caracteres), CrearDesdeCadena lo va a manejar
        return CrearDesdeCadena(suma); // para evitar repetir el malloc*/
    }
    else { // algún error no manejado
        fprintf(stderr, "Ocurrio un error en la suma.\n");
        return NULL;
    }
}

// (a==b)? 1 : 0
// Si tienen el mismo tipo de error se toma como igual
// Si solamente uno tiene error el comportamiento es indefinido
int SonIguales(NumeroAstronomico* a, NumeroAstronomico* b){
    if(EsError(a) && EsError(b)) return a->longitudError == b->longitudError;
    if(a->longitudError != b->longitudError) return 0;
    int largo = a->longitudError; // si llegan aca, son iguales en largo
    int i=0;

    for (i; ((i<largo) && (a->entero[i]==b->entero[i])); i++)
        ; // esto no es un error

    return i==largo;
}

// (a<b)? 1 : 0
// Si alguno tiene error retorna 0
int EsMenor(NumeroAstronomico* a, NumeroAstronomico* b){
    if(EsError(a) || EsError(b)) return 0;
    if (a->longitudError < b->longitudError) return 1;          //"a" es más corto
    else if (a->longitudError > b->longitudError) return 0;     //"a" es más largo
    else {                                                      // son iguales en longitud
        for(int i=0; i<a->longitudError; i++)
            if (a->entero[i] < b->entero[i]) return 1;          //"a" misma longitud que "b" pero menor
    }
    return 0; //Si llega hasta acá, son iguales (entonces no es menor)
}

//////////// Persistencia ////////////

// ###### Binario ######

size_t Read(FILE* f, NumeroAstronomico* a){
    // Primero leo longitud / error
    int longitud;
    size_t bytes_longitud = fread(&longitud, sizeof(int), 1, f);
    size_t bytes_cadena = 0;
    // Si no es error
    if (longitud > 0){
        char* cadena = malloc(longitud+1);
        bytes_cadena = fread(cadena, sizeof(char), 1+longitud, f);
        a->entero = cadena;
    }
    // Si es error, solo necesito el codigo de error
    a->longitudError = longitud;

    return bytes_cadena + bytes_longitud; //para conocer EOF
}

void Write(FILE* f, NumeroAstronomico* a){
    // escribe primero el largo y despues el entero cadena (para Read)
    fwrite(&(a->longitudError), sizeof(int), 1, f);
    if (a->longitudError > 0)
        fwrite(a->entero, sizeof(char), 1+(a->longitudError), f);
}

// ###### Texto ######

int Scan(FILE* f, NumeroAstronomico* a){
    if(a==NULL || f==NULL) return 0;
    // buffers
    char cadena[100];
    int longitud;
    // lee longitud
    int leido = fscanf(f, "%s %d\n", cadena, &longitud);
    if(longitud > 0) //si no tiene error
        a->entero = strdup(cadena);
    a->longitudError = longitud;

    return leido; // para conocer EOF
}

void Print(FILE* f, NumeroAstronomico* a){
    if(a==NULL || f==NULL) return;
    if(a->longitudError <= 0) //si tiene error
        fprintf(f, "a %d\n", a->longitudError); //para que pueda leer con formato en Scan
    else
        fprintf(f, "%s %d\n", a->entero, a->longitudError);
}