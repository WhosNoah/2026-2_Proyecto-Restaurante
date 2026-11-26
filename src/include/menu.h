#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <string.h>

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
    int unidadesVendidas;
} Platillo;

void inicializarMenu(Platillo menu[], int *totalPlatillos);
int registrarPlatilloMenu(Platillo menu[], int *totalPlatillos, int id, const char *nombre, CategoriaPlatillo categoria, double precio);
int buscarPlatilloPorId(const Platillo menu[], int totalPlatillos, int id);
const char* obtenerNombreCategoria(CategoriaPlatillo categoria);
void mostrarMenu(const Platillo menu[], int totalPlatillos);

#endif