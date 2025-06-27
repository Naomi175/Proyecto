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
    printf("Producto '%s' agregado al carro!\n", producto->nombre);
}

void seleccionarProductosParaCarro(Producto **productos, int cantidad, List *carro) {
    if (cantidad == 0) return;

    while (1) {
        limpiarPantalla();
        puts("Seleccione un producto para agregar al carro:");
        for (int i = 0; i < cantidad; i++) {
            printf("%d) %s - $%d (Stock: %d)\n", i + 1, productos[i]->nombre, productos[i]->precio, productos[i]->stock);
        }
        puts("0) Volver al menu");

        int opcion;
        printf("Ingrese una opcion: ");
        if (scanf("%d", &opcion) != 1 || opcion < 0 || opcion > cantidad) {
            limpiarBuffer();
            puts("Opción invalida.");
            continue;
        }

        if (opcion == 0){
            limpiarPantalla();
            puts("Volviendo al menu.");
            break;
        }

        Producto *seleccionado = productos[opcion - 1];

        if (seleccionado->stock <= 0) {
            printf("Lo sentimos, el producto '%s' no tiene stock disponible :(\n", seleccionado->nombre);
            puts("Desea seguir agregando productos?");
            puts("1) Continuar");
            puts("2) Salir al menu");
            printf("Ingrese su opcion: ");
            while (1){
                char opcionstock;
                scanf(" %c", &opcionstock);
                while (getchar() != '\n');
                if (opcionstock == '1'){
                    break;
                }
                else if (opcionstock == '2'){
                    limpiarPantalla();
                    puts("Volviendo al menu.");
                    return;
                } else {
                    puts("Error: caracter invalido");
                    printf("Ingrese su opcion: ");
                }
            }
            continue;
        }
        limpiarPantalla();
        agregarAlCarro(carro, seleccionado);
        puts("Desea seguir agregando productos?");
        puts("1) Continuar");
        puts("2) Salir al menu");
        printf("Ingrese su opcion: ");
        while (1){
            char opcionFinal;
            scanf(" %c", &opcionFinal);
            while (getchar() != '\n');
            if (opcionFinal == '1'){
                break;
            }
            else if (opcionFinal == '2'){
                limpiarPantalla();
                puts("Volviendo al menu.");
                return;
            } else {
                puts("Error: caracter invalido");
                printf("Ingrese su opcion: ");
            }
        }
    }
}

int obtenerProductosDeLista(List *lista, Producto **productos, int max) {
    int cantidad = 0;
    void *dato = firstList(lista);
    while (dato && cantidad < max) {
        productos[cantidad++] = (Producto *)dato;
        dato = nextList(lista);
    }
    return cantidad;
}