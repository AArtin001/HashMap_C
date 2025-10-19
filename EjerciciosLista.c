#include "EjerciciosLista.h"


int crearLista(tLista *p){
    *p = NULL;
    return 1;
}

void ponerInicio(tLista *p, void *d, unsigned tam){
    //Creo un nuevo nodo
    tNodo *nuevo;

    if(!(nuevo = (tNodo*)malloc(sizeof(tNodo)))){
        return;
    }
    if(!(nuevo->info = malloc(tam))){
        free(nuevo);
        return;
    }

    //Desplazo el puntero y asigno la info en el espacio restante
    memcpy(nuevo->info, d, tam);
    nuevo->tam = tam;
    nuevo->sig = *p;

    *p = nuevo;
}

void ponerFinal(tLista *p, void *d, unsigned tam){
    //void *aux = p;

    //Creo un nuevo nodo
    tNodo *nuevo;

    if(!(nuevo = (tNodo*)malloc(sizeof(tNodo)))){
        return;
    }
    if(!(nuevo->info = malloc(tam))){
        free(nuevo);
        return;
    }

    //Me desplazo hasta el ultimo nodo
    while(*p){
        p = &(*p)->sig;
    }

    *p = nuevo;

    //Desplazo el puntero y asigno la info en el espacio restante
    memcpy(nuevo->info, d, tam);
    nuevo->tam = tam;
    nuevo->sig = NULL; /**Esto tambien esta mal**/

    //p = aux;

}


void verNodo(tLista *p, void *d, unsigned tam){
    if(*p) memcpy(d, (*p)->info, tam);
}

void insertarOrdenado(tLista *p, void *d, unsigned tam, int (*cmpr)(void *, void *)){

    void *superaux = *p; /**Esto no puede estar**/
    tNodo *nuevo;
    if(!(nuevo = (tNodo*)malloc(sizeof(tNodo)))) return;
    if(!(nuevo->info = malloc(tam))){
        free(nuevo);
        return;
    }

    if(!*p){ //Si no hay elementos en la lista
        nuevo->tam = tam;
        memcpy(nuevo->info, d, tam);
        *p = nuevo;
        return;
    }

    tNodo *sig = (*p)->sig;  //Para sacar el superaux, esto deberia ser un tLista, ser &(*p)->sig, y en el while usar p de la misma forma

    while(sig && (cmpr(sig->info, d) < 0)){ //mientras el sig sea mas chico -> recorro hasta encontrar un sig mas grande //// o hasta que sig sea null
        *p = sig;
        sig = sig->sig;
    }

    //Aca ya estoy parado en el nodo con info mas chico y el siguiente tiene info mas grande
    nuevo->tam = tam;
    memcpy(nuevo->info, d, tam);
    nuevo->sig = (*p)->sig;
    (*p)->sig = nuevo;

    *p = superaux;/**Esto no puede estar**/
    return;

}

void insertarOrdenadoMejorado(tLista *p, void *d, unsigned tam, int (*cmpr)(void *, void *)){

    //Creo el nodo nuevo y tomo memoria
    tNodo *nuevo;
    if(!(nuevo = (tNodo*)malloc(sizeof(tNodo)))) return;
    if(!(nuevo->info = malloc(tam))){
        free(nuevo);
        return;
    }

    //Busco la posicion
    while(*p && cmpr((*p)->info, d) < 0){
        p = &(*p)->sig; //De esta forma puedo acceder al siguiente sin cambiar el valor de p por lo que no guardo un auxiliar
    }

    memcpy(nuevo->info, d, tam);
    nuevo->tam = tam;
    nuevo->sig = *p; //p es el puntero al puntero del nodo con un valor mayor
    *p = nuevo; // Asi el sig del anterior nodo apunta a este, sin tener que tocar al nodo anterior ya que no puedo volver
    return;
}

void imprimir(void *p){
    printf("\nFuncion num: %d", *(int*)p);
    return;
}

void verLista(tLista p, void (*f)(void *)){

    while(p){
        f(p->info);
        p = p->sig;
    }

    return;
}


void insertarPosicion(tLista *p, void *d, unsigned tam, int pos){
    int posAct = 0;

    tNodo *nuevo = (tNodo*) malloc(sizeof(tNodo));
    if(!nuevo) return;
    nuevo->info = malloc(tam);
    if(!nuevo->info) return;

    while (posAct < pos && (*p)->sig){ //mientras sea mas chico que la posicion por parametro y que el sig no sea null
        *p = (*p)->sig;
        posAct ++;
    }

    nuevo->sig = (*p)->sig;
    (*p)->sig = nuevo;
    nuevo->tam = tam;
    memcpy(nuevo->info, d, tam);

    return;
}

void ordenarLista(tLista *p, int (*cmpr)(void *, void *)){

    tNodo *menor;
    tNodo *buscador;

    while(*p){
        menor = *p;
        buscador = (*p)->sig;

        if(buscador && cmpr(buscador->info, menor->info) < 0){
            menor = buscador;
        }

        //Cambio el nodo a los que apuntan el uno por el otro
        void *aux = menor->sig;
        menor->sig = (*p)->sig;
        (*p)->sig = aux;

        //Ahora hago el cambio para que el nodo anterior los apunte sin tener que volver hacia atras
        aux = menor;
        menor = *p;
        *p = aux;///????????

        //Adelanto p al sig nodo
        p = &(*p)->sig;
    }

    return;
}

/*
void sacarPosicion();
void sacarInicio();
void sacarFinal();
void eliminarLista()

*/
