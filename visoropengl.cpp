#include "visoropengl.h"
#include <QCoreApplication>

 VisorOpenGL::VisorOpenGL() {
     setAutoFillBackground(false);

     connect(&timer, SIGNAL(timeout()), this, SLOT(actualizarPantalla()));
     timer.start(0);

     modo = MENU;

     // permitimos al componente tener el foco y aceptar eventos
     setFocusPolicy(Qt::StrongFocus);
 }

 VisorOpenGL::~VisorOpenGL() {
     makeCurrent();    
 }

 QSize VisorOpenGL::minimumSizeHint() const {
     return QSize(750, 400);
 }

 QSize VisorOpenGL::sizeHint() const {
     return QSize(850, 600);
 }

void VisorOpenGL::initializeGL() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0.0,0.0,0.0,1.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDisable(GL_CULL_FACE);
}

void VisorOpenGL::resizeGL(int width, int height) {
    juego.setTamanoPantalla(width, height);
    menu.setTamanoPantalla(width, height);
    demo.setTamanoPantalla(width, height);
}

void VisorOpenGL::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(modo == JUEGO)
        juego.draw();
    else if(modo == MENU)
        menu.draw();
    else if(modo == DEMO)
        demo.draw();
}

void VisorOpenGL::actualizarPantalla() {
    update();
}

void VisorOpenGL::mousePressEvent(QMouseEvent *event) {
    lastPos = event->pos();
}

void VisorOpenGL::keyPressEvent(QKeyEvent *event) {
    if(modo == JUEGO)
        juego.teclasPulsadas(event->key());
    else if(modo == DEMO)
        demo.teclasPulsadas(event->key());
}

