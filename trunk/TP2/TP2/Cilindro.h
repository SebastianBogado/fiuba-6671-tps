#ifndef CILINDRO_H
#define CILINDRO_H

#include "Superficie.h"
#include "Circunferencia.h"


class Cilindro : public Superficie{
    public:
        //Constructores con valores por defecto o especificados. Inicializan la estructura
        Cilindro();
        Cilindro(float radio, float altura, int paso);
		bool esArista(int Xn, int Yn, int Zn);
    private:
        float radio;

        //Crea todos los puntos del ente
        void construir();
		float* getNormalArista(int Xn, int Yn, int Zn);
};

#endif // CILINDRO_H
