#ifndef ENTIDAD3D_H
#define ENTIDAD3D_H

#include <iostream>
#include <QCoreApplication>
#include <GL/gl.h>
#include <QTimer>
#include <QEvent>
#include <QGLWidget>
#include <math.h>
#include <time.h>
#include "objeto3d.h"
#include "vertice.h"
#include "luz.h"

enum TipoAceleracion{
    LINEAL,
    SENOIDAL
};

class Entidad3D : public QGLWidget {
    Q_OBJECT
    protected:
        Objeto3D *obj3d;
        Vertice orientacion;
        Vertice frente;
        Vertice centro;
        Vertice posicion;
        float elevacion;
        Vertice escala;
        GLfloat colorSolido[3];
        GLfloat coloresAjedrez[2][3];
        GLenum modoSuavizado;
        int modoDibujo;

        //Animación
        QTimer timer;
        bool aleatoria;
        int aleatoriaX, aleatoriaY, aleatoriaZ;
        TipoAceleracion tipoAceleracion;
        Vertice inicioMov;
        Vertice destinoMov;
        double contadorTicksMov;
        double nTicksTotalesMov;
        float velocidadMov;
        Vertice inicioGiro;
        Vertice destinoGiro;
        double contadorTicksGiro;
        double nTicksTotalesGiro;
        float velocidadGiro;
        float velocidadAvance;
    public slots:
        void actualizar();

    public:
        Luz luz;
        Entidad3D();
        Entidad3D(Objeto3D *objasc);
        void asociarObjeto(Objeto3D *objasc);
        Vertice getVertice(int n) { return obj3d->getVertice(n); }
        void draw();
        void drawReflection();
        void drawTranslucido();
        void setModoDibujo(int modo) { modoDibujo = modo; }
        void setModoSuavizado(GLenum modo) { modoSuavizado = modo; }
        void setColorSolido(GLfloat r, GLfloat g, GLfloat b) {
            colorSolido[0] = r; colorSolido[1] = g; colorSolido[2] = b;
        }
        void setColorSolido(const GLfloat col[3]) {
            colorSolido[0] = col[0]; colorSolido[1] = col[1]; colorSolido[2] = col[2];
        }
        void getColorSolido(GLfloat col[3]) {
            col[0] = colorSolido[0]; col[1] = colorSolido[1]; col[2] = colorSolido[2];
        }
        void setColoresAjedrez(GLfloat r1, GLfloat g1, GLfloat b1, GLfloat r2, GLfloat g2, GLfloat b2) {
            coloresAjedrez[0][0] = r1; coloresAjedrez[0][1] = g1; coloresAjedrez[0][2] = b1;
            coloresAjedrez[1][0] = r2; coloresAjedrez[1][1] = g2; coloresAjedrez[1][2] = b2;
        }
        void setEscala(Vertice esc) { escala = esc; }
        void setEscala(float x, float y, float z) { escala = Vertice(x, y, z); }
        void setEscala(float esc) { escala = Vertice(esc, esc, esc); }
        void setFrente(Vertice fre) { frente = fre; }
        void setFrente(float x, float y, float z) { frente = Vertice(x, y, z); }
        void setCentro(Vertice cent) { centro = cent; }
        void setCentro(float x, float y, float z) { centro = Vertice(x, y, z); }
        Vertice getCentro() { return centro; }
        Vertice getPosicion() { return posicion; }
        void setElevacion(float ele) { elevacion = ele; }
        void setPosicion(Vertice pos) { posicion = pos; }
        void setPosicion(float x, float y, float z) { posicion = Vertice(x, y, z); }
        Vertice getOrientacion() { return orientacion; }
        void setOrientacion(Vertice ori) { orientacion = ori; }
        void setOrientacion(float x, float y, float z) { orientacion = Vertice(x, y, z); }
        GLfloat radioFrontera();

        //Animación
        bool girar;
        bool mover;
        bool avanzar;
        void animarMov(Vertice destino);
        void animarMov(Vertice destino, float vel);
        void animarAvanzar(float vel);
        void animarGiro(Vertice destino);
        void animarGiro(Vertice destino, float vel);
        Vertice getPosicionAleatoria(int margenX, int margenY, int margenZ);
        void animacionAleatoria();
        void animacionAleatoria(int margenX, int margenY, int margenZ);
        void pararAnimacion();
        void pararMover();
        void pararGirar();
        void pararAvanzar();
        void cambiarVelocidadMov(float vel);
        void cambiarVelocidadGiro(float vel);
        void setTipoAceleracion(TipoAceleracion acel);
};

#endif // ENTIDAD3D_H
