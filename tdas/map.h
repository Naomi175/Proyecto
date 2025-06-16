#ifndef MAP_H
#define MAP_H
#include <stdio.h>
#include <stdlib.h>

// Par clave-valor
typedef struct {
    void *key;
    void *value;
} MapPair;

// Estructura opaca del mapa
typedef struct Map Map;

// Crea un mapa. Recibe una función que compara claves y la funcion hash correspondiente al tipo de clave a usar.
Map *map_create(int (*is_equal)(void *, void *), unsigned long (*hash)(const void *));

// Crea un mapa que use enteros como claves.
Map *map_create_int();

// Crea un mapa que use strings como claves.
Map *map_create_string();

// Inserta un par clave-valor
void map_insert(Map *map, void *key, void *value);

// Busca un par por su clave
MapPair *map_search(Map *map, void *key);

// Elimina un par por clave
MapPair *map_remove(Map *map, void *key);

// Limpia los pares del mapa pero no lo destruye completamente
void map_clean(Map *map);

// Destruye completamente el mapa y libera memoria
void map_destroy(Map *map);

// Devuelve el primer elemento del mapa o NULL si está vacío
MapPair *map_first(Map *map);

// Devuelve el siguiente elemento o NULL si no hay más
MapPair *map_next(Map *map);

#endif /* MAP_H */
