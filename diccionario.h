#ifndef DICCIONARIO_H_INCLUDED
#define DICCIONARIO_H_INCLUDED
#include "lista.h"
#define HASHSIZE 5

//Aca pasabamos tLista* pl, pero en realidad es un puntero a tNodo*
typedef struct{
    tLista pl;
}t_diccionario;

typedef struct{ //uso memoria dinamica para guardar la info -> almaceno el puntero a donde lo guardo y el tam de cada uno
    char *clave;
    unsigned tamclave; //No es necesario -> puede calcularse buscando el \0 (Palabras de Jorge)
    void *valor;
    unsigned tamvalor;
}t_info;

///Funciones:


unsigned hash(char *s);

void mapeo(tLista*, void (*funcion)(void*));

void destruir_tinfo(t_info*);

int crear_dic(t_diccionario*, int); //Recibe un puntero a diccionario y el tamaño

int poner_dic(t_diccionario*, char*, void*, size_t); //Recibo un puntero al diccionario, un puntero a la clave(que luego va a ser hasheada) y un puntero a la info

int obtener_dic(t_diccionario*, char*, void*, size_t); //Recibo un *p a diccionario, la clave(que tengo que hashear) y devuelvo el valor (Devolver retornando o en el parametro???) --> voy a devolver en el parametro y usar el return para manejo de errores

int sacar_dic(t_diccionario*, char*); //Recibo un *p a diccionario y la clave

int recorrer_dic(t_diccionario*, int, void (*accion)(void*)); //Recibo un *p a diccionario, la accion y una func comparacion(puede ser null y ejecutar para todos)

void destruir_lista(tLista*);

int destruir_dic(t_diccionario*, int); //Recibo un *p a diccionario


#endif // DICCIONARIO_H_INCLUDED
