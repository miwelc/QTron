#include "textura.h"
#include <fstream>

using namespace std;

Textura::Textura() {
    idTextura = 0;
    data = 0;
    cargada = false;
}
Textura::~Textura() {
    glDeleteTextures(1, &idTextura);
}

void Textura::cargarTextura(const char* archivo, int anch, int alt) {
    ifstream entrada;
    entrada.open(archivo, ios::binary);

    //Calculamos tamaño
    entrada.seekg(0, ios::end);
    nBytes = entrada.tellg();
    entrada.seekg (0, ios::beg);

    delete [] data;
    data = new unsigned char[nBytes];
    entrada.read((char*)data, nBytes);

    entrada.close();

    alto = alt;
    ancho = anch;

    glGenTextures(1,&idTextura);
    glBindTexture(GL_TEXTURE_2D, idTextura);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,0,3,ancho,alto,0, GL_RGB,GL_UNSIGNED_BYTE, data);

    cargada = true;
}

void Textura::draw() {
    if(!glIsTexture(idTextura)) return;

    glPushMatrix();

    //Posicion//
    glTranslatef(posicion.x-escala.x/2, posicion.y-escala.y/2, posicion.z);

    //Escala//
    glScalef(escala.x, escala.y, escala.z);

    luz.encender();

    glColor4f(0,0,0,1);
    glBindTexture(GL_TEXTURE_2D, idTextura);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0,0.0); glVertex2f(0.0,0.0);
    glTexCoord2f(1.0,0.0); glVertex2f(1.0,0.0);
    glTexCoord2f(1.0,1.0); glVertex2f(1.0,1.0);
    glTexCoord2f(0.0,1.0); glVertex2f(0.0,1.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    luz.apagar();

    glPopMatrix();
}
