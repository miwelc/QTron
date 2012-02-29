#include "objeto3d.h"

Objeto3D::Objeto3D() {
    calculosIniciales = false;
    nVertices = nCaras = 0;
    radioFrontera = 0;
}

void Objeto3D::generarRevolucion(float *puntos, int nPuntos, int nSecciones, float altura) {
    QVector<Vertice> vertices;
    QVector<Cara> caras;

    for(float j = 0; j <= M_PI*2.0; j += M_PI*2.0/nSecciones) {
        int n = 0;
        for(float i = altura/2.0; i >= -altura/2.0; i -= 1.0*altura/(nPuntos-1)) {
            vertices.push_back(Vertice(puntos[n]*sin(j), i, puntos[n]*cos(j)));
            n++;
        }
    }

    //Cara superior
    if(puntos[0] != 0) {
        vertices.push_back(Vertice(0,altura/2.0,0));
        for(int i = 0; i < nSecciones; i++) {
            Cara cara;
            cara.a = vertices.size()-1;
            cara.b = nPuntos*i;
            cara.c = nPuntos*((i+1)%nSecciones);
            caras.push_back(cara);
        }
    }
    //Cara inferior
    if(puntos[nPuntos-1] != 0) {
        vertices.push_back(Vertice(0,-altura/2.0,0));
        for(int i = 0; i < nSecciones; i++) {
            Cara cara;
            cara.a = vertices.size()-1;
            cara.b = nPuntos*i + nPuntos-1;
            cara.c = nPuntos*((i+1)%nSecciones) + nPuntos-1;
            caras.push_back(cara);
        }
    }
    //Laterales
    for(int i = 0; i < nSecciones; i++) {
        for(int j = 0; j < nPuntos-1; j++) {
            Cara cara;
            cara.a = nPuntos*i + j;
            cara.b = nPuntos*i + j+1;
            cara.c = nPuntos*((i+1)%nSecciones) + j+1;
            caras.push_back(cara);

            cara.a = nPuntos*i + j;
            cara.b = nPuntos*((i+1)%nSecciones) + j+1;
            cara.c = nPuntos*((i+1)%nSecciones) + j;
            caras.push_back(cara);
        }
    }

    cargarDatos(vertices, caras);
}

//Vertices
void Objeto3D::anadirVertices(Vertice *Vertices, int nVertices) {
    for(int i = 0; i < nVertices; i++)
        vertices.push_back(Vertices[i]);
    this->nVertices += nVertices;
}
void Objeto3D::anadirVertices(QVector<Vertice> Vertices) {
    for(int i = 0; i < Vertices.size(); i++)
        vertices.push_back(Vertices[i]);
    this->nVertices += nVertices;
}
void Objeto3D::setVertice(int nVertice, Vertice valor) {
    vertices[nVertice] = valor;
}

//Caras
void Objeto3D::anadirCaras(Cara *Caras, int nCaras) {
    normalesVertices.resize(nVertices);

    for(int i = 0; i < nCaras; i++) {
        caras.push_back(Caras[i]);

        normalesCaras.push_back(calcularNormalCara(caras.end()-1));
        normalesVertices[Caras[i].a] = calcularNormalVertice(Caras[i].a);
        normalesVertices[Caras[i].b] = calcularNormalVertice(Caras[i].b);
        normalesVertices[Caras[i].c] = calcularNormalVertice(Caras[i].c);
    }
    this->nCaras += nCaras;
}

void Objeto3D::cargarDatos(QVector<Vertice> Vertices, QVector<Cara> Faces) {
    vertices.clear();
    caras.clear();

    nVertices = Vertices.size();
    vertices.resize(nVertices);
    for(int i = 0; i < nVertices; i++)
        vertices[i] = Vertices[i];

    nCaras = Faces.size();
    for(int i = 0; i < nCaras; i++)
        caras.push_back(Faces[i]);

    calculosIniciales = false;
}

void Objeto3D::cargarDatos(QVector<float> Vertices, QVector<int> Faces) {
    vertices.clear();
    caras.clear();

    nVertices = Vertices.size()/3;
    vertices.resize(nVertices);
    for(int i = 0; i < nVertices; i++) {
        vertices[i].x = Vertices[i*3];
        vertices[i].y = Vertices[i*3+1];
        vertices[i].z = Vertices[i*3+2];
    }

    nCaras = Faces.size()/3;
    Cara *carasAux = new Cara[nCaras];
    for(int i = 0; i < nCaras; i++) {
        carasAux[i].a = Faces[i*3];
        carasAux[i].b = Faces[i*3+1];
        carasAux[i].c = Faces[i*3+2];
    }

    for(int i = 0; i < nCaras; i++)
        caras.push_back(carasAux[i]);
    delete [] carasAux;

    calculosIniciales = false;
}

