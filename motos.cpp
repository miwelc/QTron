#include "motos.h"

/////////////////////
////   MOTOS     ////
/////////////////////
Motos::Motos() {
    QVector<float> Vertices;
    QVector<int> Caras;
    _file_ply PLY;

    if(PLY.open((char*)"./modelos/moto.ply") == -1)
        std::cout << endl << "Error al cargar el archivo moto.ply" <<endl;
    PLY.read(Vertices, Caras);
    PLY.close();
    modeloMoto.cargarDatos(Vertices, Caras);

    puntoMapa.asociarObjeto(&cubo);
    puntoMapa.setModoDibujo(2);
    puntoMapa.setEscala(4);

    nMotos = 0;
    offCentro = 1.3;
    escala = 5;
    perdido = 0;
    motos = 0;
    direccionesMov = 0;
    estelas = 0;
    camaras = 0;
    tipoCamara = 0;
    nTipoCamaras = 4;
    velocidadMotos = 0.3;
    velocidadGiro = 0.065;

    partidaEnMarcha = false;
    finPartida = false;

    connect(&timer, SIGNAL(timeout()), this, SLOT(actualizar()));

    sonidoMotor = new QSound("sonidos/motor.wav");
    sonidoMotor->setLoops(-1);
    sonidoExplosion = new QSound("sonidos/explosion.wav");
    sonidoArrancar = new QSound("sonidos/arrancar.wav");
}

Motos::~Motos() {
    delete [] perdido;
    delete [] motos;
    delete [] direccionesMov;
    delete [] estelas;
    delete [] camaras;
    delete [] tipoCamara;
}

