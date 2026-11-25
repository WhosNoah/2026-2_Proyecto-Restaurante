#include <cuenta.h>

void desglosar_iva(double total_con_iva, double *subtotal, double *iva) {
    if ( total_con_iva < 0.0 ) 
        total_con_iva = 0.0;
    double sub = total_con_iva / 1.16;
    double imp = total_con_iva - sub;

    if ( subtotal != NULL )
        *subtotal = sub;
    if ( iva != NULL )
        *iva = imp;
}

double calcular_propina(double total_con_iva, double porcentaje_propina) {
    if ( total_con_iva < 0.0 || porcentaje_propina < 0.0 )
        return 0.0;
    return total_con_iva * (porcentaje_propina / 100.0);
}

int dividir_cuenta(double total_a_pagar, int num_personas, double *monto_primera_persona, double *monto_resto_personas) {
    if ( num_personas <= 0 || total_a_pagar < 0.0 )
        return 0;

    long long total_centavos = llround(total_a_pagar * 100.0);
    long long base_centavos = total_centavos / num_personas;
    long long resto_centavos = total_centavos % num_personas;

    long long primera_centavos = base_centavos + resto_centavos;
    
    if ( monto_primera_persona != NULL )
        *monto_primera_persona = (double)primera_centavos / 100.0;
    if ( monto_resto_personas != NULL )
        *monto_resto_personas = (double)base_centavos / 100.0;

    return 1;
}

int calcular_cuenta_mesa(const Mesa *mesa, double porcentaje_propina, int num_personas, DesgloseCuenta *cuenta) {
    if ( mesa == NULL || cuenta == NULL || num_personas <= 0 )
        return 0;

    cuenta->total_con_iva = total_comanda(&mesa->comanda);
    desglosar_iva(cuenta->total_con_iva, &cuenta->subtotal, &cuenta->iva);

    cuenta->porcentaje_propina = (porcentaje_propina >= 0.0 ) ? porcentaje_propina : 0.0;
    cuenta->propina = calcular_propina(cuenta->total_con_iva, cuenta->porcentaje_propina);
    cuenta->total_a_pagar = cuenta->total_con_iva + cuenta->propina;

    cuenta->num_personas = num_personas;
    return dividir_cuenta(cuenta->total_a_pagar, cuenta->num_personas, &cuenta->monto_primera_persona, &cuenta->monto_resto_personas);
}

void imprimir_cuenta(const Mesa *mesa, const DesgloseCuenta *cuenta) {
    if ( mesa == NULL || cuenta == NULL )
        return;

    printf("\nMesa %d - Mesero: %s\n", mesa->numero, mesa->mesero);
    for ( int i = 0; i < mesa->comanda.total_renglones; i++ ) {
        const RenglonComanda *r = &mesa->comanda.items[i];
        double importe = r->precio_unitario * r->cantidad;
        printf("  %d x %-24s $%7.2f", r->cantidad, r->nombre_platillo, importe);
        if ( r->nota[0] != '\0' )
            printf(" (%s)", r->nota);
        printf("\n");
    }

    printf("--------------------------------------------\n");
    printf("Subtotal ....................... $%8.2f\n", cuenta->subtotal);
    printf("IVA (16%%) ...................... $%8.2f\n", cuenta->iva);
    printf("Total .......................... $%8.2f\n", cuenta->total_con_iva);
    printf("Propina (%.0f%%) .................. $%8.2f\n", cuenta->porcentaje_propina, cuenta->propina);
    printf("TOTAL A PAGAR .................. $%8.2f\n", cuenta->total_a_pagar);

    if ( cuenta->num_personas == 1 )
        printf("Dividido entre 1: $%.2f\n", cuenta->monto_primera_persona);
    else if ( cuenta->num_personas > 1 )
        printf("Dividido entre %d: $%.2f + %d x $%.2f\n", cuenta->num_personas, cuenta->monto_primera_persona, cuenta->num_personas - 1, cuenta->monto_resto_personas);
}