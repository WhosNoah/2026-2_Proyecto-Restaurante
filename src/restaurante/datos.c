#include <datos.h>

void cargarDatosIniciales(Platillo menu[], int *totalPlatillos, Mesa mesas[], int *totalMesas) {
    inicializarMenu(menu, totalPlatillos);

    registrarPlatilloMenu(menu, totalPlatillos, 1, "Guacamole con totopos", CAT_ENTRADA, 85.00);
    registrarPlatilloMenu(menu, totalPlatillos, 2, "Queso fundido con chorizo", CAT_ENTRADA, 110.00);
    registrarPlatilloMenu(menu, totalPlatillos, 3, "Sopa de tortilla", CAT_ENTRADA, 75.00);
    registrarPlatilloMenu(menu, totalPlatillos, 4, "Sopes de frijol y queso", CAT_ENTRADA, 80.00);

    registrarPlatilloMenu(menu, totalPlatillos, 5, "Tacos de asada (orden)", CAT_PLATO_FUERTE, 90.00);
    registrarPlatilloMenu(menu, totalPlatillos, 6, "Enchiladas suizas", CAT_PLATO_FUERTE, 135.00);
    registrarPlatilloMenu(menu, totalPlatillos, 7, "Arrachera a la parrilla", CAT_PLATO_FUERTE, 240.00);
    registrarPlatilloMenu(menu, totalPlatillos, 8, "Chilaquiles con pollo", CAT_PLATO_FUERTE, 115.00);
    registrarPlatilloMenu(menu, totalPlatillos, 9, "Milanesa de res empanizada", CAT_PLATO_FUERTE, 150.00);

    registrarPlatilloMenu(menu, totalPlatillos, 10, "Agua de horchata", CAT_BEBIDA, 35.00);
    registrarPlatilloMenu(menu, totalPlatillos, 11, "Agua de jamaica", CAT_BEBIDA, 35.00);
    registrarPlatilloMenu(menu, totalPlatillos, 12, "Refresco de cola", CAT_BEBIDA, 30.00);
    registrarPlatilloMenu(menu, totalPlatillos, 13, "Cafe de olla", CAT_BEBIDA, 40.00);

    registrarPlatilloMenu(menu, totalPlatillos, 14, "Flan napolitano", CAT_POSTRE, 60.00);
    registrarPlatilloMenu(menu, totalPlatillos, 15, "Pastel tres leches", CAT_POSTRE, 70.00);
    registrarPlatilloMenu(menu, totalPlatillos, 16, "Churros con cajeta", CAT_POSTRE, 65.00);

    inicializarMesas(mesas, totalMesas);
    registrarMesa(mesas, totalMesas, 1, 2);
    registrarMesa(mesas, totalMesas, 2, 2);
    registrarMesa(mesas, totalMesas, 3, 4);
    registrarMesa(mesas, totalMesas, 4, 4);
    registrarMesa(mesas, totalMesas, 5, 6);
    registrarMesa(mesas, totalMesas, 6, 8);
}