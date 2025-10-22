#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSO 0
#define VERDADERO 1
#define MINIMO(x,y) ((x)<=(y)?(x):(y))

typedef struct sNodo
{
    void* info;
    size_t tam;
    struct sNodo* sig;
}tNodo;

typedef tNodo* tLista;

int cmp(const void* a, const void* b);
void crear_lista(tLista* pl);
int lista_vacia(tLista* pl);
int lista_llena(tLista* pl, size_t tam);
int poner_pri_lista(tLista* pl, const void* pd, size_t tam);
int poner_ult_lista(tLista* pl, const void* pd, size_t tam);
int sacar_pri_lista(tLista* pl, void* pd, size_t tam);
int sacar_ult_lista(tLista* pl, void* pd, size_t tam);
int poner_ord_lista(tLista* pl, const void* pd, size_t tam, int (*cmp)(const void*, const void*));
int sacar_elem_ord_lista(tLista* pl, void* pd, size_t tam, int (*cmp)(const void*, const void*));
int ver_nodo(tLista* pl, void* pd, size_t tam, char* clave, int (*cmp)(const void*, const void*));

#endif // LISTA_H_INCLUDED
