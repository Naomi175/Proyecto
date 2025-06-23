#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


Queue * createQueue(int maxSize) {
    Queue * queue = (Queue *) malloc(sizeof(Queue));
    if (queue == NULL) {
        printf("Error al asignar memoria\n");
        exit(EXIT_FAILURE);
    }
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
    queue->maxSize = maxSize;
    return queue;
}


bool isEmpty(Queue * queue) {
    return queue->size == 0;
}

void enqueue(Queue * queue, void * data) {
    if (queue->maxSize > 0 && queue->size == queue->maxSize) {
        dequeue(queue);
    }

    Node * newNode = (Node *) malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Error al asignar memoria\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;

    if (queue->rear == NULL) {
        // Cola vacía
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }

    queue->size++;
}


void * dequeue(Queue * queue) {
    if (isEmpty(queue)) {
        return NULL;
    }

    Node * temp = queue->front;
    void * data = temp->data;

    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(temp);
    queue->size--;

    return data;
}

void freeQueue(Queue * queue) {
    while (!isEmpty(queue)) {
        dequeue(queue);
    }
    free(queue);
}
