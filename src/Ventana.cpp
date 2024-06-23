#include "Ventana.hpp"

Ventana::Ventana() {
    initscr(); // Inicializar la pantalla
    noecho();  // No mostrar las teclas presionadas
    curs_set(FALSE); // Ocultar el cursor
    keypad(stdscr, TRUE); // Habilitar la captura de teclas especiales
    timeout(100); // Establecer el tiempo de espera para getch()
}

Ventana::~Ventana() {
    endwin(); // Terminar ncurses
}

void Ventana::Dibujar(std::list<Dibujo*>& dibujos) {
    clear(); // Limpiar la pantalla
    for (auto& dibujo : dibujos) {
        dibujo->Dibujar();
    }
    refresh(); // Refrescar la pantalla para mostrar los cambios
}

void Ventana::Actualizar(std::list<Actualizable*>& actualizables) {
    for (auto& actualizable : actualizables) {
        actualizable->Actualizar();
    }
}