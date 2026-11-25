#include <ui.h>
#include <mesa.h>
#include <menu.h>
#include <catalogo.h>

int main(void) {
    Platillo menu[MAX_PLATILLOS];
    int total_platillos = 0;

    Mesa mesas[MAX_MESAS];
    int total_mesas = 0;

    VentaMesero ventas_meseros[MAX_MESEROS];
    int total_meseros = 0;

    inicializar_ventas_meseross(ventas_meseros, &total_meseros);
    cargar_datos(menu, &total_platillos, mesas, &total_meseros);

    user_interface(menu, total_platillos, mesas, total_mesas, ventas_meseros, &total_meseros);

    return 0;
}