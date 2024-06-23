#ifndef DIBUJO_HPP
#define DIBUJO_HPP

#include <fstream>
#include <string>
#include <curses.h>

class Dibujo {
private:
    std::fstream archivo;

protected:
    int y;
    int x;

public:
    Dibujo(int x, int y, std::string recurso) {
        abrirArchivo(recurso);
        this->x = x;
        this->y = y;
    }

    Dibujo(std::string recurso) {
        abrirArchivo(recurso);
        this->x = 0;
        this->y = 0;
    }

    void Dibujar() {
        std::string linea;
        move(this->y, this->x);
        while (std::getline(archivo, linea)) {
            mvaddstr(getcury(stdscr), this->x, linea.c_str());
            move(getcury(stdscr) + 1, this->x);
        }
        archivo.clear();
        archivo.seekg(0);
    }

    void abrirArchivo(std::string recurso) {
        if (archivo.is_open()) {
            archivo.close();
        }
        archivo.open("./Data/" + recurso + ".txt");
    }

    void cerrarArchivo() {
        if (archivo.is_open()) {
            archivo.close();
        }
    }

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    void setX(int newX) {
        x = newX;
    }

    void DesplazarIzq() {
        x -= 1;
    }

    void DesplazarDer() {
        x += 1;
    }

    ~Dibujo() {
        cerrarArchivo();
    }
};

#endif // DIBUJO_HPP
