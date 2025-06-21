#include "arraylist.h"

#define INITIAL_CAPACITY 10

struct ArrayList {
    void **items;
    int size;
    int capacity;
    int current;
};

ArrayList *createArrayList(void) {
    ArrayList *list = (ArrayList *)malloc(sizeof(ArrayList));
    if (!list) return NULL;

    list->items = (void **)malloc(sizeof(void *) * INITIAL_CAPACITY);
    if (!list->items) {
        free(list);
        return NULL;
    }

    list->size = 0;
    list->capacity = INITIAL_CAPACITY;
    list->current = -1;
    return list;
}

void ensureCapacity(ArrayList *list) {
    if (list->size < list->capacity) return;

    int newCap = list->capacity * 2;
    void **newItems = (void **)realloc(list->items, sizeof(void *) * newCap);
    if (newItems) {
        list->items = newItems;
        list->capacity = newCap;
    }
}

void pushFrontArray(ArrayList *list, void *data) {
    ensureCapacity(list);
    for (int i = list->size; i > 0; i--) {
        list->items[i] = list->items[i - 1];
    }
    list->items[0] = data;
    list->size++;
    list->current = 0;
}

void pushBackArray(ArrayList *list, void *data) {
    ensureCapacity(list);
    list->items[list->size++] = data;
    list->current = list->size - 1;
}

void pushCurrentArray(ArrayList *list, void *data) {
    if (list->current < 0 || list->current >= list->size) return;

    ensureCapacity(list);
    for (int i = list->size; i > list->current + 1; i--) {
        list->items[i] = list->items[i - 1];
    }

    list->items[++list->current] = data;
    list->size++;
}

void *firstListArray(ArrayList *list) {
    if (list->size == 0) return NULL;
    list->current = 0;
    return list->items[0];
}

void *nextListArray(ArrayList *list) {
    if (list->current < 0 || list->current + 1 >= list->size) return NULL;
    return list->items[++list->current];
}

void *lastListArray(ArrayList *list) {
    if (list->size == 0) return NULL;
    list->current = list->size - 1;
    return list->items[list->current];
}

void *prevListArray(ArrayList *list) {
    if (list->current <= 0) return NULL;
    return list->items[--list->current];
}

void *popFrontArray(ArrayList *list) {
    if (list->size == 0) return NULL;

    void *data = list->items[0];
    for (int i = 1; i < list->size; i++) {
        list->items[i - 1] = list->items[i];
    }

    list->size--;
    list->current = 0;
    return data;
}

void *popBackArray(ArrayList *list) {
    if (list->size == 0) return NULL;
    void *data = list->items[--list->size];
    list->current = list->size - 1;
    return data;
}

void *popCurrentArray(ArrayList *list) {
    if (list->current < 0 || list->current >= list->size) return NULL;

    void *data = list->items[list->current];
    for (int i = list->current + 1; i < list->size; i++) {
        list->items[i - 1] = list->items[i];
    }

    list->size--;
    if (list->current >= list->size) list->current = list->size - 1;
    return data;
}

void cleanArrayList(ArrayList *list, void (*freeData)(void *)) {
    if (freeData) {
        for (int i = 0; i < list->size; i++) {
            freeData(list->items[i]);
        }
    }
    list->size = 0;
    list->current = -1;
}

void destroyArrayList(ArrayList *list, void (*freeData)(void *)) {
    if (!list) return;
    cleanArrayList(list, freeData);
    free(list->items);
    free(list);
}