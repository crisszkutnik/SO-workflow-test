//////////// TAD ////////////
#ifndef TAD
#define TAD

typedef struct {
    char* entero; //tiene el numero en si
    int longitudError;  //tiene el largo de la cadena, o el codigo de error
} NumeroAstronomico;

typedef enum {          //codigo
    //Ninguno,          //sin codigo, longitudError > 0
    CadenaInvalida=-3,  // -3
    Overflow,           // -2
    PunteroNulo,        // -1
    CadenaNula          //  0 (coincide con el largo en este caso)
} TipoDeError;

#endif

//////////// Creación ////////////
#ifndef ASTRONUM_CREACION
#define ASTRONUM_CREACION

NumeroAstronomico* CrearDesdeCadena(char* cadena);
NumeroAstronomico* CrearDesdeCifraSeguidaDeCeros(int num, int ceros);
NumeroAstronomico* CrearAleatorio();
void* FreeNumeroAstronomico(NumeroAstronomico* a);

#endif

//////////// Errores ////////////
#ifndef ASTRONUM_ERRORES
#define ASTRONUM_ERRORES

int EsSecuenciaNula(NumeroAstronomico* a);
int EsSecuenciaInvalida(NumeroAstronomico* a);
int EsOverflow(NumeroAstronomico* a);
TipoDeError GetTipoDeError(NumeroAstronomico* a);
int EsError(NumeroAstronomico* a);
int EsPunteroNulo(NumeroAstronomico* a);

#endif

//////////// Salida ////////////
#ifndef ASTRONUM_SALIDA
#define ASTRONUM_SALIDA

void Mostrar(NumeroAstronomico* a, int grupos);

#endif

//////////// Aritmética ////////////
#ifndef ASTRONUM_ARITMETICA
#define ASTROUNM_ARITMETICA

NumeroAstronomico* Sumar(NumeroAstronomico* a, NumeroAstronomico* b);
int SonIguales(NumeroAstronomico* a, NumeroAstronomico* b);
int EsMenor(NumeroAstronomico* a, NumeroAstronomico* b);

#endif

//////////// Persistencia ////////////
#ifndef ASTRONUM_PERSISTENCIA
#define ASTRONUM_PERSISTENCIA

size_t Read(FILE* f, NumeroAstronomico* a);
void Write(FILE* f, NumeroAstronomico* a);
int Scan(FILE* f, NumeroAstronomico* a);
void Print(FILE* f, NumeroAstronomico* a);

#endif