#ifndef MENU_H
#define MENU_H

#include "camara.h"
#include "textura.h"
#include "luz.h"

class Menu {
    private:
        Camara camara;
        Luz luz;
        Textura fondo;
        float alturaVentana;
        float anchoVentana;

    public:
        Menu();
        void setTamanoPantalla(int width, int height);
        void draw();
        void showAyuda();
        void showFondo();
};

#endif // MENU_H
