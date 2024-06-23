#ifndef VENTANA_HPP
#define VENTANA_HPP

#include "Actualizable.hpp"
#include "Dibujo.hpp"
#include <list>
#include <curses.h>

class Ventana {
public:
    Ventana() {
        initscr(); // Inicializar la pantalla
        noecho();  // No mostrar las teclas presionadas
        curs_set(FALSE); // Ocultar el cursor
        keypad(stdscr, TRUE); // Habilitar la captura de teclas especiales
        timeout(100); // Establecer el tiempo de espera para getch()
    }

    ~Ventana() {
        endwin(); // Terminar ncurses
    }

    void Dibujar(std::list<Dibujo*>& dibujos) {
        clear(); // Limpiar la pantalla
        for (auto& dibujo : dibujos) {
            dibujo->Dibujar();
        }
        refresh(); // Refrescar la pantalla para mostrar los cambios
    }

    void Actualizar(std::list<Actualizable*>& actualizables) {
        for (auto& actualizable : actualizables) {
            actualizable->Actualizar();
        }
    }
};

#endif // VENTANA_HPP
