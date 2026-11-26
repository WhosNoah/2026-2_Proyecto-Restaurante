#include <comanda.h>

int buscarRenglonPorId(const Comanda *comanda, int idPlatillo) {
    for (int i = 0; i < comanda->totalRenglones; i++) {
        if (comanda->items[i].idPlatillo == idPlatillo) {
            return i;
        }
    }
    return -1;
}

void eliminarRenglonEnIndice(Comanda *comanda, int indice) {
    if (indice < 0 || indice >= comanda->totalRenglones) {
        return;
    }
    for (int i = indice; i < comanda->totalRenglones - 1; i++) {
        comanda->items[i] = comanda->items[i + 1];
    }
    comanda->totalRenglones--;
}

void inicializarComanda(Comanda *comanda) {
    if (comanda == NULL) {
        return;
    }
    comanda->totalRenglones = 0;
    for (int i = 0; i < MAX_RENGLONES; i++) {
        comanda->items[i].idPlatillo = 0;
        comanda->items[i].nombrePlatillo[0] = '\0';
        comanda->items[i].precioUnitario = 0.0;
        comanda->items[i].cantidad = 0;
        comanda->items[i].nota[0] = '\0';
    }
}

int agregarPlatillo(Comanda *comanda, const Platillo menu[], int totalPlatillos,
                    int idPlatillo, int cantidad, const char *nota) {
    if (comanda == NULL || menu == NULL || cantidad <= 0) {
        return 0;
    }

    int idxMenu = buscarPlatilloPorId(menu, totalPlatillos, idPlatillo);
    if (idxMenu == -1) {
        printf("\nError: [ El platillo no existe en el menu. ]\n");
        return 0;
    }

    int idxRenglon = buscarRenglonPorId(comanda, idPlatillo);
    if (idxRenglon != -1) {
        comanda->items[idxRenglon].cantidad += cantidad;
        if (nota != NULL && nota[0] != '\0') {
            strncpy(comanda->items[idxRenglon].nota, nota, MAX_NOTA - 1);
            comanda->items[idxRenglon].nota[MAX_NOTA - 1] = '\0';
        }
        return 1;
    }

    if (comanda->totalRenglones >= MAX_RENGLONES) {
        printf("\nError: [ Comanda llena. ]\n");
        return 0;
    }

    int nuevoIdx = comanda->totalRenglones;
    comanda->items[nuevoIdx].idPlatillo = menu[idxMenu].id;
    copiarCadena(comanda->items[nuevoIdx].nombrePlatillo, menu[idxMenu].nombre, MAX_NOMBRE_PLATILLO - 1);
    comanda->items[nuevoIdx].nombrePlatillo[MAX_NOMBRE_PLATILLO - 1] = '\0';
    comanda->items[nuevoIdx].precioUnitario = menu[idxMenu].precio;
    comanda->items[nuevoIdx].cantidad = cantidad;

    if (nota != NULL) {
        strncpy(comanda->items[nuevoIdx].nota, nota, MAX_NOTA - 1);
        comanda->items[nuevoIdx].nota[MAX_NOTA - 1] = '\0';
    } else {
        comanda->items[nuevoIdx].nota[0] = '\0';
    }

    comanda->totalRenglones++;
    return 1;
}

int quitarPlatillo(Comanda *comanda, int idPlatillo, int cantidadAQuitar) {
    if (comanda == NULL) {
        return 0;
    }

    int idx = buscarRenglonPorId(comanda, idPlatillo);
    if (idx == -1) {
        printf("\nError: [ Platillo no encontrado en la comanda. ]\n");
        return 0;
    }

    if (cantidadAQuitar <= 0 || cantidadAQuitar >= comanda->items[idx].cantidad) {
        eliminarRenglonEnIndice(comanda, idx);
    } else {
        comanda->items[idx].cantidad -= cantidadAQuitar;
    }

    return 1;
}

double totalComanda(const Comanda *comanda) {
    if (comanda == NULL) {
        return 0.0;
    }

    double suma = 0.0;
    for (int i = 0; i < comanda->totalRenglones; i++) {
        suma += comanda->items[i].precioUnitario * comanda->items[i].cantidad;
    }
    return suma;
}

void mostrarComanda(const Comanda *comanda) {
    if (comanda == NULL || comanda->totalRenglones == 0) {
        printf("  (Comanda vacia)\n");
        return;
    }

    for (int i = 0; i < comanda->totalRenglones; i++) {
        const RenglonComanda *r = &comanda->items[i];
        double importe = r->precioUnitario * r->cantidad;
        printf("  %d x %-28s $%7.2f", r->cantidad, r->nombrePlatillo, importe);
        if (r->nota[0] != '\0') {
            printf("  [%s]", r->nota);
        }
        printf("\n");
    }
}