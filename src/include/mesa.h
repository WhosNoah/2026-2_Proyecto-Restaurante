#ifndef MESA_H
#define MESA_H

#include <menu.h>
#include <stdio.h>
#include <string.h>
#include <comanda.h>

#define MAX_MESAS 20
#define MAX_MESEROS 10
#define MAX_NOMBRE_MESERO 40

typedef enum {
    MESA_LIBRE = 0,
    MESA_ABIERTA = 1
} EstadoMesa;

typedef struct {
    int numero;
    int capacidad;
    EstadoMesa estado;
    char mesero[MAX_NOMBRE_MESERO];
    int comensales;
    Comanda comanda;
} Mesa;

typedef struct {
    char nombre[MAX_NOMBRE_MESERO];
    double totalVendido;
    int mesasAtendidas;
} VentaMesero;


void inicializarMesas(Mesa mesas[], int *totalMesas);
int registrarMesa(Mesa mesas[], int *totalMesas, int numero, int capacidad);
int buscarMesaPorNumero(const Mesa mesas[], int totalMesas, int numero);
void inicializarVentasMeseros(VentaMesero ventasMeseros[], int *totalMeseros);
int asegurarMesero(VentaMesero ventasMeseros[], int *totalMeseros, const char *nombreMesero);
int abrirMesa(Mesa mesas[], int totalMesas, int numeroMesa, const char *nombreMesero, int comensales);
int cerrarMesa(Mesa mesas[], int totalMesas, int numeroMesa, Platillo menu[], int totalPlatillos, VentaMesero ventasMeseros[], int *totalMeseros, double *totalCobrado);
void mostrarMapaMesas(const Mesa mesas[], int totalMesas);
void mostrarReporteVentas(const VentaMesero ventasMeseros[], int totalMeseros, const Platillo menu[], int totalPlatillos);

#endif