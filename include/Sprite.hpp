#pragma once
#include <list>
#include "Dibujo.hpp" // Suponiendo que Dibujo.hpp está en el mismo directorio o ruta especificada

using namespace std;

class Sprite : public Dibujo {
private:
    int cuadroActual;
    list<Dibujo*> cuadros;

public:
    Sprite(list<Dibujo*> cuadros) : cuadroActual(0), cuadros(cuadros) {
        // Constructor inicializa cuadroActual a 0 y asigna la lista de cuadros
    }

    void Dibujar() override {
        if (cuadroActual >= 0 && cuadroActual < cuadros.size()) {
            cuadros[cuadroActual]->Dibujar();
        }
    }

    void AvanzarCuadro() {
        cuadroActual = (cuadroActual + 1) % cuadros.size();
        // Avanza al siguiente cuadro circularmente
    }

    ~Sprite() {
        // Liberar recursos si es necesario
        for (auto cuadro : cuadros) {
            delete cuadro;
        }
        cuadros.clear();
    }
};
