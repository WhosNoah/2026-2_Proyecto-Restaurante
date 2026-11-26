#include <limpiar_buffer.h>

void limpiar_buffer(void) {
    int c;
    while ( (c = getchar()) != '\n' && c != EOF );
}
