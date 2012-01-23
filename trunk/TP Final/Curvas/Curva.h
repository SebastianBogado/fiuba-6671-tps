#ifndef CURVA_H
#define CURVA_H

#include <glm/glm.hpp>

using namespace glm;

typedef float Flotante;

class Curva
{
    public:
        Curva();
        /*
        *  Metodo virtual que identifica a evaluar un punto de la curva segun el tipo de curva que sea.
        */
        virtual vec3 evaluar(Flotante x)=0;

        int truncar(Flotante x);

        /*
        * Incluye el punto enviado a la curva, el orden de los puntos de las curva es segun se van incluyendo.
        */
        void incluirPunto(vec3 punto);

        /*
        * Se devuelve el punto que corresponda en el orden de la curva que fue incluido.
        */
        vec3 verPunto(int num);


        /*
        *Se setea un punto en particular de la curva.
        */
        void definirPunto(int num,vec3 punto);

        virtual ~Curva();
    protected:
        vec3 *puntos;
        int cantidadPuntos,contadorPuntos;
};

#endif // CURVA_H
