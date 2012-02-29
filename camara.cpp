#include "camara.h"

void Camara::calcularNUV() {
    n = VPN;
    u = VUP*n;
    v = n*u;
}

Camara::Camara() {
    //Valores iniciales
    VRP.x = -15;
    VRP.y = 10;
    VRP.z = -20;

    VPN.x =  0;
    VPN.y =  0.5;
    VPN.z =  -1;

    VUP.x = 0;
    VUP.y = 1;
    VUP.z = 0;

    calcularNUV();

    //alpha = beta = gamma = 0;
}

void Camara::setCamara() {
    _matrix4f alphaRo, betaRo;
    Vertice VPN2, u2, v2;
    GLfloat alpha, beta, gamma;

    alpha = atan2(n.y, n.z)*180/PI_CONS;
    VPN2 = n*alphaRo.rotate_axis_x(alpha);
    u2 = u*alphaRo.rotate_axis_x(alpha);

    beta = atan2(VPN2.x, VPN2.z)*180/PI_CONS;
    v2 = u2*betaRo.rotate_axis_y(-beta);

    gamma = atan2(v2.y, v2.x)*180/PI_CONS;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(-gamma,0,0,1);
    glRotatef(-beta,0,1,0);
    glRotatef(alpha,1,0,0);
    glTranslatef(-VRP.x, -VRP.y, -VRP.z);
}

void Camara::mover(int tecla){
    Vertice orientacion;
    switch(tecla) {
        //Posicion
        case Qt::Key_W:
            setPosicion(VRP-VPN.versor()*2);
            break;
        case Qt::Key_S:
            setPosicion(VRP+VPN.versor()*2);
            break;
        case Qt::Key_A:
            setPosicion(VRP+ (VPN*Vertice(VPN.versor().x, VPN.versor().y+1, VPN.versor().z)).versor()*2);
            break;
        case Qt::Key_D:
            setPosicion(VRP- (VPN*Vertice(VPN.versor().x, VPN.versor().y+1, VPN.versor().z)).versor()*2);
            break;
        //Orientacion
        case Qt::Key_Up:
            orientacion.setFromEsfericas(1,VPN.getPhi(),VPN.getTheta()>=M_PI ? VPN.getTheta() : VPN.getTheta() + M_PI_4 /15);
            setDireccion(orientacion);
            break;
        case Qt::Key_Down:
            orientacion.setFromEsfericas(1,VPN.getPhi(),VPN.getTheta()<=0 ? VPN.getTheta() : VPN.getTheta() - M_PI_4 /15);
            setDireccion(orientacion);
            break;
        case Qt::Key_Left:
            orientacion.setFromEsfericas(1,VPN.getPhi() - M_PI / 30,VPN.getTheta());
            setDireccion(orientacion);
            break;
        case Qt::Key_Right:
            orientacion.setFromEsfericas(1,VPN.getPhi() + M_PI / 30,VPN.getTheta());
            setDireccion(orientacion);
            break;
    }
}
