#ifndef ESCENA_H
#define ESCENA_H

#include <QVector>
#include <QEvent>
#include <GL/gl.h>
#include <math.h>
#include <time.h>
#include "axis.h"
#include "luz.h"
#include "objeto3d.h"
#include "Entidad3D.h"
#include "camara.h"
#include "tablero.h"
#include "motos.h"

class Juego {
    private:
        Axis ejes;
        Luz luz;
        Camara camaraSuperior;
        Tablero tablero;
        bool reflejos;
        bool mostrarEjes;
        bool partidaEmpezada;
        bool pausa;
        bool camaraLibreActivada;
        int nMotos;
        float alturaVentana;
        float anchoVentana;
        bool mapa;
        float tamMapa;
        int tamTablero;
        void setProjection(int width, int height);
        void setViewPort(int n);

    public:
        Camara camaraLibre;
        Motos motos;
        Juego();
        void setReflejos(bool opc) { reflejos = opc; }
        void setEjes(bool opc) { mostrarEjes = opc; }
        void setCamaraLibre(bool cam) { camaraLibreActivada = cam; }
        void setTamanoPantalla(int width, int height);
        void setNumeroMotos(int n) { nMotos = n; finalizarPartida(); }
        void setTamanoTablero(int tam) { tamTablero = tam; finalizarPartida(); }
        void iniciarPartida();
        void pausarPartida();
        void finalizarPartida();
        void drawObjetos();
        void draw();
        void teclasPulsadas(int tecla);
        void setModoDibujo(int modo) {
            motos.setModoDibujo(modo);
            tablero.setModoDibujo(modo);
        }
        void setModoSuavizado(GLenum modo) {
            motos.setModoSuavizado(modo);
            tablero.setModoSuavizado(modo);
        }
};

#endif

