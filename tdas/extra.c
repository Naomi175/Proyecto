#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "extra.h"

void limpiarPantalla() { system("clear"); }

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void presioneTeclaParaContinuar() {
    printf("Presione ENTER para continuar...");
    limpiarBuffer();
    getchar();
}

int compararPorNombre(const void *a, const void *b) {
    const Producto *prodA = (const Producto *)a;
    const Producto *prodB = (const Producto *)b;
    return strcmp(prodA->nombre, prodB->nombre);
}

void eliminarDeArrayList(ArrayList *lista, void *dato) {
    void *actual = firstListArray(lista);
    while (actual != NULL) {
        if (actual == dato) {
            popCurrentArray(lista);
            return;
        }
        actual = nextListArray(lista);
    }
}

void mostrarProducto(Producto *producto) {
    if (!producto) return;
    puts("----------------------------------------");
    printf("ID: %d\n", producto->id);
    printf("Nombre: %s\n", producto->nombre);
    printf("Categoria: %s\n", producto->categoria);
    printf("Precio: $%d\n", producto->precio);
    printf("Stock: %d\n", producto->stock);
}

void agregarAlCarro(List *carro, Producto *producto) {
    if (!carro || !producto) return;
    pushBack(carro, producto);  // Agrega un puntero al producto original
    printf("Producto '%s' agregado al carro.\n", producto->nombre);
}