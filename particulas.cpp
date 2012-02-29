#include "particulas.h"

Particulas::Particulas() {
    objeto3d = 0;
    vectorEntidades = 0;
    numEntidades = 0;
    vColisiones = 0;
    timer.start(0);
    connect(&timer, SIGNAL(timeout()), this, SLOT(comprobarColisiones()));
}

Particulas::~Particulas() {
    delete [] vectorEntidades;
    delete [] vColisiones;
}

void Particulas::crearConjunto(Objeto3D *obj3d, int num) {
    objeto3d = obj3d;
    numEntidades = num;

    delete [] vectorEntidades;
    delete [] vColisiones;
    vectorEntidades = new Entidad3D[numEntidades];
    vColisiones = new bool[numEntidades];

    for(int i = 0; i < numEntidades; i++)
        vectorEntidades[i].asociarObjeto(objeto3d);
}

void Particulas::setFrente(Vertice fren) {
    for(int i = 0; i < numEntidades; i++)
        vectorEntidades[i].setFrente(fren);
}

void Particulas::setPosicion(Vertice pos) {
    for(int i = 0; i < numEntidades; i++)
        vectorEntidades[i].setPosicion(pos);
}

void Particulas::setPosicion(int n, Vertice pos) {
    vectorEntidades[n].setPosicion(pos);
}

Vertice Particulas::getPosicion(int n) {
    return vectorEntidades[n].getPosicion();
}

void Particulas::draw() {
    for(int i = 0; i < numEntidades; i++)
        vectorEntidades[i].draw();
}

void Particulas::setModoDibujo(int modo) {
    for(int i = 0; i < numEntidades; i++)
        vectorEntidades[i].setModoDibujo(modo);
}

void Particulas::setModoSuavizado(GLenum modo) {
    for(int i = 0; i < numEntidades; i++)
        vectorEntidades[i].setModoSuavizado(modo);
}

void Particulas::setColorSolido(GLfloat r, GLfloat g, GLfloat b) {
    for(int i = 0; i < numEntidades; i++)
        vectorEntidades[i].setColorSolido(r, g, b);
}

void Particulas::setEscala(float esc) {
    for(int i = 0; i < numEntidades; i++)
        vectorEntidades[i].setEscala(esc);
}

void Particulas::animacionAleatoria() {
    for(int i = 0; i < numEntidades; i++)
        vectorEntidades[i].animacionAleatoria();
}

void Particulas::animacionAleatoria(int margenX, int margenY, int margenZ) {
    for(int i = 0; i < numEntidades; i++)
        vectorEntidades[i].animacionAleatoria(margenX, margenY, margenZ);
}

void Particulas::cambiarVelocidadMov(float vel) {
    for(int i = 0; i < numEntidades; i++)
        vectorEntidades[i].cambiarVelocidadMov(vel);
}

void Particulas::cambiarVelocidadGiro(float vel) {
    for(int i = 0; i < numEntidades; i++)
        vectorEntidades[i].cambiarVelocidadGiro(vel);
}

void Particulas::setTipoAceleracion(TipoAceleracion acel) {
    for(int i = 0; i < numEntidades; i++)
        vectorEntidades[i].setTipoAceleracion(acel);
}


void Particulas::comprobarColisiones() {
    //Reseteamos
    for(int i = 0; i < numEntidades; i++)
        vColisiones[i] = false;
    //Comprobamos
    for(int i = 0; i < numEntidades; i++) {
        for(int j = i+1; j < numEntidades; j++) {
            Vertice dist = vectorEntidades[i].getPosicion()-vectorEntidades[j].getPosicion();
            if(dist.modulo() < vectorEntidades[i].radioFrontera()+vectorEntidades[j].radioFrontera())
                vColisiones[i] = vColisiones[j] = true;
        }
    }
}
