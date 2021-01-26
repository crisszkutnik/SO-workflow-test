#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "astronum.h"

int main(){ clock_t begin = clock(); //tomemos el tiempo que tarda

    NumeroAstronomico* p1 = CrearDesdeCadena("12345678900000000000000000");     // 17 ceros
        NumeroAstronomico* p1_con_ceros = CrearDesdeCadena("000012345678900000000000000000");
        NumeroAstronomico* p2 = CrearDesdeCadena("123456789000000000000000000");    // 18 ceros
            NumeroAstronomico* p3 = CrearDesdeCadena("1234567890000000000000000000");   // 19 ceros
    NumeroAstronomico* p3_equivalente = CrearDesdeCifraSeguidaDeCeros(123456789, 19);
     NumeroAstronomico* cosaNula = CrearDesdeCadena("");
       NumeroAstronomico* invalido = CrearDesdeCadena("buenas123");
       NumeroAstronomico* otro_invalido = CrearDesdeCadena("aguantePython");
         NumeroAstronomico* chiquito = CrearDesdeCadena("1427");
      NumeroAstronomico* pequenio = CrearDesdeCadena("1427");
     NumeroAstronomico* otropeque = CrearDesdeCadena("4969");
        NumeroAstronomico* largo1 = CrearDesdeCadena("11111111111111111111"); //20 "1"s
        NumeroAstronomico* largo2 = CrearDesdeCadena("11111111111111111112"); //20 "1"s + 1
     NumeroAstronomico* ceros1 = CrearDesdeCifraSeguidaDeCeros(1427, 90);
       NumeroAstronomico* ceros2 = CrearDesdeCifraSeguidaDeCeros(1, 70);
        NumeroAstronomico* aleatorio = CrearAleatorio();
              NumeroAstronomico* potenciar = CrearDesdeCadena("2");
            NumeroAstronomico* overflow = CrearDesdeCadena("1111111111111111111111111111111"
    "11111111111111111111111111111111111111111111111111111"
    "11111111111111111111111111111111111111111111111111111"
    "111111111111111111111111111111111111111111111111111111111111111116"); // 203>100 digitos
    NumeroAstronomico* pre_overflow = CrearDesdeCifraSeguidaDeCeros(9, 99); // si lo sumo a sí mismo desborda
    NumeroAstronomico* ceros_no_anda = CrearDesdeCifraSeguidaDeCeros(0, 14);

    //////// Algunos ejemplos ////////

    // PERSISTENCIA //

    // Escritura

    FILE* file_b = fopen("file_b.txt", "wb");
        FILE* file = fopen("file.txt", "w");

        Write(file_b, largo1);Write(file_b, chiquito);Write(file_b, overflow);Write(file_b, invalido);
        Write(file_b, cosaNula);
        Write(file_b, p1);

        Print(file, largo1);
        Print(file, chiquito);
        Print(file, overflow);
        Print(file, invalido);Print(file, cosaNula);Print(file, p1);

    fclose(file_b) ;fclose(file);

    // Lectura

    NumeroAstronomico* temp = malloc(sizeof(NumeroAstronomico));
    NumeroAstronomico* total = CrearDesdeCadena("");
    NumeroAstronomico* total_b = CrearDesdeCadena("");

    printf("------------Archivo NO binario------------\n\n");
    FILE* file_1 = fopen("file.txt", "r");
    fseek(file_1, 0, SEEK_SET);
    while(Scan(file_1, temp) != -1){
    printf("Leido:\n");
    Mostrar(temp, 3);
    total = Sumar(total, temp);}
        printf("Suma total:\n");
        Mostrar(total, 3);
        fclose(file_1);

    printf("\n------------Archivo binario------------\n\n");
    FILE* file_b_1 = fopen("file_b.txt", "rb");
    fseek(file_b_1, 0, SEEK_SET);
    while(Read(file_b_1, temp)){printf("Leido:\n");Mostrar(temp, 3);total_b = Sumar(total_b, temp);}
    printf("Suma total:\n");
    Mostrar(total_b, 3);
    fclose(file_b_1);

    if(temp!=NULL) FreeNumeroAstronomico(temp);
    if(total!=NULL) FreeNumeroAstronomico(total);
    if(total_b!=NULL) FreeNumeroAstronomico(total_b);
    
    // MOSTRAR //

    printf("p1, 3 grupos:\n"); Mostrar(p1, 3);
    printf("p1_con_ceros, 3 grupos:\n"); Mostrar(p1_con_ceros, 3);
    printf("p1, 5 grupos:\n"); Mostrar(p1, 5);
    printf("p2, 2 grupos:\n"); Mostrar(p2, 2);
    printf("p3, 4 grupos:\n"); Mostrar(p3, 4);
    printf("chiquito, con 'exceso' de grupos "
     "(se le piden 5 pero tiene solo 2 grupos para mostrar):\n"); Mostrar(chiquito, 5);
    Mostrar(ceros1, 2);
    Mostrar(ceros2, 3);
    Mostrar(aleatorio, 4);
    Mostrar(invalido, 4);    // Muestra error
    Mostrar(overflow, 5);    // Muestra error
    Mostrar(ceros_no_anda, 5);  // comportamiento indefinido

    // ERRORES //

    printf("%d\n", EsSecuenciaNula(cosaNula));                   // 1
    printf("%d\n", EsSecuenciaInvalida(invalido));               // 1
    printf("%d\n", EsSecuenciaInvalida(p3));                     // 0
    printf("%d\n", p1->longitudError);                           // 26
    printf("%d\n", EsError(chiquito) || EsError(cosaNula));      // 1

    // ARITMETICA //

    // Iguales
    printf("%d\n", SonIguales(chiquito, otropeque));             // chiquito!=otropeque => 0
    printf("%d\n", SonIguales(chiquito, pequenio));              // chiquito==pequenio => 1
    printf("%d\n", SonIguales(p3, p3_equivalente));              // p3==p3_equivalente => 1
    printf("%d\n", SonIguales(ceros1, ceros2));                  // ceros1 > ceros2  => 0
    printf("%d\n", SonIguales(chiquito, Sumar(cosaNula, chiquito))); // a+nulo = a => 1
    printf("%d\n", SonIguales(invalido, otro_invalido));         // mismo tipo de error => 1
    printf("%d\n", SonIguales(p1, p1_con_ceros));                // son iguales => 1

    // Menor
    printf("%d\n", EsMenor(p1, p2));                             // p1<p2            => 1
    printf("%d\n", EsMenor(p2, p1));                             // p2>p1            => 0
    printf("%d\n", EsMenor(p1, p1));                             // p1==p1           => 0
    printf("%d\n", EsMenor(largo1, largo2));                     // largo1<largo2    => 1
    printf("%d\n", EsMenor(largo1, largo1));                     // largo1==largo1   => 0
    printf("%d\n", EsMenor(largo2, largo1));                     // largo2>largo1    => 0
    printf("%d\n", EsMenor(ceros1, ceros2));                     // ceros1 > ceros2  => 0
    printf("%d\n", EsMenor(ceros2, ceros1));                     // ceros2 < ceros1  => 1
    printf("%d\n", EsMenor(aleatorio, ceros2));                  // depende del azar

    // Suma
    Mostrar(Sumar(p3, largo2), 5);                               // anda
    Mostrar(Sumar(otropeque, ceros1), 4);                        // anda
    for(int i=0; i<199; i++) potenciar = Sumar(potenciar, potenciar); // calcula 2^200
    Mostrar(potenciar, 5);                                       // muestra 2^200
    Mostrar(pre_overflow, 4);                                    // número todo correcto
    Mostrar(Sumar(pre_overflow, pre_overflow), 4);               // pero *2 da overflow (Muestra error)
    Mostrar(Sumar(invalido, p1), 5);                             // error de Sumar() y Mostrar(), se muestran
    printf("%d\n", EsSecuenciaNula(Sumar(cosaNula, cosaNula)));  // nulo+nulo = nulo => 1
    Mostrar(Sumar(cosaNula, p1), 4);                             // nulo+p1 = p1

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecucion: %f\n", time_spent);

    return 0;
}