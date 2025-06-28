#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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
    if (cantidad == 0){
        puts("No hay productos para seleccionar.");
        presioneTeclaParaContinuar();
        return;
    } 

    while (1) {
        puts("Seleccione un producto para agregar al carro:");
        for (int i = 0; i < cantidad; i++) {
            printf("%d) %s - $%d (Stock: %d)\n", i + 1, productos[i]->nombre, productos[i]->precio, productos[i]->stock);
        }
        puts("0) Cancelar y regresar");

        int opcion;
        printf("Ingrese una opcion: ");
        if (scanf("%d", &opcion) != 1 || opcion < 0 || opcion > cantidad) {
            limpiarBuffer();
            limpiarPantalla();
            puts("Opcion invalida.");
            continue;
        }

        if (opcion == 0){
            limpiarPantalla();
            puts("Regresando.");
            break;
        }

        Producto *seleccionado = productos[opcion - 1];

        if (seleccionado->stock <= 0) {
            printf("Lo sentimos, el producto '%s' no tiene stock disponible :(\n", seleccionado->nombre);
            puts("Desea seguir agregando productos?");
            puts("1) Continuar");
            puts("2) Cancelar y regresar");
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
                    puts("Regresando.");
                    return;
                } else {
                    puts("Error: caracter invalido");
                    printf("Ingrese su opcion: ");
                }
            }
            limpiarPantalla();
            continue;
        }
        limpiarPantalla();
        agregarAlCarro(carro, seleccionado);
        puts("Desea seguir agregando productos?");
        puts("1) Continuar");
        puts("2) Cancelar y regresar");
        printf("Ingrese su opcion: ");
        while (1){
            char opcionFinal;
            scanf(" %c", &opcionFinal);
            while (getchar() != '\n');
            if (opcionFinal == '1'){
                limpiarPantalla();
                break;
            }
            else if (opcionFinal == '2'){
                limpiarPantalla();
                puts("Regresando.");
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

int validarNombre(const char *nombre) {
    if (nombre == NULL || nombre[0] == '\0') return 0;

    int contieneLetra = 0;

    for (int i = 0; nombre[i] != '\0'; i++) {
        char c = nombre[i];
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            contieneLetra = 1;
        } else if (c != ' ') {
            return 0; // Contiene un carácter no permitido
        }
    }

    return contieneLetra;
}

int validarTelefono(const char *telefono) {
    if (strlen(telefono) == 0) return 0;
    for (int i = 0; telefono[i]; i++) {
        if (!isdigit(telefono[i])) return 0;
    }
    return 1;
}

int validarTextoNoVacio(const char *texto) {
    if (texto == NULL) return 0;

    // Saltar espacios en blanco
    while (*texto != '\0') {
        if (*texto != ' ' && *texto != '\t' && *texto != '\n') {
            return 1; // Hay al menos un carácter visible
        }
        texto++;
    }

    return 0; // Solo había espacios o estaba vacío
}

void mostrarMenuCarrito() {
    printf("---------------------------------------------\n");
    printf("CARRITO DE COMPRAS - SELECCIONE UNA OPCION:\n");
    printf("---------------------------------------------\n");
    printf("1. Mostrar carrito.\n");
    printf("2. Editar carrito.\n");
    printf("3. Encargar productos del carrito.\n");
    printf("4. Volver.\n");
}

void mostrarCarro(List *listaCarro) {
    limpiarPantalla();

    if (listaCarro == NULL || firstList(listaCarro) == NULL) {
        printf("El carrito esta vacio.\n");
        return;
    }

    printf("==========Mostrando Carrito==========\n");
    void *dato = firstList(listaCarro);
    while (dato != NULL) {
        Producto *producto = (Producto *) dato;
        mostrarProducto(producto);
        dato = nextList(listaCarro);
    }
    puts("----------------------------------------");
}

void eliminarDelCarro(List *listaCarro) {
    limpiarPantalla();
    if (listaCarro == NULL || firstList(listaCarro) == NULL) {
        printf("El carrito esta vacio.\n");
        presioneTeclaParaContinuar();
        return;
    }

    // Mostrar los productos en el carrito
    printf("==========Productos en el Carrito==========\n");
    int contador = 1;
    void *dato = firstList(listaCarro);
    while (dato != NULL) {
        Producto *producto = (Producto *) dato;
        printf("\nProducto %d:\n", contador++);
        mostrarProducto(producto);
        dato = nextList(listaCarro);
    }
    puts("----------------------------------------");

    // Selección del producto a eliminar
    int num;
    printf("Ingrese el numero del producto a eliminar (0 para cancelar): ");
    scanf("%d", &num);

    if (num == 0){
        puts("Accion cancelada.");
        presioneTeclaParaContinuar();
        return;
    }

    if (num < 0 || num >= contador) {
        printf("Numero invalido. No se elimino ningun producto.\n");
        presioneTeclaParaContinuar();
        return;
    }

    // Posicionar current en el producto a eliminar
    dato = firstList(listaCarro);
    for (int i = 1; i < num; i++) {
        dato = nextList(listaCarro);
    }
    setCurrent(listaCarro, dato);

    Producto *producto = (Producto *) getCurrent(listaCarro);
    int opcion;

    // Confirmación de eliminación
    while (1) {
        printf("Esta seguro de que desea eliminar '%s' del carrito?\n", producto->nombre);
        puts("1) Si");
        puts("2) No");
        printf("Ingrese su opcion: ");
        if (scanf("%d", &opcion) != 1) {
            limpiarBuffer(); // Limpia entrada inválida
            printf("Entrada no valida. Intente nuevamente.\n");
            continue;
        }

        if (opcion == 1) {
            popCurrent(listaCarro); // Elimina el producto
            limpiarPantalla();
            printf("Producto eliminado correctamente.\n");
            break;
        } else if (opcion == 2) {
            limpiarPantalla();
            printf("Eliminacion cancelada.\n");
            break;
        } else {
            limpiarPantalla();
            printf("Opcion invalida. Ingrese 1 o 2.\n");
        }
    }
    presioneTeclaParaContinuar();
}

void encargarProductos(List *listaCarro, Queue *colaPedidos) {
    limpiarPantalla();
    if (listaCarro == NULL || firstList(listaCarro) == NULL) {
        printf("El carrito esta vacio. No hay productos para encargar.\n");
        presioneTeclaParaContinuar();
        return;
    }

    mostrarCarro(listaCarro);
    int opcion;

    // Confirmación del pedido
    while (1) {
        printf("Desea confirmar el pedido?\n");
        puts("1) Si");
        puts("2) No");
        printf("Ingrese su opcion: ");

        if (scanf("%d", &opcion) != 1) {
            limpiarBuffer();
            limpiarPantalla();
            puts("Entrada no valida. Intente nuevamente.");
            continue;
        }

        if (opcion == 1) {
            limpiarPantalla();
            break; // Confirmado, continúa con el proceso
        } else if (opcion == 2) {
            limpiarPantalla();
            puts("Pedido cancelado. Volviendo al menu principal...");
            presioneTeclaParaContinuar();
            return;
        } else {
            puts("Opcion invalida. Ingrese 1 o 2.");
        }
    }

    // Verifica stock antes de continuar
    void *dato = firstList(listaCarro);
    while (dato != NULL) {
        Producto *producto = (Producto *) dato;
        if (producto->stock <= 0) {
            printf("No se puede procesar el pedido. El producto '%s' no tiene stock disponible.\n", producto->nombre);
            presioneTeclaParaContinuar();
            return;
        }
        dato = nextList(listaCarro);
    }

    // Crear nuevo pedido
    Pedido *nuevoPedido = malloc(sizeof(Pedido));
    nuevoPedido->idPedido = (colaPedidos->size) + 1;

    while (getchar() != '\n');  // Limpiar buffer

    // Ingreso de datos y validacion
    puts("Iniciando pedido.");
    char buffer[128];

    // Nombre
    while (1) {
        printf("Ingrese su nombre: ");
        fgets(buffer, sizeof(buffer), stdin);
        strtok(buffer, "\n");

        if (validarNombre(buffer)) {
            strncpy(nuevoPedido->nombreCliente, buffer, MAX_NOMBRE);
            break;
        }
        limpiarPantalla();
        puts("Nombre invalido. No puede contener numeros ni estar vacio.");
    }

    // Teléfono
    while (1) {
        printf("Ingrese su telefono: ");
        fgets(buffer, sizeof(buffer), stdin);
        strtok(buffer, "\n");

        if (validarTelefono(buffer)) {
            strncpy(nuevoPedido->telefono, buffer, MAX_TELEFONO);
            break;
        }
        limpiarPantalla();
        puts("Telefono invalido. Solo se permiten numeros.");
    }

    // Dirección
    while (1) {
        printf("Ingrese su direccion: ");
        fgets(buffer, sizeof(buffer), stdin);
        strtok(buffer, "\n");

        if (validarTextoNoVacio(buffer)) {
            strncpy(nuevoPedido->direccion, buffer, MAX_DIRECCION);
            break;
        }
        limpiarPantalla();
        puts("La direccion no puede estar vacia.");
    }

    // Agregar productos del carrito al pedido
    nuevoPedido->productos = createList();
    dato = firstList(listaCarro);
    while (dato != NULL) {
        Producto *producto = (Producto *) dato;
        producto->stock--;
        pushBack(nuevoPedido->productos, producto);
        dato = nextList(listaCarro);
    }

    // Añadir pedido a la cola
    enqueue(colaPedidos, nuevoPedido);
    cleanList(listaCarro, NULL);
    limpiarPantalla();
    printf("Pedido realizado con exito :) Sera gestionado por el administrador.\n");
    presioneTeclaParaContinuar();
}