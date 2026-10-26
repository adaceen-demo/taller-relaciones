# Makefile del Taller Relaciones en Bus Fever Party (FPOO). Este archivo NO se edita.
#
#   make                compila el programa de ejemplo (ejecutable: relaciones)
#   make test           compila y corre TODAS las pruebas y muestra el total
#   make run-fila       corre solo pruebas/test_fila.cpp (cambie 'fila' por la clase)
#   make clean          borra lo compilado
#
# Funciona en Linux, macOS y Windows (con MinGW-w64/MSYS2 y make).
# Solo usa g++ y funciones propias de make.

CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Isrc -Isrc/modelo -Ipruebas -MMD -MP

ifeq ($(OS),Windows_NT)
EXE = .exe
else
EXE =
endif

# Si falta la carpeta build/ (por ejemplo, después de borrarla a mano), se crea.
ifeq ($(wildcard build/.),)
$(shell mkdir build)
endif

# Los .cpp se buscan en estas carpetas; todo lo compilado va a build/ (carpeta plana)
vpath %.cpp src src/modelo pruebas

SRC_LIB    = $(wildcard src/modelo/*.cpp)
OBJ_LIB    = $(addprefix build/, $(notdir $(SRC_LIB:.cpp=.o)))
TEST_SRC   = $(wildcard pruebas/test_*.cpp)
TEST_NAMES = $(patsubst test_%,%,$(basename $(notdir $(TEST_SRC))))
RESUMEN    = build/resumen_pruebas$(EXE)

all: relaciones$(EXE)

relaciones$(EXE): $(OBJ_LIB) build/main.o
	$(CXX) $(CXXFLAGS) $^ -o $@

build/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/test_%$(EXE): build/test_%.o $(OBJ_LIB)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(RESUMEN): build/resumen_pruebas.o
	$(CXX) $(CXXFLAGS) $^ -o $@

# El "-" deja seguir con las demás pruebas aunque un ejecutable se caiga.
run-%: build/test_%$(EXE)
	$(info === pruebas de $* ===)
	-@build/test_$*$(EXE)

correr-todas: $(addprefix run-, $(TEST_NAMES))

test: $(RESUMEN)
	@$(RESUMEN) --reiniciar
	@$(MAKE) --no-print-directory correr-todas
	@$(RESUMEN) $(words $(TEST_NAMES))

clean:
ifeq ($(OS),Windows_NT)
	-@del /Q /F build\*.o build\*.d build\*.exe build\*.txt relaciones.exe
else
	@rm -f build/*.o build/*.d build/*.txt build/test_* build/resumen_pruebas relaciones
endif

-include $(wildcard build/*.d)

.PHONY: all test correr-todas clean
.SECONDARY:
