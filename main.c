#include "EjerciciosLista.h"


int cmprInt(void *a, void *b){
    return *(int*)a - *(int*)b;
}

int main()
{
    printf("Hello world!\n");

    tLista lista;
    int num = 4;
   // int imp;

    crearLista(&lista);

    ponerInicio(&lista, &num, sizeof(int));

    num = 3;
    ponerInicio(&lista, &num, sizeof(int));

    num = 7;
    ponerFinal(&lista, &num, sizeof(int));

    //verLista(&lista, imprimir);

    printf("\n????");
    num = 6;

    insertarOrdenado(&lista, &num, sizeof(int), cmprInt);

    verLista(lista, imprimir);

    num = 2;
    ponerFinal(&lista, &num, sizeof(int));
    printf("\ninserte");
    ordenarLista(&lista, cmprInt);
    printf("\nordene");
    //imprimir(lista->info);

    verLista(lista, imprimir);

    return 0;
}
