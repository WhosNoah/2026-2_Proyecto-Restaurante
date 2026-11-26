#ifndef ADDS_H
#define ADDS_H

#include <stdio.h>
#include <string.h>

void quitarSaltoLinea(char *cadena);
void leerCadena(const char *prompt, char *destino, int tamMax);
int leer_entero(const char *prompt);
double leer_double(const char *prompt);

#endif