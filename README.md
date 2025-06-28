
# APLICACIÓN DE GESTIÓN PARA TIENDAS MINORISTAS


## DESCRIPCIÓN
Esta aplicación permite a los usuarios la gestión de compras al interior de una tienda pequeña o mediana. Esta herramienta está diseñada para las tiendas minoristas que buscan automatizar procesos de inventario de productos y pedidos de clientes. Mejorando la eficacia y el control de estas.

**La aplicación opera con dos modalidades principales:**

- **Modo de cliente**: Permite funcionalidades como ver los productos más recientes o novedosos, consultar el catálogo de productos, buscar productos ya sea por nombre o por categoría, gestionar un carrito de compras y realizar encargos de pedidos.

- **Modo de administrador**: Ofrece funcionalidades de gestión de inventario para el administrador de la tienda. Permitiendo agregar, modificar y eliminar productos, consultar productos que posean bajo stock y procesar los pedidos de los clientes.


## ¿CÓMO COMPILAR Y EJECUTAR?
Este sistema se desarrolló en lenguaje C y puede ejecutarse utilizando Visual Studio Code, junto con una entensión para C/C++ como C/C++ Extension Pack de Microsoft.

Para comenzar a trabajar con la aplicación debes tener en cuenta lo siguiente:

### REQUISITOS PREVIOS:
- Tener instalado [Visual Studio Code](https://code.visualstudio.com/).
- Instalar la extensión C/C++ de Microsoft.
- Tener instalado un compilador de C (como gcc). Si estás en Windows, se recomienda instalar [MinGW](https://www.mingw-w64.org/) o utilizar el entorno [WSL](https://learn.microsoft.com/en-us/windows/wsl/).


### PASOS PARA COMPILAR Y EJECUTAR:
1. Descargar y descomprimir el archivo zip en una carpeta a libre elección.

2. Abre el proyecto en Visual Studio Code.
    - Inicia Visual Studio Code.
    - Selecciona, en la esquina superior izquierda o en el inicio de Visual, 'Archivo > Abrir Carpeta ...' y se elige la carpeta donde se descomprimió el proyecto.

3. Compilar código:
    - Abre el archivo principal de la aplicación (main.c en este caso).
    - Abre la terminal, en este caso la terminal de bash ('Terminal > Git Bash').
    - En la terminal bash, compila el programa con el siguiente comando (puedes copiarlo y pegarlo en la terminal):

>gcc main.c tdas/map.c tdas/linkedlist.c tdas/arraylist.c tdas/queue.c tdas/extra.c -I. -o test

4. Ejecutar el programa:
    - Si ya tienes compilado tu programa, ahora puedes ejecutarlo con esto (también se puede copiar y pegar en la terminal):

>./test

- Debería salirte una ventana emergente donde se puede ejecutar correctamente la aplicación. En caso de tener antivirus puede cerrarse esta ventana emergente, pero no hay problema, la ejecución se puede realizar en la misma terminal.

## PARA CREAR UN ARCHIVO CSV
La aplicación permite al administrador agregar productos, dando la opción de hacerlo manual o ingresando un archivo csv. Es claro que la segunda alternativa para el caso de la administración de una tienda es la más viable, asi que es importante que la persona que administra sepa cómo debe estar compuesto este archivo csv. 

La primera línea debe estar compuesta por el siguiente texto:

>ID;Nombre;Categoría;Precio;Stock

Y seguido a este, deben ir línea por línea los datos de cada producto. Por ejemplo:

>01;Tomates;Verduras;300;80

>02;Audífonos;Electrónicos;5000;10

>03;Leche;Lácteos;1000;50

>04;Cloro;Limpieza;2500;20

>05;Tijeras escolares;Papelería;1500;15

La aplicación como tal tiene ya un archivo csv de ejemplo, llamado "Ejemplo_productos.csv", este contiene 50 productos diferentes que sirven tanto para tener un ejemplo de cómo debe estar hecho el csv, como también para hacer prueba del programa y ver su funcionalidad.

**Considera que los datos que deben estar en cada producto son:**

- **ID :** dato de tipo entero, es como un código para identificar el producto por parte de la administración.
- **Nombre :** Caracteres con el nombre del producto.
- **Categoría :** Caracteres con la categoría a la que corresponde el producto.
- **Precio :** Dato de tipo entero, con el precio del producto individual.
- **Stock :** Dato de tipo entero, con la cantidad total de unidades del producto.


## FUNCIONALIDADES:
**Menú principal (Modo Cliente):**
1. **Revisar novedades:** Muestra los últimos 10 productos agregados al catálogo. Permite al usuario ver los detalles de cada producto y seleccionar alguno para agregarlo al carrito de compras.

2. **Ver catalogo completo:** Permite visualizar todos los productos disponibles en el inventario, ordenandolos alfabeticamente por nombre.

3. **Buscar productos por nombre:** Se ingresa el nombre del producto y en caso de que exista, se muestran sus datos.

4. **Ver productos por categoria:** Se ingresa el nombre de la categoria a buscar y si es que existe, muestra todos los productos de esa categoria con sus respectivos datos.

5. **Ver carrito de compras y encagar:** El usuario puede ver los productos que han sido agregados en el carrito, permitiendo opciones como editar el carrito (añadir o eliminar el producto) y realizar el encargo. Al momento de realizar el encargo del pedido, se deben ingresar datos personales.

6. **Ingresar al modo administrador:** Se solicita una clave de acceso, pero si es la primera vez que se ingresa, la clave de acceso por defecto es "0000". Esto permite ingresar al submenú del modo administrador.

**Modo administrador:**
1. **Agregar producto:** Permite agregar productos, para esto existen dos alternativas:
    1) Cargar archivo CSV: Se introduce la ruta de acceso al csv y esto hace que todos los productos de este archivo ingresen al programa.
    2) Ingresar producto manualmente: Se puede introducir un producto a la vez, se solicitan uno a uno los datos de este producto y se ingresan al programa.

