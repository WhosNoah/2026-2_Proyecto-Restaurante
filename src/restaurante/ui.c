#include <ui.h>

void user_interface(Platillo menu[], int total_platillos, Mesa mesas[], int total_mesas, VentaMesero ventas_meseros[], int *total_meseros) {
    int opcion = -1;
    while ( opcion != 0 ) {
        printf("\n================ SELECCIONE UNA OPCION ================\n");
        printf("  1. Ver menu\n");
        printf("  2. Ver mapa de mesas\n");
        printf("  3. Abrir mesa\n");
        printf("  4. Agregar platillo a comanda\n");
        printf("  5. Quitar / reducir platillo de comanda\n");
        printf("  6. Ver cuenta desglosada\n");
        printf("  7. Cerrar mesa y registrar venta\n");
        printf("  8. Ver reporte acumulado de ventas\n");
        printf("  0. Salir\n");
        printf("=========================================================\n");

        opcion = leer_entero("-> ");

        switch ( opcion ) {
            case 1:
                mostrar_menu(menu, total_platillos);
                break;
            case 2:
                mostrar_mapa_mesas(mesas, total_mesas);
                break;
            case 3:
                flujo_abrir_mesa(mesas, total_mesas);
                break;
            case 4:
                flujo_agregar_platillo(mesas, total_mesas, menu, total_platillos);
                break;
            case 5:
                flujo_quitar_platillo(mesas, total_mesas);
                break;
            case 6:
                flujo_ver_cuenta(mesas, total_mesas);
                break;
            case 7:
                flujo_cerrar_mesa(mesas, total_mesas, menu, total_platillos, ventas_meseros, total_meseros);
                break;
            case 8:
                mostrar_reporte_ventas(ventas_meseros, *total_meseros, menu, total_platillos);
                break;
            case 0:
                printf("Terminando programa...\n");
                break;
            default:
                printf("Seleccione una opcion valida.\n");
        }
    }
}