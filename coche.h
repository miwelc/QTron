#ifndef COCHE_H
#define COCHE_H

#include <GL/gl.h>
#include "Entidad3D.h"
#include "cubo.h"
#include "cilindro.h"
#include "cono.h"

class Coche {
    private:
        float anchura;
        float longitud;
        float altura;
        Vertice posActual;
        int modoDibujo;
        Cubo cuboObj;
        Entidad3D cubo;
        Vertice posTecho;
        Vertice posCarroceria;
        Cilindro rueda;
        Vertice posRuedas[4];
        Cono faro;
        Vertice posFaros[2];
    public:
        Coche();
        void setPosicion(Vertice pos);
        void draw();
        void setModoDibujo(int modo) {
             modoDibujo = modo;
             cubo.setModoDibujo(modoDibujo);
             rueda.setModoDibujo(modoDibujo);
             faro.setModoDibujo(modoDibujo);
        }
        void setModoSuavizado(GLenum modo) {
             cubo.setModoSuavizado(modo);
             rueda.setModoSuavizado(modo);
             faro.setModoSuavizado(modo);
        }
};


#endif // COCHE_H
