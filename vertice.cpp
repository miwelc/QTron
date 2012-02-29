#include "vertice.h"

Vertice::Vertice() {
    x = y = z = w = 0;
}

Vertice::Vertice(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = 0;
}

Vertice::Vertice(double x, double y, double z, double w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

Vertice::Vertice(const Vertice &vertice) {
    x = vertice.x;
    y = vertice.y;
    z = vertice.z;
    w = vertice.w;
}

void Vertice::setFromEsfericas(float radio, float phi, float theta) {
    x = radio * sin(theta) * cos(phi);
    z = radio * sin(theta) * sin(phi);
    y = radio * cos(theta);
}

float Vertice::getPhi() const {
    if(x > 0 && z > 0)
        return atan(z/x);
    else if(x > 0 && z < 0)
        return 2*M_PI + atan(z/x);
    else if(x == 0) {
        if(z > 0) return M_PI/2;
        if(z < 0) return -M_PI/2;
        if(z == 0) return 0;
    }
    else if(x < 0)
        return M_PI + atan(z/x);
}

float Vertice::getTheta() const {
    if(y > 0)
        return atan(sqrt(x*x+z*z)/y);
    else if(y == 0)
        return M_PI/2;
    else if(y < 0)
        return M_PI + atan(sqrt(x*x+z*z)/y);
}

bool Vertice::operator==(const Vertice &vertice) {
    return x==vertice.x&&y==vertice.y&&z==vertice.z&&w==vertice.w;
}

bool Vertice::operator!=(const Vertice &vertice) {
    return x!=vertice.x||y!=vertice.y||z!=vertice.z||w!=vertice.w;
}

Vertice &Vertice::operator=(const Vertice &vertice) {
    x = vertice.x;
    y = vertice.y;
    z = vertice.z;
    w = vertice.w;
    return *this;
}

Vertice &Vertice::operator-=(const Vertice &vertice) {
    x -= vertice.x;
    y -= vertice.y;
    z -= vertice.z;
    w -= vertice.w;
    return *this;
}

Vertice &Vertice::operator+=(const Vertice &vertice) {
    x += vertice.x;
    y += vertice.y;
    z += vertice.z;
    w += vertice.w;
    return *this;
}

Vertice Vertice::operator-(const Vertice &vertice) const {
    Vertice aux(*this);
    aux -= vertice;
    return aux;
}

Vertice Vertice::operator+(const Vertice &vertice) const {
    Vertice aux(*this);
    aux += vertice;
    return aux;
}

Vertice Vertice::operator*(const Vertice &vertice) const {
    Vertice aux;
    aux.x = this->y*vertice.z - this->z*vertice.y;
    aux.y = -(this->x*vertice.z - this->z*vertice.x);
    aux.z = this->x*vertice.y - this->y*vertice.x;
    return aux;
}

Vertice Vertice::operator*(const float num) const {
    return Vertice(x*num, y*num, z*num, w*num);
}

Vertice Vertice::operator*(_matrix4<float> &Matrix1) const {
    Vertice verticeTemp(*this);
    Vertice vertice(*this);
    Vertice Colum1(Matrix1.get(0,0),Matrix1.get(1,0),Matrix1.get(2,0),Matrix1.get(3,0)),
    Colum2(Matrix1.get(0,1),Matrix1.get(1,1),Matrix1.get(2,1),Matrix1.get(3,1)),
    Colum3(Matrix1.get(0,2),Matrix1.get(1,2),Matrix1.get(2,2),Matrix1.get(3,2));

    vertice.w=1.;

    verticeTemp.x = vertice.productoEscalar(Colum1);
    verticeTemp.y = vertice.productoEscalar(Colum2);
    verticeTemp.z = vertice.productoEscalar(Colum3);
    return verticeTemp;
}

float Vertice::productoEscalar(const Vertice &vertice) const {
    return x*vertice.x+y*vertice.y+z*vertice.z+w*vertice.w;
}

Vertice Vertice::operator/(const float &divisor) const {
    return Vertice(x/divisor, y/divisor, z/divisor);
}

double Vertice::modulo() const{
    return sqrt(x*x+y*y+z*z);
}

Vertice Vertice::versor() const {
    return *this/this->modulo();
}

Vertice Vertice::vectorHacia(const Vertice punto) const {
    return Vertice(punto.x-x, punto.y-y, punto.z-z, punto.w-w);
}

double Vertice::anguloV(const Vertice v2) const {
    return acos( productoEscalar(v2)/(modulo()*v2.modulo()) );
}
double Vertice::anguloX() const {
    return anguloV(Vertice(1,0,0));
}
double Vertice::anguloY() const {
    return anguloV(Vertice(0,1,0));
}
double Vertice::anguloZ() const {
    return anguloV(Vertice(0,0,1));
}
