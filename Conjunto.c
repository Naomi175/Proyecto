#include <stdio.h>
#include <stdbool.h>

#define MAX 1000 // tamaño máximo del universo

typedef struct {
    int bits[MAX]; // Arreglo binario
} Conjunto;

// Inicializa todos los bits en 0
void inicializar(Conjunto* c) {
    for (int i = 0; i < MAX; i++)
        c->bits[i] = 0;
}

// Inserta un elemento: pone 1 en el índice
void insertar(Conjunto* c, int x) {
    if (x >= 0 && x < MAX)
        c->bits[x] = 1;
}

// Elimina un elemento: pone 0 en el índice
void eliminar(Conjunto* c, int x) {
    if (x >= 0 && x < MAX)
        c->bits[x] = 0;
}

// Verifica si un elemento está en el conjunto
bool pertenece(Conjunto* c, int x) {
    return (x >= 0 && x < MAX && c->bits[x] == 1);
}

// Muestra todos los elementos
void mostrar(Conjunto* c) {
    printf("Conjunto: ");
    for (int i = 0; i < MAX; i++) {
        if (c->bits[i] == 1)
            printf("%d ", i);
    }
    printf("\n");
}

int main() {
    Conjunto c;
    int num;
    inicializar(&c);

    insertar(&c, 5);
    insertar(&c, 999);
    insertar(&c, 500);
    printf("Ingrese un numero para agregar al conjunto");
    scanf("%d", &num);
    insertar(&c, num);
    mostrar(&c);
    eliminar(&c, 500);
    mostrar(&c);

    

    return 0;
}
