/*
    Taller Relaciones en Bus Fever Party - FPOO - Universidad del Valle
    Clase: CFila  (AGREGACIÓN: CFila o-- CPasajero)

    ESTE ARCHIVO ES SUYO: reemplace cada STUB por la implementación real.
    Lea primero el contrato en CFila.h.
    Recuerde: la fila NO crea (new) ni destruye (delete) pasajeros.
*/
#include "CFila.h"
#include "CPasajero.h"

CFila::CFila() {
}

bool CFila::agregar(CPasajero* pasajero) {
    // STUB: implementar (rechazar nullptr y pasajeros repetidos)
    return false;
}

CPasajero* CFila::frente() const {
    // STUB: implementar
    return nullptr;
}

CPasajero* CFila::atender() {
    // STUB: implementar (sacar al primero SIN destruirlo)
    return nullptr;
}

int CFila::cantidad() const {
    // STUB: implementar
    return 0;
}

bool CFila::estaVacia() const {
    // STUB: implementar
    return false;
}

int CFila::contarPorColor(char color) const {
    // STUB: implementar
    return 0;
}
