#include "diccionario.h"


//Funcion Hash -> Se toma del libro "El Lenguaje de Programación C"
/* hash: forma un valor hash para la cadena s */
unsigned hash(char *s){
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
        hashval = (*s + 31 * hashval);
    return hashval % HASHSIZE;
 }

 int cmp_clave_info(const void* nodoInfo, const void* claveBuscada) {
    const t_info* info = (const t_info*)nodoInfo;
    const char*   k    = (const char*)claveBuscada;
    return strcmp(info->clave, k);
}


/**Funciones Accion**/

int accion(void *){
    return 1;
}

int ReemplazarInfo(const tLista* pl, void* nInfo){
    t_info *info = (t_info*)nInfo; //Casteo el parametro
    memcpy((*pl)->info, info, (*pl)->tam);

    return 1;
}
/**FIN Funcion Accion**/


int iniInfo(t_info* info, char* clave, char* valor){
    //Aca hay que validar que haya memoria para los malloc

    info = malloc(sizeof(t_info));

    info->tamclave = strlen(clave);
    info->clave = malloc(info->tamclave);

    info->tamvalor = strlen(valor);
    info->valor = malloc(info->tamvalor);

    return 0;
}

int crear_dic(t_diccionario* dic, int tam){
    //Recorro cada elemento e inicializo la lista para cada uno
    int pos = 0;
    while((dic+(sizeof(t_diccionario) * pos)) < dic +((sizeof(t_diccionario) * tam))){
        crear_lista((dic+(sizeof(t_diccionario) * pos))->pl);
        pos++;
    }

    return 0;
}

int poner_dic(t_diccionario *dic, char *clave, char *valor){
    //Obtengo posicion
    int pos = hash(clave);

    //Guardo la info en una estructura
    t_info *info = NULL; //Lo inicializo como null para saltearme el warning

    iniInfo(info, clave, valor);
    strcpy(info->clave, clave);
    strcpy(info->valor, valor);


    //Inserto la estructura con los datos en la lista
    ///Falta que reemplaze el valor en caso de que la clave ya exista
    poner_ord_lista((dic+(sizeof(t_diccionario)*pos))->pl, info, sizeof(t_info), cmp_clave_info, ReemplazarInfo); //El calculo para saber la posicion en el vector puede ser una macro. "sizeof(t_info)" tambien

    return 0;
}

int obtener_dic(t_diccionario* dic, char* clave, char* valor){

    int pos = hash(clave);

    t_info *info = NULL; //Lo inicializo como null para saltearme el warning
    iniInfo(info, clave, valor);

    //Funcion que retorna la info del nodo en el parametro que le paso
    ver_nodo((dic+(sizeof(t_diccionario)*pos))->pl, info, sizeof(t_info), clave, cmp_clave_info);

    //Copio el valor en el parametro recibido para el retorno
    strcpy(valor, info->valor);

    return 0;
}


int sacar_dic(t_diccionario* dic, char* clave){
    int pos = hash(clave);

    //Funcion que busca en la lista la clave y elimina el nodo
    sacar_elem_ord_lista((dic+(sizeof(t_diccionario)*pos))->pl, clave, 1, cmp_clave_info); //En lugar de 1 debo pasar el tam de ¿clave?

    return 0;
}

int recorrer_dic(t_diccionario* dic, int tam, int (*accion)(void*), int (*cmp)(const void*, const void*)){
    //Recorro cada elemento
    int pos = 0;
    while((dic+(sizeof(t_diccionario) * pos)) < dic +((sizeof(t_diccionario) * tam))){

        ///Aca va una funcion que recorra la lista y ejecute para cada elemento la accion que recibo como paramtro

        pos++;
    }

    return 0;
}

int destruir_dic(t_diccionario* dic, int tam){
    //Recorro cada elemento e inicializo la lista para cada uno
    int pos = 0;
    while((dic+(sizeof(t_diccionario) * pos)) < dic +((sizeof(t_diccionario) * tam))){

        ///Elimino la lista -> implica eliminar datos y liberar memoria
        //sacar_elem_ord_lista((dic+(sizeof(t_diccionario) * pos))->pl, , , cmp_clave_info);

        pos++;
    }

    return 0;
}
