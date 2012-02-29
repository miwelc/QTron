#ifndef HORMIGAS_H
#define HORMIGAS_H

#include "particulas.h"

class Hormigas : public Particulas {
    Q_OBJECT
    private:
        enum EstadosHormiga {
            BUSCAR_OBJETIVO,
            GIRAR,
            AVANZAR
        };
        EstadosHormiga *vEstados;
        Vertice *vDestinos;
        bool *vResolviendoColision;
        bool esperarSeparacion;
        int numEstados;
        void buscarObjetivo(int i);
        void comprobarSeparacionInicial();
    public:
        Hormigas();
        ~Hormigas();
    public slots:
        void actualizarEstados();
};

#endif // HORMIGAS_H
