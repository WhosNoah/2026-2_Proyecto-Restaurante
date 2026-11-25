#include <ui.h>
#include <data.h>
#include <menu.h>
#include <mesa.h>

int main(void) {
    Platillo menu;
    int total_platillos = 0;

    Mesa mesas[MAX_MESAS];
    int total_mesas = 0;

    VentaMesero ventas_meseros[MAX_MESEROS];
    int total_meseros = 0;

    inicializar_ventas_meseros(ventas_meseros, &total_meseros);
    cargar_datos(menu, &total_platillos, mesas, &total_mesas);

    ejecutar_sistema(menu, total_platillos, mesas, total_mesas, ventas_meseros, &total_meseros);

    return 0;
}