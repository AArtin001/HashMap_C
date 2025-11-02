#ifndef DICCIONARIO_H_INCLUDED
#define DICCIONARIO_H_INCLUDED
#include "lista.h"
#define HASHSIZE 5

typedef struct{
    tLista pl;
}t_diccionario;

typedef struct{
    char *clave;
    unsigned tamclave;
    void *valor;
    unsigned tamvalor;
}t_info;




unsigned hash(char *s);

t_diccionario* crear_dic(int);

int poner_dic(t_diccionario*, char*, void*, size_t);

int obtener_dic(t_diccionario*, char*, void*, size_t);

int sacar_dic(t_diccionario*, char*, void*, size_t);

int recorrer_dic(t_diccionario*, int, void (*accion)(void*));

int destruir_dic(t_diccionario*, int);


#endif // DICCIONARIO_H_INCLUDED
