#include "diccionario.h"


//Funcion Hash -> Se toma del libro "El Lenguaje de Programación C"
/* hash: forma un valor hash para la cadena s */
unsigned hash(char *s){
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s+ +)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
 }

int iniInfo(t_Info* info, char* clave, char* valor){
    //Aca hay que validar que haya memoria para los malloc

    info = malloc(sizeof(t_info)));

    info->tamclave = strlen(clave);
    info->clave = malloc(info->tamclave);

    info->tamvalor = strlen(valor);
    info->valor = malloc(info->tamvalor);

    return 0;
}

int crear_dic(*tDiccionario dic, int tam){
    //Recorro cada elemento e inicializo la lista para cada uno
    pos = 0;
    while((dic+(sizeof(t_diccionario) * pos)) < dic +((sizeof(t_diccionario) * tam))){
        crearLista((dic+(sizeof(t_diccionario) * pos))->pl);
        pos++;
    }

    return 0;
}

int poner_dic(tDiccionario *dic, char *clave, char *valor){
    //Obtengo posicion
    pos = hash(clave);

    //Guardo la info en una estructura
    t_info *info;

    iniInfo(info, clave, valor);
    strcpy(info->clave, clave);
    strcpy(info->valor, valor);


    //Inserto la estructura con los datos en la lista
    ///Falta que reemplaze el valor en caso de que la clave ya exista
    insertarOrdenado((dic+(sizeof(t_diccionario)*pos))->lp, info, sizeof(t_info)) //El calculo para saber la posicion en el vector puede ser una macro. "sizeof(t_info)" tambien

    return 0;
}

int obtener_dic(tDiccionario* dic, char* clave, char* valor){

    pos = hash(clave);

    t_info *info;
    iniInfo(info, clave, valor);

    //Funcion que retorna la info del nodo en el parametro que le paso
    vernodo((dic+(sizeof(t_diccionario)*pos))->lp, info, sizeof(t_info));

    //Copio el valor en el parametro recibido para el retorno
    strcpy(valor, info->valor);

    return 0;
}


int sacar_dic(tDiccionario* dic, char* clave){
    pos = hash(clave);

    //Funcion que busca en la lista la clave y elimina el nodo
    eliminarNodo((dic+(sizeof(t_diccionario)*pos))->lp, clave);
}

int recorrer_dic(tDiccionario*, accion, comparacion){
    //Recorro cada elemento
    pos = 0;
    while((dic+(sizeof(t_diccionario) * pos)) < dic +((sizeof(t_diccionario) * tam))){

        ///Aca va una funcion que recorra la lista y ejecute para cada elemento la accion que recibo como paramtro

        pos++;
    }

    return 0;
}

int destruir_dic(tDiccionario*){
    //Recorro cada elemento e inicializo la lista para cada uno
    pos = 0;
    while((dic+(sizeof(t_diccionario) * pos)) < dic +((sizeof(t_diccionario) * tam))){

        ///Elimino la lista -> implica eliminar datos y liberar memoria
        eliminarLista((dic+(sizeof(t_diccionario) * pos))->pl);

        pos++;
    }

    return 0;
}
