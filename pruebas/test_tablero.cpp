// Pruebas de CTablero (COMPOSICIÓN: CTablero *-- CVehiculo)
#include "minitest.h"
#include "CTablero.h"
#include "CVehiculo.h"
#include "CFila.h"
#include "CPasajero.h"

int main(){
    SECCION("CTablero: constructor y tamaño mínimo");
    {
        CTablero t(5, 4);
        CHECK_EQ(t.getAncho(), 5);
        CHECK_EQ(t.getAlto(), 4);
        CHECK_EQ(t.cantidadVehiculos(), 0);
        CTablero pequeno(0, -3);
        CHECK_EQ(pequeno.getAncho(), 1);
        CHECK_EQ(pequeno.getAlto(), 1);
    }

    SECCION("CTablero: estaDentro");
    {
        CTablero t(5, 4);
        CHECK(t.estaDentro(0, 0));
        CHECK(t.estaDentro(4, 3));
        CHECK(!t.estaDentro(5, 0));
        CHECK(!t.estaDentro(0, 4));
        CHECK(!t.estaDentro(-1, 2));
    }

    SECCION("CTablero: crearVehiculo y vehiculoEn");
    {
        CTablero t(5, 4);
        CVehiculo* v = t.crearVehiculo('R', 4, 1, 2);
        CHECK(v != nullptr);
        if (v != nullptr) {   // un STUB devuelve nullptr: no lo use sin revisar
            CHECK_EQ(v->getColor(), 'R');
            CHECK_EQ(v->getCapacidad(), 4);
            CHECK_EQ(v->getX(), 1);
            CHECK_EQ(v->getY(), 2);
        }
        CHECK_EQ(t.cantidadVehiculos(), 1);
        CHECK(t.vehiculoEn(1, 2) == v);
        CHECK(t.vehiculoEn(0, 0) == nullptr);
    }

    SECCION("CTablero: crearVehiculo rechaza casillas ocupadas o inválidas");
    {
        CTablero t(3, 3);
        CHECK(t.crearVehiculo('R', 4, 0, 0) != nullptr);
        CHECK(t.crearVehiculo('A', 4, 0, 0) == nullptr);   // ocupada
        CHECK(t.crearVehiculo('A', 4, 3, 0) == nullptr);   // fuera
        CHECK(t.crearVehiculo('A', 0, 1, 1) == nullptr);   // capacidad inválida
        CHECK_EQ(t.cantidadVehiculos(), 1);
    }

    SECCION("CTablero: retirarVehiculo destruye el vehículo");
    {
        CTablero t(3, 3);
        t.crearVehiculo('R', 4, 0, 0);
        t.crearVehiculo('A', 4, 1, 0);
        int antes = CVehiculo::getVivos();
        CHECK(t.retirarVehiculo(0, 0));
        CHECK_EQ(CVehiculo::getVivos(), antes - 1);
        CHECK_EQ(t.cantidadVehiculos(), 1);
        CHECK(t.vehiculoEn(0, 0) == nullptr);
        CHECK(!t.retirarVehiculo(0, 0));                  // ya no hay nada ahí
        CHECK(t.crearVehiculo('V', 4, 0, 0) != nullptr);  // la casilla quedó libre
    }

    SECCION("CTablero: COMPOSICIÓN, el destructor destruye todos sus vehículos");
    {
        int antes = CVehiculo::getVivos();
        {
            CTablero t(4, 4);
            t.crearVehiculo('R', 4, 0, 0);
            t.crearVehiculo('A', 4, 1, 1);
            t.crearVehiculo('V', 4, 2, 2);
            CHECK_EQ(CVehiculo::getVivos(), antes + 3);
        }   // aquí se destruye el tablero y, con él, sus vehículos
        CHECK_EQ(CVehiculo::getVivos(), antes);
    }

    SECCION("Las tres relaciones juntas");
    {
        CPasajero p1(1, 'N'), p2(2, 'N');      // existen fuera de todo
        CFila fila;                            // AGREGACIÓN: fila o-- pasajeros
        fila.agregar(&p1);
        fila.agregar(&p2);
        {
            CTablero t(3, 3);                  // COMPOSICIÓN: tablero *-- vehículos
            CVehiculo* bus = t.crearVehiculo('N', 4, 2, 2);
            CHECK(bus != nullptr);
            if (bus != nullptr) {
                bus->asociarFila(&fila);       // ASOCIACIÓN: vehículo --> fila
                CHECK_EQ(bus->recoger(), 2);
            }
        }   // muere el tablero y su bus; la fila y los pasajeros siguen
        CHECK(fila.estaVacia());
        CHECK_EQ(p1.getColor(), 'N');
        CHECK_EQ(p2.getId(), 2);
    }

    // TODO: agreguen sus propias pruebas. Ideas: tablero 1x1, retirar todos los
    // vehículos, buscar en las esquinas, crear después de retirar, etc.

    return RESUMEN();
}
