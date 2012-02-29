#include "tetraedro.h"

Tetraedro::Tetraedro() {
        //Vertices
        QVector<Vertice> vertices;
        vertices.resize(4);
	float incremento = 2.0*PI / 3;
	for(int i = 0; i < 3; i++) {
                vertices[i].x = cos(incremento*i);
                vertices[i].y = -(altura-radio);
                vertices[i].z = sin(incremento*i);
	}
	
        vertices[3].x = vertices[3].z = 0;
        vertices[3].y = 1;
	
        //Caras
        QVector<Cara> caras;
        caras.resize(4);
        caras[0].a = 0;
        caras[0].b = 1;
        caras[0].c = 2;
        caras[1].a = 0;
        caras[1].b = 1;
        caras[1].c = 3;
        caras[2].a = 1;
        caras[2].b = 2;
        caras[2].c = 3;
        caras[3].a = 2;
        caras[3].b = 0;
        caras[3].c = 3;

        cargarDatos(vertices, caras);
}


