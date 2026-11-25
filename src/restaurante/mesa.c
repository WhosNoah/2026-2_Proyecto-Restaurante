#include <mesa.h>

void inicializar_mesas(Mesa mesas[], int *total_mesas) {
    *total_mesas = 0;
    for ( int i = 0; i < MAX_MESAS; i++ ) {
        mesas[i].numero = 0;
        mesas[i].capacidad = 0;
        mesas[i].estado = MESA_LIBRE;
        mesas[i].mesero[0] = '\0';
        mesas[i].comensales = 0;
        inicializar_comanda(&mesas[i].comanda);
    }
}

int registrar_mesa(Mesa mesas[], int *total_mesas, int numero, int capacidad) {
    if ( *total_mesas >= MAX_MESAS || numero <= 0 || capacidad <= 0 )
        return 0;
    if ( buscar_mesa_por_numero(mesas, *total_mesas, numero) != -1 ) {
        printf("\nError: [ Numero de mesa duplicado. ]\n");
        return 0;
    }

    int idx = *total_mesas;
    mesas[idx].numero = numero;
    mesas[idx].capacidad = capacidad;
    mesas[idx].estado = MESA_LIBRE;
    mesas[idx].mesero[0] = '\0';
    mesas[idx].comensales = 0;
    inicializar_comanda(&mesas[idx].comanda);

    (*total_mesas)++;
    return 1;
}

int buscar_mesa_por_numero(const Mesa mesas[], int total_mesas, int numero) {
    for ( int i = 0; i < total_mesas; i++ ) {
        if ( mesas[i].numero == numero )
            return i;
    }
    return -1;
}

void inicializar_ventas_meseross(VentaMesero ventas_meseros[], int *total_meseros) {
    *total_meseros = 0;
    for ( int i = 0; i < MAX_MESEROS; i++ ) {
        ventas_meseros[i].nombre[0] = '\0';
        ventas_meseros[i].total_vendido = 0.0;
        ventas_meseros[i].mesas_atendidas = 0;
    }
}

int asegurar_mesero(VentaMesero ventas_meseros[], int *total_meseros, const char *nombre_mesero) {
    if ( nombre_mesero == NULL || nombre_mesero[0] == '\0' )
        return -1;
    for ( int i = 0; i < *total_meseros; i++ ) {
        if ( strcmp(ventas_meseros[i].nombre, nombre_mesero) == 0 )
            return i;
    }

    if ( *total_meseros >= MAX_MESEROS )
        return -1;

    int idx = *total_meseros;
    strncpy(ventas_meseros[idx].nombre, nombre_mesero, MAX_NOMBRE_MESERO - 1);
    ventas_meseros[idx].nombre[MAX_NOMBRE_MESERO - 1] = '\0';
    ventas_meseros[idx].total_vendido = 0.0;
    ventas_meseros[idx].mesas_atendidas = 0;

    (*total_meseros)++;
    return idx;
}

int abrir_mesa(Mesa mesas[], int total_mesas, int numero_mesa, const char *nombre_mesero, int comensales) {
    int idx = buscar_mesa_por_numero(mesas, total_mesas, numero_mesa);
    if ( idx == -1 ) {
        printf("\nError: [ Mesa inexistente. ]\n");
        return 0;
    }
    if ( mesas[idx].estado == MESA_ABIERTA ) {
        printf("\nMesa abierta!\n");
        return 0;
    }
    if ( nombre_mesero == NULL || nombre_mesero[0] == '\0' ) {
        printf("\nFalta el nombre del mesero.\n");
        return 0;
    }
    if ( comensales <= 0 || comensales > mesas[idx].capacidad ) {
        printf("\nError: [ Comensales invalidos / Exceden capacidad. ]\n");
        return 0;
    }

    strncpy(mesas[idx].mesero, nombre_mesero, MAX_NOMBRE_MESERO - 1);
    mesas[idx].mesero[MAX_NOMBRE_MESERO - 1] = '\0';
    mesas[idx].comensales = comensales;
    mesas[idx].estado = MESA_ABIERTA;
    inicializar_comanda(&mesas[idx].comanda);

    return 1;
}

