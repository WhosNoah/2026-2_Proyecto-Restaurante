# Modulos - Proyecto 7 | Sistema de Restaurante
Este documento explica la funcion de cada modulo de este proyecto, que estructuras y funciones expone y como se relacionan entre si.

## 1. Vision General
El sistema administra un restaurante desde consola:
- Un menu de platillos con categoria y precio.
- Un conjunto de mesas que se abren y cierran.
- Una comanda por mesa (los platillos que se piden)
- El calculo de la cuenta: desglose de IVA y division entre comensales
- Un reporte de ventas por mesero y por platillo.

### Arquitectura por capas.
```
┌─────────────────────────────────────────────┐
│ ui            → menú principal / bucle      │
├─────────────────────────────────────────────┤
│ flujos        → pasos interactivos          │
│ pedirpropina  → entrada del % de propina    │
├─────────────────────────────────────────────┤
│ cuenta        → cálculos de dinero          │
│ mesa          → mesas, meseros, ventas      │
│ comanda       → pedido de una mesa          │
│ menu          → catálogo de platillos       │
│ datos         → carga de datos iniciales    │
├─────────────────────────────────────────────┤
│ adds          → utilidades de entrada/cadena│
└─────────────────────────────────────────────┘
```

### Tabla de resumen.
| Módulo | Responsabilidad | Estructuras principales |
|---|---|---|
| `adds` | Utilidades de lectura y cadenas | — |
| `menu` | Catálogo de platillos | `Platillo`, `CategoriaPlatillo` |
| `comanda` | Pedido de una mesa | `RenglonComanda`, `Comanda` |
| `mesa` | Mesas, meseros y ventas | `Mesa`, `EstadoMesa`, `VentaMesero` |
| `cuenta` | IVA, propina y división de cuenta | `DesgloseCuenta` |
| `pedirpropina` | Pedir el % de propina al usuario | — |
| `datos` | Datos de arranque | — |
| `flujos` | Operaciones completas de cara al usuario | — |
| `ui` | Menú principal y ejecución del sistema | — |
 
---

## 2. `adds.h` - Utilidades generales.
**Proposito:** Este archivo incluye varias funciones auxiliares para leer datos del usuario de forma segura y manejar cadenas. Es la base del proyecto; casi todos los modulos de interfaz la incluyen.

| Función | Descripción |
|---|---|
| `void quitarSaltoLinea(char *cadena)` | Elimina el `\n` final que deja `fgets`. |
| `void leerCadena(const char *prompt, char *destino, int tamMax)` | Muestra un mensaje y lee una cadena sin desbordar el buffer. |
| `int leerEntero(const char *prompt)` | Lee un entero validando la entrada. |
| `double leerDouble(const char *prompt)` | Lee un número decimal validando la entrada. |
| `void copiarCadena(char *destino, const char *origen, int tamMax)` | Copia una cadena respetando el tamaño máximo (alternativa segura a `strcpy`). |
 
**Depende de:** solo de la biblioteca estándar.
 
---

## 3. `menu.h` — Catálogo de platillos
 
**Propósito:** guarda y consulta los platillos que ofrece el restaurante.
 
### Constantes
 
- `MAX_PLATILLOS` (30): capacidad del menú.
- `MAX_NOMBRE_PLATILLO` (50): longitud máxima del nombre.
### Tipos
 
```c
typedef enum {
    CAT_ENTRADA = 1, CAT_PLATO_FUERTE, CAT_BEBIDA, CAT_POSTRE
} CategoriaPlatillo;
 
typedef struct {
    int id;
    char nombre[MAX_NOMBRE_PLATILLO];
    CategoriaPlatillo categoria;
    double precio;
    int unidadesVendidas;   // acumulado para el reporte de ventas
} Platillo;
```
 
### Funciones
 
| Función | Descripción |
|---|---|
| `inicializarMenu` | Deja el menú vacío (total = 0). |
| `registrarPlatilloMenu` | Agrega un platillo (id, nombre, categoría, precio). Devuelve un código de éxito/error. |
| `buscarPlatilloPorId` | Devuelve el índice del platillo en el arreglo (o un valor de "no encontrado"). |
| `obtenerNombreCategoria` | Convierte la categoría (enum) a texto para mostrarla. |
| `mostrarMenu` | Imprime el menú, normalmente agrupado por categoría. |
 
**Depende de:** biblioteca estándar.
 
---
 
## 4. `comanda.h` — Pedido de una mesa
 
**Propósito:** representa lo que ha pedido una mesa: una lista de renglones con platillo, cantidad y nota.
 
### Constantes
 
