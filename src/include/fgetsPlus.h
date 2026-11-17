#ifndef FGETSPLUS_H
#define FGETSPLUS_H

#include <stdio.h>
#include <limpiadores.h>

void quitar_enter(char *cad);
void fgetsPlus(char *cad, int max);
void inicializar(char *cad, int max, char c);
int buscar_caracter(char *cad, char c);

#endif