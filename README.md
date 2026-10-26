# Taller Relaciones en Bus Fever Party
Fundamentos de Programación Orientada a Objetos (FPOO), Universidad del Valle
Clase: **Abstraer relaciones de diferente tipo** (11-11-2026)

En Bus Fever Party los vehículos de un tablero recogen a los pasajeros de su mismo color que
esperan en una fila. En este taller se implementan cuatro clases pequeñas de ese juego y cada
una practica un tipo de relación entre objetos. El taller dura entre 1 y 2 horas.

Tiene el mismo formato que el Taller Droguería: cada clase tiene un **contrato** (`.h`) que no se
edita, un `.cpp` vacío (*stub*) que usted implementa y unas pruebas que **fallan a propósito al
inicio**. Su trabajo es ponerlas en verde.

> Este taller es independiente del proyecto del curso: las clases de aquí sirven como ejemplo
> de relaciones, no son la solución del proyecto.

## Qué relación practica cada clase

| Clase | Relación | Cómo se nota en el código |
|---|---|---|
| `CTablero` | **Composición** con `CVehiculo` (`*--`) | El tablero crea los vehículos con `new` en `crearVehiculo()` y los destruye con `delete` en `retirarVehiculo()` y en su destructor. Ningún vehículo sobrevive al tablero. |
| `CVehiculo` | **Asociación** con `CFila` (`-->`) | El vehículo guarda un puntero a la fila (`asociarFila`) y recoge pasajeros de ella, pero no la crea ni la destruye. Varios vehículos pueden conocer la misma fila. |
| `CFila` | **Agregación** con `CPasajero` (`o--`) | La fila guarda punteros a pasajeros creados afuera. `atender()` los saca sin destruirlos y, si la fila se destruye, los pasajeros siguen existiendo. |
| `CPasajero` | **Dependencia** con `CVehiculo` (`..>`) y parte de la agregación | `puedeAbordar()` recibe un vehículo como parámetro y no lo guarda. |

El diagrama completo está en `docs/DiagramaRelaciones.puml` (péguelo en https://plantuml.com/).
Cada contrato explica su relación en detalle: léalo antes de programar.

## Cómo compilar y probar

Necesita `g++` (C++17) y `make`. Verifique con `g++ --version` y `make --version`.

- **Linux / macOS / WSL:** instale `g++` y `make` con el gestor de paquetes.
- **Windows:** instale MinGW-w64 (por ejemplo con MSYS2) y `make`, y agregue sus carpetas al PATH.

```
make                 # compila el programa de ejemplo -> relaciones (relaciones.exe en Windows)
make test            # corre TODAS las pruebas y muestra el total al final
make run-fila        # corre solo las pruebas de una clase (fila, pasajero, vehiculo, tablero)
make clean           # borra lo compilado
```

Al final de `make test` aparece un resumen como este:

```
==========================================================
 TOTAL: 29 pruebas OK, 71 fallidas
 RESULTADO: HAY PRUEBAS FALLIDAS
==========================================================
```

Ese es el resultado esperado al inicio. Algunas pruebas "pasan" con los stubs por casualidad
(por ejemplo, un stub que devuelve `nullptr` acierta cuando se espera `nullptr`); cuando todo
esté implementado debe ver `RESULTADO: TODAS LAS PRUEBAS PASAN`.

**Orden sugerido:** `CPasajero` y `CFila` primero, luego `CVehiculo` (usa a las dos) y por último
`CTablero` (usa a `CVehiculo`). Algunas pruebas de una clase usan otra, así que unas cuantas solo
pasan cuando la otra también está lista.

## Reglas

1. **Los headers (`.h`) son contratos: no se editan.** Si cree que falta algo o hay un error,
   abra un *issue* en este repositorio.
2. **Tampoco se editan** `src/main.cpp`, `Makefile`, `pruebas/minitest.h` ni `pruebas/resumen_pruebas.cpp`.
3. **Usted edita** los `.cpp` de `src/modelo/` y los `pruebas/test_*.cpp` (para agregar sus propias
   pruebas, sin borrar las iniciales), y crea sus archivos en `docs/`.
4. **Estas clases son del Modelo:** no usan `cin` ni `cout`.
5. **Una rama por estudiante o por grupo**, con un nombre claro (ej: `grupo-3` o `ana-perez`).
6. **Commits pequeños con mensajes claros** (ej: `CFila: implementa agregar y atender`).
   Todos los integrantes deben tener commits.
7. **Entrega:** su código, sus pruebas (las iniciales más las suyas), una tarjeta CRC por clase
   (`docs/crc_<clase>.md`, desde `docs/plantilla_crc.md`) y su fragmento UML
   (`docs/uml_<clase>.puml`, desde `docs/uml_plantilla.puml`) con el símbolo de relación correcto.

## Flujo de trabajo con Git y GitHub

```
# 1. Haga fork de este repositorio en GitHub y clone SU fork
git clone https://github.com/<su-usuario>/taller-relaciones.git
cd taller-relaciones
git remote add upstream <URL de este repositorio>

# 2. Cree su rama
git checkout -b grupo-3

# 3. Trabaje, compile y pruebe; haga commits pequeños
make && make test
git add src/modelo/CFila.cpp pruebas/test_fila.cpp docs/crc_fila.md docs/uml_fila.puml
git commit -m "CFila: implementa agregar, frente y atender"

# 4. Antes de enviar, traiga los cambios del repositorio original
git pull upstream main

# 5. Suba su rama y abra un Pull Request hacia este repositorio
git push origin grupo-3
```

En el Pull Request complete la lista de verificación de la plantilla.

## Estructura

```
src/
  main.cpp                 escena de ejemplo con las tres relaciones (NO se edita)
  modelo/
    CTablero.h  .cpp       composición
    CVehiculo.h .cpp       asociación
    CFila.h     .cpp       agregación
    CPasajero.h .cpp       dependencia / parte de la agregación
pruebas/
  minitest.h               mini framework de pruebas (NO se edita)
  resumen_pruebas.cpp      imprime el total de make test (NO se edita)
  test_<clase>.cpp         pruebas iniciales de cada clase
docs/
  DiagramaRelaciones.puml  diagrama base con los tres tipos de relación
  uml_plantilla.puml       plantilla para su fragmento UML
  plantilla_crc.md         plantilla de tarjeta CRC
```

## Preguntas para cerrar el taller

- ¿Por qué `CTablero` no tiene un método `agregarVehiculo(CVehiculo*)` y `CFila` sí tiene `agregar(CPasajero*)`?
- ¿Qué pasaría si `CFila` hiciera `delete` de sus pasajeros en un destructor?
- ¿Por qué copiar un `CTablero` está prohibido, pero copiar una `CFila` no?
- ¿Cuál es la diferencia entre la relación de `CVehiculo` con `CFila` y la de `CPasajero` con `CVehiculo`?