2. **Modificar producto:** Permite editar los datos de un producto existente, para esto se ingresa el ID del producto y se pregunta que se desea modificar, luego de seleccionar una opción, se escriben los cambios y se realiza la modificación especifica.

3. **Eliminar producto:** Permite eliminar un producto existente, para esto se ingresa el ID de este producto para proceder con su eliminación.

4. **Consultar stock bajo:** Para que el administrador sepa que se debe reponer. Se muestra un listado con los datos de productos que tengan un stock menor a 5.

5. **Gestionar pedidos de clientes:** Permite al administrador ver y procesar los pedidos realizados por clientes. Para esto se muestran dos opciones:
    1) Ver pedidos pendientes: Se mostrarán todos los pedidos actuales sin procesar y con la infromación de cada uno.
    2) Procesar pedido: Se pregunta si se desea procesar el pedido más antiguo, en caso de confirmar esto, este pedido se procesará automaticamente.

6. **Cambiar clave de administrador:** Permite modificar la clave de ingreso al modo administrador, solicitando la clave por la que se desea cambiar y realizando otra solicitud como método de confirmación.


## ASPECTOS A CONSIDERAR:

Como ya se mencionó antes, al momento de ejecutar pueden haber casos donde el antivirus cierre la ventana emergente donde se ejecuta la aplicación. Pero se puede solucionar o desactivando el antivirus o trabajando directamente con lo que aparece en la terminal.

La aplicación funciona solo si la terminal o la ventana emergente están abiertas, en caso de cerrarse, la información de los productos se borrará. Aunque es algo mejorable a futuro.


## EJEMPLO VISUAL:

**MENÚ PRINCIPAL:**
```
---------------------------------------------
MENU PRINCIPAL - SELECCIONE UNA OPCION:
---------------------------------------------
1. Revisar novedades.
2. Ver catalogo completo.
3. Buscar producto por nombre.
4. Ver productos por categoria.
5. Ver carrito de compras y encargar.
6. Ingresar al modo administrador.
7. Salir del programa.
Ingrese su opcion:

1 (Revisar novedades)
No hay novedades en el catalogo.
Presione ENTER para continuar...

2 (Ver catalogo completo)
No hay productos en el catalogo.
Presione ENTER para continuar...

3 (Buscar producto por nombre)
Ingrese el nombre del producto a buscar:

4 (Ver productos por categoria)
Ingrese la categoria de productos que le interese:

5 (Ver carrito de compras y encargar)
---------------------------------------------
CARRITO DE COMPRAS - SELECCIONE UNA OPCION:
---------------------------------------------
1. Mostrar carrito
2. Editar carrito
3. Encargar productos en el carrito
4. Volver

6 (Ingresar al modo administrador)
Ingrese la clave de administrador (4 digitos) o ingrese 0 para regresar:
```

**SUBMENU DEL MODO ADMINISTRADOR:**
```
---------------------------------------------
MODO ADMINISTRADOR - SELECCIONE UNA OPCION:
---------------------------------------------
1. Agregar producto.
2. Modificar producto.
3. Eliminar producto.
4. Consultar stock bajo.
5. Gestionar pedidos de clientes.
6. Cambiar clave de administrador.
7. Salir del modo administrador.
Ingrese su opcion:

1 (Agregar producto) 
Seleccione un modo de ingreso:
1) Cargar archivo CSV
2) Ingresar producto manualmente
3) Regresar al menu de administrador

2 (Modificar producto)
Ingrese el ID del producto a modificar:

3 (Eliminar producto)
Ingrese el ID del producto a eliminar:

4 (Consultar stock bajo)
Productos con stock bajo (menos de 5 unidades):       
No hay productos con stock bajo

5 (Gestionar pedidos de clientes)
-----Opciones de gestion-----
1) Mostrar pedidos pendientes
2) iniciar proceso de pedidos
3) Regresar al menu
Ingrese una opcion: 

6 (Cambiar clave de administrador)
Ingrese una nueva clave de 4 digitos:
```

**Proyecto realizado por:**
- Felipe Abarca
- Naomi Alveal
- Melani Sanchez
- Miguel Fuentes

**Es importante destacar que las contribuciones de cada estudiante están visualizables en el mismo link del github.**