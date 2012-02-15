#ifndef BEZIER_H
#define BEZIER_H

#include <glm/glm.hpp>
#include "Curva.h"
#include "BaseBerstein.h"


using namespace glm;

class Bezier : public Curva
{
    public:
    /*
     *Constructor que se le pasan la cantidad de tramos que contendra toda la curva. y luego se le tendran que enviar todos los puntos
     *manualmente, que segun la cantidad de tramos la cantidad de puntos es: 3*cantTramos + 1 .
     */
        Bezier(int cantidadTramos);

    /*
    *Se evalua un punto de la curva para algun valor de x. De 0  a 1 pertenece al primer tramo, del 1 al 2 al segundo, y asi recurrentemente.
    */
       vec3 evaluar(Flotante x);

	   // Para averiguar la cantidad de tramos y puntos
		int cantidadDePuntos();
		int cantidadDeTramos();

        virtual ~Bezier();
    private:
    BaseBerstein *base;
    int cantTramos;
};

#endif // BEZIER_H
