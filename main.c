#include <stdio.h>
#include "diccionario.h"

static void print_info(void* p){
    t_info* i=(t_info*)p;
    printf("%s => %d\n", i->clave, i->valor);
}

int main(){
    t_diccionario dic[HASHSIZE];
    crear_dic(dic, HASHSIZE);

    int valor1 = 1, valor2 = 5, valor3;

    poner_dic(dic, "hola", &valor1, sizeof(int));
    printf("%d\n", hash("hola"));
    poner_dic(dic, "mundo", &valor2, sizeof(int));
    printf("%d\n", hash("mundo"));


    if(obtener_dic(dic,"hola", &valor3, sizeof(int))){
        printf("hola = %d\n", valor3);
    }

//    // reemplazo
//    poner_dic(dic,"hola","7", sizeof(int));
//    if(obtener_dic(dic,"hola",out)) printf("hola=%s\n", out);


    recorrer_dic(dic, HASHSIZE, print_info);
//
//    sacar_dic(dic,"mundo");
//
//    destruir_dic(dic,HASHSIZE);
    return 0;
}
