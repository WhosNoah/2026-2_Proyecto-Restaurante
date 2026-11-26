#include <pedirpropina.h>

double pedirPorcentajePropina(void) {
    printf("\nSelecciona propina:\n");
    printf("  1. 10%%\n");
    printf("  2. 15%%\n");
    printf("  3. 20%%\n");
    printf("  4. Personalizada\n");
    printf("  5. Sin propina (0%%)\n");

    int op = leer_entero("Opcion: ");
    switch (op) {
        case 1: return 10.0;
        case 2: return 15.0;
        case 3: return 20.0;
        case 4: {
            double p = leer_double("Ingresa porcentaje de propina (ej. 12.5): ");
            return (p >= 0.0) ? p : 0.0;
        }
        default: return 0.0;
    }
}