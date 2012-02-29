#ifndef TEXTURA_H
#define TEXTURA_H

#include <GL/gl.h>
#include "luz.h"
#include "vertice.h"

class Textura {
    private:
        Luz luz;
        GLuint idTextura;
        unsigned char *data;
        int nBytes;
        int alto;
        int ancho;

        Vertice posicion;
        Vertice escala;

    public:
        bool cargada;
        Textura();
        ~Textura();
        void cargarTextura(const char* archivo, int anch, int alt);
        void draw();
        void setPosicion(Vertice pos) { posicion = pos; }
        void setPosicion(float x, float y, float z) { posicion = Vertice(x, y, z); }
        void setEscala(Vertice esc) { escala = Vertice(-esc.x,-esc.y,esc.z); }
        void setEscala(float x, float y, float z) { escala = Vertice(-x, -y, z); }
        void setEscala(float esc) { escala = Vertice(-esc, -esc, esc); }
};

#endif // TEXTURA_H
