#ifndef FLUJOS_H
#define FLUJOS_H

#include <menu.h>
#include <mesa.h>
#include <stdio.h>
#include <cuenta.h>
#include <pedirPropina.h>

void flujo_abrir_mesa(Mesa mesas[], int total_mesas);
void flujo_agregar_platillo(Mesa mesas[], int total_mesas, const Platillo menu[], int total_platillos);
void flujo_quitar_platillo(Mesa mesas[], int total_mesas);
void flujo_ver_cuenta(const Mesa mesas[], int total_mesas);
void flujo_cerrar_mesa(Mesa mesas[], int total_mesas, Platillo menu[], int total_platillos, VentaMesero ventas_meseros[], int *total_meseros);

#endif