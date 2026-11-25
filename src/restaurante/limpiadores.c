#include <limpiadores.h>

void limpiar_buffer(void) {
    int c;
    while ( (c = getchar()) != '\n' && c != EOF );
}

void limpiar_terminal(void) {
    #ifdef _WIN32
        system("cls");
    #elif defined (__linux__)
        system("clear");
    #elif defined (__APPLE__)
        system("clear");
    #endif
}
