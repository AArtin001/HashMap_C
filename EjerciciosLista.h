#ifndef EJERCICIOSLISTA_H_INCLUDED
#define EJERCICIOSLISTA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "string.h"

typedef struct sNodo{
    void *info;
    unsigned tam;
    struct sNodo *sig;
}tNodo;

typedef tNodo *tLista;


int crearLista(tLista*);
void ponerInicio(tLista *, void *, unsigned);
void ponerFinal(tLista *, void *, unsigned);

//void ponerPosicion();

void verNodo(tLista *p, void *d, unsigned tam);
void insertarOrdenado(tLista *, void *, unsigned, int (*cmpr)(void *a, void *b));
void imprimir(void *);
void verLista(tLista, void (*f)(void *d));
void ordenarLista(tLista *, int (*cmpr)(void *a, void *b));


/*
void ordenarLista();
void sacarPosicion();
void sacarInicio();
void sacarFinal();
void eliminarLista();
*/




#endif // EJERCICIOSLISTA_H_INCLUDED
