#include <adds.h>

void quitarSaltoLinea(char *cadena) {
    int i = 0;
    while ( cadena[i] != '\0' ) {
        if ( cadena[i] == '\n' ) {
            cadena[i] = '\0';
            break;
        }
        i++;
    }
}

void leerCadena(const char *prompt, char *destino, int tamMax) {
    printf("%s", prompt);
    if (fgets(destino, tamMax, stdin) != NULL) {
        if (strchr(destino, '\n') == NULL) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
        }
        quitarSaltoLinea(destino);
    } else {
        destino[0] = '\0';
    }
}

 int leer_entero(const char *prompt) {
    char buffer[64];

    while (1) {
        leerCadena(prompt, buffer, sizeof(buffer));

        int i = 0;
        int signo = 1;

        if (buffer[0] == '\0') {
            printf("  Entrada vacia. Intenta de nuevo.\n");
            continue;
        }

        if (buffer[0] == '-') {
            signo = -1;
            i = 1;
        } else if (buffer[0] == '+') {
            i = 1;
        }

        if (buffer[i] == '\0') {
            printf("  Numero entero invalido. Intenta de nuevo.\n");
            continue;
        }

        int valido = 1;
        int numero = 0;

        while (buffer[i] != '\0') {
            if (buffer[i] < '0' || buffer[i] > '9') {
                valido = 0;
                break;
            }
            numero = numero * 10 + (buffer[i] - '0');
            i++;
        }

        if (valido) {
            return numero * signo;
        }

        printf("  Numero entero invalido. Intenta de nuevo.\n");
    }
}

double leer_double(const char *prompt) {
    char buffer[64];

    while (1) {
        leerCadena(prompt, buffer, sizeof(buffer));

        int i = 0;
        int signo = 1;

        if (buffer[0] == '\0') {
            printf("  Entrada vacia. Intenta de nuevo.\n");
            continue;
        }

        if (buffer[0] == '-') {
            signo = -1;
            i = 1;
        } else if (buffer[0] == '+') {
            i = 1;
        }

        int valido = 1;
        int tiene_digito = 0;
        double parte_entera = 0.0;
        double parte_decimal = 0.0;
        double divisor = 10.0;
        int en_decimal = 0;

        while (buffer[i] != '\0') {
            char c = buffer[i];

            if (c >= '0' && c <= '9') {
                tiene_digito = 1;
                if (!en_decimal) {
                    parte_entera = parte_entera * 10.0 + (c - '0');
                } else {
                    parte_decimal += (c - '0') / divisor;
                    divisor *= 10.0;
                }
            } else if (c == '.' && !en_decimal) {
                en_decimal = 1;
            } else {
                valido = 0;
                break;
            }
            i++;
        }

        if (valido && tiene_digito) {
            return (parte_entera + parte_decimal) * signo;
        }

        printf("  Numero decimal invalido. Intenta de nuevo.\n");
    }
}