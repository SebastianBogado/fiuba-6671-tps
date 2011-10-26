#ifndef CILINDRO_H
#define CILINDRO_H

#include "Superficie.h"
#include "Circunferencia.h"

/**
 @todo : heredar Cilindro de Cono
*/

class Cilindro : public Superficie{
    public:
        //Constructores con valores por defecto o especificados. Inicializan la estructura
        Cilindro();
        Cilindro(float radio, float altura, int paso);

    private:
        float radio;

        //Crea todos los puntos del ente
        void construir();
};

#endif // CILINDRO_H