void Objeto3D::draw(int modoDibujo, GLenum modoSuavizado, GLfloat colorSolido[3], GLfloat coloresAjedrez[2][3]) {
    QList<Cara>::iterator it = caras.begin();
    QList<Vertice>::iterator itN = normalesCaras.begin();

    if(!calculosIniciales) {
        calcularNormales();
        calcularRadioFrontera();
        calculosIniciales = true;
    }

    switch(modoDibujo) {
        case 0:
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            glBegin(GL_POINTS);
            for(int i = 0; i < nVertices; i++)
                glVertex3fv(vertices[i].v());
            glEnd();
            break;
        case 1:
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glShadeModel(modoSuavizado);
            glBegin(GL_TRIANGLES);
            if(modoSuavizado == GL_SMOOTH)
                for( ; it != caras.end(); it++)
                    dibujarCaraSmooth(it);
            else
                for( ; it != caras.end(); it++, itN++)
                    dibujarCaraFlat(it,itN);
            glEnd();
            break;
        case 2:
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glShadeModel(modoSuavizado);
            glBegin(GL_TRIANGLES);
            glColor3fv(colorSolido);
            if(modoSuavizado == GL_SMOOTH)
                for( ; it != caras.end(); it++)
                    dibujarCaraSmooth(it);
            else
                for( ; it != caras.end(); it++, itN++)
                    dibujarCaraFlat(it,itN);
            glEnd();
            break;
        case 3:
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glShadeModel(modoSuavizado);
            glBegin(GL_TRIANGLES);
            if(modoSuavizado == GL_SMOOTH)
                for(int i = 0; it != caras.end(); it++, i++) {
                    (i%2==0) ? glColor3fv(coloresAjedrez[0]) : glColor3fv(coloresAjedrez[1]);
                    dibujarCaraSmooth(it);
                }
            else
                for(int i = 0; it != caras.end(); it++, itN++, i++) {
                    (i%2==0) ? glColor3fv(coloresAjedrez[0]) : glColor3fv(coloresAjedrez[1]);
                    dibujarCaraFlat(it,itN);
                }
            glEnd();
            break;
        case 4:
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glShadeModel(modoSuavizado);
            glBegin(GL_TRIANGLES);
            if(modoSuavizado == GL_SMOOTH)
                for( ; it != caras.end(); it++)
                    dibujarCaraSmooth(it);
            else
                for( ; it != caras.end(); it++, itN++)
                    dibujarCaraFlat(it,itN);
            glEnd();
            break;
    }
}

void Objeto3D::dibujarCaraSmooth(QList<Cara>::iterator it) const {
    glNormal3f(normalesVertices[it->a].x, normalesVertices[it->a].y, normalesVertices[it->a].z);
    dibujarVertice(it->a);

    glNormal3f(normalesVertices[it->b].x, normalesVertices[it->b].y, normalesVertices[it->b].z);
    dibujarVertice(it->b);

    glNormal3f(normalesVertices[it->c].x, normalesVertices[it->c].y, normalesVertices[it->c].z);
    dibujarVertice(it->c);
}

void Objeto3D::dibujarCaraFlat(QList<Cara>::iterator it, QList<Vertice>::iterator itNormal) const {
    glNormal3fv(itNormal->v());
    dibujarVertice(it->a);
    dibujarVertice(it->b);
    dibujarVertice(it->c);
}

void Objeto3D::dibujarVertice(int n) const {
    glVertex3f(vertices[n].x, vertices[n].y, vertices[n].z);
}

void Objeto3D::calcularNormales() {
    normalesVertices.clear();
    normalesCaras.clear();

    for(QList<Cara>::iterator itC = caras.begin(); itC != caras.end(); itC++)
        normalesCaras.push_back(calcularNormalCara(itC));

    normalesVertices.resize(nVertices);
    for(int i = 0; i < nVertices; i++)
        normalesVertices[i] = calcularNormalVertice(i);
}

Vertice Objeto3D::calcularNormalCara(QList<Cara>::iterator itC) const {
    Vertice normal;
    normal = (vertices[itC->c]-vertices[itC->a])*(vertices[itC->b]-vertices[itC->a]);
    return normal.versor();
}

Vertice Objeto3D::calcularNormalVertice(int n) {
    Vertice normal;
    QList<Cara>::iterator itC = caras.begin();
    QList<Vertice>::iterator itN = normalesCaras.begin();

    for( ; itC != caras.end(); itC++, itN++)
        if(itC->a == n || itC->b == n || itC->c == n)
            normal += *itN;

    return normal.versor();
}

void Objeto3D::calcularRadioFrontera() {
    double media = 0;
    float max = 0;

    for(int i = 0; i < nVertices; i++) {
        if(max < vertices[i].modulo())
            max = vertices[i].modulo();
        media += vertices[i].modulo();
    }
    media = media/nVertices;
    radioFrontera = 0.6*max+0.4*media;
}
