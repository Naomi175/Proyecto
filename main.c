#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tdas/map.h"
#include "tdas/linkedlist.h"
#include "tdas/arraylist.h"
#include "tdas/queue.h"
#include "tdas/extra.h" // Structs y funciones adicionales aqui.
#define MAX_NOMBRE 50
#define MAX_CATEGORIA 30
#define MAX_TELEFONO 15
#define MAX_DIRECCION 100
#define MAX_NOVEDADES 10

// Muestra el menú principal de opciones disponibles para el usuario
void mostrarMenuPrincipal() {
    printf("---------------------------------------------\n");
    printf("MENU PRINCIPAL - SELECCIONE UNA OPCION:\n");
    printf("---------------------------------------------\n");
    printf("1. Revisar novedades.\n");
    printf("2. Ver catalogo completo.\n");
    printf("3. Buscar producto por nombre.\n");
    printf("4. Ver productos por categoria.\n");
    printf("5. Ver carrito de compras y encargar.\n");
    printf("6. Ingresar al modo administrador.\n");
    printf("7. Salir del programa.\n");
}

// Muestra el menú del modo administrador con sus funcionalidades
void mostrarMenuAdmin() {
    printf("---------------------------------------------\n");
    printf("MODO ADMINISTRADOR - SELECCIONE UNA OPCION:\n");
    printf("---------------------------------------------\n");
    printf("1. Agregar producto.\n");
    printf("2. Modificar producto.\n");
    printf("3. Eliminar producto.\n");
    printf("4. Consultar stock bajo.\n");
    printf("5. Gestionar pedidos de clientes.\n");
    printf("6. Cambiar clave de administrador.\n");
    printf("7. Salir del modo administrador.\n");
}

// Inserta un nuevo producto en todos los TDAs correspondientes:
// mapa por ID, por nombre, por categoría, lista global y cola de novedades.
void insertarProductoEnTdas(Map *mapaPorId, Map *mapaPorNombres, Map *mapaPorCategorias,
                            ArrayList *listaProductos, Queue *colaNovedades, Producto *nuevo) {
    if (!nuevo) return;
    if (map_search(mapaPorId, &nuevo->id)) {
        printf("Ya existe un producto con el ID %d. Operacion cancelada.\n", nuevo->id);
        free(nuevo);
        return;
    }
    // Lista global
    insertSortedArray(listaProductos, nuevo, compararPorNombre);

    // Mapa por ID
    int *idKey = malloc(sizeof(int));
    *idKey = nuevo->id;
    map_insert(mapaPorId, idKey, nuevo);

    // Mapa por nombre
    char *nombreKey = strdup(nuevo->nombre);
    map_insert(mapaPorNombres, nombreKey, nuevo);

    // Mapa por categoría
    MapPair *par = map_search(mapaPorCategorias, nuevo->categoria);
    List *listaCategoria;
    if (!par) {
        listaCategoria = createList();
        char *categoriaKey = strdup(nuevo->categoria);
        map_insert(mapaPorCategorias, categoriaKey, listaCategoria);
    } else {
        listaCategoria = (List *)par->value;
    }
    pushBack(listaCategoria, nuevo);

    // Cola de novedades
    enqueue(colaNovedades, nuevo);
}

