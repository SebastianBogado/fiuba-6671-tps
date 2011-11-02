#ifndef __CUBO_H__
#define __CUBO_H__

#include "Superficie.h"
#include "Cuadrado.h"

class Cubo : public Superficie{
    public:
        //Constructores con valores por defecto o especificados. Inicializan la estructura
        Cubo();
        Cubo(float lado, int paso);
		float* getNormal(int Xn, int Yn, int Zn);
		bool esArista(int Xn, int Yn, int Zn);

    private:
        float lado;

        //Crea todos los puntos del ente
        void construir();
		float* getNormalArista(int Xn, int Yn, int Zn);
};


#endif // __CUBO_H__
