#ifndef VERTICE_H
#define VERTICE_H

#include <math.h>
#include "matrix.h"

class Vertice {
private:
        float vect[4];
    public:
        double x;
        double y;
        double z;
        double w;
        Vertice();
        Vertice(double x, double y, double z);
        Vertice(double x, double y, double z, double w);
        Vertice(const Vertice &vertice);
        void setFromEsfericas(float radio, float phi, float theta);
        float getPhi() const;
        float getTheta() const;
        float *v() { vect[0] = x; vect[1] = y; vect[2] = z; vect[3] = w; return vect; }
        bool operator==(const Vertice &vertice);
        bool operator!=(const Vertice &vertice);
        Vertice &operator=(const Vertice &vertice);
        Vertice &operator-=(const Vertice &vertice);
        Vertice &operator+=(const Vertice &vertice);
        Vertice operator-(const Vertice &vertice) const;
        Vertice operator+(const Vertice &vertice) const;
        Vertice operator*(const Vertice &vertice) const;
        Vertice operator*(const float num) const;
        Vertice operator*(_matrix4<float> &Matrix1) const;
        float productoEscalar(const Vertice &vertice) const;
        Vertice operator/(const float &divisor) const;
        double modulo() const;
        Vertice versor() const;
        Vertice vectorHacia(const Vertice punto) const;
        double anguloV(const Vertice v2) const;
        double anguloX() const;
        double anguloY() const;
        double anguloZ() const;
};

#endif // VERTICE_H
