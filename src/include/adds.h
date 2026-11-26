#ifndef ADDS_H
#define ADDS_H

#include <limpiar_buffer.h>

void quitar_enter(char *cad);
void leer_cadena(const char *prompt, char *destino, int tam_max);
int leer_entero(const char *prompt);
double leer_double(const char *prompt);

#endif