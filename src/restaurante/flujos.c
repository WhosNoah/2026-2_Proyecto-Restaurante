#include <flujos.h>

void flujoAbrirMesa(Mesa mesas[], int totalMesas) {
    mostrarMapaMesas(mesas, totalMesas);
    int numMesa = leerEntero("Numero de mesa a abrir: ");
    int idx = buscarMesaPorNumero(mesas, totalMesas, numMesa);

    if (idx == -1) {
        printf("  [Error] La mesa %d no existe.\n", numMesa);
        return;
    }
    if (mesas[idx].estado == MESA_ABIERTA) {
        printf("  [Error] La mesa %d ya esta abierta.\n", numMesa);
        return;
    }

    char mesero[MAX_NOMBRE_MESERO];
    leerCadena("Nombre del mesero asignado: ", mesero, sizeof(mesero));

    int comensales = leerEntero("Numero de comensales: ");
    if (abrirMesa(mesas, totalMesas, numMesa, mesero, comensales)) {
        printf("  [OK] Mesa %d abierta para %d comensales (Mesero: %s).\n", numMesa, comensales, mesero);
    } else {
        printf("  [Error] No se pudo abrir la mesa (verifica capacidad max %d y nombre).\n", mesas[idx].capacidad);
    }
}

void flujoAgregarPlatillo(Mesa mesas[], int totalMesas, const Platillo menu[], int totalPlatillos) {
    mostrarMapaMesas(mesas, totalMesas);
    int numMesa = leerEntero("Numero de mesa: ");
    int idx = buscarMesaPorNumero(mesas, totalMesas, numMesa);

    if (idx == -1 || mesas[idx].estado == MESA_LIBRE) {
        printf("  [Error] La mesa no existe o no esta abierta.\n");
        return;
    }

    mostrarMenu(menu, totalPlatillos);
    int idPlatillo = leerEntero("ID del platillo a agregar: ");
    int cantidad = leerEntero("Cantidad: ");

    char nota[MAX_NOTA];
    leerCadena("Nota especial (Enter para omitir): ", nota, sizeof(nota));

    if (agregarPlatillo(&mesas[idx].comanda, menu, totalPlatillos, idPlatillo, cantidad, nota)) {
        printf("  [OK] Platillo agregado a la comanda de la mesa %d.\n", numMesa);
    } else {
        printf("  [Error] ID invalido, cantidad <= 0 o comanda llena.\n");
    }
}

void flujoQuitarPlatillo(Mesa mesas[], int totalMesas) {
    mostrarMapaMesas(mesas, totalMesas);
    int numMesa = leerEntero("Numero de mesa: ");
    int idx = buscarMesaPorNumero(mesas, totalMesas, numMesa);

    if (idx == -1 || mesas[idx].estado == MESA_LIBRE) {
        printf("  [Error] La mesa no existe o no esta abierta.\n");
        return;
    }

    printf("\nComanda actual de Mesa %d:\n", numMesa);
    mostrarComanda(&mesas[idx].comanda);
    if (mesas[idx].comanda.totalRenglones == 0) {
        return;
    }

    int idPlatillo = leerEntero("ID del platillo a reducir/quitar: ");
    int cantidad = leerEntero("Cantidad a quitar (0 para eliminar todo el renglon): ");

    if (quitarPlatillo(&mesas[idx].comanda, idPlatillo, cantidad)) {
        printf("  [OK] Comanda actualizada.\n");
    } else {
        printf("  [Error] Ese platillo no esta en la comanda.\n");
    }
}

void flujoVerCuenta(const Mesa mesas[], int totalMesas) {
    mostrarMapaMesas(mesas, totalMesas);
    int numMesa = leerEntero("Numero de mesa para ver cuenta: ");
    int idx = buscarMesaPorNumero(mesas, totalMesas, numMesa);

    if (idx == -1 || mesas[idx].estado == MESA_LIBRE) {
        printf("  [Error] La mesa no existe o esta libre.\n");
        return;
    }

    double propinaPct = pedirPorcentajePropina();
    int personas = leerEntero("Dividir entre cuantas personas (0 para usar comensales de mesa): ");
    if (personas <= 0) {
        personas = mesas[idx].comensales;
    }

    DesgloseCuenta cuenta;
    if (calcularCuentaMesa(&mesas[idx], propinaPct, personas, &cuenta)) {
        imprimirCuenta(&mesas[idx], &cuenta);
    } else {
        printf("  [Error] No se pudo calcular la cuenta.\n");
    }
}

void flujoCerrarMesa(Mesa mesas[], int totalMesas, Platillo menu[], int totalPlatillos, VentaMesero ventasMeseros[], int *totalMeseros) {
    mostrarMapaMesas(mesas, totalMesas);
    int numMesa = leerEntero("Numero de mesa a cerrar: ");
    int idx = buscarMesaPorNumero(mesas, totalMesas, numMesa);

    if (idx == -1 || mesas[idx].estado == MESA_LIBRE) {
        printf("  [Error] La mesa no existe o ya esta libre.\n");
        return;
    }

    double propinaPct = pedirPorcentajePropina();
    int personas = leerEntero("Dividir entre cuantas personas (0 para usar comensales de mesa): ");
    if (personas <= 0) {
        personas = mesas[idx].comensales;
    }

    DesgloseCuenta cuenta;
    calcularCuentaMesa(&mesas[idx], propinaPct, personas, &cuenta);
    imprimirCuenta(&mesas[idx], &cuenta);

    char confirmacion[16];
    leerCadena("\nConfirmar cierre de mesa? (s/n): ", confirmacion, sizeof(confirmacion));
    if (confirmacion[0] != 's' && confirmacion[0] != 'S') {
        printf("  Cierre cancelado.\n");
        return;
    }

    double totalBase = 0.0;
    if (cerrarMesa(mesas, totalMesas, numMesa, menu, totalPlatillos, ventasMeseros, totalMeseros, &totalBase)) {
        printf("  [OK] Mesa %d cerrada y liberada. Venta registrada: $%.2f\n", numMesa, totalBase);
    } else {
        printf("  [Error] No se pudo cerrar la mesa.\n");
    }
}