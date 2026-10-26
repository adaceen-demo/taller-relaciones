/*
    Taller Relaciones en Bus Fever Party - FPOO - Universidad del Valle
    Clase: CVehiculo  (ASOCIACIÓN: CVehiculo --> CFila; parte de la COMPOSICIÓN de CTablero)

    ESTE ARCHIVO ES SUYO: reemplace cada STUB por la implementación real.
    Lea primero el contrato en CVehiculo.h.
    Recuerde: el vehículo NO crea (new) ni destruye (delete) la fila que conoce.
*/
#include "CVehiculo.h"
#include "CFila.h"
#include "CPasajero.h"

// Definición del atributo estático (debe existir una sola vez en todo el programa).
// No la borre: sin ella el programa no enlaza.
int CVehiculo::vivos = 0;

CVehiculo::CVehiculo(char color, int capacidad, int x, int y)
    : color('?'), capacidad(0), ocupados(0), x(0), y(0), filaAsociada(nullptr) {
    // STUB: guardar los datos (capacidad mínima 1) y sumar 1 a los vivos
}

CVehiculo::~CVehiculo() {
    // STUB: restar 1 a los vivos (y NADA más: la fila no es suya)
}

char CVehiculo::getColor() const {
    // STUB: implementar
    return '?';
}

int CVehiculo::getCapacidad() const {
    // STUB: implementar
    return 0;
}

int CVehiculo::getOcupados() const {
    // STUB: implementar
    return -1;
}

int CVehiculo::getX() const {
    // STUB: implementar
    return -1;
}

int CVehiculo::getY() const {
    // STUB: implementar
    return -1;
}

bool CVehiculo::estaLleno() const {
    // STUB: implementar
    return false;
}

void CVehiculo::asociarFila(CFila* fila) {
    // STUB: implementar
}

CFila* CVehiculo::getFilaAsociada() const {
    // STUB: implementar
    return nullptr;
}

int CVehiculo::recoger() {
    // STUB: implementar (usar frente(), puedeAbordar() y atender())
    return 0;
}

int CVehiculo::getVivos() {
    // STUB: implementar
    return 0;
}
