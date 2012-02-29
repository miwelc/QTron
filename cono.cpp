#include "cono.h"

Cono::Cono() {
    obj3d = new Objeto3D;
    float puntos[] = {0, 0.5};
    obj3d->generarRevolucion(puntos, 2, 10, 1);
}

Cono::~Cono() {
    delete obj3d;
}
