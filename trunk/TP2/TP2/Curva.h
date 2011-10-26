#ifndef __CURVA_H__
#define __CURVA_H__

#include "Punto.h"

//Interfaz para curvas en el plano z = cte.
class Curva{
    public:
        virtual ~Curva();

        float Xn(int n);
        float Yn(int n);

        int cantDePuntos();

    protected:
        Punto** puntos;
        int cantidadDePuntos;

        //Crea todos los puntos del ente
        virtual void construir() = 0;
};

#endif // __CURVA_H__
