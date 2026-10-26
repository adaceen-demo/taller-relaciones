/*
    Taller Relaciones en Bus Fever Party - FPOO - Universidad del Valle
    Clase: CPasajero  (parte de la AGREGACIÓN de CFila; DEPENDENCIA con CVehiculo)

    ESTE ARCHIVO ES SUYO: reemplace cada STUB por la implementación real.
    Lea primero el contrato en CPasajero.h.
*/
#include "CPasajero.h"
#include "CVehiculo.h"   // se necesita para consultar al vehículo en puedeAbordar()

CPasajero::CPasajero(int id, char color) : id(0), color('?') {
    // STUB: guardar el id y el color recibidos
}

int CPasajero::getId() const {
    // STUB: implementar
    return 0;
}

char CPasajero::getColor() const {
    // STUB: implementar
    return '?';
}

bool CPasajero::puedeAbordar(const CVehiculo& vehiculo) const {
    // STUB: implementar (mismo color y el vehículo no está lleno)
    return false;
}
