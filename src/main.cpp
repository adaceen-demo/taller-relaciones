/*
    Taller Relaciones en Bus Fever Party
    Curso: Fundamentos de Programación Orientada a Objetos (FPOO)
    Universidad del Valle

    Escena de ejemplo que usa las tres relaciones. Con los STUB no hace nada
    útil; cuando las cuatro clases estén implementadas, el bus recoge a los
    pasajeros rojos del frente de la fila.

    NOTA: este archivo NO se edita durante el taller.
*/
#include <iostream>
#include "CTablero.h"
#include "CVehiculo.h"
#include "CFila.h"
#include "CPasajero.h"
using namespace std;

int main(){
    // AGREGACIÓN: los pasajeros existen por fuera; la fila solo los agrupa.
    CPasajero p1(1, 'R'), p2(2, 'R'), p3(3, 'A');
    CFila fila;
    fila.agregar(&p1);
    fila.agregar(&p2);
    fila.agregar(&p3);

    // COMPOSICIÓN: el tablero crea (y luego destruye) su vehículo.
    CTablero tablero(4, 3);
    CVehiculo* bus = tablero.crearVehiculo('R', 4, 0, 0);

    cout << "Taller Relaciones en Bus Fever Party" << endl;
    cout << "Tablero de " << tablero.getAncho() << " x " << tablero.getAlto()
         << " con " << tablero.cantidadVehiculos() << " vehiculo(s)" << endl;
    cout << "Pasajeros en la fila: " << fila.cantidad() << endl;

    if (bus == nullptr) {
        cout << "crearVehiculo devolvio nullptr: CTablero todavia es un STUB." << endl;
        return 0;
    }

    // ASOCIACIÓN: el bus conoce la fila, pero no es su dueño.
    bus->asociarFila(&fila);
    int subieron = bus->recoger();
    cout << "Subieron al bus rojo: " << subieron << endl;
    cout << "Quedan en la fila: " << fila.cantidad() << endl;
    return 0;
}
