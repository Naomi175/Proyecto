#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tdas/map.h"
#include "tdas/linkedlist.h"
#include "tdas/arraylist.h"
#include "tdas/queue.h"
#define MAX_NOMBRE 50
#define MAX_CATEGORIA 30
#define MAX_TELEFONO 15
#define MAX_DIRECCION 100
#define MAX_NOVEDADES 10

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


void mostrarMenuPrincipal() {
    printf("---------------------------------------------\n");
    printf("\nMENU PRINCIPAL - SELECCIONE UNA OPCIÓN:\n");
    printf("---------------------------------------------\n");
    printf("1. Revisar novedades.\n");
    printf("2. Ver catálogo completo.\n");
    printf("3. Buscar producto por nombre.\n");
    printf("4. Ver productos por categoría.\n");
    printf("5. Ver carrito de compras y encargar.");
    printf("6. Ingresar al modo administrador.\n");
    printf("7. Salir del programa.\n");
}

void mostrarMenuAdmin() {
    printf("---------------------------------------------\n");
    printf("\nMODO ADMINISTRADOR - SELECCIONE UNA OPCIÓN:\n");
    printf("---------------------------------------------\n");
    printf("1. Agregar producto.\n");
    printf("2. Modificar producto.\n");
    printf("3. Eliminar producto.\n");
    printf("4. Consultar stock bajo.\n");
    printf("5. Gestionar pedidos de clientes.");
    printf("6. Cambiar clave de administrador.\n");
    printf("7. Salir del modo administrador.\n");
}

// Función para limpiar la pantalla
void limpiarPantalla() { system("clear"); }

void presioneTeclaParaContinuar() {
  puts("Presione una tecla para continuar...");
  getchar(); // Consume el '\n' del buffer de entrada
}

void mostrarProducto(Producto *producto) {
    if (!producto) return;
    printf("ID: %d\n", producto->id);
    printf("Nombre: %s\n", producto->nombre);
    printf("Categoría: %s\n", producto->categoria);
    printf("Precio: $%d\n", producto->precio);
    printf("Stock: %d\n", producto->stock);
}

void agregarAlCarro(List *carro, Producto *producto) {
    if (!carro || !producto) return;

    // Crear una copia del producto
    Producto *nuevoProducto = malloc(sizeof(Producto));
    if (!nuevoProducto) return;

    memcpy(nuevoProducto, producto, sizeof(Producto));

    // Agregar al final del carro
    pushBack(carro, nuevoProducto);
    printf("Producto '%s' agregado al carro.\n", nuevoProducto->nombre);
}

