#ifndef FLUJOS_H
#define FLUJOS_H

#include <adds.h>
#include <menu.h>
#include <mesa.h>
#include <stdio.h>
#include <cuenta.h>

void flujoAbrirMesa(Mesa mesas[], int totalMesas);
void flujoAgregarPlatillo(Mesa mesas[], int totalMesas, const Platillo menu[], int totalPlatillos);
void flujoQuitarPlatillo(Mesa mesas[], int totalMesas);
void flujoVerCuenta(const Mesa mesas[], int totalMesas);
void flujoCerrarMesa(Mesa mesas[], int totalMesas, Platillo menu[], int totalPlatillos, VentaMesero ventasMeseros[], int *totalMeseros);


#endif