void Motos::iniciarCarrera(int nMotos, int tamTablero) {
    this->nMotos = nMotos;
    delete [] perdido;
    delete [] motos;
    delete [] direccionesMov;
    delete [] camaras;
    delete [] tipoCamara;
    camaras = new Camara[nMotos];
    tipoCamara = new int[nMotos];
    direccionesMov = new DireccionMov[nMotos];
    estelas = new Estela[nMotos];
    motos = new Entidad3D[nMotos];
    perdido = new bool[nMotos];
    this->tamTablero = tamTablero;
    for(int i = 0; i < nMotos; i++) {
        perdido[i] = false;
        motos[i].asociarObjeto(&modeloMoto);
        motos[i].setEscala(escala,escala,escala);
        motos[i].setCentro(0,0,offCentro);
        motos[i].setElevacion(2.8);
        motos[i].setFrente(0,0,1);
        motos[i].setPosicion(motos->getPosicionAleatoria(tamTablero/3, 0, tamTablero/3));
        estelas[i].setOffsetAtras(0);
        estelas[i].setAltura(4.5);
        estelas[i].setAnchura(1);
        switch(rand()%4) {
            case 0:
                direccionesMov[i] = ADELANTE;
                motos[i].setOrientacion(0,0,1);
                break;
            case 1:
                direccionesMov[i] = ATRAS;
                motos[i].setOrientacion(0,0,-1);
                break;
            case 2:
                direccionesMov[i] = DERECHA;
                motos[i].setOrientacion(-1,0,0);
                break;
            case 3:
                direccionesMov[i] = IZQUIERDA;
                motos[i].setOrientacion(1,0,0);
                break;
        }
        switch(i%4) {
            case 0: //Rojo
                motos[i].setColorSolido(1,0,0);
                motos[i].luz.setMaterialAmbiente(0.6, 0.1, 0.1, 1.0f);
                motos[i].luz.setMaterialDifusa(0.6, 0.1, 0.1, 1.0f);
                motos[i].luz.setMaterialEspecular(0.2, 0.1, 0.1, 1.0f);
                motos[i].luz.setBrillo(0.01f);
                motos[i].luz.setLuzAmbiente(0.2, 0.1, 0.1, 1.0f);
                motos[i].luz.setLuzDifusa(0.5, 0.1, 0.1, 1.0f);
                motos[i].luz.setLuzEspecular(0.4, 0.4, 0.4, 1.0f);
                estelas[i].setColorSolido(1,0,0);
                estelas[i].luz.setMaterialAmbiente(0.6, 0.1, 0.1, 1.0f);
                estelas[i].luz.setMaterialDifusa(0.6, 0.1, 0.1, 1.0f);
                estelas[i].luz.setMaterialEspecular(0.2, 0.1, 0.1, 1.0f);
                estelas[i].luz.setBrillo(0.01f);
                estelas[i].luz.setLuzAmbiente(0.2, 0.1, 0.1, 1.0f);
                estelas[i].luz.setLuzDifusa(0.5, 0.1, 0.1, 1.0f);
                estelas[i].luz.setLuzEspecular(0.4, 0.4, 0.4, 1.0f);
                break;
            case 1: //Azul
                motos[i].setColorSolido(0,0,1);
                motos[i].luz.setMaterialAmbiente(0.1, 0.1, 0.6, 1.0f);
                motos[i].luz.setMaterialDifusa(0.1, 0.1, 0.6, 1.0f);
                motos[i].luz.setMaterialEspecular(0.1, 0.1, 0.2, 1.0f);
                motos[i].luz.setBrillo(0.01f);
                motos[i].luz.setLuzAmbiente(0.1, 0.1, 0.2, 1.0f);
                motos[i].luz.setLuzDifusa(0.1, 0.1, 0.5, 1.0f);
                motos[i].luz.setLuzEspecular(0.4, 0.4, 0.4, 1.0f);
                estelas[i].setColorSolido(0,0,1);
                estelas[i].luz.setMaterialAmbiente(0.1, 0.1, 0.6, 1.0f);
                estelas[i].luz.setMaterialDifusa(0.1, 0.1, 0.6, 1.0f);
                estelas[i].luz.setMaterialEspecular(0.1, 0.1, 0.2, 1.0f);
                estelas[i].luz.setBrillo(0.01f);
                estelas[i].luz.setLuzAmbiente(0.1, 0.1, 0.2, 1.0f);
                estelas[i].luz.setLuzDifusa(0.1, 0.1, 0.5, 1.0f);
                estelas[i].luz.setLuzEspecular(0.4, 0.4, 0.4, 1.0f);
                break;
            case 2: //Gris
                motos[i].setColorSolido(0.5,0.5,0.5);
                motos[i].luz.setMaterialAmbiente(0.3, 0.3, 0.3, 1.0f);
                motos[i].luz.setMaterialDifusa(0.3, 0.3, 0.3, 1.0f);
                motos[i].luz.setMaterialEspecular(0.2, 0.2, 0.2, 1.0f);
                motos[i].luz.setBrillo(0.01f);
                motos[i].luz.setLuzAmbiente(0.2, 0.2, 0.2, 1.0f);
                motos[i].luz.setLuzDifusa(0.3, 0.3, 0.3, 1.0f);
                motos[i].luz.setLuzEspecular(0.4, 0.4, 0.4, 1.0f);
                estelas[i].setColorSolido(0.5,0.5,0.5);
                estelas[i].luz.setMaterialAmbiente(0.3, 0.3, 0.3, 1.0f);
                estelas[i].luz.setMaterialDifusa(0.3, 0.3, 0.3, 1.0f);
                estelas[i].luz.setMaterialEspecular(0.2, 0.2, 0.2, 1.0f);
                estelas[i].luz.setBrillo(0.01f);
                estelas[i].luz.setLuzAmbiente(0.2, 0.2, 0.2, 1.0f);
                estelas[i].luz.setLuzDifusa(0.3, 0.3, 0.3, 1.0f);
                estelas[i].luz.setLuzEspecular(0.4, 0.4, 0.4, 1.0f);
                break;
            case 3: //Verde
                motos[i].setColorSolido(0,1,0);
                motos[i].luz.setMaterialAmbiente(0.1, 0.6, 0.1, 1.0f);
                motos[i].luz.setMaterialDifusa(0.1, 0.6, 0.1, 1.0f);
                motos[i].luz.setMaterialEspecular(0.1, 0.2, 0.1, 1.0f);
                motos[i].luz.setBrillo(0.01f);
                motos[i].luz.setLuzAmbiente(0.1, 0.2, 0.1, 1.0f);
                motos[i].luz.setLuzDifusa(0.1, 0.5, 0.1, 1.0f);
                motos[i].luz.setLuzEspecular(0.4, 0.4, 0.4, 1.0f);
                estelas[i].setColorSolido(0,1,0);
                estelas[i].luz.setMaterialAmbiente(0.1, 0.6, 0.1, 1.0f);
                estelas[i].luz.setMaterialDifusa(0.1, 0.6, 0.1, 1.0f);
                estelas[i].luz.setMaterialEspecular(0.1, 0.2, 0.1, 1.0f);
                estelas[i].luz.setBrillo(0.01f);
                estelas[i].luz.setLuzAmbiente(0.1, 0.2, 0.1, 1.0f);
                estelas[i].luz.setLuzDifusa(0.1, 0.5, 0.1, 1.0f);
                estelas[i].luz.setLuzEspecular(0.4, 0.4, 0.4, 1.0f);
                break;
        }
        tipoCamara[i] = CERCANA;
    }
}

