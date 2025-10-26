#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSO 0
#define VERDADERO 1

#define MIN(X,Y)( X < Y ? X : Y)

typedef struct sNodo{
    void *info;
    unsigned tam;
    struct sNodo *sig;
}tNodo;

typedef tNodo *tLista;

int poner_pri_lista(tLista* pl, const void* pd, size_t tam);
int lista_buscar(tLista* pl, void* info, size_t tamInfo, int(*Cmp)(const void*, const void*));
int sacar_elem_ord_lista(tLista* pl, void* pd, size_t tam, int (*cmp)(const void*, const void*));



#endif // LISTA_H_INCLUDED
