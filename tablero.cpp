#include "tablero.h"
Tablero::~Tablero() {
    delete obj3d;
}

Tablero::Tablero() {
    setTamanoYDivisiones(300, 23);
}

void Tablero::setTamanoYDivisiones(int tam, int nDiv) {
    tamano = tam;
    nDivisiones = nDiv;

    delete obj3d;
    obj3d = new Objeto3D;

    float distanciaX, distanciaZ;
    QVector<Cara> caras;
    QVector<Vertice> vertices;
    int nVertices = (nDivisiones+1)*(nDivisiones+1);
    int nCaras = nDivisiones*nDivisiones*2;

    //Vertices
    vertices.resize(nVertices);
    float incremento = tamano / nDivisiones;
    distanciaX = -tamano/2;
    for(int i = 0; i <= nDivisiones; i++) {
        distanciaZ = -tamano/2;
        for(int j = 0; j <= nDivisiones; j++) {
            vertices[(nDivisiones+1)*i+j].x = distanciaX;
            vertices[(nDivisiones+1)*i+j].y = 0;
            vertices[(nDivisiones+1)*i+j].z = distanciaZ;
            distanciaZ += incremento;
         }
         distanciaX += incremento;
    }

    //Caras
    caras.resize(nCaras);
    for(int j = 0; j < nDivisiones; j++) {
        for(int i = 0; i < nDivisiones; i++) {
            int numVertice = i + (nDivisiones+1)*j;
            int numCara = 2*i + 2*nDivisiones*j;
            caras[numCara].a = numVertice;
            caras[numCara].b = numVertice+1;
            caras[numCara].c = numVertice + (nDivisiones+1);
            caras[numCara+1].a = numVertice+1;
            caras[numCara+1].b = numVertice+1 + (nDivisiones+1);
            caras[numCara+1].c = numVertice + (nDivisiones+1);
        }
    }

    obj3d->cargarDatos(vertices, caras);

    setModoDibujo(4);
    luz.setMaterialAmbiente(0.07, 0.07, 0.07, 1.0f);
    luz.setMaterialDifusa(0.07, 0.07, 0.07, 1.0f);
    luz.setMaterialEspecular(0.2, 0.2, 0.2, 1.0f);
    luz.setComponenteAmbiente(0.3, 0.3, 0.3, 1.0f);
    luz.setLuzAmbiente(0.3, 0.3, 0.3, 1.0f);
    luz.setLuzDifusa(0.2, 0.2, 0.2, 1.0f);
    luz.setLuzEspecular(0.4, 0.4, 0.4, 1.0f);
    luz.setBrillo(0.1f);
}
