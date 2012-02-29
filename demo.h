#ifndef DEMO_H
#define DEMO_H

#include <QVector>
#include <iostream>
#include <GL/gl.h>
#include "axis.h"
#include "objeto3d.h"
#include "Entidad3D.h"
#include "cubo.h"
#include "cilindro.h"
#include "esfera.h"
#include "cono.h"
#include "tetraedro.h"
#include "coche.h"
#include "hormigas.h"
#include "file_ply_stl.h"
#include "tablero.h"
#include "luz.h"
#include "camara.h"

enum MODO_DEMO {
    FIGURAS,
    HORMIGAS
};

class Demo {
    private:
        MODO_DEMO modoDemo;
        Axis ejes;
        Cubo cuboObj;
        Entidad3D cubo;
        Cilindro cilindro;
        Esfera esfera;
        Cono cono;
        Tetraedro tetraObj;
        Entidad3D tetraedro;
        Coche coche;
        Objeto3D objetoPLY;
        Tablero tablero;
        Hormigas hormigas;
        float velocidadAnimacion;
        float alturaVentana;
        float anchoVentana;

    public:
        Camara camara;
        Demo();
        void setModoDemo(MODO_DEMO mod) { modoDemo = mod; }
        void teclasPulsadas(int tecla);
        void setTamanoPantalla(int width, int height);
        void setImagen();
        void draw();
        void setModoDibujo(int modo) {
            cubo.setModoDibujo(modo);
            tetraedro.setModoDibujo(modo);
            cilindro.setModoDibujo(modo);
            esfera.setModoDibujo(modo);
            cono.setModoDibujo(modo);
            coche.setModoDibujo(modo);
            hormigas.setModoDibujo(modo);
            tablero.setModoDibujo(modo);
        }
        void setModoSuavizado(GLenum modo) {
            cubo.setModoSuavizado(modo);
            tetraedro.setModoSuavizado(modo);
            cilindro.setModoSuavizado(modo);
            esfera.setModoSuavizado(modo);
            cono.setModoSuavizado(modo);
            coche.setModoSuavizado(modo);
            hormigas.setModoSuavizado(modo);
            tablero.setModoSuavizado(modo);
        }
};

#endif

