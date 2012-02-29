#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <QObject>
#include <QVector>
#include <QTimer>
#include "particulas.h"

class Explosion : public Particulas {
    Q_OBJECT
    private:
        Objeto3D obj;
        int nParticulas;
        int nNiveles;
        float radio;
        float velocidad;
        float gravedad;
        QVector<Vertice> orientaciones;

    private slots:
        void actualizar();

    public:
        Explosion();
        void crearExplosion(Vertice centro, int nParticulas, int nNiveles, float radio, float velocidad, float gravedad);
        void draw();
};

#endif // EXPLOSION_H
