#include <stdio.h>
#include "diccionario.h"
#include "Utils.h"

int main(){
    menu();
}










///Casos de prueba para las funciones de diccionario
/*
static void print_info(void* p){
    t_info i=*(t_info*)p;
    printf("\n%s => %d", i.clave, *(int*)i.valor);
}

int main(){
    t_diccionario dic[HASHSIZE];
    crear_dic(dic, HASHSIZE);

    int valor1 = 1, valor2 = 5, valor3, valor4 = 7;

    poner_dic(dic, "hola", &valor1, sizeof(int));
    poner_dic(dic, "mundo", &valor2, sizeof(int));


    if(obtener_dic(dic,"hola", &valor3, sizeof(int))){
        printf("hola = %d\n", valor3);
    }

    printf("\nReemplazo el valor de 'hola' por un 7");
    poner_dic(dic,"hola",&valor4, sizeof(int));

    printf("\nRecorro imprimiendo valores:");
    recorrer_dic(dic, HASHSIZE, print_info);

    printf("\nSaco 'Mundo':");
    sacar_dic(dic,"mundo");

    printf("\nRecorro imprimiendo valores:");
    recorrer_dic(dic, HASHSIZE, print_info);

    printf("\nDestruyo diccionario:");
    destruir_dic(dic,HASHSIZE);

    printf("\nDestruyo??");
    printf("\nRecorro imprimiendo valores:");
    recorrer_dic(dic, HASHSIZE, print_info);
    return 0;
}
*/
