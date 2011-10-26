#ifndef __CIRCUNFERENCIA_H__
#define __CIRCUNFERENCIA_H__

#include "Curva.h"
#include "Punto.h"
#include <cmath>

#define M_PI 3.14159265358979323846

class Circunferencia : public Curva{
    public:
        //Constructores con valores por defecto o especificados. Inicializan la estructura
        Circunferencia();
        Circunferencia(float radio, int paso);

    private:
        int paso;
        float radio;

        //Crea todos los puntos del ente
        void construir();
};

#endif // __CIRCUNFERENCIA_H__
