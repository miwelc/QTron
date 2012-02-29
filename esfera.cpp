#include "esfera.h"

Esfera::Esfera() {
    obj3d = new Objeto3D;
    int nPuntosSemicircun = 11; //Número IMPARRR

    float *puntos = new float[nPuntosSemicircun];
    for(int i = -nPuntosSemicircun/2; i <= nPuntosSemicircun/2; i++)
        puntos[i+nPuntosSemicircun/2] = sin(acos(i/5.0))*0.5;
    obj3d->generarRevolucion(puntos, nPuntosSemicircun, 8, 1);
    delete [] puntos;
}

Esfera::~Esfera() {
    delete obj3d;
}