void Motos::pausarCarrera(bool pause) {
    if(pause)
        pararMotos();
    else if(!finPartida)
        arrancarMotos();
}

void Motos::terminarCarrera() {
    finPartida = true;
    pararMotos();
}

void Motos::pararMotos() {
    partidaEnMarcha = false;
    timer.stop();
    sonidoMotor->stop();
    for(int i = 0; i < nMotos; i++)
        motos[i].pararAnimacion();
}

void Motos::arrancarMotos() {
    finPartida = false;
    partidaEnMarcha = true;
    //sonidoArrancar->play();
    sonidoMotor->play();
    for(int i = 0; i < nMotos; i++)
        if(!perdido[i])
            motos[i].animarAvanzar(velocidadMotos);
    timer.start(0);
}

void Motos::actualizarCamaras() {
    /*GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    float alturaViewPort = viewport[3]-viewport[1];*/
    for(int i = 0; i < nMotos; i++) {
        if(perdido[i])
            tipoCamara[i] = AEREA;
        if(tipoCamara[i] == CENTRO_COORDENADAS) {
            camaras[i].setPosicion(0,15,0);
            camaras[i].setDireccion(camaras[i].getPosicion()-(motos[i].getPosicion()+motos[i].getOrientacion().versor()*(offCentro*escala)));
        }
        else if(tipoCamara[i] == CERCANA) {
            camaras[i].setPosicion(motos[i].getPosicion()+Vertice(0,6.5,0)+motos[i].getOrientacion().versor()*-9);
            camaras[i].setDireccion(camaras[i].getPosicion()-(motos[i].getPosicion()+motos[i].getOrientacion().versor()*(offCentro*escala)));
        }
        else if(tipoCamara[i] == FRONTAL) {
            camaras[i].setPosicion(motos[i].getPosicion()+Vertice(0,escala+0.5,0)+motos[i].getOrientacion().versor()*-offCentro);
            camaras[i].setDireccion(motos[i].getOrientacion().versor()*-1);
        }
        else if(tipoCamara[i] == AEREA) {
            camaras[i].setPosicion(0,150,0);
            camaras[i].setDireccion(camaras[i].getPosicion()-(motos[i].getPosicion()+motos[i].getOrientacion().versor()*(offCentro*escala)));
        }
    }
}

void Motos::setCamara(int n) {
    camaras[n].setCamara();
}

void Motos::cambiarTipoCamara(int n) {
    if(n > nMotos) return;
    tipoCamara[n-1] = (tipoCamara[n-1]+1)%nTipoCamaras;
}

void Motos::draw() {
    for(int i = 0; i < nMotos; i++) {
        estelas[i].draw();
        if(!perdido[i])
            motos[i].draw();
        //else
        //    explosion.draw();
    }
}

void Motos::drawReflection() {
    for(int i = 0; i < nMotos; i++) {
        estelas[i].drawReflection();
        if(!perdido[i])
            motos[i].drawReflection();
    }
}

