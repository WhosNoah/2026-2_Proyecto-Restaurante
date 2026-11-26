#include <ui.h>

void ejecutarSistemaRestaurante(Platillo menu[], int totalPlatillos, Mesa mesas[], int totalMesas, VentaMesero ventasMeseros[], int *totalMeseros) {
    int opcion = -1;

    while (opcion != 0) {
        printf("\n================ SISTEMA DE RESTAURANTE ================\n");
        printf("  1. Ver menu\n");
        printf("  2. Ver mapa de mesas\n");
        printf("  3. Abrir mesa\n");
        printf("  4. Agregar platillo a comanda\n");
        printf("  5. Quitar / reducir platillo de comanda\n");
        printf("  6. Ver cuenta desglosada\n");
        printf("  7. Cerrar mesa y registrar venta\n");
        printf("  8. Ver reporte acumulado de ventas\n");
        printf("  0. Salir\n");
        printf("========================================================\n");

        opcion = leerEntero("Selecciona una opcion: ");

        switch (opcion) {
            case 1:
                mostrarMenu(menu, totalPlatillos);
                break;
            case 2:
                mostrarMapaMesas(mesas, totalMesas);
                break;
            case 3:
                flujoAbrirMesa(mesas, totalMesas);
                break;
            case 4:
                flujoAgregarPlatillo(mesas, totalMesas, menu, totalPlatillos);
                break;
            case 5:
                flujoQuitarPlatillo(mesas, totalMesas);
                break;
            case 6:
                flujoVerCuenta(mesas, totalMesas);
                break;
            case 7:
                flujoCerrarMesa(mesas, totalMesas, menu, totalPlatillos, ventasMeseros, totalMeseros);
                break;
            case 8:
                mostrarReporteVentas(ventasMeseros, *totalMeseros, menu, totalPlatillos);
                break;
            case 0:
                printf("Saliendo del sistema...\n");
                break;
            default:
                printf("  Opcion invalida.\n");
                break;
        }
    }
}