#include <menu.h>

void inicializar_menu(Platillo menu[], int *total_platillos) {
    *total_platillos = 0;

    for ( int i = 0; i < MAX_PLATILLOS; i++ ) {
        menu[i].id = 0;
        menu[i].nombre[0] = '\0';
        menu[i].categoria = CAT_ENTRADA;
        menu[i].precio = 0.0;
        menu[i].unidades_vendidas = 0;
    }
}

int registrar_platillo(Platillo menu[], int *total_platillos, int id, const char *nombre, CategoriaPlatillo categoria, double precio) {
    if ( *total_platillos >= MAX_PLATILLOS || precio < 0.0 ) {
        printf("\nError: [ Menu lleno o precio invalido ].\n");
        return 0;
    }

    if ( buscar_platillo_por_id(menu, *total_platillos, id) != -1 ) {
        printf("\nError: [ Platillo no encontrado / ID inexistente ].\n");
        return 0;
    }

    int idx = *total_platillos;
    menu[idx].id = id;
    strncpy(menu[idx].nombre, nombre, MAX_NOMBRE_PLATILLO - 1);
    menu[idx].nombre[MAX_NOMBRE_PLATILLO - 1] = '\0';
    menu[idx].categoria = categoria;
    menu[idx].precio = precio;
    menu[idx].unidades_vendidas = 0;

    (*total_platillos)++;
    return 1;
}

int buscar_platillo_id(const Platillo menu[], int total_platillos, int id) {
    for ( int i = 0; i < total_platillos; i++ ) {
        if ( menu[i].id == id )
            return i;
    }
    return -1;
}

const char *obtener_nombre_categoria(CategoriaPlatillo categoria) {
    switch ( categoria ) {
        case CAT_ENTRADA:       return "Entradas";
        case CAT_PLATO_FUERTE:  return "Platos Fuertes";
        case CAT_BEBIDAS:       return "Bebidas";
        case CAT_POSTRE:       return "Postres";
        default:                return "Otras";
    }
}

void mostrar_menu(const Platillo menu[], int total_platillos) {
    CategoriaPlatillo categorias = {
        CAT_ENTRADA, CAT_PLATO_FUERTE, CAT_BEBIDAS, CAT_POSTRE
    };

    printf("*-------------------------------------------------------*\n");
    printf("|                            MENU                       |\n");
    printf("|       Todos los precios incluyen el iva del 16%%      |\n");

    for ( int c = 0; c < 4; i++ ) {
        printf("\n-- %s --\n". obtener_nombre_categoria(categorias[c]));
        for ( int i = 0; i < total_platillos; i++ ) {
            if ( menu[i].categoria == categorias[c] ) {
                printf("  [%2d] %-32s  $%7.2f\n", menu[i].id, menu[i].nombre, menu[i.precio]);
            }
        }
    }
    printf("*-------------------------------------------------------*\n");
}
