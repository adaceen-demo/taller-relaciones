/**
 * @file CTablero.h
 * @brief CONTRATO de la clase CTablero: la cuadrícula donde están los vehículos.
 *
 * ATENCIÓN: ESTE ARCHIVO ES UN CONTRATO. NO SE EDITA.
 * Si cree que falta algo o hay un error, abra un issue en el repositorio.
 *
 * -----------------------------------------------------------------------------
 * RELACIÓN QUE PRACTICA: COMPOSICIÓN  (CTablero *-- CVehiculo)
 * -----------------------------------------------------------------------------
 *   El tablero es el ÚNICO DUEÑO de sus vehículos:
 *     - Los CREA él mismo (con new) dentro de crearVehiculo(). Por eso ese método
 *       recibe los datos del vehículo y no un CVehiculo* hecho afuera.
 *     - Los DESTRUYE él mismo (con delete): en retirarVehiculo() y, para todos los
 *       que queden, en su destructor. Ningún vehículo del tablero sobrevive al
 *       tablero.
 *     - Quien recibe el puntero que devuelve crearVehiculo() o vehiculoEn() puede
 *       usarlo, pero NUNCA debe hacer delete de él.
 *     - Un tablero no se copia (constructor de copia y asignación eliminados): si
 *       se copiaran los punteros, dos tableros creerían ser dueños de los mismos
 *       vehículos y ambos intentarían destruirlos.
 *
 *   Compare con CFila (agregación): la fila recibe punteros de afuera y nunca los
 *   destruye. Aquí es al revés: el tablero crea y destruye.
 *
 * -----------------------------------------------------------------------------
 * Estándar CRC
 * -----------------------------------------------------------------------------
 *   Clase: CTablero
 *   Responsabilidades:
 *     - Conocer su tamaño (ancho y alto) y saber si una posición está dentro.
 *     - Crear vehículos en casillas libres y válidas.
 *     - Encontrar el vehículo que hay en una casilla.
 *     - Retirar (y destruir) vehículos.
 *     - Destruir todos sus vehículos cuando el tablero deja de existir.
 *   Colaboradores:
 *     - CVehiculo: sus partes (composición).
 *
 * -----------------------------------------------------------------------------
 * REGLAS DEL CONTRATO
 * -----------------------------------------------------------------------------
 *   Posiciones: (x, y) con x = columna e y = renglón, ambos desde 0.
 *   (Se dice "renglón" para no confundirlo con CFila, la fila de pasajeros.)
 *
 *   - Constructor: guarda ancho y alto; si alguno es menor que 1, se usa 1.
 *       Empieza sin vehículos.
 *   - estaDentro(x, y): true si 0 <= x < ancho y 0 <= y < alto.
 *   - crearVehiculo(color, capacidad, x, y): crea un vehículo nuevo en (x, y),
 *       lo guarda y devuelve su puntero. Devuelve nullptr (y no crea nada) si
 *       (x, y) está fuera del tablero, si la casilla ya tiene un vehículo o si
 *       capacidad es menor que 1.
 *   - vehiculoEn(x, y): el vehículo que está en (x, y), o nullptr si no hay.
 *   - cantidadVehiculos(): cuántos vehículos tiene el tablero.
 *   - retirarVehiculo(x, y): destruye el vehículo de (x, y), lo saca del tablero
 *       y devuelve true. Si no había vehículo ahí devuelve false.
 *   - Destructor: destruye TODOS los vehículos que queden.
 *   - Esta clase es del Modelo: no usa cin ni cout.
 */
#ifndef _CTABLERO_H_
#define _CTABLERO_H_
#include <vector>
#include "CVehiculo.h"
using namespace std;

class CTablero
{
  private:
    int ancho, alto;
    vector<CVehiculo*> vehiculos;   // COMPOSICIÓN: el tablero los crea y los destruye

  public:
    CTablero(int ancho, int alto);
    ~CTablero();

    CTablero(const CTablero&) = delete;              // no se copia
    CTablero& operator=(const CTablero&) = delete;   // no se asigna

    int getAncho() const;
    int getAlto() const;
    bool estaDentro(int x, int y) const;

    CVehiculo* crearVehiculo(char color, int capacidad, int x, int y);
    CVehiculo* vehiculoEn(int x, int y) const;
    int cantidadVehiculos() const;
    bool retirarVehiculo(int x, int y);
};
#endif
