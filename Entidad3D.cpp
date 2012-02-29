#include "Entidad3D.h"

Entidad3D::Entidad3D() {
    setModoDibujo(4);
    setModoSuavizado(GL_SMOOTH);
    setColorSolido(1, 1, 1);
    setColoresAjedrez(0,1,0, 1,0,0);
    setFrente(0, 0, -1);
    setEscala(1, 1, 1);
    setElevacion(0);
    setCentro(0, 0, 0);
    setPosicion(0, 0, 0);
    setOrientacion(0, 0, -1);

    //Animación
    mover = girar = avanzar = false;
    tipoAceleracion = LINEAL;
    aleatoria = false;
    aleatoriaX = 120;
    aleatoriaY = 0;
    aleatoriaZ = 120;
    velocidadMov = 0.45;
    velocidadGiro = 0.05;
    velocidadAvance = 0.3;
    connect(&timer, SIGNAL(timeout()), this, SLOT(actualizar()));
}

Entidad3D::Entidad3D(Objeto3D *objasc) {
    obj3d = objasc;
    Entidad3D();
}

void Entidad3D::asociarObjeto(Objeto3D *objasc) { obj3d = objasc; }

void Entidad3D::draw() {
    double rad;

    glPushMatrix();

    //Posicion//
    glTranslatef(posicion.x, posicion.y+elevacion, posicion.z);

    //Orientacion//
    //Ajustar el frente
    if(frente.z == 0) frente.z = 0.01;
    rad = Vertice(frente.x,0,frente.z).anguloZ();
    if(frente.x<0)
        rad *= -1;
    glRotatef(180*rad/M_PI, 0, 1, 0);

    //Rotacion sobre ejeY
    if(orientacion.z == 0) orientacion.z = 0.01;
    rad = Vertice(orientacion.x,0,orientacion.z).anguloZ();
    if(orientacion.x<0)
        rad *= -1;
    glRotatef(180*rad/M_PI, 0, 1, 0);

    //Rotacion sobre ejeX
    rad = Vertice(0,orientacion.y,orientacion.z).anguloZ();
    if(orientacion.z < 0)
        rad = M_PI-rad;
    if(orientacion.y < 0)
        rad *= -1;
    if(abs(rad) > 0.01) glRotatef(180*rad/M_PI, -1, 0, 0);

    //Escala//
    glScalef(escala.x, escala.y, escala.z);

    //Centro//
    glTranslatef(centro.x, centro.y, centro.z);

    //Luz//
   if(modoDibujo == 4)
        luz.encender();

    //Dibujar//
    obj3d->draw(modoDibujo, modoSuavizado, colorSolido, coloresAjedrez);

    luz.apagar();

    glPopMatrix();
}

void Entidad3D::drawReflection() {
    setEscala(escala.x, -escala.y, escala.z);
    setCentro(centro.x, -centro.y, centro.z);
    setElevacion(-elevacion);
    draw();
    setElevacion(-elevacion);
    setCentro(centro.x, -centro.y, centro.z);
    setEscala(escala.x, -escala.y, escala.z);
}

void Entidad3D::drawTranslucido() {
    glPushMatrix();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    draw();
    glDisable(GL_BLEND);

    glPopMatrix();
}

GLfloat Entidad3D::radioFrontera() {
    GLfloat aux = 0;
    if(aux < escala.x)
        aux = escala.x;
    if(aux < escala.y)
        aux = escala.y;
    if(aux < escala.z)
        aux = escala.z;
    return aux*obj3d->radioFrontera;
}

void Entidad3D::animarMov(Vertice destino) {
    animarMov(destino, velocidadMov);
}

void Entidad3D::animarMov(Vertice destino, float vel) {
    velocidadMov = vel;
    inicioMov = posicion;
    destinoMov = destino;
    contadorTicksMov = 0;
    nTicksTotalesMov = inicioMov.vectorHacia(destinoMov).modulo() / velocidadMov;

    mover = true;
    timer.start(0);
}

//Se mueve hacia donde está orientado
void Entidad3D::animarAvanzar(float vel) {
    velocidadAvance = vel;

    avanzar = true;
    timer.start(0);
}

