# Convenciones UTNSO (stdutnso)
En un proyecto de extensión mediana o grande es importante ponerse de acuerdo en ciertos estándares de diseño o estándares en general para hacer todo de la misma forma y evitar confusiones.

Son en su mayoría decisiones *arbitrarias*, pero que ayudaría hacer de forma consistente.

Algunas que pensamos:

## Estilo de código
La idea es usar un formateador de C que aplique un formato estandarizado cada vez que se haga un *push* a GitHub. Ya lo probamos [acá](https://github.com/crisszkutnik/SO-workflow-test).  
Igualmente, es bueno ponerse de acuerdo en algunas cosas antes.

#### Convenciones:

Configurar el editor de texto para que indente usando **espacios** (tab size = 4). Esa es la configuración del auto-formateador, así que los archivos en GitHub siempre van a estar con ese formato.

Escribir bucles `while, if, for` preferiblemente de esta forma (formato "Attach"):

### SÍ:
```c
while (i>0) {
    //...
}

if (hola && !chau) {
    //...
}
```

### NO
```c
for(uint16_t i=0; i<10; i++)
{
    //...
}

void buenas(char* s)
{
    //...
}
```

Escribir `if-else` así:

```c
if (cond) {
    //...
}
else {
    //...
}
```

Escribir los asteriscos de punteros pegados al tipo de dato (e inicializarlos **siempre** con algún valor si son variables):

### NO
```c
char *str;
int **lista;

char *reverse_string(char *s) {
    //...
}
```
### SÍ
```c
char* str = string_create();
int** lista = NULL;

char* reverse_string(char* s) {
    //...
}
```

Usar `stdbool.h` para poder usar tipos de datos booleanos `true` y `false` (en las guias de SO lo usan así que ya fue).

```c
#include <stdbool.h>
bool flag = false;

bool esPar(int x) {
    return x%2 == 0;
}
```

Preferir codigo un poco mas largo por sobre algo mas corto o conciso pero mas dificil de leer. Ejemplo:

### NO
```c
for (uint16_t i=0; str[i]!='\0'; (printf("%c ",str[i]), isspace(str[i])? func(str[i++]) : other_func(str[i++])));
// quien fue???? SE BUSCA: con o sin vida
```
### SI
```c
for (uint16_t i=0; str[i]!='\0'; i++) {
    printf("%c ", str[i]);
    isspace(str[i])? func(str[i]) : other_func(str[i]);
}
// mucho mejor, thanks
```

### Convención de nombres
Esto es lo que se suele usar para distintos tipos de dato.
- **Variables y funciones:** _underscore_case_
    - `int habitantes_por_pais = 0;`
- **Structs:** _StructTipoDeDato_
    - `typedef struct { //... } StructPersona;`
- **Constantes:** _ALL_CAPS_UNDERSCORE_ (con `#define`)
    - `#define PI 3.145926535897`
    - `#define LIST_MAX_SIZE 10`

Y finalmente...
**COMENTAR bien el código, preferiblemente en español. Esto es importante. XD.**

## Flujo de trabajo en GitHub
Con el Workflow que preparamos, cada *push* o *pull request* ejecuta automáticamente un auto-formateador de código, **y** busca errores en todos los archivos del directorio `./test`. Si hay errores, nos notifica _Git-Gariol_ a Discord. :shipit:  

De todas formas, siempre es conveniente chequear que las cosas que agregamos no tengan errores (y evidentemente, que compilen bien **¡XD!**).

Algunas recomendaciones:

#### Siempre hacer `git pull` antes de empezar a trabajar
Suena obvio pero es muy muy importante. Todos nos olvidamos a veces de esto y arreglar los conflictos de merge no es divertido.

#### Trabajar en branches (ramas)
Si ya hay una parte del TP que está funcionando, y vamos a agregar un nuevo módulo o algo de tamaño mediano, es conveniente crear una nueva **branch** y trabajar ahí, probar que siga todo en orden, y posteriormente hacer un **merge**.

#### Ejecutar Valgrind en archivos nuevos que agreguemos
Solo cuesta un comando para verificar que todo siga bien. O arreglarlo si se rompió.
`valgrind -s ./programa`