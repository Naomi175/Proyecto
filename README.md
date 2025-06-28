===================================================
---APLICACIÓN DE GESTIÓN PARA TIENDAS MINORISTAS---
===================================================

`DESCRIPCIÓN`
Esta aplicación permite a los usuarios la gestión de compras al interior de una tienda pequeña o mediana. Esta herramienta está diseñada para las tiendas minoristas que buscan automatizar procesos de inventario de productos y pedidos de clientes. Mejorando la eficacia y el control de estas.

> La aplicación opera con dos modalidades principales:

- Modo de cliente: Permite funcionalidades como ver los productos más recientes o novedosos, consultar el catálogo de productos, buscar productos ya sea por nombre o por categoría, gestionar un carrito de compras y realizar encargos de pedidos.

- Modo de administrador: Ofrece funcionalidades de gestión de inventario para el administrador de la tienda. Permitiendo agregar, modificar y eliminar productos, consultar productos que posean bajo stock y procesar los pedidos de los clientes.


¿CÓMO COMPILAR Y EJECUTAR?
Este sistema se desarrolló en lenguaje C y puede ejecutarse utilizando Visual Studio Code, junto con una entensión para C/C++ como C/C++ Extension Pack de Microsoft.

Para comenzar a trabajar con la aplicación debes tener en cuenta lo siguiente:

REQUISITOS PREVIOS:
- Tener instalado Visual Studio Code (https://code.visualstudio.com/).
- Instalar la extensión C/C++ de Microsoft.
- Tener instalado un compilador de C (como gcc). Si estás en Windows, se recomienda instalar MinGW (https://www.mingw-w64.org/) o utilizar el entorno WSL (https://learn.microsoft.com/en-us/windows/wsl/).


PASOS PARA COMPILAR Y EJECUTAR:
1. Descargar y descomprimir el archivo zip en una carpeta a libre elección.

2. Abre el proyecto en Visual Studio Code.
    - Inicia Visual Studio Code.
    - Selecciona, en la esquina superior izquierda o en el inicio de Visual, 'Archivo > Abrir Carpeta ...' y se elige la carpeta donde se descomprimió el proyecto.

3. Compilar código:
    - Abre el archivo principal de la aplicación (main.c en este caso).
    - Abre la terminal, en este caso la terminal de bash ('Terminal > Git Bash').
    - En la terminal bash, compila el programa con el siguiente comando (puedes copiarlo y pegarlo en la terminal):

gcc main.c tdas/map.c tdas/linkedlist.c tdas/arraylist.c tdas/queue.c tdas/extra.c -I. -o test

4. Ejecutar el programa:
    - Si ya tienes compilado tu programa, ahora puedes ejecutarlo con esto (también se puede copiar y pegar en la terminal):

./test

- Debería salirte una ventana emergente donde se puede ejecutar correctamente la aplicación. En caso de tener antivirus puede cerrarse esta ventana emergente, pero no hay problema, la ejecución se puede realizar en la misma terminal.

FUNCIONALIDADES:
Menú principal (Modo Cliente):
1. Revisar novedades: Muestra los últimos 10 productos agregados al catálogo. Permite al usuario ver los detalles de cada producto y seleccionar alguno para agregarlo al carrito de compras.

2. Ver catalogo completo: Permite visualizar todos los productos disponibles en el inventario, ordenandolos alfabeticamente por nombre.

3. Buscar productos por nombre: Se ingresa el nombre del producto y en caso de que exista, se muestran sus datos.

4. Ver productos por categoria: Se ingresa el nombre de la categoria a buscar y si es que existe, muestra todos los productos de esa categoria con sus respectivos datos.

5. Ver carrito de compras y encagar: El usuario puede ver los productos que han sido agregados en el carrito, permitiendo opciones como editar el carrito (añadir o eliminar el producto) y realizar el encargo. Al momento de realizar el encargo del pedido, se deben ingresar datos personales.

6. Ingresar al modo administrador: Se solicita una clave de acceso, pero si es la primera vez que se ingresa, la clave de acceso por defecto es "0000". Esto permite ingresar al submenú del modo administrador.

Modo administrador:
1. Agregar producto: Permite agregar productos, para esto existen dos alternativas:
    1) Cargar archivo CSV: Se introduce la ruta de acceso al csv y esto hace que todos los productos de este archivo ingresen al programa.
    2) Ingresar producto manualmente: Se puede introducir un producto a la vez, se solicitan uno a uno los datos de este producto y se ingresan al programa.

2. Modificar producto: Permite editar los datos de un producto existente, para esto se ingresa el ID del producto y se pregunta que se desea modificar, luego de seleccionar una opción, se escriben los cambios y se realiza la modificación especifica.

3. Eliminar producto: Permite eliminar un producto existente, para esto se ingresa el ID de este producto para proceder con su eliminación.

4. Consultar stock bajo: Para que el administrador sepa que se debe reponer. Se muestra un listado con los datos de productos que tengan un stock de 10 a menos.

5. Gestionar pedidos de clientes: Permite al administrador ver y procesar los pedidos realizados por clientes. Para esto se muestran dos opciones:
    1) Ver pedidos pendientes: Se mostrarán todos los pedidos actuales sin procesar y con la infromación de cada uno.
    2) Procesar pedido: Se pregunta si se desea procesar el pedido más antiguo, en caso de confirmar esto, este pedido se procesará automaticamente.

6. Cambiar clave de administrador: Permite modificar la clave de ingreso al modo administrador, solicitando nuevamente la clave actual y también solicitando la clave por la que se desea cambiar. Este cambio ocurrirá solo si las claves son distintas, ya que si son iguales, la modificación sería innecesaria.


ASPECTOS A CONSIDERAR:

Como ya se mencionó antes, al momento de ejecutar pueden haber casos donde el antivirus cierre la ventana emergente donde se ejecuta la aplicación. Pero se puede solucionar o desactivando el antivirus o trabajando directamente con lo que aparece en la terminal.



EJEMPLO DE USO DE FUNCIONES: