#include "diccionario.h"


//Funcion Hash -> Se toma del libro "El Lenguaje de Programación C"
/* hash: forma un valor hash para la cadena s */
unsigned hash(char *s){
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
        hashval = (*s + 31 * hashval);
    return hashval % HASHSIZE;
}

 ///Recibe como parametros una t_info y un string
int cmp_clave_info(const void* nodoInfo, const void* claveBuscada) {
    const t_info* info = (const t_info*)nodoInfo;
    const char*   k    = (const char*)claveBuscada;
    return strcmp(info->clave, k);
}

///Recibe como parametros dos t_info
int cmp_clave_info_2(const void* nodoInfo, const void* claveBuscada) {
    const t_info* info = (const t_info*)nodoInfo;
    const t_info* info2 = (const t_info*)claveBuscada;
    return strcmp(info->clave, info2->clave);
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

void destruir_tinfo(void* pi)
{
    t_info* pinfo = (t_info*)pi;

    if(!pinfo){
        return;
    }

    free(pinfo->clave);
    free(pinfo->valor);
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

t_diccionario* crear_dic(int tam){
    //Recorro cada elemento e inicializo la lista para cada uno
    t_diccionario* dic = calloc(tam, sizeof(t_diccionario));
    if(!dic){
        return NULL;
    }
    t_diccionario* ini = dic;
    t_diccionario* fin = dic + tam;

    while(ini < fin){
        crear_lista(&ini->pl);
        ini++;
    }

    return dic;
}

int poner_dic(t_diccionario *dic, char *clave, void* valor, size_t tamValor){
    //Obtengo posicion
    int pos = hash(clave);
    t_diccionario* ins = dic + pos;

    //Guardo la info en una estructura
    t_info *info = iniInfo(clave, valor, tamValor);
    if(!info){
        return 0;
    }

    //Inserto la estructura con los datos en la lista
    poner_ord_lista(&ins->pl, info, sizeof(t_info), cmp_clave_info_2, ReemplazarInfo);

    free(info);
    return 1;
}

int obtener_dic(t_diccionario* dic, char* clave, void* valor, size_t tamValor){

    int pos = hash(clave);
    t_diccionario* ins = dic + pos;
    t_info info;

    //Funcion que retorna la info del nodo en el parametro que le paso
    if(!ver_nodo(&ins->pl, &info, sizeof(t_info), clave, cmp_clave_info)){
        return 0;
    }

    //Copio el valor en el parametro recibido para el retorno
    memcpy(valor, info.valor, MINIMO(tamValor, info.tamvalor));

    return 1;
}


int sacar_dic(t_diccionario* dic, char* clave, void* valor, size_t tamValor){
    int pos = hash(clave);
    t_diccionario* del = dic + pos;
    t_info info;

    //Funcion que busca en la lista la clave y elimina el nodo
    sacar_elem_ord_lista(&del->pl, clave, &info, sizeof(t_info), cmp_clave_info);
    memcpy(valor, info.valor, MINIMO(tamValor, info.tamvalor));

    return 1;
}

int recorrer_dic(t_diccionario* dic, int tam, void (*accion)(void*)){
    //Recorro cada elemento
    t_diccionario* ini = dic;
    t_diccionario* fin = dic + tam;

    while(ini < fin){
        mapeo(&ini->pl, accion);
        ini++;
    }

    return 1;
}


int destruir_dic(t_diccionario* dic, int tam){
    t_diccionario* ini = dic;
    t_diccionario* fin = dic + tam;

    while(ini < fin){
        destruir_lista(&ini->pl, destruir_tinfo);
        ini++;
    }

    free(dic);
    return 1;
}
