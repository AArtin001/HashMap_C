#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct sNodo{
    void *info;
    unsigned tam;
    struct sNodo *sig;
}tNodo;

typedef tNodo *tLista;

int crearLista(tLista*);
void ponerInicio(tLista *, void *, unsigned);
void ponerFinal(tLista *, void *, unsigned);



#endif // LISTA_H_INCLUDED
