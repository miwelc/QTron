#ifndef VISOROPENGL
#define VISOROPENGL

#include <QGLWidget>
#include <QEvent>
#include <QMouseEvent>
#include <QTimer>

#include "juego.h"
#include "menu.h"
#include "demo.h"

enum MODO_VISOR {
    JUEGO,
    MENU,
    DEMO
};

class VisorOpenGL: public QGLWidget {
    Q_OBJECT
    private:
        QPoint lastPos;
        QTimer timer;
        MODO_VISOR modo;

    public:
        Juego juego;
        Menu menu;
        Demo demo;
        VisorOpenGL();
        ~VisorOpenGL();
        void setModo(MODO_VISOR mod) { juego.finalizarPartida(); modo = mod; }
        QSize minimumSizeHint() const;
        QSize sizeHint() const;

    public slots:
        void actualizarPantalla();

    protected:
        void initializeGL();
        void paintGL();
        void resizeGL(int width, int height);
        void mousePressEvent(QMouseEvent *event);
        void keyPressEvent(QKeyEvent *event);
 };

#endif

