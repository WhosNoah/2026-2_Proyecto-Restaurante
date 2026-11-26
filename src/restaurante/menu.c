#include <menu.h>

void inicializarMenu(Platillo menu[], int *totalPlatillos) {
    *totalPlatillos = 0;
    for (int i = 0; i < MAX_PLATILLOS; i++) {
        menu[i].id = 0;
        menu[i].nombre[0] = '\0';
        menu[i].categoria = CAT_ENTRADA;
        menu[i].precio = 0.0;
        menu[i].unidadesVendidas = 0;
    }
}

int registrarPlatilloMenu(Platillo menu[], int *totalPlatillos, int id, const char *nombre, CategoriaPlatillo categoria, double precio) {
    if (*totalPlatillos >= MAX_PLATILLOS || precio < 0.0) {
        printf("\nError: [ Menu lleno / Precio invalido. ]\n")
        return 0;
    }
    if (buscarPlatilloPorId(menu, *totalPlatillos, id) != -1) {
        printf("\nError: [ ID duplicado. ]\n");
        return 0;
    }

    int idx = *totalPlatillos;
    menu[idx].id = id;
    strncpy(menu[idx].nombre, nombre, MAX_NOMBRE_PLATILLO - 1);
    menu[idx].nombre[MAX_NOMBRE_PLATILLO - 1] = '\0';
    menu[idx].categoria = categoria;
    menu[idx].precio = precio;
    menu[idx].unidadesVendidas = 0;

    (*totalPlatillos)++;
    return 1;
}

int buscarPlatilloPorId(const Platillo menu[], int totalPlatillos, int id) {
    for (int i = 0; i < totalPlatillos; i++) {
        if (menu[i].id == id) {
            return i;
        }
    }
    return -1;
}

const char* obtenerNombreCategoria(CategoriaPlatillo categoria) {
    switch (categoria) {
        case CAT_ENTRADA:      return "Entradas";
        case CAT_PLATO_FUERTE: return "Platos Fuertes";
        case CAT_BEBIDA:       return "Bebidas";
        case CAT_POSTRE:       return "Postres";
        default:               return "Otra";
    }
}

void mostrarMenu(const Platillo menu[], int totalPlatillos) {
    CategoriaPlatillo categorias[] = {
        CAT_ENTRADA, CAT_PLATO_FUERTE, CAT_BEBIDA, CAT_POSTRE
    };

    printf("\n==================== MENU DEL RESTAURANTE ====================\n");
    printf("  (Todos los precios incluyen IVA del 16%%)\n");

    for (int c = 0; c < 4; c++) {
        printf("\n--- %s ---\n", obtenerNombreCategoria(categorias[c]));
        for (int i = 0; i < totalPlatillos; i++) {
            if (menu[i].categoria == categorias[c]) {
                printf("  [%2d] %-32s $%7.2f\n",
                       menu[i].id, menu[i].nombre, menu[i].precio);
            }
        }
    }
    printf("==============================================================\n");
}