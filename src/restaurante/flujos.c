#include <flujos.h>

void flujo_abrir_mesa(Mesa mesas[], int total_mesas) {
    mostrar_mapa_mesas(mesas, total_mesas);
    int num_mesa = leer_entero("Numero de mesa a abrir: ");
    int idx = buscar_mesa_por_numero(mesas, total_mesas, num_mesa);

    if ( idx == -1 ) {
        printf("\nError: [ La mesa %d no existe. ]\n");
        return;
    }
    if ( mesas[idx].estado == MESA_ABIERTA ) {
        printf("\nError: [ La mesa %d ya esta abierta. ]\n");
        return;
    }

    char mesero[MAX_NOMBRE_MESERO];
    leer_cadena("Nombre del mesero asignado: ", mesero, sizeof(mesero));

    int comensales = leer_entero("Numero de comensales: ");
    if ( abrir_mesa(mesas, total_mesas, num_mesa, mesero, comensales) )
        printf("[OK] Mesa %d abierta para %d comensales ( Mesero: %s ).\n", num_mesa, comensales, mesero);
    else
        printf("[ERROR] No se pudo abrir la mesa ( verifica capacidad max %d y nombre ).\n", mesas[idx].capacidad);
}

int flujo_agregar_platillo(Mesa mesas[], int total_mesas, const Platillo menu[], int total_platillos) {
    mostrar_mapa_mesas(mesas, total_mesas);
    int num_mesa = leer_entero("Numero de mesa: ");
    int idx = buscar_mesa_por_numero(mesas, total_mesas, num_mesa);

    if ( idx == -1 || mesas[idx].estado == MESA_LIBRE ) {
        printf("\nError: [ Mesa inexistente / No abierta. ]\n");
        return;
    }

    mostrar_menu(menu, total_platillos);
    int id_platillo = leer_entero("ID del platillo a agregar: ");
    int cantidad = leer_entero("Cantidad: ");

    char nota[MAX_NOTA];
    leer_cadena("Nota especial (Enter para omitir): ", nota, sizeof(nota));

    if ( agregar_platillo(&mesas[idx].comanda, menu, total_platillos, id_platillo, cantidad, nota) )
        printf("[OK]: Platillo agregado a la comanda de la mesa %d.\n", num_mesa);
    else
        printf("[ERROR]: ID invalido, cantidad <= 0 o comanda llena.\n");
}

void flujo_quitar_platillo(Mesa mesas[], int total_mesas) {
    mostrar_mapa_mesas(mesas, total_mesas);
    int num_mesa = leer_entero("Numero de mesa: ");
    int idx = buscar_mesa_por_numero(mesas, total_mesas, num_mesa);

    if ( idx == -1 || mesas[idx].estado == MESA_LIBRE ) {
        printf("\nError: [ Mesa inexistente / Sin abrir. ]\n");
        return;
    }

    printf("\nComanda actual de la mesa %d:\n", num_mesa);
    mostrar_comanda(&mesas[idx].comanda);
    if ( mesas[idx].comanda.total_renglones == 0 )
        return;

    int id_platillo = leer_entero("ID del platillo a reducir/quitar: ");
    int cantidad = leer_entero("Cantidad a quitar ( 0 para eliminar todo el renglon ): ");

    if ( quitar_platillo(&mesas[idx].comanda, id_platillo, cantidad) )
        printf("  [OK] Comanda actualizada.\n");
    else
        printf("  [ERROR Ese platillo no esta en la comanda.\n");
}

void flujo_ver_cuenta(const Mesa mesas[], int total_mesas) {
    mostrar_mapa_mesas(mesas, total_mesas);
    int num_mesa = leer_entero("Numero de mesa: ");
    int idx = buscar_mesa_por_numero(mesas, total_mesas, num_mesa);

    if ( idx == -1 || mesas[idx].estado == MESA_LIBRE ) {
        printf("\nError: [ Mesa inexistente / Sin abrir. ]\n");
        return;
    }

    double propina_pct = pedir_porcentaje_propina();
    int personas = leer_entero("Dividir entre cuantas personas ( 0 para usar comensales de mesa ): ");
    if ( personas <= 0 )
        personas = mesas[idx].comensales;

    DesgloseCuenta cuenta;
    if ( calcular_cuenta_mesa(&mesas[idx], propina_pct, personas, &cuenta) )
        imprimir_cuenta(&mesas[idx], &cuenta);
    else
        printf("  [ERROR] No se puede calcular la cuenta.\n");
}

void flujo_cerrar_mesa(Mesa mesas[], int total_mesas, Platillo menu[], int total_platillos, VentaMesero ventas_meseros[], int *total_meseros) {
    mostrar_mapa_mesas(mesas, total_mesas);
    int num_mesa = leer_entero("Numero de mesa a cerrar: ");
    int idx = buscar_mesa_por_numero(mesas, total_mesas, num_mesa);

    if ( idx == -1 || mesas[idx].estado == MESA_LIBRE ) {
        printf("\nError: [ Mesa inexistente / Sin abrir. ]\n");
        return;
    }

    double propina_pct = pedir_porcentaje_propina();
    int personas = leer_entero("Dividir entre cuantas personas ( 0 para usar comensales de mesa ): ");
    if ( personas <= 0 )
        personas = mesas[idx].comensales;

    DesgloseCuenta cuenta;
    calcular_cuenta_mesa(&mesas[idx], propina_pct, personas, &cuenta);
    imprimir_cuenta(&mesas[idx], &cuenta);

    char confirmacion[64];
    leer_cadena("\nConfirmar cierre de mesa? (s/n): ", confirmacion, sizeof(confirmacion));
    if ( confirmacion[0] != 's' && confirmacion != 'S' ) {
        printf("  Cierre cancelado.\n");
        return;
    }

    double total_base = 0.0;
    if ( cerrar_mesa(mesas, total_mesas, num_mesa, menu, total_platillos, ventas_meseros, total_meseros, &total_base) )
        printf(" [OK] Mesa %d cerrada y liberada. Venta registrada $%.2f\n", num_mesa, total_base);
    else
        printf(" [ERROR] No se pudo cerrar la mesa.\n");
}