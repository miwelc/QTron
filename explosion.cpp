#include "explosion.h"

Explosion::Explosion() {
    connect(&timer, SIGNAL(timeout()), this, SLOT(actualizar()));
}

/**********************************************************
** IMPORTANTE: nParticulas debe ser divisible por nNiveles
**********************************************************/
void Explosion::crearExplosion(Vertice centro, int nParticulas, int nNiveles, float radio, float velocidad, float gravedad) {
    QVector<Vertice> vertices;
    QVector<Cara> cara;

    this->nParticulas = nParticulas;
    this->nNiveles = nNiveles;
    this->radio = radio;
    this->velocidad = velocidad;
    this->gravedad = gravedad;

    vertices.resize(3);
    vertices[0].x = -1; vertices[0].y = 0; vertices[0].z = 1;
    vertices[1].x = 1; vertices[1].y = 0; vertices[1].z = 1;
    vertices[2].x = 0; vertices[2].y = 0; vertices[2].z = -1;
    cara.resize(1);
    cara[0].a = 0; cara[0].b = 1; cara[0].c = 2;
    obj.cargarDatos(vertices, cara);


    crearConjunto(&obj, nParticulas);
    setColorSolido(255,165,0);
    setModoDibujo(2);
    setPosicion(centro);
    setEscala(5);

    int particulasPorNivel = nParticulas/nNiveles;
    for(float theta = -M_PI/2; theta <= M_PI/2; theta += M_PI/nNiveles) {
        for(float phi = 0; phi < 2*M_PI; phi += 2*M_PI/particulasPorNivel) { //Dividimos en nNiveles alturas con nParticulasPorNivel para cada circunferencia
            Vertice vertAux;
            vertAux.setFromEsfericas(radio, phi, theta);
            orientaciones.push_back(vertAux);
        }
    }

    timer.start(0);
}

void Explosion::actualizar() {
    for(int i = 0; i < nParticulas; i++) {
        setPosicion(i, getPosicion(i)+orientaciones[i].versor()*velocidad);
        //particulas.setOrientacion();
    }
    //disconnect(&timer, SIGNAL(timeout()), this, SLOT(actualizar()));
}

void Explosion::draw() {
    draw();
}
