#ifndef MESA_H
#define MESA_H

#include <menu.h>
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
    double total_vendido;
    int mesas_atendidas;
} VentaMesero;

void inicializar_mesas(Mesa mesas[], int *total_mesas);
int registrar_mesa(Mesa mesas[], int *total_mesas, int numero, int capacidad);
int buscar_mesa_por_numero(const Mesa mesas[], int total_mesas, int numero);
void inicializar_ventas_meseros(VentaMesero ventas_meseros[], int *total_meseros);
int asegurar_mesero(VentaMesero ventas_meseros[], int *total_meseros, const char *nombre);

int abrir_mesa(Mesa mesas[], int total_mesas, int numero_mesa, const char *nombre_mesero, int comensales);
int cerrar_mesa(Mesa mesas[], int total_mesas, VentaMesero ventas_meseros[], int *total_meseros, double *total_cobrado);
void mostrar_mapa_mesas(const Mesa mesas[], int total_mesas);
void mostrar_reporte_ventas(const VentaMesero mostrar_reporte_ventas[], int total_meseros, const Platillo menu[], int total_platillos);

#endif