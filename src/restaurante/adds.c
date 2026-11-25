#include <adds.h>

void leer_cadena(const char *prompt, char *destino, int tam_max) {
    printf("%s", prompt);
    if ( fgetsPlus(destino, tam_max) != NULL )
        limpiar_buffer();
    else
        destino[0] = '\0';
}

int leer_entero(const char *prompt) {
    char buffer[64];
    
    while ( 1 ) {
        leer_cadena(prompt, buffer, sizeof(buffer));

        int i = 0;
        int signo = 1;

        if ( buffer[0] == '\0' ) {
            printf("  Entrada vacia. Intente de nuevo.\n");
            continue;
        }
        if ( buffer[0] == '-' ) {
            signo = -1;
            i = 1;
        } else if ( buffer[0] == '+' ) {
            i = 1;
        }

        if ( buffer[i] == '\0' ) {
            printf("  Numero entero invalido. Intente de nuevo.\n");
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
            i++;
        }

        if ( valido )
            return numero * signo;

        printf("  Numero entero invalido. Intente de nuevo.\n");
    }
}

double leer_double(const char *prompt) {
    char buffer[64];

    while ( 1 ) {
        leer_cadena(prompt, buffer, sizeof(buffer));

        int i = 0;
        int signo = 1;

        if ( buffer[0] == '\0' ) {
            printf("  Entrada vacia. Intente de nuevo.\n");
            continue;
        }
        if ( buffer[0] == '-' ) {
            signo = -1;
            i = 1;
        } else if ( buffer[0] == '+' ) {
            i = 1;
        }

        int valido = 1;
        int tiene_digito = 0;
        double parte_entera = 0.0;
        double parte_decimal = 0.0;
        double divisor = 10.0;
        int en_decimal = 0;

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
            i++;
        }

        if ( valido && tiene_digito )
            return ( parte_entera + parte_decimal ) * signo;

        printf("  Numero decimal invalido. Intente denuevo.\n");
    }
}

double pedir_porcentaje_propina(void) {
    printf("\nCuanto va a dejar de propina:\n");
    printf(" 1. 10%%\n");
    printf(" 2. 15%%\n");
    printf(" 3. 20%%\n");
    printf(" 4. Personalizada\n");
    printf(" 5. Sin propina ( 0%% )\n");

    int op = leer_entero("Opcion: ");
    switch ( op ) {
        case 1: return 10.0;
        case 2: return 15.0;
        case 3: return 20.0;
        case 4: {
            double p = leer_double("Ingresa porcentaje de propina (ej: 12.5): ");
            return ( p >= 0.0 ) ? p : 0.0;
        }
        default: return 0.0;
    }
}