int cerrar_mesa(Mesa mesas[], int total_mesas, int numero_mesa, Platillo menu[], int total_platillos, VentaMesero ventas_meseros[], int *total_meseros, double *total_cobrado) {
    int idx = buscar_mesa_por_numero(mesas, total_mesas, numero_mesa);
    if ( idx == -1 || mesas[idx].estado == MESA_LIBRE )
        return 0;

    double monto = total_comanda(&mesas[idx].comanda);
    if ( total_cobrado != NULL )
        *total_cobrado = monto;

    for ( int i = 0; i < mesas[idx].comanda.total_renglones; i++ ) {
        const RenglonComanda *r = &mesas[idx].comanda.items[i];
        int idx_menu = buscar_platillo_id(menu, total_platillos, r->id_platillo);
        if ( idx_menu != -1 )
            menu[idx].unidades_vendidas += r->cantidad;
    }

    int idx_mesero = asegurar_mesero(ventas_meseros, total_meseros, mesas[idx].mesero);
    if ( idx_mesero != -1 ) {
        ventas_meseros[idx].total_vendido += monto;
        ventas_meseros[idx].mesas_atendidas++;
    }

    // Liberar la mesa y limpiar la comanda.
    inicializar_comanda(&mesas[idx].comanda);
    mesas[idx].mesero[0] = '\0';
    mesas[idx].comensales = 0;
    mesas[idx].estado = MESA_LIBRE;
}

void mostrar_mapa_mesas(const Mesa mesas[], int total_mesas) {
    printf("\n==================== MAPA DE MESAS ====================\n");
    printf("  Mesa | Capacidad | Estado   | Comensales | Mesero\n");
    printf("  -----+-----------+----------+------------+----------------\n");

    for ( int i = 0; i < total_mesas; i++ ) {
        const char *estadoStr = (mesas[i].estado == MESA_ABIERTA) ? "ABIERTA" : "LIBRE";
        const char *meseroStr = (mesas[i].estado == MESA_ABIERTA) ? mesas[i].mesero : "-";
        int comensalesStr = (mesas[i].estado == MESA_ABIERTA) ? mesas[i].comensales : 0;

        printf("  %4d | %9d | %-8s | %10d | %s\n", mesas[i].numero, mesas[i].capacidad, estadoStr, comensalesStr, meseroStr);
    }
    printf("=======================================================\n");
}

void mostrar_reporte_ventas(const VentaMesero ventas_meseros[], int total_meseros, const Platillo menu[], int total_platillos) {
    printf("\n================ REPORTE DE VENTAS (CIERRES) ================\n");

    printf("\n--- Ventas por Mesero ---\n");
    if ( total_meseros == 0 ) {
        printf("  Sin ventas registradas... Aun.\n");
    } else {
        for ( int i = 0; i < total_meseros; i++ ) 
            printf("  %-18s | Mesas: %2d | Total: $%8.2f.\n", ventas_meseros[i].nombre, ventas_meseros[i].mesas_atendidas, ventas_meseros[i].total_vendido);
    }

    printf("\n--- Unidades Vendidas por Platillo ---\n");
    int hay_vendidos = 0;
    for ( int i = 0; i < total_platillos; i++ ) {
        if ( menu[i].unidades_vendidas > 0 ) {
            hay_vendidos = 1;
            printf("  [%2d] %-30s | %3d uds | %8.2f\n", menu[i].id, menu[i].nombre, menu[i].unidades_vendidas, menu[i].unidades_vendidas * menu[i].precio);
        }
    }
    if ( !hay_vendidos )
        printf("  Aun no se han cerrado las mesas con platillos.\n");
    printf("=============================================================\n");
}