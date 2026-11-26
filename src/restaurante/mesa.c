#include <mesa.h>

void inicializarMesas(Mesa mesas[], int *totalMesas) {
    *totalMesas = 0;
    for (int i = 0; i < MAX_MESAS; i++) {
        mesas[i].numero = 0;
        mesas[i].capacidad = 0;
        mesas[i].estado = MESA_LIBRE;
        mesas[i].mesero[0] = '\0';
        mesas[i].comensales = 0;
        inicializarComanda(&mesas[i].comanda);
    }
}

int registrarMesa(Mesa mesas[], int *totalMesas, int numero, int capacidad) {
    if (*totalMesas >= MAX_MESAS || numero <= 0 || capacidad <= 0) {
        return 0;
    }
    if (buscarMesaPorNumero(mesas, *totalMesas, numero) != -1) {
        printf("\nError: [ Numero de mesa duplicado. ]\n");
        return 0;
    }

    int idx = *totalMesas;
    mesas[idx].numero = numero;
    mesas[idx].capacidad = capacidad;
    mesas[idx].estado = MESA_LIBRE;
    mesas[idx].mesero[0] = '\0';
    mesas[idx].comensales = 0;
    inicializarComanda(&mesas[idx].comanda);

    (*totalMesas)++;
    return 1;
}

int buscarMesaPorNumero(const Mesa mesas[], int totalMesas, int numero) {
    for (int i = 0; i < totalMesas; i++) {
        if (mesas[i].numero == numero) {
            return i;
        }
    }
    return -1;
}

void inicializarVentasMeseros(VentaMesero ventasMeseros[], int *totalMeseros) {
    *totalMeseros = 0;
    for (int i = 0; i < MAX_MESEROS; i++) {
        ventasMeseros[i].nombre[0] = '\0';
        ventasMeseros[i].totalVendido = 0.0;
        ventasMeseros[i].mesasAtendidas = 0;
    }
}

int asegurarMesero(VentaMesero ventasMeseros[], int *totalMeseros,
                   const char *nombreMesero) {
    if (nombreMesero == NULL || nombreMesero[0] == '\0') {
        return -1;
    }

    for (int i = 0; i < *totalMeseros; i++) {
        if (strcmp(ventasMeseros[i].nombre, nombreMesero) == 0) {
            return i;
        }
    }

    if (*totalMeseros >= MAX_MESEROS) {
        return -1;
    }

    int idx = *totalMeseros;
    strncpy(ventasMeseros[idx].nombre, nombreMesero, MAX_NOMBRE_MESERO - 1);
    ventasMeseros[idx].nombre[MAX_NOMBRE_MESERO - 1] = '\0';
    ventasMeseros[idx].totalVendido = 0.0;
    ventasMeseros[idx].mesasAtendidas = 0;

    (*totalMeseros)++;
    return idx;
}

int abrirMesa(Mesa mesas[], int totalMesas, int numeroMesa,
              const char *nombreMesero, int comensales) {
    int idx = buscarMesaPorNumero(mesas, totalMesas, numeroMesa);
    if (idx == -1) {
        printf("\nError: [ Mesa inexistente. ]\n");
        return 0;
    }
    if (mesas[idx].estado == MESA_ABIERTA) {
        printf("\nError: [ Mesa ya abierta. ]\n");
        return 0;
    }
    if (nombreMesero == NULL || nombreMesero[0] == '\0') {
        printf("\nError: [ Falta nombre de mesero. ]\n");
        return 0;
    }
    if (comensales <= 0 || comensales > mesas[idx].capacidad) {
        printf("\nError: [ Comensales invalidos / Exceden capacidad. ]\n");
        return 0;
    }

    strncpy(mesas[idx].mesero, nombreMesero, MAX_NOMBRE_MESERO - 1);
    mesas[idx].mesero[MAX_NOMBRE_MESERO - 1] = '\0';
    mesas[idx].comensales = comensales;
    mesas[idx].estado = MESA_ABIERTA;
    inicializarComanda(&mesas[idx].comanda);

    return 1;
}

