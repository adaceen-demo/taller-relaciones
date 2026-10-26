/**
 * @file CFila.h
 * @brief CONTRATO de la clase CFila: la fila de pasajeros que esperan un vehículo.
 *
 * ATENCIÓN: ESTE ARCHIVO ES UN CONTRATO. NO SE EDITA.
 * Si cree que falta algo o hay un error, abra un issue en el repositorio.
 *
 * -----------------------------------------------------------------------------
 * RELACIÓN QUE PRACTICA: AGREGACIÓN  (CFila o-- CPasajero)
 * -----------------------------------------------------------------------------
 *   La fila AGRUPA pasajeros, pero NO es su dueña:
 *     - Los pasajeros se crean afuera (en main o en una prueba) y llegan a la fila
 *       como punteros mediante agregar().
 *     - La fila NUNCA hace new ni delete de un pasajero.
 *     - atender() saca al pasajero de la fila y lo devuelve vivo: solo deja de
 *       estar en la fila.
 *     - Si la fila se destruye, los pasajeros siguen existiendo.
 *     - Un mismo pasajero puede estar en otra agrupación al mismo tiempo.
 *
 *   CFila no declara destructor a propósito: el que genera el compilador solo
 *   libera el vector de punteros y no toca a los pasajeros, que es justo lo que
 *   pide la agregación. Por la misma razón, copiar una fila copia los punteros:
 *   la copia y el original apuntan a los mismos pasajeros.
 *
 * -----------------------------------------------------------------------------
 * Estándar CRC
 * -----------------------------------------------------------------------------
 *   Clase: CFila
 *   Responsabilidades:
 *     - Mantener el orden de llegada de los pasajeros (el primero en llegar es
 *       el primero en salir).
 *     - Mostrar quién está al frente y sacarlo cuando aborda.
 *     - Contar cuántos pasajeros hay, en total y por color.
 *   Colaboradores:
 *     - CPasajero: los agrupa (agregación) y les pregunta su color.
 *
 * -----------------------------------------------------------------------------
 * REGLAS DEL CONTRATO
 * -----------------------------------------------------------------------------
 *   - agregar(p): pone a p al FINAL de la fila y devuelve true.
 *       Devuelve false (y no agrega nada) si p es nullptr o si ese mismo
 *       pasajero (el mismo puntero) ya está en la fila.
 *   - frente(): el pasajero del frente, sin sacarlo. nullptr si la fila está vacía.
 *   - atender(): saca al pasajero del frente y lo devuelve (NO lo destruye).
 *       nullptr si la fila está vacía.
 *   - cantidad(): cuántos pasajeros hay en la fila.
 *   - estaVacia(): true si no hay pasajeros.
 *   - contarPorColor(c): cuántos pasajeros de color c hay en la fila.
 *   - Esta clase es del Modelo: no usa cin ni cout.
 */
#ifndef _CFILA_H_
#define _CFILA_H_
#include <vector>
using namespace std;

class CPasajero;   // basta la declaración: la fila solo guarda punteros

class CFila
{
  private:
    vector<CPasajero*> pasajeros;   // AGREGACIÓN: punteros a objetos que la fila no posee

  public:
    CFila();

    bool agregar(CPasajero* pasajero);
    CPasajero* frente() const;
    CPasajero* atender();

    int cantidad() const;
    bool estaVacia() const;
    int contarPorColor(char color) const;
};
#endif
