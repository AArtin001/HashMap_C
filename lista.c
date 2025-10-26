#include "lista.h"


int lista_buscar(tLista* pl, void* info, size_t tamInfo, int(*Cmp)(const void*, const void*)){
    while(*pl && Cmp((*pl)->info, info) != 0){
        pl = &(*pl)->sig;
    }
    if(!*pl){
        return 0;
    }

    memcpy(info, (*pl)->info, MIN((*pl)->tam, tamInfo));
    return 1;
}

int poner_pri_lista(tLista* pl, const void* pd, size_t tam)
{
    tNodo* nue=(tNodo*)malloc(sizeof(tNodo)+tam);
    if(!nue)
        return FALSO;   // sin memoria
    nue->info=nue+1;

    memcpy(nue->info,pd,tam);
    nue->tam=tam;

    nue->sig=*pl;
    *pl=nue;

    return VERDADERO;
}

int sacar_elem_ord_lista(tLista* pl, void* pd, size_t tam, int (*cmp)(const void*, const void*))
{
    tNodo* elim;
    int comp;
    if(!*pl)
        return FALSO;   // lista vacia
    while(*pl && (comp=cmp((*pl)->info,pd)>0))
        pl=&(*pl)->sig;
    if(!*pl || comp)
        return FALSO;   // lista vacia o duplicado

    elim=*pl;
    memcpy(pd,elim->info,MINIMO(tam,elim->tam));

    *pl=elim->sig;
    free(elim->info);
    free(elim);
    return VERDADERO;
}


