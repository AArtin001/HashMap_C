#ifndef DICCIONARIO_H_INCLUDED
#define DICCIONARIO_H_INCLUDED
#include "lista.h"

#define HASHSIZE 1000

typedef size_t (*hash_func_t)(const char* clave);
typedef int    (*cmp_func_t)(const char* a, const char* b); // strcmp

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
//int poner_dic(tDiccionario*, char*, char*); //Recibo un puntero al diccionario, un puntero a la clave(que luego va a ser hasheada) y un puntero a la info
//
//int obtener_dic(tDiccionario*, char*, char*); //Recibo un *p a diccionario, la clave(que tengo que hashear) y devuelvo el valor (Devolver retornando o en el parametro???) --> voy a devolver en el parametro y usar el return para manejo de errores
//
//int sacar_dic(tDiccionario*, char*); //Recibo un *p a diccionario y la clave
//
//int recorrer_dic(tDiccionario*, accion, comparacion); //Recibo un *p a diccionario, la accion y una func comparacion(puede ser null y ejecutar para todos)
//
//int destruir_dic(tDiccionario*); //Recibo un *p a diccionario

#endif // DICCIONARIO_H_INCLUDED
