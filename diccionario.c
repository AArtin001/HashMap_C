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

int ReemplazarInfo(const tLista* pl, void* nInfo) {
    if (!pl || !*pl || !nInfo)
        return 0;

    t_info* dst = (t_info*)(*pl)->info;   // info existente en la lista
    t_info* src = (t_info*)nInfo;         // nueva info con valor actualizado

    // liberar valor anterior
    free(dst->valor);

    // reservar y copiar el nuevo valor
    dst->valor = malloc(src->tamvalor);
    if (!dst->valor)
        return 0;

    memcpy(dst->valor, src->valor, src->tamvalor);
    dst->tamvalor = src->tamvalor;

    return 1;
}

void mapeo(tLista* pl, void (*funcion)(void*))
{
    while(*pl)
    {
        funcion((*pl)->info);
        pl=&(*pl)->sig;
    }
}

void destruir_tinfo(t_info* pinfo)
{
    if(!pinfo)
        return;
    free(pinfo->clave);
    free(pinfo->valor);
    //free(pinfo);
}

/**FIN Funcion Accion**/

t_info* iniInfo(char* clave, void* valor, size_t tamValor){

    t_info* info = malloc(sizeof(t_info));
    if(!info){
        return NULL;
    }

    info->tamclave = (size_t)(strlen(clave) + 1);
    info->clave = malloc(info->tamclave);
    if(!info->clave){
        free(info);
        return NULL;
    }

    memcpy(info->clave, clave, info->tamclave);

    info->tamvalor = tamValor;
    info->valor = malloc(tamValor);
    if(!info->valor){
        free(info->clave);
        free(info);
        return NULL;
    }

    memcpy(info->valor, valor, tamValor);

    return info;
}

int crear_dic(t_diccionario* dic, int tam){
    //Recorro cada elemento e inicializo la lista para cada uno
    int pos = 0;
    while((dic + pos) < (dic + tam)){
        crear_lista(&dic[pos].pl);
        pos++;
    }

    return 1;
}

int poner_dic(t_diccionario *dic, char *clave, void* valor, size_t tamValor){
    //Obtengo posicion
    int pos = hash(clave);

    //Guardo la info en una estructura
    t_info *info = iniInfo(clave, valor, tamValor); //Lo inicializo como null para saltearme el warning


//    strcpy(info->clave, clave);
//    strcpy(info->valor, valor);


    //Inserto la estructura con los datos en la lista
    ///Falta que reemplaze el valor en caso de que la clave ya exista
    poner_ord_lista(&dic[pos].pl, info, sizeof(t_info), cmp_clave_info, ReemplazarInfo); //El calculo para saber la posicion en el vector puede ser una macro. "sizeof(t_info)" tambien

    return 0;
}

int obtener_dic(t_diccionario* dic, char* clave, void* valor, size_t tamValor){

    int pos = hash(clave);

    t_info *info = iniInfo(clave, valor, tamValor);; //Lo inicializo como null para saltearme el warning


    //Funcion que retorna la info del nodo en el parametro que le paso
    ver_nodo(&dic[pos].pl, info, sizeof(t_info), clave, cmp_clave_info);

    //Copio el valor en el parametro recibido para el retorno
    memcpy(valor, info->valor, tamValor);

    free(info);

    return 1;
}


int sacar_dic(t_diccionario* dic, char* clave){
    int pos = hash(clave);

    //Funcion que busca en la lista la clave y elimina el nodo
    sacar_elem_ord_lista(&dic[pos].pl, clave, 1, cmp_clave_info); //En lugar de 1 debo pasar el tam de ¿clave?

    return 0;
}

int recorrer_dic(t_diccionario* dic, int tam, void (*accion)(void*)){
    //Recorro cada elemento

    for(int i = 0; i < tam; i++){
        mapeo(&dic[i].pl, accion);
    }

    return 0;
}

void destruir_lista(tLista* pl)
{
    tNodo* elim;
    //Si no hay lista retorno
    if(!*pl)
        return;
    //Recorro lista, destruyendo info y el nodo
    while(*pl)
    {
        destruir_tinfo((*pl)->info);
        free((*pl)->info);

        elim=*pl;
        *pl=elim->sig;
        free(elim);
    }
}

int destruir_dic(t_diccionario* dic, int tam){
    //Recorro cada elemento e inicializo la lista para cada uno
    int pos = 0;
    while((dic+(sizeof(t_diccionario) * pos)) < dic +((sizeof(t_diccionario) * tam))){

        ///Elimino la lista -> implica eliminar datos y liberar memoria
        destruir_lista((dic+(sizeof(t_diccionario) * pos))->pl);

        pos++;
    }

    return 0;
}
