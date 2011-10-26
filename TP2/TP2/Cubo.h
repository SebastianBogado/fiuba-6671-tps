#ifndef __CUBO_H__
#define __CUBO_H__

#include "Superficie.h"
#include "Cuadrado.h"

class Cubo : public Superficie{
    public:
        //Constructores con valores por defecto o especificados. Inicializan la estructura
        Cubo();
        Cubo(float lado, int paso);

    private:
        float lado;

        //Crea todos los puntos del ente
        void construir();
};


#endif // __CUBO_H__