// Permite al administrador agregar productos, ya sea desde un CSV o manualmente.
// Llama a `insertarProductoEnTdas` después de obtener los datos.
void agregarProducto(Map *mapaPorId, Map *mapaPorNombres, Map *mapaPorCategorias, ArrayList *listaProductos, Queue *colaNovedades) {
    limpiarPantalla();
    while (1) {
        char opcion;
        puts("Seleccione un modo de ingreso:");
        puts("1) Cargar archivo CSV");
        puts("2) Ingresar producto manualmente");
        puts("3) Regresar al menu de administrador");
        scanf(" %c", &opcion);
        while (getchar() != '\n');
        if (opcion == '1'){
            limpiarPantalla();
            char ruta[256];
            printf("Introduce la ruta del archivo CSV: ");
            fgets(ruta, sizeof(ruta), stdin);
            ruta[strcspn(ruta, "\n")] = '\0';  // Eliminar salto de línea

            FILE *archivo = fopen(ruta, "r");
            if (archivo == NULL) {
                perror("Error al abrir el archivo");
                presioneTeclaParaContinuar();
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

                insertarProductoEnTdas(mapaPorId, mapaPorNombres, mapaPorCategorias,
                                       listaProductos, colaNovedades, nuevo);

                total++;
            }
            fclose(archivo);
            printf("Productos cargados exitosamente: %d\n", total);
            break;
        } 
        else if (opcion == '2') {
            limpiarPantalla();
            Producto *nuevo = malloc(sizeof(Producto));
            if (!nuevo) {
                perror("No se pudo asignar memoria para el producto");
                presioneTeclaParaContinuar();
                continue;
            }

            printf("Ingrese un ID para el producto: ");
            scanf("%d", &nuevo->id);
            while (getchar() != '\n'); // Limpiar buffer

            printf("Ingrese el nombre del producto: ");
            fgets(nuevo->nombre, MAX_NOMBRE, stdin);
            nuevo->nombre[strcspn(nuevo->nombre, "\n")] = '\0'; // Quitar salto de línea

            printf("Ingrese la categoria del producto: ");
            fgets(nuevo->categoria, MAX_CATEGORIA, stdin);
            nuevo->categoria[strcspn(nuevo->categoria, "\n")] = '\0';

            printf("Ingrese el precio del producto: ");
            scanf("%d", &nuevo->precio);
            while (getchar() != '\n');

            printf("Ingrese el stock del producto: ");
            scanf("%d", &nuevo->stock);
            while (getchar() != '\n');

            insertarProductoEnTdas(mapaPorId, mapaPorNombres, mapaPorCategorias,
                                   listaProductos, colaNovedades, nuevo);

            printf("Producto agregado correctamente.\n");
            break;
        }
        else if (opcion == '3') {
            limpiarPantalla();
            puts("Regresando al menu de administrador.");
            break;
        } else {
            puts("Error: Caracter invalido.");
        }
    }
    presioneTeclaParaContinuar();
}

// Permite modificar atributos de un producto existente: nombre, categoría, precio o stock.
// También actualiza los TDAs para reflejar los cambios.
void modificarProducto(Map *mapaPorId, Map *mapaPorNombres, Map *mapaPorCategorias, ArrayList *listaProductos) {
    limpiarPantalla();

    printf("Ingrese el ID del producto a modificar: ");
    int id;
    scanf("%d", &id);
    while (getchar() != '\n');

    MapPair *par = map_search(mapaPorId, &id);
    if (!par) {
        printf("No se encontro ningun producto con el ID: %d\n", id);
        presioneTeclaParaContinuar();
        return;
    }

    Producto *producto = (Producto *)par->value;

    while (1) {
        limpiarPantalla();
        printf("Producto actual:\n");
        mostrarProducto(producto);
        puts("----------------------------------------");
        puts("\nQue desea modificar?");
        puts("1. Nombre");
        puts("2. Categoria");
        puts("3. Precio");
        puts("4. Stock");
        puts("5. Volver al menu");

        char opcion;
        scanf(" %c", &opcion);
        while (getchar() != '\n');

        if (opcion == '1') {
            // Eliminar del mapa por nombre
            map_remove(mapaPorNombres, producto->nombre);

            // Eliminar de lista global
            eliminarDeArrayList(listaProductos, producto);

            printf("Nuevo nombre: ");
            fgets(producto->nombre, MAX_NOMBRE, stdin);
            producto->nombre[strcspn(producto->nombre, "\n")] = '\0';

            // Insertar con nuevo nombre
            char *nuevaClave = strdup(producto->nombre);
            map_insert(mapaPorNombres, nuevaClave, producto);

            // Insertar ordenadamente en lista global
            insertSortedArray(listaProductos, producto, compararPorNombre);

            printf("Nombre actualizado correctamente.\n");
        }
        else if (opcion == '2') {
            // Eliminar de la categoría anterior
            MapPair *parCat = map_search(mapaPorCategorias, producto->categoria);
            if (parCat) {
                List *listaCat = parCat->value;
                void *dato = firstList(listaCat);
                while (dato) {
                    if (dato == producto) {
                        popCurrent(listaCat);
                        break;
                    }
                    dato = nextList(listaCat);
                }
            }

            printf("Nueva categoria: ");
            fgets(producto->categoria, MAX_CATEGORIA, stdin);
            producto->categoria[strcspn(producto->categoria, "\n")] = '\0';

            // Insertar en nueva categoría
            MapPair *nuevaCat = map_search(mapaPorCategorias, producto->categoria);
            List *listaNuevaCat;
            if (!nuevaCat) {
                listaNuevaCat = createList();
                char *clave = strdup(producto->categoria);
                map_insert(mapaPorCategorias, clave, listaNuevaCat);
            } else {
                listaNuevaCat = nuevaCat->value;
            }
            pushBack(listaNuevaCat, producto);

            printf("Categoria actualizada correctamente.\n");
        }
        else if (opcion == '3') {
            printf("Nuevo precio: ");
            scanf("%d", &producto->precio);
            while (getchar() != '\n');
            printf("Precio actualizado correctamente.\n");
        }
        else if (opcion == '4') {
            printf("Nuevo stock: ");
            scanf("%d", &producto->stock);
            while (getchar() != '\n');
            printf("Stock actualizado correctamente.\n");
        }
        else if (opcion == '5') {
            break;
        } else {
            printf("Opcion invalida.\n");
        }

        presioneTeclaParaContinuar();
    }
}

