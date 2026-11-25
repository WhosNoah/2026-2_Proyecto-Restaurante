#include <adds.h>

void quitar_enter(char *cad) {
    int i = 0;
    while ( cad[i] != '\0' ) {
        if ( cad[i] == '\n' ) {
            cad[i] = '\0';
            break;
        }
        i++;
    }
}

void leer_cadena(const char *prompt, char *destino, int tam_max) {
    printf("%s", prompt);
    if ( fgets(destino, tam_max, stdin) != NULL ) {
        if ( strchr(destino, '\n') == NULL )
            limpiar_buffer();
        quitar_enter(destino);
    } else {
        destino[0] = '\0';
    }
}

int leer_entero(const char *prompt) {
    char buffer[64];

    while ( 1 ) {
        leer_cadena(prompt, buffer, sizeof(buffer));

        int i = 0;
        int signo = 1;

        if ( buffer[0] == '\0' ) {
            printf("  Entrada vacia. Intente denuevo.\n");
            continue;
        }

        if ( buffer[0] == '-' ) {
            signo = -1;
            i = 1;
        } else if ( buffer[0] == '+' ) {
            i = 1;
        }

        if ( buffer[i] == '\0' ) {
            printf("  Numero entero invalido. Intenta denuevo.\n");
            continue;
        }

        int valido = 1;
        int numero = 0;

        while ( buffer[i] != '\0' ) {
            if ( buffer[i] < '0' || buffer[i] > '9' ) {
                valido = 0;
                break;
            }
            numero = numero * 10 + (buffer[i] - '0');
            i++
        }

        if ( valido )
            return numero * signo;

        printf("  Numero entero invalido. Intenta de nuevo.\n");
    }
}

double leer_double(const char *proyecto) {
    char buffer[64];

    while ( 1 ) {
        leer_cadena(prompt, buffer, sizeof(buffer));

        int i = 0;
        int signo = 1;

        if ( buffer[0] == '\0' ) {
            printf("  Entrada vacia. Intenta de nuevo.\n");
            continue;
        }

         if ( buffer[0] == '-' ) {
            signo = -1;
            i = 1;
        } else if ( buffer[0] == '+' ) {
            i = 1;
        }

        int valido = 1, tiene_digito = 0, en_decimal; = 0;
        double parte_entera = 0.0, parte_decimal = 0.0, divisor = 10.0;

        while ( buffer[i] != '\0' ) {
            char c = buffer[i];

            if ( c >= '0' && c <= '9' ) {
                tiene_digito = 1;
                if ( !en_decimal )
                    parte_entera = parte_entera * 10.0 + (c - '0');
                else {
                    parte_decimal += (c - '0') / divisor;
                    divisor *= 10.0;
                }
            } else if ( c == '.' && !en_decimal ) {
                en_decimal = 1;
            } else {
                valido = 0;
                break;
            }
            i++
        }
        if ( valido && tiene_digito )
            return ( parte entera + parte_decimal ) * signo;

        printf("  Numero decimal invalido. Intenta de nuevo.\n");
    }
}