#ifndef COMANDA_H
#define COMANDA_H

#include <menu.h>
#include <stdio.h>
#include <string.h>

#define MAX_RENGLONES 50
#define MAX_NOTA 80

typedef struct {
    int id_platillo;
    char nombre_platillo[MAX_NOMBRE_PLATILLO];
    double precio_unitario;
    int cantidad;
    char nota[MAX_NOTA];
} RenglonComanda;

typedef struct {
    RenglonComanda items[MAX_RENGLONES];
    int total_renglones;
} Comanda;

void inicializar_comanda(Comanda *comanda);
int agregar_platillo(Comanda *comanda, const Platillo menu[], int total_platillos, int id_platillo, int cantidad, const char *nota);
int quitar_platillo(Comanda *comanda, int id_platillo, int cantidad_a_quitar);
double total_comanda(const Comanda *comanda);
void mostrar_comanda(const Comanda *comanda);

#endif
