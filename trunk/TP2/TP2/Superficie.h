#ifndef __SUPERFICIE_H__
#define __SUPERFICIE_H__

#include "Curva.h"
#include "Punto.h"

class Superficie{
    public:
        virtual ~Superficie();

        virtual float* getPunto(int Xn, int Yn, int Zn);

        virtual float getAltura();
        virtual int getPaso();
        bool tieneTapas();
        int cantidadDePuntosBorde();
        int cantidadDePuntosEnAlto();

    protected:
        Curva* curvaBorde;
        int paso;
        int puntosEnAlto;
        float altura;
        bool tengoTapas;
        virtual void construir() = 0;
        virtual float Xn(int n);
        virtual float Yn(int n);
        virtual float Zn(int n);
};

#endif // __SUPERFICIE_H__
