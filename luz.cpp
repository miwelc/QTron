#include "luz.h"

void copiarV4(GLfloat* A, GLfloat *B){
    A[0] = B[0];
    A[1] = B[1];
    A[2] = B[2];
    A[3] = B[3];
}
Luz::Luz() {
    setPosicion(1.0, 1.0, 1.0, 0.0);
    setComponenteAmbiente(0.4, 0.4, 0.4, 1.0);
    setLuzAmbiente(0.6, 0.6, 0.6, 1.0);
    setLuzDifusa(0.4, 0.4, 0.4, 1.0);
    setLuzEspecular(0.2, 0.2, 0.2, 1);
    setMaterialAmbiente(0.7,0.7, 0.7, 1);
    setMaterialDifusa(0.7,0.7, 0.7, 1);
    setMaterialEspecular(0.2, 0.2, 0.2, 1);
    setBrillo(0.2);
}

void Luz::encender() {
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_POSITION, posicion);
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
    glEnable(GL_LIGHT0);

    glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbiente);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDifusa);
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialEspecular);
    glMaterialf(GL_FRONT, GL_SHININESS, brillo);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, componenteAmbiente);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
}

void Luz::setComponenteAmbiente(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
    componenteAmbiente[0] = r;
    componenteAmbiente[1] = g;
    componenteAmbiente[2] = b;
    componenteAmbiente[3] = a;
}

void Luz::setColoresLuz(GLfloat *ambiente, GLfloat *difusa, GLfloat *especular) {
    copiarV4(luzAmbiente, ambiente);
    copiarV4(luzDifusa, difusa);
    copiarV4(luzEspecular, especular);
}

void Luz::setLuzAmbiente(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
    luzAmbiente[0] = r;
    luzAmbiente[1] = g;
    luzAmbiente[2] = b;
    luzAmbiente[3] = a;
}
void Luz::setLuzDifusa(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
    luzDifusa[0] = r;
    luzDifusa[1] = g;
    luzDifusa[2] = b;
    luzDifusa[3] = a;
}
void Luz::setLuzEspecular(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
    luzEspecular[0] = r;
    luzEspecular[1] = g;
    luzEspecular[2] = b;
    luzEspecular[3] = a;
}

void Luz::setColoresMaterial(GLfloat *ambiente, GLfloat *difusa, GLfloat *especular) {
    copiarV4(materialAmbiente, ambiente);
    copiarV4(materialDifusa, difusa);
    copiarV4(materialEspecular, especular);
}

void Luz::setMaterialAmbiente(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
    materialAmbiente[0] = r;
    materialAmbiente[1] = g;
    materialAmbiente[2] = b;
    materialAmbiente[3] = a;
}
void Luz::setMaterialDifusa(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
    materialDifusa[0] = r;
    materialDifusa[1] = g;
    materialDifusa[2] = b;
    materialDifusa[3] = a;
}
void Luz::setMaterialEspecular(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
    materialEspecular[0] = r;
    materialEspecular[1] = g;
    materialEspecular[2] = b;
    materialEspecular[3] = a;
}

void Luz::setPosicion(GLfloat x, GLfloat y, GLfloat z, GLfloat a) {
    posicion[0] = -x;
    posicion[1] = -y;
    posicion[2] = -z;
    posicion[3] = -a;
}
