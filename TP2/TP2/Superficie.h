#ifndef __SUPERFICIE_H__
#define __SUPERFICIE_H__

#include "Curva.h"
#include "Punto.h"
#include <cmath>

class Superficie{
    public:
		Superficie();
        virtual ~Superficie();

        virtual float* getPunto(int Xn, int Yn, int Zn);		
        virtual float* getNormal(int Xn, int Yn, int Zn);
		//Además de devolver si algún punto es o no una arista, devuelve también true
        //para aquellos puntos que merecen trato especial como el primer y último puntos de la esfera
        virtual bool esArista(int Xn, int Yn, int Zn);


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
		
        float* calcularNormal(float* p, float* q, float* r);
        virtual float* getNormalArista(int Xn, int Yn, int Zn);
};
		

#endif // __SUPERFICIE_H__
