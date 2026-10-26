/**
 * @file CPasajero.h
 * @brief CONTRATO de la clase CPasajero (Taller Relaciones en Bus Fever Party).
 *
 * ATENCIÓN: ESTE ARCHIVO ES UN CONTRATO. NO SE EDITA.
 * Si cree que falta algo o hay un error, abra un issue en el repositorio.
 *
 * -----------------------------------------------------------------------------
 * RELACIONES QUE PRACTICA
 * -----------------------------------------------------------------------------
 *   1. Es la PARTE de una AGREGACIÓN (ver CFila.h).
 *      CFila guarda punteros a pasajeros, pero no los crea ni los destruye.
 *      El pasajero existe antes de entrar a la fila y sigue existiendo cuando
 *      sale de ella o cuando la fila se destruye. Quien lo crea (main o una
 *      prueba) es quien lo destruye.
 *
 *   2. DEPENDENCIA (relación de uso) con CVehiculo.
 *      puedeAbordar() recibe un vehículo como parámetro, lo consulta y lo olvida.
 *      El pasajero NO guarda el vehículo como atributo: por eso no es una
 *      asociación. En UML se dibuja con flecha punteada:  CPasajero ..> CVehiculo
 *
 * -----------------------------------------------------------------------------
 * Estándar CRC
 * -----------------------------------------------------------------------------
 *   Clase: CPasajero
 *   Responsabilidades:
 *     - Conocer su identificador y su color.
 *     - Decidir si puede abordar un vehículo dado.
 *   Colaboradores:
 *     - CVehiculo: lo consulta en puedeAbordar() (color y cupo).
 *
 * -----------------------------------------------------------------------------
 * REGLAS DEL CONTRATO
 * -----------------------------------------------------------------------------
 *   - Los colores son letras mayúsculas: 'R' rojo, 'A' azul, 'V' verde,
 *     'M' morado, 'N' naranja. El constructor guarda el color tal como llega.
 *   - puedeAbordar(vehiculo): true solo si el vehículo es del MISMO color que el
 *     pasajero Y todavía tiene cupo (no está lleno). En otro caso, false.
 *     Consultar no es abordar: este método no modifica ni al pasajero ni al vehículo.
 *   - Esta clase es del Modelo: no usa cin ni cout.
 */
#ifndef _CPASAJERO_H_
#define _CPASAJERO_H_

class CVehiculo;   // declaración adelantada: basta para recibirlo por referencia

class CPasajero
{
  private:
    int id;
    char color;

  public:
    CPasajero(int id, char color);

    int getId() const;
    char getColor() const;

    // DEPENDENCIA: usa el vehículo solo durante la llamada.
    bool puedeAbordar(const CVehiculo& vehiculo) const;
};
#endif
