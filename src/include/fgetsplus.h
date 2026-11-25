#ifndef FGETSPLUS_H
#define FGETSPLUS_H

#include <stdio.h>
#include <limpiadores.h>

void inicializar(char *cadena, int max, char c);
void quitar_salto(char *cadena);
void fgetsPlus(char *cadena, int max);
int buscar_caracter(char *cadena, char c);

#endif