void Entidad3D::animarGiro(Vertice destino) {
    animarGiro(destino, velocidadGiro);
}

void Entidad3D::animarGiro(Vertice destino, float vel) {
    velocidadGiro = vel;
    inicioGiro = orientacion;
    destinoGiro = destino;
    contadorTicksGiro = 0;
    nTicksTotalesGiro = inicioGiro.anguloV(destinoGiro) / velocidadGiro;

    girar = true;
    timer.start(0);
}

void Entidad3D::pararAnimacion() {
    timer.stop();
    mover = false;
    girar = false;
    avanzar = false;
}

void Entidad3D::pararMover() {
    mover = false;
    if(girar == false && avanzar == false)
        timer.stop();
}

void Entidad3D::pararGirar() {
    girar = false;
    if(mover == false && avanzar == false)
        timer.stop();
}

void Entidad3D::pararAvanzar() {
    avanzar = false;
    if(mover == false && girar == false)
        timer.stop();
}

Vertice Entidad3D::getPosicionAleatoria(int margenX, int margenY, int margenZ) {
    Vertice dest;

    if(margenX > 0) {
        dest.x = rand() % margenX;
        if(rand()%2)
            dest.x *= -1;
    }
    if(margenZ > 0) {
        dest.z = rand() % margenZ;
        if(rand()%2)
            dest.z *= -1;
    }
    if(margenY > 0) {
        dest.y = rand() % margenY;
        if(rand()%2)
            dest.y *= -1;
    }

    return dest;
}

void Entidad3D::animacionAleatoria() {
    animacionAleatoria(aleatoriaX, aleatoriaY, aleatoriaZ);
}

void Entidad3D::animacionAleatoria(int margenX, int margenY, int margenZ) {
    Vertice dest;

    aleatoria = true;
    aleatoriaX = margenX;
    aleatoriaY = margenY;
    aleatoriaZ = margenZ;

    dest = getPosicionAleatoria(margenX, margenY, margenZ);

    animarMov(dest, velocidadMov);
}

void Entidad3D::cambiarVelocidadMov(float vel) {
    velocidadMov = vel;
    inicioMov = posicion;
    contadorTicksMov = 0;
    nTicksTotalesMov = inicioMov.vectorHacia(destinoMov).modulo() / velocidadMov;
}

void Entidad3D::cambiarVelocidadGiro(float vel) {
    velocidadGiro = vel;
    inicioGiro = orientacion;
    contadorTicksGiro = 0;
    nTicksTotalesGiro = inicioGiro.anguloV(destinoGiro) / velocidadGiro;
}

void Entidad3D::setTipoAceleracion(TipoAceleracion acel) {
    tipoAceleracion = acel;
}

void Entidad3D::actualizar() {
    double t;

    if(mover) {
        t = contadorTicksMov / nTicksTotalesMov;
        if(tipoAceleracion == LINEAL)
            setPosicion(inicioMov*(1-t)+destinoMov*t);
        if(tipoAceleracion == SENOIDAL) {
            t = (sin(t*M_PI-M_PI/2)+1) / 2;
            setPosicion(inicioMov*(1-t)+destinoMov*t);
        }

        if(++contadorTicksMov > nTicksTotalesMov) {
            pararMover();
            if(aleatoria)
                animacionAleatoria();
        }
    } else if(avanzar)
        setPosicion(posicion+orientacion*velocidadAvance);

    if(girar) {
        t = contadorTicksGiro / nTicksTotalesGiro;
        if(tipoAceleracion == LINEAL)
            setOrientacion(inicioGiro*(1-t)+destinoGiro*t);
        if(tipoAceleracion == SENOIDAL) {
            t = (sin(t*M_PI-M_PI/2)+1) / 2;
            setOrientacion(inicioGiro*(1-t)+destinoGiro*t);
        }

        if(++contadorTicksGiro > nTicksTotalesGiro) {
            setOrientacion(destinoGiro);
            pararGirar();
            if(aleatoria)
                animacionAleatoria();
        }
    }
}
