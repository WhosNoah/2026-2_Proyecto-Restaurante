#ifndef MENU_H
#define MENU_H

#define MAX_PLATILLOS 30
#define MAX_NOMBRE_PLATILLO 50

typedef enum {
    CAT_ENTRADA = 1,
    CAT_PLATO_FUERTE,
    CAT_BEBIDA,
    CAT_POSTRE
} CategoriaPlatillo;

typedef struct {
    int id;
    char nombre[MAX_NOMBRE_PLATILLO];
    CategoriaPlatillo categoria;
    double precio;
    int unidades_vendidas;
} Platillo;

void inicializar_menu(Platillo menu[], int *total_platillos);
int registrar_platillo_menu(Platillo menu[], int *total_platillos, int id, const char *nombre, CategoriaPlatillo categoria, double precio);
int buscar_platillo_id(const Platillo menu[], int total_platillos, int id);
const char* obtener_nombre_categoria(CategoriaPlatillo categoria);
void mostrar_menu(const Platillo menu[], int total_platillos);

#endif
