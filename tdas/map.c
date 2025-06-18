#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include <string.h>

struct Map {
    MapPair **buckets;
    int capacity;
    int size;
    int (*is_equal)(void *, void *);
    unsigned long (*hash_function)(const void *);
    int iter_index;  // índice para iterador interno
};

// Comparar claves enteras
int is_equal_int(void *key1, void *key2) {
    return *((int *)key1) == *((int *)key2);
}

// Comparar claves strings
int is_equal_str(void *key1, void *key2) {
    return strcmp((char *)key1, (char *)key2) == 0;
}

// Funcion hash para strings
unsigned long hash_string(const void *key) {
    unsigned long hash = 5381;
    const char *str = key;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}

// Funcion hash para enteros
unsigned long hash_int(const void *key) {
    return (*(int *)key) * 2654435761 % 4294967296;
}

Map *map_create(int (*is_equal)(void *, void *), unsigned long (*hash_function)(const void *)) {
    Map *map = malloc(sizeof(Map));
    map->capacity = 16;
    map->size = 0;
    map->is_equal = is_equal;
    map->hash_function = hash_function;
    map->buckets = calloc(map->capacity, sizeof(MapPair *));
    return map;
}

Map *map_create_int() {
    return map_create(is_equal_int, hash_int);
}

Map *map_create_string() {
    return map_create(is_equal_str, hash_string);
}

void map_expand(Map *map) {
    int old_capacity = map->capacity;
    MapPair **old_buckets = map->buckets;

    map->capacity *= 2;
    map->buckets = calloc(map->capacity, sizeof(MapPair *));
    map->size = 0;

    for (int i = 0; i < old_capacity; i++) {
        if (old_buckets[i] && old_buckets[i]->key != NULL)
            map_insert(map, old_buckets[i]->key, old_buckets[i]->value);
    }
    free(old_buckets);
}

void map_insert(Map *map, void *key, void *value) {
    if ((float)map->size / map->capacity >= 0.7)
        map_expand(map);

    unsigned long index = map->hash_function(key) % map->capacity;
    while (map->buckets[index] != NULL && map->buckets[index]->key != NULL) {
        if (map->is_equal(map->buckets[index]->key, key)) {
            map->buckets[index]->value = value;
            return;
        }
        index = (index + 1) % map->capacity;
    }

    MapPair *pair = malloc(sizeof(MapPair));
    pair->key = key;
    pair->value = value;
    map->buckets[index] = pair;
    map->size++;
}


MapPair *map_search(Map *map, void *key) {
    unsigned long index = map->hash_function(key) % map->capacity;
    while (map->buckets[index] != NULL) {
        if (map->buckets[index]->key != NULL &&
            map->is_equal(map->buckets[index]->key, key))
            return map->buckets[index];
        index = (index + 1) % map->capacity;
    }
    return NULL;
}


MapPair *map_remove(Map *map, void *key) {
    unsigned long index = map->hash_function(key) % map->capacity;
    while (map->buckets[index] != NULL) {
        if (map->buckets[index]->key != NULL &&
            map->is_equal(map->buckets[index]->key, key)) {
            map->buckets[index]->key = NULL; // Marca como borrado
            map->size--;
            return map->buckets[index];
        }
        index = (index + 1) % map->capacity;
    }
    return NULL;
}


void map_clean(Map *map) {
    for (int i = 0; i < map->capacity; i++) {
        MapPair *pair = map->buckets[i];
        if (pair != NULL && pair->key != NULL) {
            free(pair->value);
            free(pair);
            map->buckets[i] = NULL;
        }
    }
    map->size = 0;
}


void map_destroy(Map *map) {
    if (map == NULL) return;

    map_clean(map);
    free(map->buckets);
    free(map);
}

MapPair *map_first(Map *map) {
    if (!map) return NULL;
    map->iter_index = 0;

    while (map->iter_index < map->capacity) {
        if (map->buckets[map->iter_index] != NULL &&
            map->buckets[map->iter_index]->key != NULL) {
            return map->buckets[map->iter_index];
        }
        map->iter_index++;
    }
    return NULL;
}

MapPair *map_next(Map *map) {
    if (!map) return NULL;
    map->iter_index++;

    while (map->iter_index < map->capacity) {
        if (map->buckets[map->iter_index] != NULL &&
            map->buckets[map->iter_index]->key != NULL) {
            return map->buckets[map->iter_index];
        }
        map->iter_index++;
    }
    return NULL;
}
