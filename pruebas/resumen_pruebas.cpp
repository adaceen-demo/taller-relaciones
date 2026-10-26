// resumen_pruebas.cpp - Muestra el total de "make test". ATENCIÓN: este archivo NO se edita.
//
//   resumen_pruebas --reiniciar   borra el total anterior (se llama antes de las pruebas)
//   resumen_pruebas <n>           imprime el total; <n> = cuántos archivos de prueba hay
//
// Cada archivo de prueba suma sus resultados en build/total_pruebas.txt (ver minitest.h).
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char* argv[]){
    const char* RUTA = "build/total_pruebas.txt";
    if (argc > 1 && string(argv[1]) == "--reiniciar") {
        remove(RUTA);
        return 0;
    }
    int esperados = (argc > 1) ? atoi(argv[1]) : 0;
    int ok = 0, mal = 0, archivos = 0;
    ifstream entrada(RUTA);
    entrada >> ok >> mal >> archivos;

    cout << "==========================================================" << endl;
    cout << " TOTAL: " << ok << " pruebas OK, " << mal << " fallidas" << endl;
    if (archivos < esperados) {
        cout << " ATENCION: solo " << archivos << " de " << esperados
             << " archivos de prueba terminaron (alguno se cayó; revise la salida)" << endl;
    }
    if (mal == 0 && archivos >= esperados) {
        cout << " RESULTADO: TODAS LAS PRUEBAS PASAN" << endl;
    } else {
        cout << " RESULTADO: HAY PRUEBAS FALLIDAS" << endl;
    }
    cout << "==========================================================" << endl;
    return 0;
}
