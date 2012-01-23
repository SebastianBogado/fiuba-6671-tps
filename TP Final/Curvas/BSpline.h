#ifndef BSPLINE_H
#define BSPLINE_H

#include "Curva.h"
#include "BaseBSpline.h"

using namespace glm;

class BSpline : public Curva
{
    public:
        /*
         *Se le indica al constructor la cantidad de puntos que contendra la Curva.
         *Luego se le iran agregando los puntos manualmente
         */
        BSpline(int cantPuntos);

        /*
         * Se evalua la curva. de 0 a 1 equivale al primer tramo, del 1 al 2 el segundo, y asi consecutivamente
         */
        vec3 evaluar(Flotante x);

        /*
         *Se evalua el valor de la tangente para algun punto de la curva.
         */
        vec3 tangente(Flotante x);

        virtual ~BSpline();

    private:
        BaseBSpline *bases;
};

#endif // BSPLINE_H
