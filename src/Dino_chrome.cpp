#include "Dibujo.hpp"
#include "Ventana.hpp"
#include "Dino.hpp"
#include <list>
#include <curses.h>
#include <cstdlib>
#include <ctime>
#include <fstream> // Para escribir en un archivo

using namespace std;

bool detectarColision(Dibujo* dino, Dibujo* cactus) {
    // Asegúrate de ajustar las coordenadas y tamaños según tu gráfico
    return abs(dino->getX() - cactus->getX()) < 2 && dino->getY() == cactus->getY();
}

void logEstado(ofstream& logFile, const Dino* dino, const list<Dibujo*>& cactus) {
    logFile << "Estado del Dino: x=" << dino->getX() << ", y=" << dino->getY() << endl;
    for (const auto& c : cactus) {
        logFile << "Cactus en: x=" << c->getX() << ", y=" << c->getY() << endl;
    }
    logFile << "--------------------------------" << endl;
}

int main(int argc, char const *argv[])
{
    srand(time(0));

    ofstream logFile("game_debug.log");

    Ventana ventana;
    Dino *dino = new Dino(5, 15);
    Dibujo *camino1 = new Dibujo(0, 20, "Camino");
    Dibujo *camino2 = new Dibujo(80, 20, "Camino");
    Dibujo *nube = new Dibujo(20, 5, "Nube");

    list<Dibujo *> dibujos;
    dibujos.push_back(dino);
    dibujos.push_back(camino1);
    dibujos.push_back(camino2);
    dibujos.push_back(nube);

    list<Actualizable *> actualizables;
    actualizables.push_back(dino);

    list<Dibujo *> cactus;

    int tick = 0;
    bool gameOver = false;

    while (true)
    {
        int key = getch();
        if (key == 'q' || key == 'Q')
        {
            break;
        }
        if (!gameOver) {
            if (key == 'a' || key == KEY_LEFT)
            {
                dino->DesplazarIzq();
            }
            if (key == 'd' || key == KEY_RIGHT)
            {
                dino->DesplazarDer();
            }
            if (key == 'w' || key == KEY_UP)
            {
                dino->Saltar();
            }
            if (key == 's' || key == KEY_DOWN)
            {
                dino->Agacharse();
            }
            if (key == 'e' || key == 'E')
            {
                dino->Levantarse();
            }

            if (tick % 50 == 0) {
                int cactus_x = rand() % 50 + 80;
                Dibujo *nuevoCactus = new Dibujo(cactus_x, 19, "Cactus"); // Ajusta la posición de los cactus
                dibujos.push_back(nuevoCactus);
                cactus.push_back(nuevoCactus);
            }

            for (auto it = cactus.begin(); it != cactus.end(); ) {
                Dibujo *c = *it;
                c->DesplazarIzq();
                if (c->getX() < 0) {
                    // Log de depuración para ver cuándo se elimina un cactus
                    logFile << "Eliminando cactus en x=" << c->getX() << ", y=" << c->getY() << endl;
                    it = cactus.erase(it);
                    delete c;
                } else {
                    if (detectarColision(dino, c)) {
                        gameOver = true;
                        break;
                    }
                    ++it;
                }
            }

            if (gameOver) {
                Dibujo *gameOverMessage = new Dibujo(10, 10, "GameOver");
                dibujos.push_back(gameOverMessage);
            }

            // Desplazar los segmentos del camino
            camino1->DesplazarIzq();
            camino2->DesplazarIzq();
            
            // Si un segmento del camino sale de la pantalla, reposiciónalo al final del otro segmento
            if (camino1->getX() < -80) {
                camino1->setX(camino2->getX() + 80);
            }
            if (camino2->getX() < -80) {
                camino2->setX(camino1->getX() + 80);
            }

            ventana.Actualizar(actualizables);
            ventana.Dibujar(dibujos);
            tick++;

            // Log del estado del juego para depuración
            logEstado(logFile, dino, cactus);
        }
    }

    // Limpiar memoria
    for (auto c : cactus) {
        delete c;
    }
    delete dino;
    delete camino1;
    delete camino2;
    delete nube;

    logFile.close();

    return 0;
}