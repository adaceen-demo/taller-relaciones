/**
 * @file CVehiculo.h
 * @brief CONTRATO de la clase CVehiculo: un bus, van o taxi del tablero.
 *
 * ATENCIÓN: ESTE ARCHIVO ES UN CONTRATO. NO SE EDITA.
 * Si cree que falta algo o hay un error, abra un issue en el repositorio.
 *
 * -----------------------------------------------------------------------------
 * RELACIÓN QUE PRACTICA: ASOCIACIÓN  (CVehiculo --> CFila)
 * -----------------------------------------------------------------------------
 *   El vehículo CONOCE la fila de la que recoge pasajeros, pero no es su dueño:
 *     - La fila se crea afuera y el vehículo solo recibe su dirección de memoria
 *       con asociarFila(). Varios vehículos pueden conocer la misma fila.
 *     - El vehículo NUNCA hace new ni delete de la fila.
 *     - Si el vehículo se destruye, la fila sigue existiendo, con los pasajeros
 *       que no alcanzaron a subir.
 *     - La asociación se puede cambiar o romper en cualquier momento
 *       (asociarFila(otraFila) o asociarFila(nullptr)).
 *
 *   Además, CVehiculo es la PARTE de una COMPOSICIÓN (ver CTablero.h): los
 *   vehículos del juego los crea y los destruye el tablero. Para poder comprobar
 *   esto en las pruebas, la clase lleva la cuenta de cuántos vehículos existen
 *   en cada momento (getVivos).
 *
 *   Un vehículo no se copia (constructor de copia y asignación eliminados): así
 *   nadie duplica un vehículo del tablero y el contador de vivos es exacto.
 *
 * -----------------------------------------------------------------------------
 * Estándar CRC
 * -----------------------------------------------------------------------------
 *   Clase: CVehiculo
 *   Responsabilidades:
 *     - Conocer su color, su capacidad, cuántos pasajeros lleva y su posición.
 *     - Recordar con qué fila trabaja (asociación) y recoger pasajeros de ella.
 *     - Saber si ya está lleno.
 *     - Llevar la cuenta de cuántos vehículos existen (getVivos).
 *   Colaboradores:
 *     - CFila: de ella saca pasajeros (frente y atender).
 *     - CPasajero: le pregunta si puede abordar (puedeAbordar).
 *
 * -----------------------------------------------------------------------------
 * REGLAS DEL CONTRATO
 * -----------------------------------------------------------------------------
 *   - Constructor: guarda color, capacidad y posición (x = columna, y = renglón).
 *       Empieza con 0 ocupados y sin fila asociada (nullptr).
 *       Si capacidad es menor que 1, se guarda 1.
 *       Suma 1 al contador de vehículos vivos.
 *   - Destructor: resta 1 al contador de vehículos vivos. NO destruye la fila.
 *   - asociarFila(f): guarda el puntero f (puede ser nullptr para romper la asociación).
 *   - getFilaAsociada(): el puntero guardado (nullptr si no hay).
 *   - recoger(): mientras haya cupo y el pasajero del frente de la fila asociada
 *       pueda abordar este vehículo (CPasajero::puedeAbordar), lo saca de la fila
 *       con atender() y suma 1 a los ocupados. Se detiene en el primer pasajero
 *       que no pueda abordar o cuando la fila quede vacía.
 *       Devuelve cuántos subieron en ESTA llamada. Sin fila asociada devuelve 0.
 *   - estaLleno(): true si ocupados == capacidad.
 *   - getVivos(): cuántos objetos CVehiculo existen en este momento.
 *   - Esta clase es del Modelo: no usa cin ni cout.
 */
#ifndef _CVEHICULO_H_
#define _CVEHICULO_H_

class CFila;   // basta la declaración: el vehículo solo guarda un puntero

class CVehiculo
{
  private:
    char color;
    int capacidad;
    int ocupados;
    int x, y;              // posición en el tablero (x = columna, y = renglón)
    CFila* filaAsociada;   // ASOCIACIÓN: la conoce, no es su dueño

    static int vivos;      // cuántos CVehiculo existen en este momento

  public:
    CVehiculo(char color, int capacidad, int x, int y);
    ~CVehiculo();

    CVehiculo(const CVehiculo&) = delete;              // no se copia
    CVehiculo& operator=(const CVehiculo&) = delete;   // no se asigna

    char getColor() const;
    int getCapacidad() const;
    int getOcupados() const;
    int getX() const;
    int getY() const;
    bool estaLleno() const;

    void asociarFila(CFila* fila);
    CFila* getFilaAsociada() const;
    int recoger();

    static int getVivos();
};
#endif
