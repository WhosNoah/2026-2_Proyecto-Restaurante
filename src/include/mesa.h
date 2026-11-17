#ifndef MESA_H
#define MESA_H

#include "comanda.h"

#define MAX_MESAS 10
#define MAX_MESEROS 3

typedef enum
{
	LIBRE,
	OCUPADA
} EstadoMesa;

typedef enum 
{
	INACTIVO,
	ACTIVO
} EstadoMesero;

typedef struct
{
	int id;
	char nombre[MAX_NOMBRE];
	EstadoMesero estado;
} Mesero;

typedef struct
{
	char id[4];
	
	int capacidad;
	EstadoMesa estado;
	int num_comensales;
	
	int id_mesero_og;
	int id_mesero_responsable;
	
	Comanda comanda;
} Mesa;

#endif