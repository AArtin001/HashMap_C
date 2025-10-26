#ifndef DICCIONARIO_H_INCLUDED
#define DICCIONARIO_H_INCLUDED
#include "lista.h"

#define HASHSIZE 1000

typedef size_t (*hash_func_t)(const char* clave);
typedef int (*cmp_func_t)(const void* a, const void* b); // strcmp

typedef struct{
    size_t capacidad;
    tLista *pl;
    size_t cantidad;
    hash_func_t hash_cmp;
    cmp_func_t cmp;
}t_diccionario;

typedef struct{ //uso memoria dinamica para guardar la info -> almaceno el puntero a donde lo guardo y el tam de cada uno
    char *clave;
    char *valor;
    unsigned tamValor;
}t_info;

///Funciones:
unsigned hash(char *s);

int crear_dic(t_diccionario* d, int capacidad, hash_func_t hash_func, cmp_func_t Cmp); //Recibe un puntero a diccionario y el tamaño
//
int poner_dic(t_diccionario* d, const char* clave, const void* valor, size_t tam_valor); //Recibo un puntero al diccionario, un puntero a la clave(que luego va a ser hasheada) y un puntero a la info
//
int obtener_dic(t_diccionario* pd, const char* clave, void* dato, size_t tamDato);

int sacar_dic(t_diccionario* pd, const char* clave);
//
//int recorrer_dic(tDiccionario*, accion, comparacion); //Recibo un *p a diccionario, la accion y una func comparacion(puede ser null y ejecutar para todos)
//
//int destruir_dic(tDiccionario*); //Recibo un *p a diccionario

#endif // DICCIONARIO_H_INCLUDED
