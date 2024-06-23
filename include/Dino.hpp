#ifndef DINO_HPP
#define DINO_HPP

#include "Dibujo.hpp"
#include "Actualizable.hpp"

class Dino : public Dibujo, public Actualizable {
private:
    bool saltando;
    bool agachado;
    int altura_salto;
    int velocidad_salto;
    int y_inicial;

public:
    Dino(int x, int y) : Dibujo(x, y, "Dino"), saltando(false), agachado(false), altura_salto(5), velocidad_salto(1), y_inicial(y) {}

    void DesplazarIzq() {
        x -= 1;
    }

    void DesplazarDer() {
        x += 1;
    }

    void Saltar() {
        if (!saltando && !agachado && y == y_inicial) {
            saltando = true;
        }
    }

    void Agacharse() {
        if (!saltando) {
            agachado = true;
            abrirArchivo("Dino_agachado");
        }
    }

    void Levantarse() {
        if (agachado) {
            agachado = false;
            abrirArchivo("Dino");
        }
    }

    void Actualizar() override {
        if (saltando) {
            y -= velocidad_salto;
            if (y <= y_inicial - altura_salto) {
                saltando = false;
            }
        } else if (y < y_inicial) {
            y += velocidad_salto;
        }
    }

    ~Dino() {}
};

#endif // DINO_HPP
