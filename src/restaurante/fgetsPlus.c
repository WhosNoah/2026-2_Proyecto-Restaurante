#include <fgetsPlus.h>

void quitar_enter(char *cad)
{
    int i = 0;
    while ( cad[i] != '\0' )
    {
        if ( cad[i] == '\n' )
        {
            cad[i] = '\0';
            break;
        }
        i++;
    }
}

void fgetsPlus(char *cad, int max)
{
    int e = max-2;
    inicializar(cad, max, '\0');
    cad[e] = '\n';
    fgets(cad, max, stdin);
    if ( cad[e] != '\n' && buscar_caracter(cad, '\n') == 0 )
        limpiar_buffer();
    else
        quitar_enter(cad);
}

void inicializar(char *cad, int max, char c)
{
    for ( int i = 0; i < max; i++ )
        cad[i] = c;
}

int buscar_caracter(char *cad, char c)
{
    int i = 0;
    while ( cad[i] != '\0' )
    {
        if ( cad[i] == c )
            return 1;
        i++;
    }
    return 0;
}