void Motos::drawPosicionesMapa() {
    GLfloat col[3];
    for(int i = 0; i < nMotos; i++) {
        estelas[i].drawPosicionMapa();
        puntoMapa.setPosicion(motos[i].getPosicion());
        motos[i].getColorSolido(col);
        puntoMapa.setColorSolido(col);
        if(!perdido[i])
            puntoMapa.draw();
    }
}

void Motos::setModoDibujo(int modo) {
    for(int i = 0; i < nMotos; i++) {
        estelas[i].setModoDibujo(modo);
        motos[i].setModoDibujo(modo);
    }
}

void Motos::setModoSuavizado(GLenum modo) {
    for(int i = 0; i < nMotos; i++) {
        estelas[i].setModoSuavizado(modo);
        motos[i].setModoSuavizado(modo);
    }
}

void Motos::girar(DireccionMov direccionGiro, int nJugador) {
    if(!partidaEnMarcha || perdido[nJugador-1] || nJugador > nMotos) return;
    if(direccionGiro == DERECHA) {
        switch(direccionesMov[nJugador-1]) {
            case ADELANTE:
                direccionesMov[nJugador-1] = DERECHA;
                motos[nJugador-1].animarAvanzar(velocidadMotos);
                motos[nJugador-1].animarGiro(Vertice(-1,0,0), velocidadGiro);
                break;
            case DERECHA:
                direccionesMov[nJugador-1] = ATRAS;
                motos[nJugador-1].animarAvanzar(velocidadMotos);
                motos[nJugador-1].animarGiro(Vertice(0,0,-1), velocidadGiro);
                break;
            case ATRAS:
                direccionesMov[nJugador-1] = IZQUIERDA;
                motos[nJugador-1].animarAvanzar(velocidadMotos);
                motos[nJugador-1].animarGiro(Vertice(1,0,0), velocidadGiro);
                break;
            case IZQUIERDA:
                direccionesMov[nJugador-1] = ADELANTE;
                motos[nJugador-1].animarAvanzar(velocidadMotos);
                motos[nJugador-1].animarGiro(Vertice(0,0,1), velocidadGiro);
                break;
        }
    }
    else if(direccionGiro == IZQUIERDA) {
        switch(direccionesMov[nJugador-1]) {
            case ADELANTE:
                direccionesMov[nJugador-1] = IZQUIERDA;
                motos[nJugador-1].animarAvanzar(velocidadMotos);
                motos[nJugador-1].animarGiro(Vertice(1,0,0), velocidadGiro);
                break;
            case DERECHA:
                direccionesMov[nJugador-1] = ADELANTE;
                motos[nJugador-1].animarAvanzar(velocidadMotos);
                motos[nJugador-1].animarGiro(Vertice(0,0,1), velocidadGiro);
                break;
            case ATRAS:
                direccionesMov[nJugador-1] = DERECHA;
                motos[nJugador-1].animarAvanzar(velocidadMotos);
                motos[nJugador-1].animarGiro(Vertice(-1,0,0), velocidadGiro);
                break;
            case IZQUIERDA:
                direccionesMov[nJugador-1] = ATRAS;
                motos[nJugador-1].animarAvanzar(velocidadMotos);
                motos[nJugador-1].animarGiro(Vertice(0,0,-1), velocidadGiro);
                break;
        }
    }
}

void Motos::actualizar() {
    for(int i = 0; i < nMotos; i++)
        estelas[i].setOrigenEstela(motos[i].getPosicion(), motos[i].getOrientacion());
    for(int i = 0; i < nMotos; i++) {
        if(!perdido[i] && comprobarColisiones(i)) {
            perdido[i] = true;
            //sonidoExplosion->play();
            //explosion.crearExplosion(motos[i].getPosicion(), 30, 3, 5, 0.5, 0.1);
            motos[i].pararAnimacion();

            int k = 0, ganador = 0;
            for(int j = 0; j < nMotos; j++) {
                if(perdido[j]) k++;
                else ganador = j;
            }
            if(k == nMotos-1 || (nMotos == 1 && k == 1)) {
                sonidoMotor->stop();
                sonidoExplosion->play();
                terminarCarrera();
                QMessageBox msgBox;
                msgBox.setText(QString("El jugador %1 es el ganador!       ").arg(ganador+1));
                msgBox.setWindowTitle("Partida finalizada");
                msgBox.exec();
            }
        }
    }
}