void agregarProducto(Map *mapaPorId, Map *mapaPorNombres, Map *mapaPorCategorias, ArrayList *listaProductos) {
    char ruta[256];
    printf("Introduce la ruta del archivo CSV: ");
    fgets(ruta, sizeof(ruta), stdin);
    ruta[strcspn(ruta, "\n")] = '\0';  // Eliminar salto de línea

    FILE *archivo = fopen(ruta, "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    printf("Cargando productos...\n");

    char linea[256];
    fgets(linea, sizeof(linea), archivo); // Leer encabezados y descartarlos

    int total = 0;
    while (fgets(linea, sizeof(linea), archivo)) {
        Producto *nuevo = malloc(sizeof(Producto));
        if (!nuevo) continue;

        // Separar campos por comas
        char *campo = strtok(linea, ",");
        if (!campo) continue;
        nuevo->id = atoi(campo);

        campo = strtok(NULL, ",");
        if (!campo) continue;
        strncpy(nuevo->nombre, campo, MAX_NOMBRE);

        campo = strtok(NULL, ",");
        if (!campo) continue;
        strncpy(nuevo->categoria, campo, MAX_CATEGORIA);

        campo = strtok(NULL, ",");
        if (!campo) continue;
        nuevo->precio = atoi(campo);

        campo = strtok(NULL, ",");
        if (!campo) continue;
        nuevo->stock = atoi(campo);

        // Insertar en lista de productos
        pushBackArray(listaProductos, nuevo);

        // Insertar en mapa por ID
        int *idKey = malloc(sizeof(int));
        *idKey = nuevo->id;
        map_insert(mapaPorId, idKey, nuevo);

        // Insertar en mapa por nombre
        char *nombreKey = strdup(nuevo->nombre);
        map_insert(mapaPorNombres, nombreKey, nuevo);

        // Insertar en mapa por categoría (lista de productos)
        MapPair *par = map_search(mapaPorCategorias, nuevo->categoria);
        List *listaCategoria;
        if (par == NULL) {
            listaCategoria = createList();
            char *categoriaKey = strdup(nuevo->categoria);
            map_insert(mapaPorCategorias, categoriaKey, listaCategoria);
        } else {
            listaCategoria = (List *)par->value;
        }
        pushBack(listaCategoria, nuevo);

        total++;
    }

    fclose(archivo);
    printf("Productos cargados exitosamente: %d\n", total);
}

void modoAdmin(Map *mapaPorId, Map *mapaPorCategorias, Map *mapaPorNombres, ArrayList *listaProductos, List *listaCarro, Queue *colaPedidos, Queue *colaNovedades) {
    while (1) {
        mostrarMenuAdmin();
        char op[10];
        scanf("%s", op);

        if (strcmp(op,"1") == 0) agregarProducto(mapaPorId, mapaPorNombres, mapaPorCategorias, listaProductos); //1. Agregar producto.
        else if (strcmp(op, "2") == 0) modificarProducto(mapaPorId, mapaPorNombres, mapaPorCategorias, listaProductos);//2. Modificar producto.
        else if (strcmp(op, "3") == 0) eliminarProducto(mapaPorId, mapaPorNombres, mapaPorCategorias, listaProductos, listaCarro); //3. Eliminar producto.
        else if (strcmp(op, "4") == 0) consultarStock(listaProductos);//4. Consultar stock bajo.
        else if (strcmp(op, "5") == 0) gestionPedidos(colaPedidos);//5. Gestionar pedidos de clientes.
        else if (strcmp(op, "6") == 0) cambiarClave();//6. Cambiar clave de administrador.
        else if (strcmp(op, "7") == 0) {  //7. Salir del modo administrador.
            printf("Volviendo al menú principal...\n");
            break;
        }
        else printf("Respuesta inválida, inténtelo de nuevo.\n");
        
    }
}
/* 
*/
void ejecutarApliacion() {
    Map *mapaPorId = map_create_int();
    Map *mapaPorNombres = map_create_string();
    Map *mapaPorCategorias = map_create_string();
    ArrayList *listaProductos = createArrayList();
    List *listaCarro = createList();
    Queue *colaNovedades = createQueue(MAX_NOVEDADES);
    Queue *colaPedidos = createQueue(0);

    while (1) {
        mostrarMenuPrincipal();
        char op[10];
        scanf("%s", op);

        if (strcmp(op,"1") == 0) revisarNovedades(colaNovedades); //1. Revisar novedades.
        else if (strcmp(op, "2") == 0) verCatalogo(listaProductos); //2. Ver catálogo completo.
        else if (strcmp(op, "3") == 0) buscarPorNombre(mapaPorNombres); //3. Buscar producto por nombre.
        else if (strcmp(op, "4") == 0) buscarPorCategoria(mapaPorCategorias);//4. Ver productos por categoría.
        else if (strcmp(op, "5") == 0) verCarrito(listaCarro);//5. Ver carrito de compras y encargar.
        else if (strcmp(op, "6") == 0) modoAdmin(mapaPorId, mapaPorCategorias, mapaPorNombres, listaProductos, listaCarro, colaPedidos, colaNovedades);//6. Ingresar al modo administrador.
        else if (strcmp(op, "7") == 0) {  //7. Salir del programa.
            printf("Saliendo del programa...\n");
            break;
        }
        else printf("Respuesta inválida, inténtelo de nuevo.\n");
    }
}

int main() {
    ejecutarApliacion();

    printf("Programa Funcionando :)");
    return 0;
}