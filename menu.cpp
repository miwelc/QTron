#include "menu.h"

Menu::Menu() {
    alturaVentana = 0;
    anchoVentana = 0;
    camara.setPosicion(0,0,-8);
    camara.setDireccion(camara.getPosicion()-Vertice(0,0,0));
}

void Menu::setTamanoPantalla(int width, int height) {
    alturaVentana = height;
    anchoVentana = width;
}

void Menu::draw() {
    if(!fondo.cargada)
        showFondo();

    int Front_plane = 7;
    int Back_plane = 1800;
    double tangent = tan(60/2 * 3.14159265/180);
    double h = Front_plane * tangent;
    double w = h*anchoVentana/alturaVentana;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-w, w, -h, h, Front_plane, Back_plane);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, anchoVentana, alturaVentana);
    camara.setCamara();

    luz.encender();
    fondo.draw();
    luz.apagar();
}

void Menu::showAyuda() {
    fondo.cargarTextura("img/ayuda(465x203).raw", 465, 203);
    fondo.setEscala(13,5,0);
}

void Menu::showFondo() {
    fondo.cargarTextura("img/fondo(540x360).raw", 540, 360);
    fondo.setEscala(-15,10,0);
}
