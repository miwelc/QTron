#ifndef TETRAEDRO_H
#define TETRAEDRO_H

#include <GL/gl.h>
#include <math.h>
#include "objeto3d.h"

#define PI 3.14159265

class Tetraedro : public Objeto3D {
	private:
                float radio;
                float altura;
	public:
                Tetraedro();
};

#endif

