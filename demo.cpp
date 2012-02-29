#include "demo.h"

Demo::Demo() {
    QVector<float> Vertices;
    QVector<int> Caras;
    _file_ply PLY;

    modoDemo = FIGURAS;

    PLY.open((char*)"modelos/ant.ply");
    PLY.read(Vertices, Caras);
    PLY.close();
    objetoPLY.cargarDatos(Vertices, Caras);
    hormigas.crearConjunto(&objetoPLY, 10);
    hormigas.setFrente(Vertice(0,0,1));
    velocidadAnimacion = 0.3;

    cubo.asociarObjeto(&cuboObj);
    cubo.setPosicion(6,1.5,6);
    cubo.setEscala(2);
    cubo.setColorSolido(0.2,0.2,0.2);

    tetraedro.asociarObjeto(&tetraObj);
    tetraedro.setPosicion(-5,0,5);
    tetraedro.setEscala(2);
    tetraedro.setColorSolido(0.2,0.2,0.2);

    cilindro.setPosicion(2,1,2);
    cilindro.setEscala(2);
    cilindro.setColorSolido(0.2,0.2,0.2);

    esfera.setPosicion(-4,1,20);
    esfera.setEscala(2,2,2);
    esfera.setColorSolido(0.2,0.2,0.2);

    cono.setPosicion(-2,1,-2);
    cono.setEscala(2);
    cono.setColorSolido(0.2,0.2,0.2);

    coche.setPosicion(Vertice(-15,0,-10));

    camara.setPosicion(0,8,-20);
    camara.setDireccion(camara.getPosicion()-Vertice(0,0,0));
}

void Demo::setTamanoPantalla(int width, int height) {
    alturaVentana = height;
    anchoVentana = width;
}

void Demo::setImagen() {
    int Front_plane = 3.5;
    int Back_plane = 1800;
    double tangent = tan(60/2 * 3.14159265/180);
    double h = Front_plane * tangent;
    double w = h*anchoVentana/alturaVentana;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-w, w, -h, h, Front_plane, Back_plane);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, anchoVentana, alturaVentana);
}

void Demo::draw() {
    setImagen();
    camara.setCamara();
    ejes.draw();
    tablero.draw();
    if(modoDemo == FIGURAS) {
        cilindro.draw();
        esfera.draw();
        cubo.draw();
        tetraedro.draw();
        cono.draw();
        coche.draw();
    }
    else if(modoDemo == HORMIGAS)
        hormigas.draw();
}

void Demo::teclasPulsadas(int tecla) {
    camara.mover(tecla);
    if(modoDemo == HORMIGAS) {
        switch(tecla) {
            case Qt::Key_Minus:
                velocidadAnimacion -= 0.05;
                if(velocidadAnimacion <= 0)
                    velocidadAnimacion = 0.05;
                hormigas.cambiarVelocidadMov(velocidadAnimacion);
                break;
            case Qt::Key_Plus:
                velocidadAnimacion += 0.05;
                hormigas.cambiarVelocidadMov(velocidadAnimacion);
                break;
            case Qt::Key_K:
                hormigas.setTipoAceleracion(SENOIDAL);
                break;
            case Qt::Key_L:
                hormigas.setTipoAceleracion(LINEAL);
                break;
        }
    }
}
