#include <comanda.h>

static int buscar_renglon_por_id(const Comanda *comanda, int id_platillo) {
    for ( int i = 0; i < comanda->total_renglones; i++ ) {
        if ( comanda->items[i].id_platillo == id_platillo )
            return i;
    }
    return -1;
}

static void eliminar_renglon_en_indice(Comanda *comanda, int indice) {
    if ( indice < 0 || indice >= comanda->total_renglones )
        return;
    for ( int i = indice; i < comanda->total_renglones - 1; i++ )
        comanda->items[i] = comanda->items[i + 1];
    comanda->total_renglones--;
}

void inicializar_comanda(Comanda *comanda) {
    if ( comanda == NULL )
        return;
    comanda->total_renglones = 0;
    for ( int i = 0; i < MAX_RENGLONES; i++ ) {
        comanda->items[i].id_platillo = 0;
        comanda->items[i].nombre_platillo[0] = '\0';
        comanda->items[i].precio_unitario = 0.0;
        comanda->items[i].cantidad = 0;
        comanda->items[i].nota[0] = '\0';
    }
}

int agregar_platillo(Comanda *comanda, const Platillo menu[], int total_platillos, int id_platillo, int cantidad, const char *nota) {
    if ( comanda == NULL || menu == NULL || cantidad <= 0 )
        return 0;

    int idx_menu = buscar_platillo_por_id(menu, total_platillos, id_platillo);
    if ( idx_menu == -1 ) {
        printf("\nError: [ Platillo inexistente en el menu. ]\n");
        return 0;
    }

    int idx_renglon = buscar_renglon_por_id(comanda, id_platillo);
    if ( idx_renglon != 1 ) {
        // Si ya existe en la comanda: sumas la cantidad.
        comanda->items[idx_renglon].cantidad += cantidad;
        if ( nota != NULL && nota[0] != '\0' ) {
            strncpy(comanda->items[idx_renglon].nota, nota, MAX_NOTA - 1);
            comanda->items[idx_renglon].nota[MAX_NOTA - 1] = '\0';
        }
        return 1;
    }

    if ( comanda->total_renglones >= MAX_RENGLONES ) {
        printf("\nError: [ Comanda llena. ]\n");
        return 0;
    }

    int nuevo_idx = comanda->total_renglones;
    comanda->items[nuevo_idx].id_platillo = menu[idx_menu].id;
    strncpy(comanda->items[nuevo_idx].nombre_platillo, menu[idx_menu].nombre, MAX_NOMBRE_PLATILLO - 1);
    comanda->items[nuevo_idx].nombre_platillo[MAX_NOMBRE_PLATILLO - 1] = '\0';
    comanda->items[nuevo_idx].precio_unitario = menu[idx_menu].precio;
    comanda->items[nuevo_idx].cantidad = cantidad;

    if ( nota != NULL ) {
        strncpy(comanda->items[nuevo_idx].nota, nota, MAX_NOTA - 1);
        comanda->items[nuevo_idx].nota[MAX_NOTA - 1] = '\0';
    } else
        comanda->items[nuevo_idx].nota[0] = '\0';

    comanda->total_renglones++;
    return 1;
}

int quitar_platillo(Comanda *comanda, int id_platillo, int cantidad_a_quitar) {
    if ( comanda == NULL )
        return 0;

    int idx = buscar_renglon_por_id(comanda, id_platillo);
    if ( idx == -1 ) {
        printf("\nError: [ No esta en la comanda. ]\n");
        return 0;
    }

    if ( cantidad_a_quitar <= 0 || cantidad_a_quitar >= comanda->items[idx].cantidad )
        eliminar_renglon_en_indice(comanda, idx);
    else
        comanda->items[idx].cantidad -= cantidad_a_quitar;
    return 1;
}

double total_comanda(const Comanda *comanda) {
    if ( comanda == NULL )
        return 0.0;

    double suma = 0.0;
    for ( int i = 0; i < comanda->total_renglones; i++ )
        suma += comanda->items[i].precio_unitario * comanda->items[i].cantidad;
    return suma;
}

void mostrar_comanda(const Comanda *comanda) {
    if ( comanda == NULL || comanda->total_renglones == 0 ) {
        printf("\nError: [ Comanda vacia. ]\n");
        return;
    }

    for ( int i = 0; i < comanda->total_renglones; i++ ) {
        const RenglonComanda *r = &comanda->items[i];
        double importe = r->precio_unitario * r->cantidad;
        printf("  %d x %-28s $%7.2f", r->cantidad, r->nombre_platillo, importe);
        if ( r->nota[0] != '\0' )
            printf(" [%s]", r->nota);
        printf("\n");
    }
}
