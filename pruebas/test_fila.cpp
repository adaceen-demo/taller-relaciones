// Pruebas de CFila (AGREGACIÓN: CFila o-- CPasajero)
#include "minitest.h"
#include "CFila.h"
#include "CPasajero.h"

int main(){
    // Los pasajeros se crean AFUERA de la fila: la fila solo recibe sus direcciones.
    CPasajero p1(1, 'R');
    CPasajero p2(2, 'A');
    CPasajero p3(3, 'R');

    SECCION("CFila: una fila nueva está vacía");
    {
        CFila fila;
        CHECK_EQ(fila.cantidad(), 0);
        CHECK(fila.estaVacia());
        CHECK(fila.frente() == nullptr);
        CHECK(fila.atender() == nullptr);
    }

    SECCION("CFila: agregar conserva el orden de llegada");
    CFila fila;
    CHECK(fila.agregar(&p1));
    CHECK(fila.agregar(&p2));
    CHECK(fila.agregar(&p3));
    CHECK_EQ(fila.cantidad(), 3);
    CHECK(!fila.estaVacia());
    CHECK(fila.frente() == &p1);

    SECCION("CFila: agregar rechaza nullptr y pasajeros repetidos");
    CHECK(!fila.agregar(nullptr));
    CHECK(!fila.agregar(&p2));
    CHECK_EQ(fila.cantidad(), 3);

    SECCION("CFila: contarPorColor");
    CHECK_EQ(fila.contarPorColor('R'), 2);
    CHECK_EQ(fila.contarPorColor('A'), 1);
    CHECK_EQ(fila.contarPorColor('V'), 0);

    SECCION("CFila: atender saca al del frente SIN destruirlo");
    CPasajero* atendido = fila.atender();
    CHECK(atendido == &p1);
    CHECK_EQ(fila.cantidad(), 2);
    CHECK(fila.frente() == &p2);
    CHECK_EQ(p1.getId(), 1);   // p1 sigue existiendo fuera de la fila

    SECCION("CFila: AGREGACIÓN, los pasajeros sobreviven a la fila");
    {
        CPasajero viajero(9, 'M');
        {
            CFila temporal;
            CHECK(temporal.agregar(&viajero));
        }   // aquí se destruye 'temporal'
        CHECK_EQ(viajero.getId(), 9);
        CHECK_EQ(viajero.getColor(), 'M');
    }

    SECCION("CFila: AGREGACIÓN, un pasajero puede estar en dos agrupaciones");
    {
        CFila otra;
        CHECK(otra.agregar(&p3));   // p3 ya está en 'fila' y también puede estar aquí
        CHECK_EQ(otra.cantidad(), 1);
        CHECK_EQ(fila.cantidad(), 2);
    }

    SECCION("CFila: copiar una fila copia los punteros, no los pasajeros");
    {
        CFila copia = fila;
        CHECK_EQ(copia.cantidad(), fila.cantidad());
        CHECK(copia.frente() != nullptr);
        CHECK(copia.frente() == fila.frente());   // apuntan al MISMO pasajero
    }

    // TODO: agreguen sus propias pruebas. Ideas: atender hasta vaciar la fila,
    // agregar de nuevo a un pasajero que ya fue atendido, contar en una fila vacía, etc.

    return RESUMEN();
}
