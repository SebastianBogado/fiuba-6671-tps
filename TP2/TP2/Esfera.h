#ifndef __ESFERA_H__
#define __ESFERA_H__

#include "Superficie.h"
#include "Circunferencia.h"


class Esfera : public Superficie{
    public:
        Esfera();
        Esfera(float radio, int paso);

        float* getPunto(int Xn, int Yn, int Zn);
		bool esArista(int Xn, int Yn, int Zn);

    private:
        void construir();
        float calcularRadioSegunAltura(float altura);
        float radio;
		float* getNormalArista(int Xn, int Yn, int Zn);
};

#endif // __ESFERA_H__