// Elimina un producto completamente del sistema:
// de mapas, lista global, cola de novedades y libera su memoria.
void eliminarProducto(Map *mapaPorId, Map *mapaPorNombres, Map *mapaPorCategorias, ArrayList *listaProductos, Queue *colaNovedades) {
    limpiarPantalla();
    printf("Ingrese el ID del producto a eliminar: ");
    int id;
    scanf("%d", &id);
    while (getchar() != '\n');

    MapPair *par = map_search(mapaPorId, &id);
    if (!par) {
        printf("No se encontro ningun producto con el ID %d.\n", id);
        presioneTeclaParaContinuar();
        return;
    }

    Producto *producto = (Producto *)par->value;
    mostrarProducto(producto);
    puts("----------------------------------------");
    puts("Desea eliminar este producto?");
    puts("1) Eliminar producto");
    puts("2) Cancelar accion");
    while(1) {
        puts("Ingrese una opcion:");
        char opcion;
        scanf(" %c", &opcion);
        while (getchar() != '\n');
        if (opcion == '1'){
            // Eliminar de mapaPorId
            map_remove(mapaPorId, &producto->id);

            // Eliminar de mapaPorNombres
            map_remove(mapaPorNombres, producto->nombre);

            // Eliminar de mapaPorCategorias
            MapPair *catPar = map_search(mapaPorCategorias, producto->categoria);
            if (catPar) {
                List *listaCat = (List *)catPar->value;
                void *p = firstList(listaCat);
                while (p) {
                    if (p == producto) {
                        popCurrent(listaCat);
                        break;
                    }
                    p = nextList(listaCat);
                }
            }

            // Eliminar de listaProductos
            eliminarDeArrayList(listaProductos, producto);

            // Eliminar de la cola de novedades (con cola auxiliar)
            Queue *colaAux = createQueue(MAX_NOVEDADES);
            while (!isEmpty(colaNovedades)) {
                Producto *productoQ = dequeue(colaNovedades);
                if (productoQ != producto) {
                    enqueue(colaAux, productoQ);
                }
            }
            // Restaurar productos a la cola original
            while (!isEmpty(colaAux)) {
                enqueue(colaNovedades, dequeue(colaAux));
            }
            free(colaAux);

            // Liberar memoria del producto
            free(producto);

            limpiarPantalla();
            printf("\nProducto eliminado correctamente.\n");
            break;
        }
        else if (opcion == '2'){
            limpiarPantalla();
            puts("Accion cancelada.");
            break;
        } else {
            puts("Error: Caracter invalido.");
        }
    }
    presioneTeclaParaContinuar();
}

