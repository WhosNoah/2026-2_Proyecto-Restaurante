#include <fgetsplus.h>

void inicializar(char *cadena, int max, char c) {
    for ( int i = 0; i < max; i++ )
        cadena[i] = c;
}

void quitar_salto(char *cadena) {
    if ( cadena == NULL )
        return;

    int i = 0;
    while ( cadena[i] != '\0' ) {
        if ( cadena[i] == '\n' ) {
            cadena[i] = '\0';
            break;
        }
        i++;
    }
}

void fgetsPlus(char *cadena, int max) {
    int e = max - 2;
    inicializar(cadena, max, '\0');
    cadena[e] = '\n';
    fgets(cadena, max, stdin);
    if ( cadena[e] != '\n' && buscar_caracter(cadena, '\n') == 0 )
        limpiar_buffer();
    else
        quitar_salto(cadena);
}

int buscar_caracter(char *cadena, char c) {
    int i = 0;
    while ( cadena[i] != '\0' ) {
        if ( cadena[i] == c )
            return 1;
        i++;
    }
    return 0;
}