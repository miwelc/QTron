#include "cubo.h"

Cubo::Cubo() {
        nVertices = 8;
        nCaras = 12;

        //Vertices
        vertices.resize(nVertices);

        vertices[0].x = -1;
        vertices[0].y = -1;
        vertices[0].z = -1;

        vertices[1].x = -1;
        vertices[1].y = 1;
        vertices[1].z = -1;

        vertices[2].x = -1;
        vertices[2].y = -1;
        vertices[2].z = 1;

        vertices[3].x = -1;
        vertices[3].y = 1;
        vertices[3].z = 1;

        vertices[4].x = 1;
        vertices[4].y = -1;
        vertices[4].z = 1;

        vertices[5].x = 1;
        vertices[5].y = 1;
        vertices[5].z = 1;

        vertices[6].x = 1;
        vertices[6].y = -1;
        vertices[6].z = -1;

        vertices[7].x = 1;
        vertices[7].y = 1;
        vertices[7].z = -1;

        //Caras
        Cara caraAux;
        for(int i = 0; i < nVertices; i += 2) {
            caraAux.a = i;
            caraAux.b = (i+1)%nVertices;
            caraAux.c = (i+2)%nVertices;
            caras.push_back(caraAux);
            caraAux.a = (i+3)%nVertices;
            caraAux.b = (i+2)%nVertices;
            caraAux.c = (i+1)%nVertices;
            caras.push_back(caraAux);
        }
        //Bases
        caraAux.a = 4;
        caraAux.b = 2;
        caraAux.c = 0;
        caras.push_back(caraAux);
        caraAux.a = 6;
        caraAux.b = 4;
        caraAux.c = 0;
        caras.push_back(caraAux);
        //
        caraAux.a = 5;
        caraAux.b = 3;
        caraAux.c = 1;
        caras.push_back(caraAux);
        caraAux.a = 7;
        caraAux.b = 5;
        caraAux.c = 1;
        caras.push_back(caraAux);
}