// Muestra los últimos productos agregados a la cola de novedades.
// Permite al usuario agregar alguno al carrito.
void revisarNovedades(Queue *colaNovedades, List *carro) {
    limpiarPantalla();
    if (isEmpty(colaNovedades)) {
        puts("No hay novedades en el catalogo.");
        presioneTeclaParaContinuar();
        return;
    }

    puts("Novedades recientes del catalogo:");

    Producto *productos[10]; // Arreglo de productos para añadir a carro
    int cantidad = 0;

    Queue *colaAux = createQueue(colaNovedades->maxSize);

    while (!isEmpty(colaNovedades)) {
        Producto *producto = dequeue(colaNovedades);

        if (cantidad < 10) {
            productos[cantidad++] = producto;
        }

        mostrarProducto(producto);
        enqueue(colaAux, producto);  // Guardar en cola auxiliar
    }

    puts("----------------------------------------");

    // Restaurar cola original
    while (!isEmpty(colaAux)) {
        enqueue(colaNovedades, dequeue(colaAux));
    }
    free(colaAux);

    // Permitir seleccionar producto para agregar al carrito
    puts("Desea agregar algun producto al carro?");
    puts("1) Seleccionar producto");
    puts("2) Volver al menu");
    printf("Ingrese su opcion: ");
    while (1){
        char opcion;
        scanf(" %c", &opcion);
        while (getchar() != '\n');

        if (opcion == '1'){
            limpiarPantalla();
            seleccionarProductosParaCarro(productos, cantidad, carro);
            break;
        }
        else if (opcion == '2'){
            limpiarPantalla();
            puts("Volviendo al menu.");
            break;
        } else {
            puts("Error: Caracter invalido.");
            printf("Ingrese su opcion nuevamente: ");
        }
    }
    presioneTeclaParaContinuar();
}

// Busca un producto por su nombre usando el mapa correspondiente.
// Permite agregarlo al carrito si se encuentra.
void buscarPorNombre(Map *mapaPorNombres, List *listaCarro) {
    limpiarPantalla();

    char nombre[MAX_NOMBRE];
    printf("Ingrese el nombre del producto a buscar: ");
    
    limpiarBuffer();

    // Leer el nombre y quitar el salto de línea
    fgets(nombre, sizeof(nombre), stdin);
    nombre[strcspn(nombre, "\n")] = '\0';

    MapPair *par = map_search(mapaPorNombres, nombre);
    if (!par) {
        puts("No se encontraron productos con ese nombre.");
        presioneTeclaParaContinuar();
        return;
    }

    Producto *producto = (Producto *)par->value;
    mostrarProducto(producto);

    // Preguntar si desea agregar al carro
    puts("----------------------------------------");
    puts("Desea agregar este producto al carrito?");
    puts("1) Si");
    puts("2) No");
    char opcion;
    scanf(" %c", &opcion);
    limpiarBuffer();

    if (opcion == '1') {
        limpiarPantalla();
        agregarAlCarro(listaCarro, producto);
    } else {
        limpiarPantalla();
        puts("Producto no agregado.");
    }
    presioneTeclaParaContinuar();
}

// Muestra productos con stock menor a 5 unidades.
void consultarStock(Map *mapaPorId) {
    limpiarPantalla();
    puts("Productos con stock bajo (menos de 5 unidades):");
    int encontrado = 0;

    MapPair *par = map_first(mapaPorId);
    while (par) {
        Producto *producto = (Producto *)par->value;
        if (producto->stock < 5) {
            mostrarProducto(producto);
            encontrado = 1;
        }
        par = map_next(mapaPorId);
    }

    if (!encontrado) {
        puts("No hay productos con stock bajo.");
    }
    presioneTeclaParaContinuar();
}

