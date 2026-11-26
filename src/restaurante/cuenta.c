#include <cuenta.h>

void desglosarIVA(double totalConIVA, double *subtotal, double *iva) {
    if (totalConIVA < 0.0) {
        totalConIVA = 0.0;
    }
    double sub = totalConIVA / 1.16;
    double imp = totalConIVA - sub;

    if (subtotal != NULL) {
        *subtotal = sub;
    }
    if (iva != NULL) {
        *iva = imp;
    }
}

double calcularPropina(double totalConIVA, double porcentajePropina) {
    if (totalConIVA < 0.0 || porcentajePropina < 0.0) {
        return 0.0;
    }
    return totalConIVA * (porcentajePropina / 100.0);
}

int dividirCuenta(double totalAPagar, int numPersonas, double *montoPrimeraPersona, double *montoRestoPersonas) {
    if (numPersonas <= 0 || totalAPagar < 0.0) {
        return 0;
    }

    long long totalCentavos = llround(totalAPagar * 100.0);
    long long baseCentavos = totalCentavos / numPersonas;
    long long restoCentavos = totalCentavos % numPersonas;

    long long primeraCentavos = baseCentavos + restoCentavos;

    if (montoPrimeraPersona != NULL) {
        *montoPrimeraPersona = (double)primeraCentavos / 100.0;
    }
    if (montoRestoPersonas != NULL) {
        *montoRestoPersonas = (double)baseCentavos / 100.0;
    }

    return 1;
}

int calcularCuentaMesa(const Mesa *mesa, double porcentajePropina, int numPersonas, DesgloseCuenta *cuenta) {
    if (mesa == NULL || cuenta == NULL || numPersonas <= 0) {
        return 0;
    }

    cuenta->totalConIVA = totalComanda(&mesa->comanda);
    desglosarIVA(cuenta->totalConIVA, &cuenta->subtotal, &cuenta->iva);

    cuenta->porcentajePropina = (porcentajePropina >= 0.0) ? porcentajePropina : 0.0;
    cuenta->propina = calcularPropina(cuenta->totalConIVA, cuenta->porcentajePropina);
    cuenta->totalAPagar = cuenta->totalConIVA + cuenta->propina;

    cuenta->numPersonas = numPersonas;
    return dividirCuenta(cuenta->totalAPagar, cuenta->numPersonas, &cuenta->montoPrimeraPersona, &cuenta->montoRestoPersonas);
}

void imprimirCuenta(const Mesa *mesa, const DesgloseCuenta *cuenta) {
    if (mesa == NULL || cuenta == NULL) {
        return;
    }

    printf("\nMesa %d — Mesero: %s\n", mesa->numero, mesa->mesero);
    for (int i = 0; i < mesa->comanda.totalRenglones; i++) {
        const RenglonComanda *r = &mesa->comanda.items[i];
        double importe = r->precioUnitario * r->cantidad;
        printf("  %d x %-24s $%7.2f", r->cantidad, r->nombrePlatillo, importe);
        if (r->nota[0] != '\0') {
            printf(" (%s)", r->nota);
        }
        printf("\n");
    }

    printf("--------------------------------------------\n");
    printf("Subtotal ....................... $%8.2f\n", cuenta->subtotal);
    printf("IVA (16%%) ...................... $%8.2f\n", cuenta->iva);
    printf("Total .......................... $%8.2f\n", cuenta->totalConIVA);
    printf("Propina (%.0f%%) .................. $%8.2f\n", cuenta->porcentajePropina, cuenta->propina);
    printf("TOTAL A PAGAR .................. $%8.2f\n", cuenta->totalAPagar);

    if (cuenta->numPersonas == 1) {
        printf("Dividido entre 1: $%.2f\n", cuenta->montoPrimeraPersona);
    } else if (cuenta->numPersonas > 1) {
        printf("Dividido entre %d: $%.2f + %d x $%.2f\n", cuenta->numPersonas, cuenta->montoPrimeraPersona, cuenta->numPersonas - 1, cuenta->montoRestoPersonas);
    }
}