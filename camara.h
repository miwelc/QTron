#ifndef CAMARA_H
#define CAMARA_H

#include <GL/gl.h>
#include <QEvent>
#include <math.h>
#include "vertice.h"
#include "matrix.h"

#define PI_CONS 3.14159265

class Camara {
    private:
        Vertice VRP;
        Vertice VPN;
        Vertice VUP;
        Vertice n; //Z' ~ VPN
        Vertice u; //X' ~ VPN X VUP
        Vertice v; //Y' ~ n X u
        void calcularNUV();
    public:
        Camara();
        void setCamara();
        void configurarCamara(Vertice vrp, Vertice vpn, Vertice vup) { VRP = vrp; VPN = vpn; VUP = vup; calcularNUV(); }
        Vertice getPosicion() { return VRP; }
        void setPosicion(GLfloat x, GLfloat y, GLfloat z) { VRP = Vertice(x, y, z); }
        void setPosicion(Vertice pos) { VRP = pos; }
        void setDireccion(Vertice dir) { VPN = dir;  calcularNUV(); }
        void setDireccion(GLfloat x, GLfloat y, GLfloat z) { VPN = Vertice(x, y, z);  calcularNUV(); }
        void mover(int tecla);
        /*
        void rotarN(GLfloat angulo);
        void rotarU(GLfloat angulo);
        void rotarV(GLfloat angulo);
        */

};

#endif // CAMARA_H
