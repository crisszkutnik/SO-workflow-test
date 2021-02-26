# SO-workflow-test

### Cómo probarlo

Los tests `.c` en el directorio `./test` se compilarán por arte de magia usando los `.h` en `./headers` y otros archivos `.c` en `./lib`, además linkeando algunas librerías como las *Commons* de UTNSO, y *lpthread*.

Para probarlo, solo queda agregar un archivo `.c` a `./test` (puede hacer include de otros archivos o ser solo uno individual), y luego hacer el *push*.  
Automáticamente se va a ejecutar un formateador de código, y un comando de Valgrind que busca _memory leaks_. De haberlos, Git-Gariol nos avisa por Discord.

Probá, por ejemplo, con algo así:

```c
// guardar como cualquier_cosa.c en ./test

int main() {
      char* cadena = malloc(5);
      // falta el free(cadena), por lo tanto hay un leak
      return 0;
}
```
