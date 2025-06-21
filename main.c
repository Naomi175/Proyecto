#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tdas/map.h"
#include "tdas/linkedlist.h"
#include "tdas/arraylist.h"
#define MAX_NOMBRE 50
#define MAX_CATEGORIA 30
#define MAX_TELEFONO 15
#define MAX_DIRECCION 100

typedef struct {
    int id;
    char nombre[MAX_NOMBRE];
    char categoria[MAX_CATEGORIA];
    int precio;
    int stock;
} Producto;

typedef struct {
    int idPedido;
    char nombreCliente[MAX_NOMBRE];
    char telefono[MAX_TELEFONO];
    char direccion[MAX_DIRECCION];
    List* productos;
} Pedido;

int main() {
    Map *mapaPorId = map_create_int();
    Map *mapaPorNombres = map_create_string();
    Map *mapaPorCategorias = map_create_string();
    ArrayList *listaProductos = createArrayList();
    List *listaCarro = createList();

    printf("Programa Funcionando :)");
    return 0;
}