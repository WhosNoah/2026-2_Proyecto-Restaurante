#ifndef COMANDA_H
#define COMANDA_H

#include <adds.h>
#include <menu.h>
#include <stdio.h>
#include <string.h>

#define MAX_RENGLONES 40
#define MAX_NOTA 80

typedef struct {
    int idPlatillo;
    char nombrePlatillo[MAX_NOMBRE_PLATILLO];
    double precioUnitario;
    int cantidad;
    char nota[MAX_NOTA];
} RenglonComanda;

typedef struct {
    RenglonComanda items[MAX_RENGLONES];
    int totalRenglones;
} Comanda;

int buscarRenglonPorId(const Comanda *comanda, int idPlatillo);
void eliminarRenglonEnIndice(Comanda *comanda, int indice);
void inicializarComanda(Comanda *comanda);
int agregarPlatillo(Comanda *comanda, const Platillo menu[], int totalPlatillos, int idPlatillo, int cantidad, const char *nota);
int quitarPlatillo(Comanda *comanda, int idPlatillo, int cantidadAQuitar);
double totalComanda(const Comanda *comanda);
void mostrarComanda(const Comanda *comanda);

#endif