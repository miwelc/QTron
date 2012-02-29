#include "cilindro.h"

Cilindro::Cilindro() {
    obj3d = new Objeto3D;
    float puntos[] = {0.5, 0.5};
    obj3d->generarRevolucion(puntos, 2, 10, 1);
}

Cilindro::~Cilindro() {
    delete obj3d;
}
