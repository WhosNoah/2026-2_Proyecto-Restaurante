#ifndef CUENTA_H
#define CUENTA_H

#include <math.h>
#include <mesa.h>
#include <stdio.h>

typedef struct {
    double total_con_iva;
    double subtotal;
    double iva;
    double porcentaje_propina;
    double propina;
    double total_a_pagar;
    int num_personas;
    double monto_primera_persona;
    double monto_resto_personas;
} DesgloseCuenta;

void desglosar_iva(double total_con_iva, double *subtotal, double *iva);
double calcular_propina(double total_con_iva, double porcentaje_propina);
int dividir_cuenta(double total_a_pagar, int num_personas, double *monto_primera_persona, double *monto_resto_personas);
int calcular_cuenta_mesa(const Mesa *mesa, double porcentaje_propina, int num_personas, DesgloseCuenta *cuenta);
void imprimir_cuenta(const Mesa *mesa, const DesgloseCuenta *cuenta);

#endif