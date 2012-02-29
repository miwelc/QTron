#ifndef PARTICULAS_H
#define PARTICULAS_H

#include <QTimer>
#include "Entidad3D.h"

class Particulas : public QGLWidget {
    Q_OBJECT
    protected:
        Objeto3D *objeto3d;
        Entidad3D *vectorEntidades;
        int numEntidades;
        bool *vColisiones;
        QTimer timer;
    public:
        Particulas();
        ~Particulas();
        void crearConjunto(Objeto3D *obj3d, int num);
        void setFrente(Vertice fren);
        void setPosicion(Vertice pos);
        void setPosicion(int n, Vertice pos);
        Vertice getPosicion(int n);
        void draw();
        void setModoDibujo(int modo);
        void setModoSuavizado(GLenum modo);
        void setColorSolido(GLfloat r, GLfloat g, GLfloat b);
        void setEscala(float esc);

        void animacionAleatoria();
        void animacionAleatoria(int margenX, int margenY, int margenZ);
        void cambiarVelocidadMov(float vel);
        void cambiarVelocidadGiro(float vel);
        void setTipoAceleracion(TipoAceleracion acel);
    public slots:
        void comprobarColisiones();
};

#endif // PARTICULAS_H
