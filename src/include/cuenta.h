#ifndef CUENTA_H
#define CUENTA_H

#include "mesa.h"

#define MAX_VENTAS_DIA 100

typedef enum
{
	EFECTIVO,
	TARJETA
} MetodoPago;

typedef struct
{
	int id_venta;
	
	char id_mesa[4];
	
	int id_mesero_og;
	int id_mesero_responsable;
	
	int num_comensales;
	
	DetalleComanda detalles[MAX_RENGLONES_COMANDA];
	int num_detalles;
	
	int subtotal_centavos;
	int iva_centavos;
	
	int porcentaje_propina;
	int propina_centavos;
	
	int total_consumo_centavos;
	int total_pagar_centavos;
	
	MetodoPago metodo_pago;
	
	int efectivo_recibido_centavos;
	int cambio_centavos;
} Venta;

typedef struct
{
	Venta ventas[MAX_VENTAS_DIA];
	int num_ventas;
} HistorialVentas;

#endif