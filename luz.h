#ifndef LUZ_H
#define LUZ_H

#include <GL/gl.h>

class Luz{
    private:
        GLfloat posicion[4];
        GLfloat color[4];
        GLfloat brillo;
        GLfloat componenteAmbiente[4];
        GLfloat luzAmbiente[4];
        GLfloat luzDifusa[4];
        GLfloat luzEspecular[4];
        GLfloat materialAmbiente[4];
        GLfloat materialDifusa[4];
        GLfloat materialEspecular[4];

    public:
        Luz();
        void encender();
        void apagar() { glDisable(GL_LIGHT0); glDisable(GL_LIGHTING); glDisable(GL_COLOR_MATERIAL);}
        void setComponenteAmbiente(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

        void setColoresLuz(GLfloat *ambiente, GLfloat *difusa, GLfloat *especular);
        void setLuzAmbiente(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
        void setLuzDifusa(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
        void setLuzEspecular(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

        void setColoresMaterial(GLfloat *ambiente, GLfloat *difusa, GLfloat *especular);
        void setMaterialAmbiente(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
        void setMaterialDifusa(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
        void setMaterialEspecular(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

        void setBrillo(GLfloat br) { brillo = br; }

        void setPosicion(GLfloat x, GLfloat y, GLfloat z, GLfloat a);
};

#endif // LUZ_H
