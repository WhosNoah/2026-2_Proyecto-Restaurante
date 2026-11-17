#ifndef MENU_H
#define MENU_H

#include <stdbool.h>

#define MAX_PLATILLOS 20
#define MAX_NOMBRE 50

typedef enum
{
	ENTRADA,
	PLATO_FUERTE,
	BEBIDA,
	POSTRE,
} Categoria;

typedef struct
{
	int id;
	char nombre[MAX_NOMBRE];
	Categoria categoria;
	int precio_centavos;
	bool disponible;
} Platillo;

#endif