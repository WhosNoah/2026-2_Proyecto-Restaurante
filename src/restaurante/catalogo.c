#include <catalogo.h>

void cargar_datos(Platillo menu[], int *total_platillos, Mesa mesas[], int *total_meseros) {
    inicializar_menu(menu, total_platillos);

    // Entradas
    registrar_platillo_menu(menu, total_platillos, 1, "Guacamole con totopos", CAT_ENTRADA, 85.00);
    registrar_platillo_menu(menu, total_platillos, 2, "Queso fundido con chorizo", CAT_ENTRADA, 110.00);
    registrar_platillo_menu(menu, total_platillos, 3, "Sopa de tortilla", CAT_ENTRADA, 75.00);
    registrar_platillo_menu(menu, total_platillos, 4, "Sopes de frijol y queso", CAT_ENTRADA, 80.00);

    // Platos fuertes
    registrar_platillo_menu(menu, total_platillos, 5, "Tacos de asada (orden)", CAT_PLATO_FUERTE, 90.00);
    registrar_platillo_menu(menu, total_platillos, 6, "Enchiladas suizas", CAT_PLATO_FUERTE, 135.00);
    registrar_platillo_menu(menu, total_platillos, 7, "Arrachera a la parrilla", CAT_PLATO_FUERTE, 240.00);
    registrar_platillo_menu(menu, total_platillos, 8, "Chilaquiles con pollo", CAT_PLATO_FUERTE, 115.00);
    registrar_platillo_menu(menu, total_platillos, 9, "Milanesa de res empanizada", CAT_PLATO_FUERTE, 150.00);

    // Bebidas
    registrar_platillo_menu(menu, total_platillos, 10, "Agua de horchata", CAT_BEBIDA, 35.00);
    registrar_platillo_menu(menu, total_platillos, 11, "Agua de jamaica", CAT_BEBIDA, 35.00);
    registrar_platillo_menu(menu, total_platillos, 12, "Refresco de cola", CAT_BEBIDA, 30.00);
    registrar_platillo_menu(menu, total_platillos, 13, "Cafe de olla", CAT_BEBIDA, 40.00);

    // Postres
    registrar_platillo_menu(menu, total_platillos, 14, "Flan napolitano", CAT_POSTRE, 60.00);
    registrar_platillo_menu(menu, total_platillos, 15, "Pastel tres leches", CAT_POSTRE, 70.00);
    registrar_platillo_menu(menu, total_platillos, 16, "Churros con cajeta", CAT_POSTRE, 65.00);

    // Mesas
    inicializar_mesas(mesas, total_mesas);
    registrar_mesa(mesas, total_mesas, 1, 2);
    registrar_mesa(mesas, total_mesas, 2, 2);
    registrar_mesa(mesas, total_mesas, 3, 4);
    registrar_mesa(mesas, total_mesas, 4, 4);
    registrar_mesa(mesas, total_mesas, 5, 6);
    registrar_mesa(mesas, total_mesas, 6, 8);
}