// Muestra el catálogo completo por páginas de 10 productos,
// y permite agregar productos al carrito.
void verCatalogo(ArrayList *listaProductos, List *listaCarro) {
    limpiarPantalla();

    void *producto = firstListArray(listaProductos);
    if (!producto) {
        puts("No hay productos en el catalogo.");
        presioneTeclaParaContinuar();
        return;
    }

    int pagina = 0;
    const int porPagina = 10;

    while (1) {
        limpiarPantalla();

        Producto *productos[porPagina];
        int contador = 0;

        producto = firstListArray(listaProductos);
        int i = 0;

        // Avanzar hasta el comienzo de la pagina actual
        while (producto && i < pagina * porPagina) {
            producto = nextListArray(listaProductos);
            i++;
        }

        // Mostrar hasta 10 productos de esta pagina
        while (producto && contador < porPagina) {
            mostrarProducto((Producto *)producto);
            productos[contador++] = producto;
            producto = nextListArray(listaProductos);
        }

        // Si no se mostraron productos, retroceder y avisar
        if (contador == 0) {
            pagina--;
            limpiarPantalla();
            puts("Ya estas en la ultima pagina.");
            presioneTeclaParaContinuar();
            continue;
        }

        puts("----------------------------------------");
        printf("                Pagina %d\n", pagina + 1);
        puts("----------------------------------------");
        puts("                OPCIONES");
        puts("1) Agregar producto(s) al carro");
        puts("2) Siguiente pagina");
        puts("3) Pagina anterior");
        puts("0) Volver al menu principal");
        printf("Ingrese una opcion: ");

        char opcion;
        scanf(" %c", &opcion);
        limpiarBuffer();

        if (opcion == '1') {
            limpiarPantalla();
            seleccionarProductosParaCarro(productos, contador, listaCarro);
            presioneTeclaParaContinuar();
        } else if (opcion == '2') {
            pagina++;
        } else if (opcion == '3') {
            if (pagina > 0) {
                pagina--;
            } else {
                limpiarPantalla();
                puts("Ya estas en la primera pagina.");
                presioneTeclaParaContinuar();
            }
        } else if (opcion == '0') {
            limpiarPantalla();
            puts("Volviendo al menu.");
            break;
        } else {
            puts("Opcion invalida.");
            presioneTeclaParaContinuar();
        }
    }
    presioneTeclaParaContinuar();
}

// Muestra productos pertenecientes a una categoría específica, paginados.
// También permite agregar productos al carrito.
void verPorCategoria(Map *mapaPorCategorias, List *listaCarro) {
    limpiarPantalla();

    char categoriaBuscada[MAX_CATEGORIA];
    printf("Ingrese la categoria de productos que le interese: ");
    scanf(" %[^\n]", categoriaBuscada); // Leer cadena con espacios
    limpiarBuffer();

    MapPair *par = map_search(mapaPorCategorias, categoriaBuscada);

    if (!par || !par->value) {
        puts("No se encontraron productos para esta categoria.");
        presioneTeclaParaContinuar();
        return;
    }

    List *lista = (List *)par->value;
    const int porPagina = 10;
    int pagina = 0;

    while (1) {
        limpiarPantalla();
        
        Producto *productos[porPagina];
        int cantidadTotal = 0;

        void *dato = firstList(lista);
        while (dato) {
            cantidadTotal++;
            dato = nextList(lista);
        }

        if (cantidadTotal == 0) {
            puts("No hay productos disponibles en esta categoria.");
            presioneTeclaParaContinuar();
            return;
        }

        // Avanzar a la pagina deseada
        dato = firstList(lista);
        int i = 0;
        while (dato && i < pagina * porPagina) {
            dato = nextList(lista);
            i++;
        }
        printf("Productos encontrados de la categoria '%s':\n", categoriaBuscada);

        // Mostrar hasta 10 productos de la pagina actual
        int contador = 0;
        while (dato && contador < porPagina) {
            Producto *producto = (Producto *)dato;
            mostrarProducto(producto);
            productos[contador++] = producto;
            dato = nextList(lista);
        }

        if (contador == 0) {
            pagina--;
            limpiarPantalla();
            puts("Ya estas en la ultima pagina.");
            presioneTeclaParaContinuar();
            continue;
        }

        puts("----------------------------------------");
        printf("                Pagina %d\n", pagina + 1);
        puts("----------------------------------------");
        puts("                OPCIONES");
        puts("1) Agregar producto(s) al carro");
        puts("2) Siguiente pagina");
        puts("3) Pagina anterior");
        puts("0) Volver al menu principal");
        printf("Ingrese una opcion: ");

        char opcion;
        scanf(" %c", &opcion);
        limpiarBuffer();

        if (opcion == '1') {
            limpiarPantalla();
            seleccionarProductosParaCarro(productos, contador, listaCarro);
            presioneTeclaParaContinuar();
        } else if (opcion == '2') {
            pagina++;
        } else if (opcion == '3') {
            if (pagina > 0) pagina--;
            else {
                limpiarPantalla();
                puts("Ya estas en la primera pagina.");
                presioneTeclaParaContinuar();
            }
        } else if (opcion == '0') {
            limpiarPantalla();
            puts("Volviendo al menu.");
            break;
        } else {
            puts("Opcion invalida.");
            presioneTeclaParaContinuar();
        }
    }
    presioneTeclaParaContinuar();
}

