#include <ui.h>
#include <menu.h>
#include <mesa.h>
#include <datos.h>

int main(void) {
    Platillo menu[MAX_PLATILLOS];
    int totalPlatillos = 0;

    Mesa mesas[MAX_MESAS];
    int totalMesas = 0;

    VentaMesero ventasMeseros[MAX_MESEROS];
    int totalMeseros = 0;

    inicializarVentasMeseros(ventasMeseros, &totalMeseros);
    cargarDatosIniciales(menu, &totalPlatillos, mesas, &totalMesas);

    ejecutarSistemaRestaurante(menu, totalPlatillos, mesas, totalMesas, ventasMeseros, &totalMeseros);

    return 0;
}