/**
 * minitest.h - Mini framework de pruebas (sin librerías externas).
 * ATENCIÓN: este archivo NO se edita.
 *
 * Uso:
 *   CHECK(condicion);             -> pasa si la condición es true
 *   CHECK_EQ(obtenido, esperado); -> pasa si son iguales (deben poder imprimirse con <<)
 *   CHECK_NEAR(a, b, tolerancia); -> para números reales (float/double)
 *   CHECK_CONTIENE(texto, trozo); -> pasa si "texto" contiene "trozo"
 *   SECCION("titulo");            -> imprime un título para agrupar pruebas
 *   return RESUMEN();             -> al final del main
 *
 * Para comparar punteros use CHECK(p == q) o CHECK(p != nullptr).
 * Para comparar tamaños use un cast: CHECK_EQ((int)v.size(), 2);
 * Antes de usar un puntero que devuelve un método, verifique que no sea nullptr:
 * un STUB devuelve nullptr y usarlo haría caer el programa.
 *
 * RESUMEN() imprime cuántas pruebas pasaron y fallaron en el archivo, y suma esos
 * números en build/total_pruebas.txt para que "make test" muestre el total.
 * Siempre devuelve 0: las fallas se leen en la salida y no en el código de salida,
 * así make no se detiene en el primer archivo que tenga pruebas fallidas.
 */
#ifndef _MINITEST_H_
#define _MINITEST_H_
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

namespace minitest {
    inline int& pasaron()  { static int n = 0; return n; }
    inline int& fallaron() { static int n = 0; return n; }

    inline void registrar(bool ok, const std::string& descripcion, const char* archivo, int linea) {
        if (ok) {
            pasaron()++;
        } else {
            fallaron()++;
            std::cout << "  [FALLO] " << descripcion << "   (" << archivo << ":" << linea << ")" << std::endl;
        }
    }

    inline bool contiene(const std::string& texto, const std::string& trozo) {
        return texto.find(trozo) != std::string::npos;
    }

    // Suma los resultados de este archivo al total que muestra "make test".
    // Formato de build/total_pruebas.txt: <pasaron> <fallaron> <archivos terminados>
    inline void acumularTotal() {
        const char* ruta = "build/total_pruebas.txt";
        int ok = 0, mal = 0, archivos = 0;
        {
            std::ifstream entrada(ruta);
            if (!(entrada >> ok >> mal >> archivos)) { ok = 0; mal = 0; archivos = 0; }
        }
        std::ofstream salida(ruta);
        if (salida) {
            salida << (ok + pasaron()) << " " << (mal + fallaron()) << " " << (archivos + 1) << "\n";
        }
    }

    inline int resumen(const char* archivo) {
        std::cout << "  -> " << pasaron() << " pruebas OK, " << fallaron() << " fallidas  (" << archivo << ")" << std::endl;
        acumularTotal();
        return 0;
    }
}

#define SECCION(titulo) std::cout << "- " << titulo << std::endl

#define CHECK(cond) minitest::registrar((cond), #cond, __FILE__, __LINE__)

#define CHECK_EQ(a, b) do { \
    auto _obtenido = (a); auto _esperado = (b); \
    bool _ok = (_obtenido == _esperado); \
    std::ostringstream _os; \
    _os << #a << " == " << #b; \
    if (!_ok) _os << "   [obtenido: " << _obtenido << " | esperado: " << _esperado << "]"; \
    minitest::registrar(_ok, _os.str(), __FILE__, __LINE__); \
} while (0)

#define CHECK_NEAR(a, b, tol) minitest::registrar( \
    std::fabs((double)(a) - (double)(b)) <= (tol), \
    std::string(#a) + " ~= " + #b, __FILE__, __LINE__)

#define CHECK_CONTIENE(texto, trozo) minitest::registrar( \
    minitest::contiene((texto), (trozo)), \
    std::string("el texto contiene ") + #trozo, __FILE__, __LINE__)

#define RESUMEN() minitest::resumen(__FILE__)

#endif
