#ifndef CUENTA_H
#define CUENTA_H

#include <math.h>
#include <mesa.h>
#include <stdio.h>

typedef struct {
    double totalConIVA;
    double subtotal; 
    double iva;
    double porcentajePropina;
    double propina;
    double totalAPagar;
    int numPersonas;
    double montoPrimeraPersona;
    double montoRestoPersonas;
} DesgloseCuenta;

void desglosarIVA(double totalConIVA, double *subtotal, double *iva);
double calcularPropina(double totalConIVA, double porcentajePropina);
int dividirCuenta(double totalAPagar, int numPersonas, double *montoPrimeraPersona, double *montoRestoPersonas);
int calcularCuentaMesa(const Mesa *mesa, double porcentajePropina, int numPersonas, DesgloseCuenta *cuenta);
void imprimirCuenta(const Mesa *mesa, const DesgloseCuenta *cuenta);

#endif