// Pruebas de CVehiculo (ASOCIACIÓN: CVehiculo --> CFila)
#include "minitest.h"
#include "CVehiculo.h"
#include "CFila.h"
#include "CPasajero.h"

int main(){
    SECCION("CVehiculo: constructor y getters");
    {
        CVehiculo v('A', 4, 2, 3);
        CHECK_EQ(v.getColor(), 'A');
        CHECK_EQ(v.getCapacidad(), 4);
        CHECK_EQ(v.getOcupados(), 0);
        CHECK_EQ(v.getX(), 2);
        CHECK_EQ(v.getY(), 3);
        CHECK(!v.estaLleno());
        CHECK(v.getFilaAsociada() == nullptr);
    }

    SECCION("CVehiculo: capacidad menor que 1 se guarda como 1");
    {
        CVehiculo v('R', 0, 0, 0);
        CHECK_EQ(v.getCapacidad(), 1);
    }

    SECCION("CVehiculo: asociarFila guarda, cambia y rompe la asociación");
    {
        CFila filaUno, filaDos;
        CVehiculo v('R', 4, 0, 0);
        v.asociarFila(&filaUno);
        CHECK(v.getFilaAsociada() == &filaUno);
        v.asociarFila(&filaDos);
        CHECK(v.getFilaAsociada() == &filaDos);
        v.asociarFila(nullptr);
        CHECK(v.getFilaAsociada() == nullptr);
    }

    SECCION("CVehiculo: recoger sin fila asociada devuelve 0");
    {
        CVehiculo v('R', 4, 0, 0);
        CHECK_EQ(v.recoger(), 0);
        CHECK_EQ(v.getOcupados(), 0);
    }

    SECCION("CVehiculo: recoger se detiene en el primer pasajero de otro color");
    {
        CPasajero r1(1, 'R'), r2(2, 'R'), a3(3, 'A'), r4(4, 'R');
        CFila fila;
        fila.agregar(&r1); fila.agregar(&r2); fila.agregar(&a3); fila.agregar(&r4);
        CVehiculo v('R', 3, 0, 0);
        v.asociarFila(&fila);
        CHECK_EQ(v.recoger(), 2);
        CHECK_EQ(v.getOcupados(), 2);
        CHECK_EQ(fila.cantidad(), 2);
        CHECK(fila.frente() == &a3);
    }

    SECCION("CVehiculo: recoger se detiene cuando el vehículo se llena");
    {
        CPasajero r1(1, 'R'), r2(2, 'R'), r3(3, 'R');
        CFila fila;
        fila.agregar(&r1); fila.agregar(&r2); fila.agregar(&r3);
        CVehiculo v('R', 2, 0, 0);
        v.asociarFila(&fila);
        CHECK_EQ(v.recoger(), 2);
        CHECK(v.estaLleno());
        CHECK_EQ(v.recoger(), 0);      // ya no cabe nadie
        CHECK_EQ(fila.cantidad(), 1);
        CHECK(fila.frente() == &r3);
    }

    SECCION("CVehiculo: ASOCIACIÓN, la fila sobrevive al vehículo y se puede compartir");
    {
        CPasajero v1(1, 'V'), m2(2, 'M'), m3(3, 'M');
        CFila fila;
        fila.agregar(&v1); fila.agregar(&m2); fila.agregar(&m3);
        {
            CVehiculo verde('V', 4, 0, 0);
            verde.asociarFila(&fila);
            CHECK_EQ(verde.recoger(), 1);
        }   // aquí se destruye 'verde', pero NO la fila
        CHECK_EQ(fila.cantidad(), 2);
        CHECK(fila.frente() == &m2);

        CVehiculo moradoUno('M', 1, 1, 0), moradoDos('M', 1, 2, 0);
        moradoUno.asociarFila(&fila);
        moradoDos.asociarFila(&fila);   // dos vehículos conocen la MISMA fila
        CHECK_EQ(moradoUno.recoger(), 1);
        CHECK_EQ(moradoDos.recoger(), 1);
        CHECK(fila.estaVacia());
    }

    SECCION("CVehiculo: getVivos cuenta los vehículos que existen");
    {
        int antes = CVehiculo::getVivos();
        {
            CVehiculo a('R', 2, 0, 0);
            CVehiculo b('A', 2, 1, 0);
            CHECK_EQ(CVehiculo::getVivos(), antes + 2);
            CVehiculo* c = new CVehiculo('V', 2, 2, 0);
            CHECK_EQ(CVehiculo::getVivos(), antes + 3);
            delete c;
            CHECK_EQ(CVehiculo::getVivos(), antes + 2);
        }
        CHECK_EQ(CVehiculo::getVivos(), antes);
    }

    // TODO: agreguen sus propias pruebas. Ideas: recoger de una fila vacía, llamar
    // recoger dos veces con pasajeros nuevos en la fila, capacidad negativa, etc.

    return RESUMEN();
}
