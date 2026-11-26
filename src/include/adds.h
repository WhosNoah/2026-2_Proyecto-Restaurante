#ifndef ADDS_H
#define ADDS_H

#include <stdio.h>
#include <string.h>

void quitarSaltoLinea(char *cadena);
void leerCadena(const char *prompt, char *destino, int tamMax);
int leerEntero(const char *prompt);
double leerDouble(const char *prompt);
void copiarCadena(char *destino, const char *origen, int tamMax);

#endif