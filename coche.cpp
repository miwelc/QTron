#include "coche.h"

Coche::Coche() {
    anchura = 4;
    longitud = 7;
    altura = 3;

    rueda.setColorSolido(0,0,1);
    rueda.setEscala(1.5,0.7,1.5);
    rueda.setOrientacion(0,1,0);
    posRuedas[0].x = posRuedas[1].x = longitud*2/3;
    posRuedas[2].x = posRuedas[3].x = -longitud*2/3;
    posRuedas[0].y = posRuedas[1].y = posRuedas[2].y = posRuedas[3].y = 0.5;
    posRuedas[0].z = posRuedas[2].z = -anchura+0.5;
    posRuedas[1].z = posRuedas[3].z = anchura-0.5;

    faro.setColorSolido(1,0,1);
    faro.setEscala(0.6);
    faro.setOrientacion(-1,1,0);
    posFaros[0].x = posFaros[1].x = longitud;
    posFaros[0].y = posFaros[1].y = altura*3/4;
    posFaros[0].z = -anchura*3/7;
    posFaros[1].z = anchura*3/7;

    cubo.asociarObjeto(&cuboObj);
    posCarroceria.x = posTecho.x = 0;
    posCarroceria.y = altura/2 + altura*1/5;
    posTecho.y = altura+(altura*1/3);
    posCarroceria.z = posTecho.z = 0;

}

void Coche::setPosicion(Vertice pos) {
    Vertice posAnt = posActual;
    posActual = pos;
    posTecho += posActual-posAnt;
    posCarroceria += posActual-posAnt;
    for(int i = 0; i < 4; i++)
        posRuedas[i] += posActual-posAnt;
    for(int i = 0; i < 2; i++)
        posFaros[i] += posActual-posAnt;
}

void Coche::draw() {
    //Dibujamos las ruedas
    for(int i = 0; i < 4; i++) {
        rueda.setPosicion(posRuedas[i]);
        rueda.draw();
    }

    //Dibujamos los faros
    for(int i = 0; i < 2; i++) {
        faro.setPosicion(posFaros[i]);
        faro.draw();
    }

    //Dibujamos la carroceria
    cubo.setColorSolido(1,0,0);
    cubo.setPosicion(posCarroceria);
    cubo.setEscala(longitud,altura*2/5,anchura);
    cubo.draw();

    //Dibujamos el techo
    cubo.setColorSolido(0,1,0);
    cubo.setPosicion(posTecho);
    cubo.setEscala(longitud/2,altura*1/3,anchura*5/6);
    cubo.draw();
}
