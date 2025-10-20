#include "diccionario.h"

//Funcion Hash -> Se toma del libro "El Lenguaje de Programación C"
/* hash: forma un valor hash para la cadena s */
unsigned hash(char *s){
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

int cmp_clave_info(const void* nodoInfo, const void* claveBuscada) {
    const t_info* info = (const t_info*)nodoInfo;
    const char*   k    = (const char*)claveBuscada;
    return strcmp(info->clave, k);
}


int crear_dic(t_diccionario* d, int capacidad, hash_func_t hash_func, cmp_func_t Cmp){
    d = malloc(sizeof(t_diccionario));

    d->pl = (tLista*)calloc(capacidad, sizeof(tLista));
    if(!d->pl){
        free(d);
        return 0;
    }
    //o podemos usar crearLista con un for que inicialice cada bucket.

//    d->buckets = (tLista*)malloc(capacidad * sizeof(tLista));
//    if (!d->buckets)
//        return 0;
//
//    for (size_t i = 0; i < capacidad; i++)
//        crear_lista(&d->pl[i]);

    d->capacidad = capacidad;
    d->cantidad = 0;
    d->hash_cmp = hash_func;
    d->cmp = Cmp;

    return 1;
}

int poner_dic(t_diccionario* d, const char* clave, const void* valor, size_t tam_valor)
{
    if (!d || !clave) return 0;

    size_t idx   = d->hash_cmp(clave) % d->capacidad;
    tLista* bucket = &d->pl[idx];

    if (lista_buscar(bucket, (void*)clave, cmp_clave_info)) {
        //encontro el nodo a insertar
        tNodo* actual = *bucket;
        while (actual) {
            t_info* info = (t_info*)actual->info;
            if (strcmp(info->clave, clave) == 0) { // aca remplazas y cambias el valor por uno nuevo
                void* nuevo = NULL;
                if (valor && tam_valor > 0) {
                    nuevo = malloc(tam_valor);
                    if (!nuevo) return 0;
                    memcpy(nuevo, valor, tam_valor);
                }
                free(info->valor);
                info->valor     = nuevo;
                info->tamValor = tam_valor;
                return 1;
            }
            actual = actual->sig;
        }
    }
    //Se arma t_info*
    t_info* dato = malloc(sizeof(t_info));
    if (!dato)
        return 0;

    dato->clave = malloc(strlen(clave) + 1);
    if (!dato->clave){
        free(dato);
        return 0;
    }
    strcpy(dato->clave, clave);

    if (valor && tam_valor > 0) {
        dato->valor = malloc(tam_valor);
        if (!dato->valor){
            free(dato->clave);
            free(dato);
            return 0;
        }
        memcpy(dato->valor, valor, tam_valor);
        dato->tamValor = tam_valor;
    } else {
        dato->valor = NULL;
        dato->tamValor = 0;
    }

    if (!poner_pri_lista(bucket, dato, sizeof(t_info))) {
        free(dato->valor);
        free(dato->clave);
        free(dato);
        return 0;
    }

    free(dato);
    d->cantidad++;
    return 1;
}
