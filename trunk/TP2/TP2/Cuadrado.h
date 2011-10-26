#ifndef __CUADRADO_H__
#define __CUADRADO_H__

#include "Punto.h"
#include "Curva.h"

class Cuadrado : public Curva{
    public:
        //Constructores con valores por defecto o especificados. Inicializan la estructura
        Cuadrado();
        Cuadrado(float lado, int paso);

    private:
        int paso;
        float lado;

        //Crea todos los puntos del ente
        void construir();
};


#endif // __CUADRADO_H__
