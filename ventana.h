#ifndef VENTANA_H
#define VENTANA_H

#include <QMainWindow>
#include <QInputDialog>
#include "visoropengl.h"

class QMenu;
class QAction;
class Ventana : public QMainWindow {
    Q_OBJECT
    public:
        Ventana();
        ~Ventana();

    private slots:
        void empezarPartida();
        void pausarPartida();
        void terminarPartida();

        void elegirNJugadores();
        void elegirTamTablero();
        void setVelocidad();

        void modoPuntos();
        void modoLineas();
        void modoSolido();
        void modoAjedrez();
        void modoFlat();
        void modoSmooth();
        void elegirReflejos();
        void elegirEjes();
        void setCamaraLibre();

        void showAcerca();
        void showAyuda();
        void showDemo();

    private:
        VisorOpenGL *visorOpenGL;
        QMenu *Juego;
            QAction *nuevoJuego;
            QAction *pausar;
            QAction *terminar;
            QAction *salir;
        QMenu *Opciones;
            QAction *NJugadores;
            QAction *TamTablero;
            QAction *Velocidad;
        QMenu *ModosVisualizacion;
            QAction *Reflejos;
            QAction *Ejes;
            QAction *CamaraLibre;
            QAction *Puntos;
            QAction *Lineas;
            QAction *Solido;
            QAction *Ajedrez;
            QAction *Flat;
            QAction *Smooth;
        QMenu *fullScreen;
            QAction *pantCompleta;
            QAction *pantNormal;
        QMenu *Extra;
            QAction *Ayuda;
            QAction *Acerca;
            QAction *Demo;
        void crearMenu();
};

#endif
