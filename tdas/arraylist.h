#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <stdlib.h>

typedef struct ArrayList ArrayList;

// Crea una lista vacía
ArrayList *createArrayList(void);

// Inserta un elemento al inicio de la lista
void pushFrontArray(ArrayList *list, void *data);

// Inserta un elemento al final de la lista
void pushBackArray(ArrayList *list, void *data);

// Inserta un elemento después del nodo actual
void pushCurrentArray(ArrayList *list, void *data);

// Devuelve el primer elemento de la lista y lo deja como actual
void *firstListArray(ArrayList *list);

// Devuelve el siguiente elemento de la lista o NULL si no hay más
void *nextListArray(ArrayList *list);

// Devuelve el último elemento de la lista y lo deja como actual
void *lastListArray(ArrayList *list);

// Devuelve el elemento anterior en la lista o NULL si no hay más
void *prevListArray(ArrayList *list);

// Elimina el primer nodo de la lista y retorna su dato
void *popFrontArray(ArrayList *list);

// Elimina el último nodo de la lista y retorna su dato
void *popBackArray(ArrayList *list);

// Elimina el nodo actual de la lista y retorna su dato
void *popCurrentArray(ArrayList *list);

// Elimina todos los nodos de la lista, opcionalmente liberando los datos (usando free si se usa dinamicamente o NULL)
void cleanArrayList(ArrayList *list, void (*freeData)(void *));

// Libera completamente la lista y todos sus elementos (usando free si se usa dinamicamente o NULL)
void destroyArrayList(ArrayList *list, void (*freeData)(void *));

// Inserta ordenadamente en el ArrayList según una función comparadora
void insertSortedArray(ArrayList *list, void *data, int (*cmp)(const void *, const void *));

#endif /* ARRAY_LIST_H */