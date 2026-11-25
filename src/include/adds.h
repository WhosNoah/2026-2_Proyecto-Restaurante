#ifndef ADDS_H
#define ADDS_H

#include <stdio.h>
#include <fgetsplus.h>
#include <limpiadores.h>

void leer_cadena(const char *prompt, char *destino, int tam_max);
int leer_entero(const char *prompt);
double leer_double(const char *prompt);
double pedir_porcentaje_propina(void);

#endif