// Muestra todos los pedidos pendientes de ser procesados sin eliminarlos de la cola.
void mostrarPedidosPendientes(Queue *colaPedidos) {
    limpiarPantalla();

    if (isEmpty(colaPedidos)) {
        puts("No hay pedidos pendientes.");
        presioneTeclaParaContinuar();
        return;
    }

    puts("Pedidos pendientes:");

    Queue *colaAux = createQueue(colaPedidos->maxSize);
    int contador = 1;

    while (!isEmpty(colaPedidos)) {
        Pedido *pedido = (Pedido *)dequeue(colaPedidos);
        puts("----------------------------------------------");
        printf("Pedido #%d\n", contador++);
        printf("Nombre cliente: %s\n", pedido->nombreCliente);
        printf("Telefono: %s\n", pedido->telefono);
        printf("Direccion: %s\n", pedido->direccion);
        puts("Productos encargados:");

        void *prod = firstList(pedido->productos);
        while (prod) {
            Producto *producto = (Producto *)prod;
            printf("- %s (ID: %d | Precio: $%d | Stock: %d)\n",
                   producto->nombre, producto->id, producto->precio, producto->stock);
            prod = nextList(pedido->productos);
        }

        enqueue(colaAux, pedido);
    }
    puts("----------------------------------------------");

    // Restaurar cola original
    while (!isEmpty(colaAux)) {
        enqueue(colaPedidos, dequeue(colaAux));
    }

    free(colaAux);
    presioneTeclaParaContinuar();
}

// Procesa los pedidos uno por uno permitiendo al administrador aceptarlos (libera memoria)
// o reenviarlos a la cola si decide no procesarlos.
void procesarPedidos(Queue *colaPedidos) {
    limpiarPantalla();

    if (isEmpty(colaPedidos)) {
        puts("No hay pedidos para procesar.");
        presioneTeclaParaContinuar();
        return;
    }

    Queue *colaTemporal = createQueue(0);

    while (!isEmpty(colaPedidos)) {
        limpiarPantalla();
        Pedido *pedido = dequeue(colaPedidos);

        // Mostrar información del pedido
        puts("----- Pedido pendiente -----");
        printf("ID Pedido: %d\n", pedido->idPedido);
        printf("Cliente: %s\n", pedido->nombreCliente);
        printf("Telefono: %s\n", pedido->telefono);
        printf("Direccion: %s\n", pedido->direccion);

        puts("Productos del pedido:");
        void *prod = firstList(pedido->productos);
        while (prod) {
            Producto *producto = (Producto *)prod;
            printf("- %s (ID: %d | Precio: $%d | Stock: %d)\n",
                   producto->nombre, producto->id, producto->precio, producto->stock);
            prod = nextList(pedido->productos);
        }

        puts("----------------------------");
        puts("Desea procesar este pedido?");
        puts("1) Procesar y eliminar pedido");
        puts("2) Saltar y ver siguiente pedido");
        puts("3) Cancelar proceso y salir");
        printf("Ingrese una opcion: ");

        char opcion;
        scanf(" %c", &opcion);
        limpiarBuffer();

        if (opcion == '1') {
            cleanList(pedido->productos, NULL);  // Solo limpiar lista
            free(pedido);
            puts("Pedido procesado exitosamente.");
            presioneTeclaParaContinuar();
            limpiarPantalla();
        } 
        else if (opcion == '2') {
            enqueue(colaTemporal, pedido); // Volver a encolar al final
            puts("Pedido saltado. Pasando al siguiente...");
            presioneTeclaParaContinuar();
        }
        else if (opcion == '3') {
            enqueue(colaTemporal, pedido); // Reencolar y salir
            puts("Proceso de pedidos cancelado.");
            break;
        } else {
            puts("Opcion invalida. Reenviando el pedido al final de la cola.");
            enqueue(colaTemporal, pedido);
            presioneTeclaParaContinuar();
        }
    }

    // Reinsertar los pedidos no procesados
    while (!isEmpty(colaTemporal)) {
        enqueue(colaPedidos, dequeue(colaTemporal));
    }

    freeQueue(colaTemporal);

    limpiarPantalla();

    if (isEmpty(colaPedidos)) {
        puts("Todos los pedidos han sido procesados :)");
    }
    else {
        puts("Fin de proceso de pedidos.");
    }
    presioneTeclaParaContinuar();
}