- `MAX_RENGLONES` (40): máximo de renglones distintos por comanda.
- `MAX_NOTA` (80): longitud máxima de la nota (ej. "sin cebolla").
### Tipos
 
```c
typedef struct {
    int idPlatillo;
    char nombrePlatillo[MAX_NOMBRE_PLATILLO];
    double precioUnitario;   // copia del precio al momento de pedir
    int cantidad;
    char nota[MAX_NOTA];
} RenglonComanda;
 
typedef struct {
    RenglonComanda items[MAX_RENGLONES];
    int totalRenglones;
} Comanda;
```
 
> El renglón guarda una **copia** del nombre y del precio, de modo que la comanda no cambia si el menú se modifica después.
 
### Funciones
 
| Función | Descripción |
|---|---|
| `inicializarComanda` | Vacía la comanda. |
| `buscarRenglonPorId` | Busca si ya existe un renglón para ese platillo. |
| `eliminarRenglonEnIndice` | Borra un renglón y recorre los siguientes (función auxiliar interna). |
| `agregarPlatillo` | Valida el platillo contra el menú y lo agrega (o suma cantidad si ya existía). |
| `quitarPlatillo` | Resta cantidad; si llega a 0, elimina el renglón. |
| `totalComanda` | Suma `precioUnitario × cantidad` de todos los renglones. |
| `mostrarComanda` | Imprime el detalle del pedido. |
 
**Depende de:** `adds.h`, `menu.h`.
 
---
 
## 5. `mesa.h` — Mesas, meseros y ventas
 
**Propósito:** es el módulo central. Controla el estado de cada mesa, quién la atiende y acumula las ventas por mesero.
 
### Constantes
 
- `MAX_MESAS` (20), `MAX_MESEROS` (10), `MAX_NOMBRE_MESERO` (40).
### Tipos
 
```c
typedef enum { MESA_LIBRE = 0, MESA_ABIERTA = 1 } EstadoMesa;
 
typedef struct {
    int numero;
    int capacidad;
    EstadoMesa estado;
    char mesero[MAX_NOMBRE_MESERO];
    int comensales;
    Comanda comanda;        // la comanda vive dentro de la mesa
} Mesa;
 
typedef struct {
    char nombre[MAX_NOMBRE_MESERO];
    double totalVendido;
    int mesasAtendidas;
} VentaMesero;
```
 
### Funciones
 
| Función | Descripción |
|---|---|
| `inicializarMesas` | Pone el total de mesas en 0. |
| `registrarMesa` | Da de alta una mesa (número y capacidad). |
| `buscarMesaPorNumero` | Devuelve el índice de la mesa con ese número. |
| `inicializarVentasMeseros` | Vacía el arreglo de ventas por mesero. |
| `asegurarMesero` | Busca al mesero por nombre y, si no existe, lo crea. Devuelve su índice. |
| `abrirMesa` | Marca la mesa como abierta, asigna mesero y comensales, y reinicia la comanda. |
| `cerrarMesa` | Cobra la mesa: suma al mesero, incrementa `unidadesVendidas` de los platillos, libera la mesa y devuelve el total cobrado por `totalCobrado`. |
| `mostrarMapaMesas` | Imprime el estado de todas las mesas (libre/abierta, mesero, etc.). |
| `mostrarReporteVentas` | Reporte por mesero y por platillo. |
 
**Depende de:** `menu.h`, `comanda.h`.
 
---
 
## 6. `cuenta.h` — Cálculo de la cuenta
 
**Propósito:** toda la aritmética de dinero: separar el IVA, calcular la propina y dividir entre personas.
 
### Tipo
 
```c
typedef struct {
    double totalConIVA;
    double subtotal;
    double iva;
    double porcentajePropina;
    double propina;
    double totalAPagar;          // totalConIVA + propina
    int numPersonas;
    double montoPrimeraPersona;
    double montoRestoPersonas;
} DesgloseCuenta;
```
 
### Funciones
 
| Función | Descripción |
|---|---|
| `desglosarIVA` | A partir de un total que **ya incluye IVA**, obtiene subtotal e IVA (subtotal = total / (1 + tasa)). |
| `calcularPropina` | Propina = total × porcentaje / 100. |
| `dividirCuenta` | Reparte el total entre N personas. Devuelve un código de error si N es inválido. |
| `calcularCuentaMesa` | Junta todo: toma el total de la comanda de la mesa y llena un `DesgloseCuenta`. |
| `imprimirCuenta` | Imprime el ticket con el desglose completo. |
 