int cerrarMesa(Mesa mesas[], int totalMesas, int numeroMesa, Platillo menu[], int totalPlatillos, VentaMesero ventasMeseros[], int *totalMeseros, double *totalCobrado) {
    int idx = buscarMesaPorNumero(mesas, totalMesas, numeroMesa);
    if (idx == -1 || mesas[idx].estado == MESA_LIBRE) {
        return 0;
    }

    double monto = totalComanda(&mesas[idx].comanda);
    if (totalCobrado != NULL) {
        *totalCobrado = monto;
    }

    for (int i = 0; i < mesas[idx].comanda.totalRenglones; i++) {
        const RenglonComanda *r = &mesas[idx].comanda.items[i];
        int idxMenu = buscarPlatilloPorId(menu, totalPlatillos, r->idPlatillo);
        if (idxMenu != -1) {
            menu[idxMenu].unidadesVendidas += r->cantidad;
        }
    }

    int idxMesero = asegurarMesero(ventasMeseros, totalMeseros, mesas[idx].mesero);
    if (idxMesero != -1) {
        ventasMeseros[idxMesero].totalVendido += monto;
        ventasMeseros[idxMesero].mesasAtendidas++;
    }

    inicializarComanda(&mesas[idx].comanda);
    mesas[idx].mesero[0] = '\0';
    mesas[idx].comensales = 0;
    mesas[idx].estado = MESA_LIBRE;

    return 1;
}

void mostrarMapaMesas(const Mesa mesas[], int totalMesas) {
    printf("\n==================== MAPA DE MESAS ====================\n");
    printf("  Mesa | Capacidad | Estado   | Comensales | Mesero\n");
    printf("  -----+-----------+----------+------------+----------------\n");

    for (int i = 0; i < totalMesas; i++) {
        const char *estadoStr = (mesas[i].estado == MESA_ABIERTA) ? "ABIERTA" : "LIBRE";
        const char *meseroStr = (mesas[i].estado == MESA_ABIERTA) ? mesas[i].mesero : "-";
        int comensalesStr = (mesas[i].estado == MESA_ABIERTA) ? mesas[i].comensales : 0;

        printf("  %4d | %9d | %-8s | %10d | %s\n",
               mesas[i].numero,
               mesas[i].capacidad,
               estadoStr,
               comensalesStr,
               meseroStr);
    }
    printf("=======================================================\n");
}

void mostrarReporteVentas(const VentaMesero ventasMeseros[], int totalMeseros,
                          const Platillo menu[], int totalPlatillos) {
    printf("\n================ REPORTE DE VENTAS (CIERRES) ================\n");

    printf("\n--- Ventas por Mesero ---\n");
    if (totalMeseros == 0) {
        printf("  Sin ventas registradas aun.\n");
    } else {
        for (int i = 0; i < totalMeseros; i++) {
            printf("  %-18s | Mesas: %2d | Total: $%8.2f\n",
                   ventasMeseros[i].nombre,
                   ventasMeseros[i].mesasAtendidas,
                   ventasMeseros[i].totalVendido);
        }
    }

    printf("\n--- Unidades Vendidas por Platillo ---\n");
    int hayVendidos = 0;
    for (int i = 0; i < totalPlatillos; i++) {
        if (menu[i].unidadesVendidas > 0) {
            hayVendidos = 1;
            printf("  [%2d] %-30s | %3d uds | $%8.2f\n",
                   menu[i].id,
                   menu[i].nombre,
                   menu[i].unidadesVendidas,
                   menu[i].unidadesVendidas * menu[i].precio);
        }
    }
    if (!hayVendidos) {
        printf("  Aun no se han cerrado mesas con platillos.\n");
    }
    printf("=============================================================\n");
}