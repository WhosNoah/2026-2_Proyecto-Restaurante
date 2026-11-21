## 7. Restaurante: mesas, comandas y cuenta

### Descripcion

Desarrollar el sistema de un restaurante pequeÃ±o: abrir mesas, asignar meseros, tomar la orden (comanda), calcular la cuenta con propina, dividirla entre comensales y cerrar la mesa.

### Reglas

- Los precios del menu **ya incluyen IVA (16%)**. La cuenta debe desglosarlo: `subtotal = total / 1.16`, `iva = total âˆ’ subtotal`.
- La propina se calcula sobre el total: 10%, 15%, 20% o un porcentaje personalizado.
- Al dividir la cuenta entre N personas, los centavos sobrantes se cargan a la primera persona, para que la suma cuadre exactamente.

### Requisitos mÃ­nimos

- Menu con **al menos 15 platillos** en varias categori­as (entradas, platos fuertes, bebidas, postres), predefinido en el codigo o cargado desde un archivo.
- **Mapa de mesas**: numero, capacidad, estado y mesero asignado.
- **Abrir mesa**: asignar mesero y numero de comensales (sin exceder la capacidad).
- **Agregar platillos a la comanda**: si el platillo ya esta en la comanda, se suma la cantidad en lugar de agregar otro renglon. Permitir notas ("sin cebolla").
- **Quitar** platillos o reducir la cantidad.
- **Ver la cuenta** desglosada:
  ```
  Mesa 4 â€” Mesero: Laura
  2 x Tacos de asada ........ $180.00
  1 x Agua de horchata ....... $35.00
  ----------------------------------
  Subtotal ................. $185.34
  IVA (16%) ................. $29.66
  Total .................... $215.00
  Propina (15%) ............. $32.25
  TOTAL A PAGAR ............ $247.25
  Dividido entre 3: $82.43 + 2 x $82.41
  ```
- **Cerrar mesa**: registrar la venta (acumular por mesero y por platillo) y liberar la mesa.


### Funciones mi­nimas

```c
abrirMesa;
agregarPlatillo;
quitarPlatillo;
totalComanda;
desglosarIVA;
calcularPropina;
dividirCuenta;
imprimirCuenta;
cerrarMesa;
```

### Archivos esperados

`menu.h/.c`, `comanda.h/.c`, `mesa.h/.c`, `cuenta.h/.c` , `ui.h/.c`, `main.c`.
