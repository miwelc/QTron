#ifndef MOTOS_H
#define MOTOS_H

#include <QList>
#include <QTimer>
#include <QTime>
#include <QGLWidget>
#include <QSound>
#include <QMessageBox>
#include <math.h>
#include "cubo.h"
#include "objeto3d.h"
#include "luz.h"
#include "Entidad3D.h"
#include "camara.h"
#include "file_ply_stl.h"
#include "explosion.h"

enum TipoCamara {
    CERCANA = 0,
    FRONTAL,
    AEREA,
    CENTRO_COORDENADAS
};

enum DireccionMov {
    ADELANTE,
    ATRAS,
    IZQUIERDA,
    DERECHA
};

class Estela;

class Motos : public QGLWidget {
    Q_OBJECT
    private:
        Objeto3D modeloMoto;
        float offCentro;
        float escala;
        int nMotos;
        Entidad3D *motos;
        DireccionMov *direccionesMov;
        Explosion explosion;
        Cubo cubo;
        Entidad3D puntoMapa;
        Camara *camaras;
        int *tipoCamara;
        int nTipoCamaras;
        int tamTablero;

        bool finPartida;
        bool partidaEnMarcha;
        bool *perdido;
        Estela *estelas;
        QTimer timer;
        float velocidadMotos;
        float velocidadGiro;

        QSound *sonidoMotor;
        QSound *sonidoExplosion;
        QSound *sonidoArrancar;

        //Gestión de las motos
        bool comprobarColisiones(int n);

    public:
        Motos();
        ~Motos();
        void iniciarCarrera(int nMotos, int tamTablero);
        void pausarCarrera(bool pausa);
        void terminarCarrera();
        void arrancarMotos();
        void pararMotos();
        void setVelocidadMotos(float vel) { velocidadMotos = vel; }
        void actualizarCamaras();
        void setCamara(int n);
        void cambiarTipoCamara(int n);
        void draw();
        void drawReflection();
        void drawPosicionesMapa();
        void setModoDibujo(int modo);
        void setModoSuavizado(GLenum modo);

        //Manejo
        void girar(DireccionMov direccionGiro, int nJugador);

    private slots:
        void actualizar();
};

class Estela : public Entidad3D {
    private:
        float offsetAtras;
        float altura;
        float anchura;
        Vertice orientacion;
        QVector<Vertice> lineas;
        int nSecciones;

    public:
        Estela();
        void drawPosicionMapa();
        int getNSecciones() { return nSecciones; }
        void setOffsetAtras(float offAtras) { offsetAtras = offAtras; }
        void setAltura(float alt) { altura = alt; }
        void setAnchura(float anch) { anchura = anch; }
        void setOrigenEstela(Vertice posicion, Vertice orientacion);
};

bool puntoEnCubo(Vertice punto, Vertice cubA, Vertice cubB, Vertice cubC, Vertice cubD,
                      Vertice cubE, Vertice cubF, Vertice cubG, Vertice cubH);

#endif // MOTO_H
