#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

// Estructura opaca de lista doblemente enlazada
typedef struct List List;

// Crea una lista vacía
List *createList(void);

// Inserta un elemento al inicio de la lista
void pushFront(List *list, void *data);

// Inserta un elemento al final de la lista
void pushBack(List *list, void *data);

// Inserta un elemento después del nodo actual
void pushCurrent(List *list, void *data);

// Devuelve el primer elemento de la lista y lo deja como actual
void *firstList(List *list);

// Devuelve el siguiente elemento de la lista o NULL si no hay más
void *nextList(List *list);

// Devuelve el último elemento de la lista y lo deja como actual
void *lastList(List *list);

// Devuelve el elemento anterior en la lista o NULL si no hay más
void *prevList(List *list);

// Elimina el primer nodo de la lista y retorna su dato
void *popFront(List *list);

// Elimina el último nodo de la lista y retorna su dato
void *popBack(List *list);

// Elimina el nodo actual de la lista y retorna su dato
void *popCurrent(List *list);

// Elimina todos los nodos de la lista, opcionalmente liberando los datos (usando free si se usa dinamicamente o NULL)
void cleanList(List *list, void (*freeData)(void *));

// Libera completamente la lista y todos sus elementos (usando free si se usa dinamicamente o NULL)
void destroyList(List *list, void (*freeData)(void *));

// Establece el nodo actual (current) en la lista que contiene el dato dado.
void setCurrent(List *list, void *dato);

// Obtiene el dato almacenado en el nodo actual (current) de la lista.
void *getCurrent(List *list);

#endif /* LIST_H */