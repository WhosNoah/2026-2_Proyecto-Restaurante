# Sistema de Restaurante en C — Funciones clave

Este documento explica solo las funciones **más importantes y elaboradas** del proyecto: las que contienen lógica real, validaciones o decisiones de diseño. Las funciones simples (inicializadores, búsquedas lineales, getters) se mencionan al final en una tabla corta.

---

## Índice

1. [Entrada de datos (`adds.c`)](#1-entrada-de-datos-addsc)
2. [Comanda (`comanda.c`)](#2-comanda-comandac)
3. [Mesas y ventas (`mesa.c`)](#3-mesas-y-ventas-mesac)
4. [Cuenta (`cuenta.c`)](#4-cuenta-cuentac)
5. [Flujos y UI (`flujos.c`, `ui.c`)](#5-flujos-y-ui-flujosc-uic)
6. [Funciones simples (resumen)](#6-funciones-simples-resumen)
7. [Observaciones y posibles mejoras](#7-observaciones-y-posibles-mejoras)

---

## 1. Entrada de datos (`adds.c`)

El proyecto no usa `scanf` ni `atoi`; toda la lectura pasa por estas funciones, que implementan su propia validación.

### `leerCadena(prompt, destino, tamMax)`

Es la base de todas las lecturas.

1. Imprime el `prompt` y lee con `fgets`.
2. Si en lo leído **no hay `\n`**, significa que el usuario escribió más de lo que cabe en el buffer. Entonces **vacía el resto de la línea** con un bucle `getchar()` para que los caracteres sobrantes no contaminen la siguiente lectura.
3. Quita el salto de línea con `quitarSaltoLinea`.
4. Si `fgets` falla (EOF), deja la cadena vacía.

```c
if (strchr(destino, '\n') == NULL) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}
```

### `leerEntero(prompt)`

Lee un entero **parseando a mano**, carácter por carácter, dentro de un bucle `while (1)` que no termina hasta recibir una entrada válida.

- Rechaza cadena vacía.
- Acepta un signo `+` o `-` solo al inicio, y exige al menos un dígito después.
- Si encuentra cualquier carácter que no sea dígito, marca la entrada como inválida y vuelve a pedirla.
- Construye el número con `numero = numero * 10 + (c - '0')`.

### `leerDouble(prompt)`

Misma idea que `leerEntero`, pero separando **parte entera** y **parte decimal**:

- Acepta un solo punto `.` (la bandera `en_decimal` impide un segundo).
- Cada dígito decimal se suma como `dígito / divisor`, y el divisor se multiplica por 10 en cada paso (0.1, 0.01, 0.001…).
- Exige `tiene_digito` para rechazar entradas como `"."` o `"-"`.

### `copiarCadena(destino, origen, tam_max)`

Reemplazo seguro de `strcpy`: valida punteros nulos, copia como máximo `tam_max - 1` caracteres y **siempre** termina con `'\0'`.

---

## 2. Comanda (`comanda.c`)

### `agregarPlatillo(comanda, menu, totalPlatillos, idPlatillo, cantidad, nota)`

Es la función más completa de este módulo. Sigue este orden de decisiones:

1. **Validación de argumentos:** punteros nulos o `cantidad <= 0` → devuelve `0`.
2. **Existe en el menú:** busca con `buscarPlatilloPorId`; si no, error.
3. **Ya está en la comanda:** si hay un renglón con ese id, **suma la cantidad** en vez de crear uno nuevo. La nota solo se sobrescribe si la nueva no está vacía.
4. **Comanda llena:** si `totalRenglones >= MAX_RENGLONES`, error.
5. **Renglón nuevo:** copia id, nombre y precio **desde el menú** al renglón.

Detalle importante de diseño: el renglón guarda **copia del nombre y precio unitario**. Así la cuenta no cambia si luego se modifica el menú.

### `quitarPlatillo(comanda, idPlatillo, cantidadAQuitar)`

Reduce o elimina un renglón:

```c
if (cantidadAQuitar <= 0 || cantidadAQuitar >= comanda->items[idx].cantidad) {
    eliminarRenglonEnIndice(comanda, idx);   // se elimina todo el renglón
} else {
    comanda->items[idx].cantidad -= cantidadAQuitar;
}
```

Es decir: una cantidad `<= 0` o mayor/igual a la existente **elimina el renglón completo**. Por eso la interfaz dice "0 para eliminar todo el renglón".

### `eliminarRenglonEnIndice(comanda, indice)`

Borra un elemento del arreglo **recorriendo hacia atrás** todos los siguientes (`items[i] = items[i + 1]`) y decrementa `totalRenglones`. Mantiene el arreglo compacto, sin huecos.

### `totalComanda(comanda)`

Suma `precioUnitario × cantidad` de cada renglón. Es la **fuente única** del monto: la usan la cuenta y el cierre de mesa.

---

## 3. Mesas y ventas (`mesa.c`)

### `abrirMesa(mesas, totalMesas, numeroMesa, nombreMesero, comensales)`

Valida en cadena antes de modificar nada:

| Validación | Mensaje de error |
|---|---|
| La mesa existe | "Mesa inexistente" |
| No está ya abierta | "Mesa ya abierta" |
| El nombre del mesero no está vacío | "Falta nombre de mesero" |
| `0 < comensales <= capacidad` | "Comensales invalidos / Exceden capacidad" |

Si todo pasa: copia el mesero, guarda los comensales, cambia el estado a `MESA_ABIERTA` y **reinicia la comanda** para no heredar datos de un cliente anterior.

### `cerrarMesa(...)`

Es la función con más responsabilidades del proyecto. En una sola operación:

1. Calcula `monto = totalComanda(...)` y lo devuelve por `totalCobrado`.
2. **Actualiza el menú:** por cada renglón suma su cantidad a `unidadesVendidas` del platillo correspondiente.
3. **Actualiza al mesero:** `asegurarMesero` lo crea si no existe; luego suma `totalVendido` y `mesasAtendidas`.
4. **Libera la mesa:** limpia comanda, mesero y comensales, y cambia el estado a `MESA_LIBRE`.

> El monto registrado como venta es el total **con IVA y sin propina**. La propina no se acumula en el reporte.

### `asegurarMesero(ventasMeseros, totalMeseros, nombreMesero)`

Patrón "buscar o crear" (*get-or-create*):

- Busca por nombre con `strcmp`; si lo encuentra, devuelve su índice.
- Si no existe y hay espacio (`MAX_MESEROS`), lo agrega con totales en cero.
- Devuelve `-1` si el nombre es inválido o ya no cabe otro mesero.

Gracias a esto no hace falta registrar a los meseros por adelantado: nacen la primera vez que cierran una mesa.

### `mostrarReporteVentas(...)`

Genera dos secciones:

- **Ventas por mesero:** nombre, mesas atendidas y total vendido.
- **Unidades vendidas por platillo:** solo los que tienen `unidadesVendidas > 0`, con el importe calculado como `unidades × precio`.

Maneja los casos vacíos con mensajes ("Sin ventas registradas aun").

### `mostrarMapaMesas(...)`

Tabla formateada con `printf` y anchos fijos (`%4d`, `%-8s`…). Para mesas libres muestra `-` en lugar del mesero y `0` comensales.

---

## 4. Cuenta (`cuenta.c`)

### `desglosarIVA(totalConIVA, &subtotal, &iva)`

Los precios del menú **ya incluyen IVA**, así que el IVA se obtiene "hacia atrás":

```c
double sub = totalConIVA / 1.16;
double imp = totalConIVA - sub;
```

Permite que `subtotal` o `iva` sean `NULL` si el llamador solo necesita uno de los dos.

### `dividirCuenta(totalAPagar, numPersonas, &primera, &resto)`

La parte más delicada del módulo: dividir dinero sin perder centavos. Trabaja **en enteros (centavos)** para evitar errores de punto flotante:

```c
long long totalCentavos = llround(totalAPagar * 100.0);
long long baseCentavos  = totalCentavos / numPersonas;
long long restoCentavos = totalCentavos % numPersonas;
long long primeraCentavos = baseCentavos + restoCentavos;
```

Ejemplo: $100.00 entre 3 personas → 10000 centavos → base 3333, residuo 1.

- Primera persona: $33.34
- Las otras dos: $33.33 cada una
- Suma exacta: $100.00

Devuelve `0` si `numPersonas <= 0` o el total es negativo.

### `calcularCuentaMesa(mesa, porcentajePropina, numPersonas, &cuenta)`

Orquesta todo el cálculo y llena la estructura `DesgloseCuenta`:

```
totalConIVA  = totalComanda(mesa)
subtotal/iva = desglosarIVA(totalConIVA)
propina      = totalConIVA × porcentaje / 100
totalAPagar  = totalConIVA + propina
montos       = dividirCuenta(totalAPagar, numPersonas)
```

> La propina se calcula sobre el total **con IVA**, no sobre el subtotal.

### `imprimirCuenta(mesa, cuenta)`

Imprime el ticket: encabezado con mesa y mesero, un renglón por platillo (con su nota entre paréntesis), el desglose (subtotal, IVA, total, propina, total a pagar) y la división:

- 1 persona → `Dividido entre 1: $X`
- N personas → `Dividido entre N: $primera + (N-1) x $resto`

---

## 5. Flujos y UI (`flujos.c`, `ui.c`)

Los flujos no contienen lógica de negocio: **piden datos, validan el contexto y delegan** a los módulos de abajo. Todos comparten el mismo patrón:

```
mostrarMapaMesas → leerEntero(mesa) → buscarMesaPorNumero
   → ¿existe y está en el estado correcto? → pedir más datos → llamar a la lógica → imprimir [OK]/[Error]
```

### `flujoCerrarMesa(...)`

El flujo más completo:

1. Valida que la mesa exista y esté abierta.
2. Pide propina (`pedirPorcentajePropina`) y número de personas. Si el usuario escribe `0` o menos, usa los `comensales` de la mesa.
3. Calcula e **imprime la cuenta** para que el mesero la revise.
4. Pide **confirmación** (`s/n`); cualquier cosa distinta de `s`/`S` cancela.
5. Solo si confirma, llama a `cerrarMesa` y muestra la venta registrada.

### `flujoVerCuenta(...)`

Igual que el anterior, pero **sin cerrar**: recibe `const Mesa mesas[]` porque es solo de lectura.

### `flujoAgregarPlatillo(...)` / `flujoQuitarPlatillo(...)`

- Agregar: muestra el menú, pide id, cantidad y nota opcional (Enter para omitir).
- Quitar: muestra la comanda actual y, si está vacía, termina sin preguntar nada más.

### `pedirPorcentajePropina()`

Submenú con `switch`: 10 %, 15 %, 20 %, personalizada (usa `leerDouble`) o sin propina. Cualquier opción desconocida devuelve 0 %, y una propina personalizada negativa se corrige a 0.

### `ejecutarSistemaRestaurante(...)`

Bucle principal con `while (opcion != 0)`: muestra el menú, lee la opción con `leerEntero` y la despacha con un `switch` a las funciones de `flujos` o de visualización (`mostrarMenu`, `mostrarMapaMesas`, `mostrarReporteVentas`).

---

## 6. Funciones simples (resumen)

| Función | Qué hace |
|---|---|
| `inicializarMenu`, `inicializarMesas`, `inicializarComanda`, `inicializarVentasMeseros` | Ponen contadores en 0 y limpian los arreglos. |
| `buscarPlatilloPorId`, `buscarMesaPorNumero`, `buscarRenglonPorId` | Búsqueda lineal; devuelven el índice o `-1`. |
| `registrarPlatilloMenu`, `registrarMesa` | Agregan un elemento validando límite y duplicados. |
| `obtenerNombreCategoria` | `switch` de enum a texto. |
| `mostrarMenu`, `mostrarComanda` | Solo impresión con formato. |
| `calcularPropina` | `total × porcentaje / 100`, con 0 si los datos son negativos. |
| `cargarDatosIniciales` | Registra 16 platillos y 6 mesas de ejemplo. |

---

## 7. Observaciones y posibles mejoras

Cosas que noté al revisar el código; ninguna rompe el funcionamiento normal.

1. **`leerEntero` / `leerDouble` y el fin de entrada (EOF).** Si `fgets` falla (por ejemplo con Ctrl+D), `leerCadena` deja la cadena vacía y los bucles `while (1)` imprimen "Entrada vacia" **para siempre**. Una solución es que `leerCadena` devuelva un valor de error y que las funciones de lectura salgan del bucle.
2. **Desbordamiento en `leerEntero`.** Un número con muchos dígitos desborda `int` sin aviso (comportamiento indefinido). Se puede limitar la cantidad de dígitos o usar `long long` para acumular y validar el rango.
3. **IVA fijo en el código.** El `1.16` de `desglosarIVA` y el texto "IVA (16%)" de `imprimirCuenta` y `mostrarMenu` están escritos a mano. Un `#define TASA_IVA 0.16` evitaría inconsistencias.
4. **`flujoCerrarMesa` no revisa el resultado de `calcularCuentaMesa`.** Hoy es seguro porque `personas` siempre queda `> 0`, pero conviene comprobarlo como se hace en `flujoVerCuenta`.
5. **El reporte usa el precio actual del menú.** En "Unidades vendidas por platillo" el importe es `unidades × precio vigente`; si el precio cambiara, el reporte no reflejaría lo que realmente se cobró. Guardar el importe acumulado por platillo lo resolvería.
6. **La propina no entra en el reporte.** Es una decisión válida (la propina no es venta), pero conviene dejarlo documentado o registrar propinas aparte por mesero.
7. **Inconsistencia menor en la nota al agregar.** Si se agrega el mismo platillo dos veces con notas distintas, la segunda nota **reemplaza** a la primera en lugar de combinarse.