bool Motos::comprobarColisiones(int n) {
    Vertice puntoColision = motos[n].getPosicion()+motos[n].getOrientacion().versor()*motos[n].getCentro().modulo();

    //Se sale del tablero
    if(puntoColision.x > tamTablero/2 || puntoColision.x < -tamTablero/2 || puntoColision.z > tamTablero/2 || puntoColision.z < -tamTablero/2)
        return true;

    for(int i = 0; i < nMotos; i++) {
        for(int j = 0; j < estelas[i].getNSecciones()-1; j++) {
            if(puntoEnCubo(puntoColision, estelas[i].getVertice(j*4), estelas[i].getVertice(j*4+1), estelas[i].getVertice(j*4+2), estelas[i].getVertice(j*4+3),
                        estelas[i].getVertice((j+1)*4), estelas[i].getVertice((j+1)*4+1), estelas[i].getVertice((j+1)*4+2), estelas[i].getVertice((j+1)*4+3)))
                return true;
        }
    }
    return false;
}

bool puntoEnCubo(Vertice punto, Vertice cubA, Vertice cubB, Vertice cubC, Vertice cubD,
                      Vertice cubE, Vertice cubF, Vertice cubG, Vertice cubH) {
    Vertice max, min;

    //Calculamos la bounding box
    max.x = min.x = cubA.x;
    max.y = min.y = cubA.y;
    max.z = min.z = cubA.z;

    if(cubB.x > max.x) max.x = cubB.x;
    if(cubB.x < min.x) min.x = cubB.x;
    if(cubB.y > max.y) max.y = cubB.y;
    if(cubB.y < min.y) min.y = cubB.y;
    if(cubB.z > max.z) max.z = cubB.z;
    if(cubB.z < min.z) min.z = cubB.z;

    if(cubC.x > max.x) max.x = cubC.x;
    if(cubC.x < min.x) min.x = cubC.x;
    if(cubC.y > max.y) max.y = cubC.y;
    if(cubC.y < min.y) min.y = cubC.y;
    if(cubC.z > max.z) max.z = cubC.z;
    if(cubC.z < min.z) min.z = cubC.z;

    if(cubD.x > max.x) max.x = cubD.x;
    if(cubD.x < min.x) min.x = cubD.x;
    if(cubD.y > max.y) max.y = cubD.y;
    if(cubD.y < min.y) min.y = cubD.y;
    if(cubD.z > max.z) max.z = cubD.z;
    if(cubD.z < min.z) min.z = cubD.z;

    if(cubE.x > max.x) max.x = cubE.x;
    if(cubE.x < min.x) min.x = cubE.x;
    if(cubE.y > max.y) max.y = cubE.y;
    if(cubE.y < min.y) min.y = cubE.y;
    if(cubE.z > max.z) max.z = cubE.z;
    if(cubE.z < min.z) min.z = cubE.z;

    if(cubF.x > max.x) max.x = cubF.x;
    if(cubF.x < min.x) min.x = cubF.x;
    if(cubF.y > max.y) max.y = cubF.y;
    if(cubF.y < min.y) min.y = cubF.y;
    if(cubF.z > max.z) max.z = cubF.z;
    if(cubF.z < min.z) min.z = cubF.z;

    if(cubG.x > max.x) max.x = cubG.x;
    if(cubG.x < min.x) min.x = cubG.x;
    if(cubG.y > max.y) max.y = cubG.y;
    if(cubG.y < min.y) min.y = cubG.y;
    if(cubG.z > max.z) max.z = cubG.z;
    if(cubG.z < min.z) min.z = cubG.z;

    if(cubH.x > max.x) max.x = cubH.x;
    if(cubH.x < min.x) min.x = cubH.x;
    if(cubH.y > max.y) max.y = cubH.y;
    if(cubH.y < min.y) min.y = cubH.y;
    if(cubH.z > max.z) max.z = cubH.z;
    if(cubH.z < min.z) min.z = cubH.z;

    if(punto.x >= min.x && punto.x <= max.x &&
            punto.y >= min.y && punto.y <= max.y &&
            punto.z >= min.z && punto.z <= max.z)
        return true;
    else
        return false;
}

