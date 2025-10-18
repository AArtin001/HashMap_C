#include "diccionario.h"


//Funcion Hash -> Se toma del libro "El Lenguaje de Programación C"
/* hash: forma un valor hash para la cadena s */
unsigned hash(char *s){
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s+ +)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
 }

int crear_dic(*tDiccionario dic, int tam){
    //Recorro cada elemento e inicializo la lista para cada uno
    while(dic < dic * tam){
        crearLista(dic->pl);
    }
}

int poner_dic(tDiccionario *dic, char *clave, char *valor){

    pos = hash(clave);

    t_info info;

    //Aca validar que haya memoria para los malloc
    info->tamclave = strlen(clave);
    info->clave = malloc(info->tamclave);
    strcpy(info->clave, clave);

    info->tamvalor = strlen(valor);
    info->valor = malloc(info->tamvalor)
    strcpy(info->valor, valor)

    //ponerInicio((dic+(dic*pos))->lp, info, sizeof(info))
    insertarOrdenado((dic+(dic*pos))->lp, info, sizeof(info))
}

int obtener_dic(tDiccionario* dic, char* clave, char* valor){
    pos = hash(clave);

}

int sacar_dic(tDiccionario* dic, char* valor){

}

int recorrer_dic(tDiccionario*, accion, comparacion){

}

int destruir_dic(tDiccionario*){

}
