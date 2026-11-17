#ifndef COMANDA_H
#define COMANDA_H

#include "menu.h"

#define MAX_RENGLONES_COMANDA 30
#define MAX_CANTIDAD_PLATILLO 99
#define MAX_NOTA 100

typedef struct
{
	int id_platillo;
	char nombre[MAX_NOMBRE];
	int precio_unitario_centavos;
	int cantidad;
	char nota[MAX_NOTA + 1];
} DetalleComanda;

typedef struct
{
	DetalleComanda detalles[MAX_RENGLONES_COMANDA];
	int num_detalles;
} Comanda;

#endif