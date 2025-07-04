#ifndef EXTRA_H
#define EXTRA_H

#include "tdas/arraylist.h"
#include "tdas/linkedlist.h"
#include "tdas/map.h"
#include "tdas/queue.h"

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

// Limpia la pantalla del terminal
void limpiarPantalla();

// Limpia el buffer de entrada del teclado
void limpiarBuffer();

// Espera que el usuario presione ENTER para continuar
void presioneTeclaParaContinuar();

// Función para comparar productos por nombre (para ordenamiento alfabético)
int compararPorNombre(const void *a, const void *b);

// Elimina un producto específico de un ArrayList
void eliminarDeArrayList(ArrayList *lista, void *dato);

// Muestra la información de un producto en consola
void mostrarProducto(Producto *producto);

// Agrega un producto al carro de compras
void agregarAlCarro(List *carro, Producto *producto);

// Muestra hasta max 10 productos y permite seleccionar para agregar al carro
void seleccionarProductosParaCarro(Producto **productos, int cantidad, List *carro);

// Extrae hasta max 10 productos de una List* en un arreglo Producto*[]
int obtenerProductosDeLista(List *lista, Producto **productos, int max);

// Valida si no contiene caracteres no permitidos
int validarNombre(const char *nombre);

// Valida si se ingresan numeros
int validarTelefono(const char *telefono);

// valida cuando no se escriba
int validarTextoNoVacio(const char *texto);

// Muestra el menú del carrito de compras con opciones disponibles
void mostrarMenuCarrito();

// Muestra todos los productos actualmente en el carrito
void mostrarCarro(List *listaCarro);

// Permite al usuario eliminar un producto específico del carrito
void eliminarDelCarro(List *listaCarro);

// Crea un nuevo pedido con los productos del carrito y lo añade a la cola de pedidos
void encargarProductos(List *listaCarro, Queue *colaPedidos);

#endif