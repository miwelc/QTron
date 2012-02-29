#ifndef TABLERO_H
#define TABLERO_H

#include "Entidad3D.h"
#include "vertice.h"

class Tablero : public Entidad3D {
        private:
                int tamano;
                int nDivisiones;
        public:
                ~Tablero();
                Tablero();
                void setTamanoYDivisiones(int tam, int nDiv);
                //void drawTranslucido();
};

#endif // TABLERO_H
