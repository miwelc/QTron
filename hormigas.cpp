#include "hormigas.h"

Hormigas::Hormigas() {
    vEstados = 0;
    vDestinos = 0;
    vResolviendoColision = 0;
    esperarSeparacion = true;
    numEstados = 0;
    connect(&timer, SIGNAL(timeout()), this, SLOT(actualizarEstados()));
}

Hormigas::~Hormigas() {
    delete [] vEstados;
    delete [] vDestinos;
    delete [] vResolviendoColision;
}

void Hormigas::actualizarEstados() {
    if(numEstados != numEntidades) {
        numEstados = numEntidades;
        delete [] vEstados;
        delete [] vDestinos;
        delete [] vResolviendoColision;
        vEstados = new EstadosHormiga[numEntidades];
        for(int i = 0; i < numEntidades; i++)
            vEstados[i] = BUSCAR_OBJETIVO;
        vDestinos = new Vertice[numEntidades];
        vResolviendoColision = new bool[numEntidades];
        for(int i = 0; i < numEntidades; i++)
            vResolviendoColision[i] = false;
    }
    if(esperarSeparacion)
        comprobarSeparacionInicial();
    for(int i = 0; i < numEntidades; i++) {
        //vColisiones[i] = false;
        if(!esperarSeparacion && vColisiones[i] && !vResolviendoColision[i]) {
            vDestinos[i] = vDestinos[i]*-1;
            vEstados[i] = GIRAR;
            vResolviendoColision[i] = true;
        } else if(!vColisiones[i] && vResolviendoColision[i])
            vResolviendoColision[i] = false;
        switch(vEstados[i]) {
            case BUSCAR_OBJETIVO:
                if(vectorEntidades[i].mover == false) {
                    buscarObjetivo(i);
                    vEstados[i] = GIRAR;
                }
                break;
            case GIRAR:
                if(vResolviendoColision[i] || vectorEntidades[i].mover == false) {
                    vectorEntidades[i].pararAnimacion();
                    vectorEntidades[i].animarGiro(vDestinos[i]-vectorEntidades[i].getPosicion());
                    vEstados[i] = AVANZAR;
                }
                break;
            case AVANZAR:
                if(vectorEntidades[i].girar == false) {
                    vectorEntidades[i].animarMov(vDestinos[i]);
                    vEstados[i] = BUSCAR_OBJETIVO;
                }
                break;
        }
    }
}

void Hormigas::buscarObjetivo(int i) {
    vDestinos[i].x = rand() % 160;
    if(rand()%2)
        vDestinos[i].x *= -1;
    vDestinos[i].z = rand() % 160;
    if(rand()%2)
        vDestinos[i].z *= -1;
}

void Hormigas::comprobarSeparacionInicial() {
    esperarSeparacion = false;
    for(int i = 0; i < numEntidades; i++)
        if(vColisiones[i] == true)
            esperarSeparacion = true;
}
