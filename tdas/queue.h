#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

// Estructura del nodo de la cola
typedef struct Node {
    void * data;            // Dato genérico almacenado
    struct Node * next;     // Puntero al siguiente nodo
} Node;

// Estructura de la cola
typedef struct Queue {
    Node * front;           
    Node * rear;            
    int size;               
    int maxSize;            
} Queue;

Queue * createQueue(int maxSize);

bool isEmpty(Queue * queue);

void enqueue(Queue * queue, void * data);

void * dequeue(Queue * queue);

void freeQueue(Queue * queue);

#endif // QUEUE_H