// Ofrece al administrador un submenú para mostrar o procesar pedidos.
void gestionarPedidos(Queue *colaPedidos){
    limpiarPantalla();
    while(1){
        puts("-----Opciones de gestion-----");
        puts("1) Mostrar pedidos pendientes");
        puts("2) iniciar proceso de pedidos");
        puts("3) Regresar al menu");
        printf("Ingrese una opcion: ");
        char opcion;
        scanf(" %c", &opcion);
        limpiarBuffer();

        if (opcion == '1'){
            mostrarPedidosPendientes(colaPedidos);
            limpiarPantalla();
        }
        else if (opcion == '2'){
            procesarPedidos(colaPedidos);
            limpiarPantalla();
        }
        else if (opcion == '3'){
            limpiarPantalla();
            puts("Regresando al menu.");
            break;
        } else {
            limpiarPantalla();
            puts("Error: Caracter invalido.");
        }
    }
    presioneTeclaParaContinuar();
}

// Menú principal del carrito: permite mostrar, editar o encargar productos. Utiliza funciones en extra.h
void verCarrito(List *listaCarro, ArrayList *listaProductos, Queue *colaPedidos) {
    char op[10];

    while (1) {
        limpiarPantalla();
        mostrarMenuCarrito();
        scanf("%s", op);

        if (strcmp(op, "1") == 0) {
            mostrarCarro(listaCarro);
            presioneTeclaParaContinuar();
        } else if (strcmp(op, "2") == 0) {
            eliminarDelCarro(listaCarro);
        } else if (strcmp(op, "3") == 0) {
            encargarProductos(listaCarro, colaPedidos);
        } else if (strcmp(op, "4") == 0) {
            limpiarPantalla();
            printf("Volviendo al menu principal...\n");
            break;
        } else {
            printf("Opcion invalida, intentelo de nuevo.\n");
        }
    }
}


// Cambia la clave del administrador, asegurando que tenga 4 dígitos y sea confirmada.
void cambiarClave(char *claveAdmin) {
    limpiarPantalla();
    
    char nuevaClave[10];
    char confirmarClave[10];

    printf("Ingrese una nueva clave de 4 digitos: ");
    scanf("%s", nuevaClave);
    limpiarBuffer();

    if (strlen(nuevaClave) != 4) {
        puts("Error: La clave debe tener exactamente 4 digitos.");
        presioneTeclaParaContinuar();
        return;
    }

    printf("Confirme la nueva clave: ");
    scanf("%s", confirmarClave);
    limpiarBuffer();

    if (strcmp(nuevaClave, confirmarClave) != 0) {
        puts("Error: Las claves no coinciden.");
        presioneTeclaParaContinuar();
        return;
    }

    // Cambiar la clave
    strcpy(claveAdmin, nuevaClave);
    puts("Clave cambiada exitosamente.");
    presioneTeclaParaContinuar();
}