> **Sobre `montoPrimeraPersona` / `montoRestoPersonas`:** al dividir dinero casi nunca sale exacto en centavos. El diseño asigna a la primera persona el monto ajustado (con el residuo) y las demás pagan un monto igual, para que la suma sea exactamente el total. `math.h` se usa seguramente para redondear (`round`, `floor`, `ceil`).
 
**Depende de:** `mesa.h`, `math.h`.
 
---
 
## 7. `pedirpropina.h` — Entrada de propina
 
**Propósito:** aislar en un módulo pequeño la interacción para pedir el porcentaje de propina.
 
| Función | Descripción |
|---|---|
| `double pedirPorcentajePropina(void)` | Pide el porcentaje (por ejemplo 0, 10, 15 o 20 %), valida y lo devuelve. |
 
**Depende de:** `adds.h`.
 
Mantenerlo separado de `cuenta` es una buena decisión: `cuenta` queda como lógica pura (sin `scanf`) y es más fácil de probar.
 
---
 
## 8. `datos.h` — Datos iniciales
 
**Propósito:** poblar el sistema al arrancar con un menú y mesas de ejemplo.
 
| Función | Descripción |
|---|---|
| `cargarDatosIniciales(menu, &totalPlatillos, mesas, &totalMesas)` | Llama a `registrarPlatilloMenu` y `registrarMesa` para dejar todo listo. |
 
**Depende de:** `menu.h`, `mesa.h`.
 
---
 
## 9. `flujos.h` — Flujos de interacción
 
**Propósito:** cada función es una **operación completa de cara al usuario**: pide los datos, valida, llama a la lógica de los demás módulos e imprime el resultado.
 
| Función | Qué hace |
|---|---|
| `flujoAbrirMesa` | Pide número de mesa, mesero y comensales → `abrirMesa`. |
| `flujoAgregarPlatillo` | Pide mesa, platillo, cantidad y nota → `agregarPlatillo`. |
| `flujoQuitarPlatillo` | Pide mesa, platillo y cantidad → `quitarPlatillo`. |
| `flujoVerCuenta` | Pide mesa y propina, calcula e imprime la cuenta (solo lectura, por eso `const Mesa mesas[]`). |
| `flujoCerrarMesa` | Calcula la cuenta, confirma y llama a `cerrarMesa` para registrar la venta. |
 
**Depende de:** `adds.h`, `menu.h`, `mesa.h`, `cuenta.h`, `pedirpropina.h`.
 
---
 
## 10. `ui.h` — Interfaz principal
 
**Propósito:** punto de entrada de la parte interactiva. Muestra el menú principal, lee la opción y delega en `flujos`.
 
| Función | Descripción |
|---|---|
| `ejecutarSistemaRestaurante(...)` | Bucle principal: mapa de mesas, abrir/cerrar mesa, agregar/quitar platillos, ver cuenta, reporte de ventas, salir. |
 
**Depende de:** `adds.h`, `menu.h`, `mesa.h`, `flujos.h`, `cuenta.h`.
 
---
 
## 11. Flujo típico de uso
 
```
main()
 ├─ inicializar menú, mesas y ventas
 ├─ cargarDatosIniciales()
 └─ ejecutarSistemaRestaurante()
      └─ [bucle]
          1. flujoAbrirMesa        → mesa pasa a MESA_ABIERTA
          2. flujoAgregarPlatillo  → se llena la comanda
          3. flujoVerCuenta        → desglose IVA + propina (opcional)
          4. flujoCerrarMesa       → suma ventas, mesa vuelve a MESA_LIBRE
          5. mostrarReporteVentas  → resumen por mesero y platillo
```
 
---
 
## 12. Compilación y observaciones técnicas
 
### Includes con `<>`
 
Los headers propios se incluyen con `#include <adds.h>`, `<menu.h>`, etc. Con ese estilo el compilador solo los encuentra si le indicas el directorio:
 
```bash
gcc -I. -Wall -Wextra -o restaurante *.c -lm
```
 
(`-lm` por `math.h`.) Lo habitual es usar comillas para archivos del proyecto: `#include "adds.h"`. Así funciona sin `-I.`.
 
### Dependencias circulares
 
- `mesa.h` incluye `comanda.h`, y `comanda.h` incluye `menu.h`.
- `flujos.h` usa el tipo `VentaMesero`, que viene de `mesa.h` (a través de `cuenta.h`).
Los *include guards* (`#ifndef ... #define ... #endif`) evitan inclusiones duplicadas, y por ahora no hay un ciclo real. Si en el futuro `comanda.h` necesitara algo de `mesa.h`, aparecería un ciclo; conviene mantener el orden: `adds → menu → comanda → mesa → cuenta → flujos → ui`.