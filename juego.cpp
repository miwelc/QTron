#include "juego.h"

Juego::Juego() {
    srand(time(NULL));
    alturaVentana = 0;
    anchoVentana = 0;
    reflejos = true;
    mostrarEjes = false;
    partidaEmpezada = false;
    pausa = false;
    mapa = true;
    tamMapa = 120;
    tamTablero = 300;

    luz.setPosicion(0,-1,0, 1);
    camaraSuperior.setDireccion(0,1,0);

    nMotos = 2;
}

void Juego::iniciarPartida() {
    setModoSuavizado(GL_SMOOTH);
    camaraSuperior.setPosicion(0,tamTablero-20,0);
    tablero.setTamanoYDivisiones(tamTablero, 23);
    motos.iniciarCarrera(nMotos, tamTablero);
    motos.arrancarMotos();
    partidaEmpezada = true;
    camaraLibreActivada = false;
}

void Juego::pausarPartida() {
    if(partidaEmpezada) {
        pausa = !pausa;
        motos.pausarCarrera(pausa);
    }
}

void Juego::finalizarPartida() {
    partidaEmpezada = false;
    motos.terminarCarrera();
}

void Juego::setTamanoPantalla(int width, int height) {
    alturaVentana = height;
    anchoVentana = width;
}

void Juego::setProjection(int width, int height) {
    int Front_plane = 3.5;
    int Back_plane = 1800;
    double tangent = tan(60/2 * 3.14159265/180);
    double h = Front_plane * tangent;
    double w = h*width/height;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-w, w, -h, h, Front_plane, Back_plane);
    glMatrixMode(GL_MODELVIEW);
}

void Juego::setViewPort(int n) {
    int nViewPortsMitadInferior = nMotos/2;
    int nViewPortsMitadSuperior = nMotos-nViewPortsMitadInferior;
    float anchoViewPortMitadSuperior = anchoVentana/nViewPortsMitadSuperior;
    float anchoViewPortMitadInferior = anchoVentana/nViewPortsMitadInferior;
    float alturaViewPort = (nMotos == 1 ? alturaVentana : alturaVentana/2);

    if(n == -2) { //ViewPort para camara libre
        setProjection(anchoVentana, alturaVentana);
        glViewport(0, 0, anchoVentana, alturaVentana);
    }
    else if(n == -1) { //ViewPort para el mapa
        glScissor(anchoVentana/2 - tamMapa/2, alturaVentana/2, tamMapa, tamMapa);
        setProjection(tamMapa, tamMapa);
        glViewport(anchoVentana/2 - tamMapa/2, alturaVentana/2, tamMapa, tamMapa);
    }
    else if(n < nViewPortsMitadSuperior) {
        setProjection(anchoViewPortMitadSuperior, alturaViewPort);
        glViewport(anchoViewPortMitadSuperior*n, alturaVentana-alturaViewPort, anchoViewPortMitadSuperior, alturaViewPort);
    } else {
        setProjection(anchoViewPortMitadInferior, alturaViewPort);
        glViewport(anchoViewPortMitadInferior*(n-nViewPortsMitadSuperior), 0, anchoViewPortMitadInferior, alturaViewPort);
    }
}

void Juego::drawObjetos() {
    if(mostrarEjes)
        ejes.draw();
    motos.draw();
    if(reflejos)
        motos.drawReflection();
    tablero.drawTranslucido();
}

void Juego::draw() {
    if(partidaEmpezada) {
        if(camaraLibreActivada) {
            setViewPort(-2);
            camaraLibre.setCamara();
            drawObjetos();
        } else {
            motos.actualizarCamaras();
            for(int i = 0; i < nMotos; i++) {
                setViewPort(i);
                motos.setCamara(i);
                drawObjetos();
            }
            if(mapa) {
                glDisable(GL_DEPTH_TEST);
                setViewPort(-1);
                glEnable(GL_SCISSOR_TEST);
                glClear(GL_COLOR_BUFFER_BIT); //Borramos lo que haya debajo del mapa
                glDisable(GL_SCISSOR_TEST);
                camaraSuperior.setCamara();
                if(mostrarEjes)
                    ejes.draw();
                motos.drawPosicionesMapa();
                glEnable(GL_DEPTH_TEST);
            }
        }
    }
}

void Juego::teclasPulsadas(int tecla) {
    if(tecla == Qt::Key_P) pausarPartida();
    //Controles
    if(camaraLibreActivada) {
        camaraLibre.mover(tecla);
    } else {
        switch(tecla) {
            case Qt::Key_A:
                motos.girar(IZQUIERDA, 1);
                break;
            case Qt::Key_S:
                motos.girar(DERECHA, 1);
                break;
            case Qt::Key_Z:
                motos.cambiarTipoCamara(1);
                break;

            case Qt::Key_G:
                motos.girar(IZQUIERDA, 2);
                break;
            case Qt::Key_H:
                motos.girar(DERECHA, 2);
                break;
            case Qt::Key_B:
                motos.cambiarTipoCamara(2);
                break;

            case Qt::Key_L:
                motos.girar(IZQUIERDA, 3);
                break;
            case Qt::Key_Ntilde:
                motos.girar(DERECHA, 3);
                break;
            case Qt::Key_Period:
                motos.cambiarTipoCamara(3);
                break;

            case Qt::Key_Left:
                motos.girar(IZQUIERDA, 4);
                break;
            case Qt::Key_Right:
                motos.girar(DERECHA, 4);
                break;
            case Qt::Key_Up:
                motos.cambiarTipoCamara(4);
                break;
        }
    }
}
