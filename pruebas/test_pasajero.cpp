// Pruebas de CPasajero (parte de la AGREGACIÓN de CFila; DEPENDENCIA con CVehiculo)
// Algunas pruebas de puedeAbordar también necesitan CFila y CVehiculo implementados.
#include "minitest.h"
#include "CPasajero.h"
#include "CVehiculo.h"
#include "CFila.h"

int main(){
    SECCION("CPasajero: constructor y getters");
    CPasajero p(7, 'R');
    CHECK_EQ(p.getId(), 7);
    CHECK_EQ(p.getColor(), 'R');

    SECCION("CPasajero: puedeAbordar (DEPENDENCIA: recibe el vehículo, no lo guarda)");
    {
        CVehiculo rojo('R', 2, 0, 0);
        CVehiculo azul('A', 2, 1, 0);
        CHECK(p.puedeAbordar(rojo));     // mismo color y con cupo
        CHECK(!p.puedeAbordar(azul));    // otro color
        CHECK_EQ(rojo.getOcupados(), 0); // consultar no es abordar
    }

    SECCION("CPasajero: puedeAbordar con un vehículo lleno (usa CFila y CVehiculo)");
    {
        CPasajero primero(1, 'V');
        CPasajero segundo(2, 'V');
        CFila fila;
        fila.agregar(&primero);
        CVehiculo verde('V', 1, 0, 0);
        verde.asociarFila(&fila);
        CHECK_EQ(verde.recoger(), 1);
        CHECK(verde.estaLleno());
        CHECK(!segundo.puedeAbordar(verde));   // mismo color, pero sin cupo
    }

    // TODO: agreguen sus propias pruebas. Ideas: id 0 o negativo, varios pasajeros
    // del mismo color, un vehículo con capacidad grande, colores en minúscula, etc.

    return RESUMEN();
}