// Muestra el menú administrador y permite ejecutar operaciones como agregar, modificar,
// eliminar productos, revisar stock bajo, gestionar pedidos o cambiar la clave.
void modoAdmin(Map *mapaPorId, Map *mapaPorCategorias, Map *mapaPorNombres, ArrayList *listaProductos, List *listaCarro, Queue *colaPedidos, Queue *colaNovedades, char *claveAdmin) {
    while (1) {
        limpiarPantalla();
        mostrarMenuAdmin();
        char op[10];
        printf("Ingrese su opcion: ");
        scanf("%s", op);

        if (strcmp(op,"1") == 0) agregarProducto(mapaPorId, mapaPorNombres, mapaPorCategorias, listaProductos, colaNovedades); //1. Agregar producto.
        else if (strcmp(op, "2") == 0) modificarProducto(mapaPorId, mapaPorNombres, mapaPorCategorias, listaProductos);//2. Modificar producto.
        else if (strcmp(op, "3") == 0) eliminarProducto(mapaPorId, mapaPorNombres, mapaPorCategorias, listaProductos, colaNovedades); //3. Eliminar producto.
        else if (strcmp(op, "4") == 0) consultarStock(mapaPorId);//4. Consultar stock bajo.
        else if (strcmp(op, "5") == 0) gestionarPedidos(colaPedidos);//5. Gestionar pedidos de clientes.
        else if (strcmp(op, "6") == 0) cambiarClave(claveAdmin);//6. Cambiar clave de administrador.
        else if (strcmp(op, "7") == 0) {  //7. Salir del modo administrador.
            printf("Volviendo al menu principal...\n");
            break;
        }
        else printf("Respuesta invalida, intentelo de nuevo.\n");
    }
}

// Crea los TDAs principales, muestra el menú y ejecuta la funcionalidad
// seleccionada por el usuario. Incluye verificación de clave para modo admin.
void ejecutarAplicacion() {
    Map *mapaPorId = map_create_int();
    Map *mapaPorNombres = map_create_string();
    Map *mapaPorCategorias = map_create_string();
    ArrayList *listaProductos = createArrayList();
    List *listaCarro = createList();
    Queue *colaNovedades = createQueue(MAX_NOVEDADES);
    Queue *colaPedidos = createQueue(0);
    char claveAdmin[5] = "0000";

    while (1) {
        limpiarPantalla();
        mostrarMenuPrincipal();
        char op[10];
        puts("Ingrese su opcion: ");
        scanf("%s", op);

        if (strcmp(op,"1") == 0) revisarNovedades(colaNovedades, listaCarro); //1. Revisar novedades.
        else if (strcmp(op, "2") == 0) verCatalogo(listaProductos, listaCarro); //2. Ver catálogo completo.
        else if (strcmp(op, "3") == 0) buscarPorNombre(mapaPorNombres, listaCarro); //3. Buscar producto por nombre.
        else if (strcmp(op, "4") == 0) verPorCategoria(mapaPorCategorias, listaCarro);//4. Ver productos por categoría.
        else if (strcmp(op, "5") == 0) verCarrito(listaCarro, listaProductos, colaPedidos);//5. Ver carrito de compras y encargar.
        else if (strcmp(op, "6") == 0){ //6. Ingresar al modo administrador.
            limpiarPantalla();
            int claveCorrecta = 0;
            char claveIngresada[10];
            while (1) {
                printf("Ingrese la clave de administrador (4 digitos) o ingrese 0 para regresar: ");
                scanf("%9s", claveIngresada);

                if (strcmp(claveIngresada, "0") == 0) {
                    limpiarPantalla();
                    puts("Ingreso de clave cancelado. Volviendo al menu principal.");
                    break;
                }
                if (strlen(claveIngresada) != 4) {
                    limpiarPantalla();
                    puts("La clave debe tener exactamente 4 digitos.");
                    continue;
                }

                if (strcmp(claveIngresada, claveAdmin) == 0) {
                    claveCorrecta = 1;
                    break;
                } else {
                    limpiarPantalla();
                    puts("Clave incorrecta, intente nuevamente.");
                }
            }

            if (claveCorrecta){
                modoAdmin(mapaPorId, mapaPorCategorias, mapaPorNombres, listaProductos, listaCarro, colaPedidos, colaNovedades, claveAdmin);
            }
        }
        else if (strcmp(op, "7") == 0) {  //7. Salir del programa.
            limpiarPantalla();
            printf("Saliendo del programa...\n");
            break;
        }
        else printf("Respuesta invalida, intentelo de nuevo.\n");
    }
}

// Función principal del programa.
int main() {
    ejecutarAplicacion();
    printf("Programa Finalizado.");
    return 0;
}