/////////////////////
////   ESTELA    ////
/////////////////////
Estela::Estela() {
    offsetAtras = altura = anchura = nSecciones = 0;
    obj3d = new Objeto3D;
}

void Estela::drawPosicionMapa() {
    glBegin(GL_LINES);
    glColor3fv(colorSolido);
    for(int i = 0; i < nSecciones-1; i++) {
        glVertex3fv(lineas[i].v());
        glVertex3fv(lineas[i+1].v());
    }
    glEnd();
}

void Estela::setOrigenEstela(Vertice posicion, Vertice orientacion) {
    Vertice V; //Vector en el plano de la seccion y paralelo al suelo
    Vertice puntoBase; //Punto en el centro de la seccion y tocando el suelo
    V = (orientacion*Vertice(0,1,0)).versor();
    puntoBase = posicion+orientacion.versor()*offsetAtras; puntoBase.y = 0;

    //Si hay una nueva orientación o es la primera sección
    if(this->orientacion.anguloV(orientacion) > M_PI_2/4 || nSecciones <= 1) {
        //Añadimos Vertices
        Vertice nuevaSeccion[4];
        nuevaSeccion[0] = puntoBase-V*anchura/2;
        nuevaSeccion[1] = puntoBase+V*anchura/2;
        nuevaSeccion[2] = puntoBase-V*anchura/2+Vertice(0,altura,0);
        nuevaSeccion[3] = puntoBase+V*anchura/2+Vertice(0,altura,0);
        obj3d->anadirVertices(nuevaSeccion, 4);

        //Versión simplificada de las estelas
        lineas.push_back(puntoBase);

        if(nSecciones) {
            //Añadimos Caras
            Cara nuevasCaras[6];
            nuevasCaras[0].a = 4*(nSecciones-1); nuevasCaras[0].b = 4*(nSecciones-1)+4; nuevasCaras[0].c = 4*(nSecciones-1)+2;
            nuevasCaras[1].a = 4*(nSecciones-1)+2; nuevasCaras[1].b = 4*(nSecciones-1)+4; nuevasCaras[1].c = 4*(nSecciones-1)+6;
            nuevasCaras[2].a = 4*(nSecciones-1)+1; nuevasCaras[2].b = 4*(nSecciones-1)+5; nuevasCaras[2].c = 4*(nSecciones-1)+3;
            nuevasCaras[3].a = 4*(nSecciones-1)+3; nuevasCaras[3].b = 4*(nSecciones-1)+5; nuevasCaras[3].c = 4*(nSecciones-1)+7;
            nuevasCaras[4].a = 4*(nSecciones-1)+2; nuevasCaras[4].b = 4*(nSecciones-1)+7; nuevasCaras[4].c = 4*(nSecciones-1)+6;
            nuevasCaras[5].a = 4*(nSecciones-1)+3; nuevasCaras[5].b = 4*(nSecciones-1)+7; nuevasCaras[5].c = 4*(nSecciones-1)+2;
            obj3d->anadirCaras(nuevasCaras, 6);
        }
        else {
            Cara nuevasCaras[2];
            nuevasCaras[0].a = 0; nuevasCaras[0].b = 1; nuevasCaras[0].c = 2;
            nuevasCaras[1].a = 1; nuevasCaras[1].b = 3; nuevasCaras[1].c = 2;
            obj3d->anadirCaras(nuevasCaras, 2);
        }

        this->orientacion = orientacion;
        nSecciones++;
    }
    else { //Misma orientación que antes
        obj3d->setVertice(4*(nSecciones-1), puntoBase-V*anchura/2);
        obj3d->setVertice(4*(nSecciones-1)+1, puntoBase+V*anchura/2);
        obj3d->setVertice(4*(nSecciones-1)+2, puntoBase-V*anchura/2+Vertice(0,altura,0));
        obj3d->setVertice(4*(nSecciones-1)+3, puntoBase+V*anchura/2+Vertice(0,altura,0));

        //Versión simplificada de las estelas
        lineas[nSecciones-1] = puntoBase;
    }
}
