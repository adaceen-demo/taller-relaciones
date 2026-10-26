/*
    Taller Relaciones en Bus Fever Party - FPOO - Universidad del Valle
    Clase: CTablero  (COMPOSICIÓN: CTablero *-- CVehiculo)

    ESTE ARCHIVO ES SUYO: reemplace cada STUB por la implementación real.
    Lea primero el contrato en CTablero.h.
    Recuerde: el tablero CREA (new) y DESTRUYE (delete) sus vehículos.
*/
#include "CTablero.h"

CTablero::CTablero(int ancho, int alto) : ancho(0), alto(0) {
    // STUB: guardar ancho y alto (mínimo 1 cada uno)
}

CTablero::~CTablero() {
    // STUB: destruir TODOS los vehículos que queden
}

int CTablero::getAncho() const {
    // STUB: implementar
    return 0;
}

int CTablero::getAlto() const {
    // STUB: implementar
    return 0;
}

bool CTablero::estaDentro(int x, int y) const {
    // STUB: implementar
    return false;
}

CVehiculo* CTablero::crearVehiculo(char color, int capacidad, int x, int y) {
    // STUB: validar la casilla y la capacidad, crear el vehículo con new y guardarlo
    return nullptr;
}

CVehiculo* CTablero::vehiculoEn(int x, int y) const {
    // STUB: implementar
    return nullptr;
}

int CTablero::cantidadVehiculos() const {
    // STUB: implementar
    return 0;
}

bool CTablero::retirarVehiculo(int x, int y) {
    // STUB: destruir el vehículo de la casilla (delete) y sacarlo del vector
    return false;
}
