#ifndef OBJETO3D_H
#define OBJETO3D_H

#include <GL/gl.h>
#include <QVector>
#include <QList>
#include "vertice.h"
#include "luz.h"


struct Cara{
    int a;
    int b;
    int c;
};

class Objeto3D {
    protected:
        bool calculosIniciales;
        int nVertices;
        QVector<Vertice> vertices;
        QVector<Vertice> normalesVertices;
        int nCaras;
        QList<Cara> caras;
        QList<Vertice> normalesCaras;
        void dibujarCaraSmooth(QList<Cara>::iterator it) const;
        void dibujarCaraFlat(QList<Cara>::iterator it, QList<Vertice>::iterator itNormal) const;
        void dibujarVertice(int n) const;
        void calcularListaIndizadaVertices();
        void calcularNormales();
        Vertice calcularNormalCara(QList<Cara>::iterator itC) const;
        Vertice calcularNormalVertice(int n);
        void calcularRadioFrontera();

    public:
        Objeto3D();
        GLfloat radioFrontera;
        void generarRevolucion(float *puntos, int nPuntos, int nSecciones, float altura);
        void anadirVertices(Vertice *Vertices, int nVertices);
        void anadirVertices(QVector<Vertice> Vertices);
        void setVertice(int nVertice, Vertice valor);
        Vertice getVertice(int nVertice) { return vertices[nVertice]; }
        void anadirCaras(Cara *Caras, int nCaras);
        void cargarDatos(QVector<Vertice> Vertices, QVector<Cara> Faces);
        void cargarDatos(QVector<float> Vertices, QVector<int> Faces);
        virtual void draw(int modoDibujo, GLenum modoSuavizado, GLfloat colorSolido[3], GLfloat coloresAjedrez[2][3]);
};

#endif // OBJETO3D_H
