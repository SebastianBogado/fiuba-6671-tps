#include "VectoresCamara.h"

VectoresCamara::VectoresCamara()
{
        this->arriba = new float[3];
        arriba[0]=0.0; arriba[1]=0.0; arriba[2]=1.0;

        this->direccion = new float[3];
        direccion[0]=-1.0; direccion[1]=-1.0; direccion[2]=0.0;

        this->posicionOjo = new float[3];
        posicionOjo[0]=10.0; posicionOjo[1]=10.0; posicionOjo[2]=5.0;

        this->puntoDeVista = new float[3];
        puntoDeVista[0]=0.0; puntoDeVista[1]=0.0; puntoDeVista[2]=0.0;
}

VectoresCamara::~VectoresCamara()
{
        delete[] arriba;
        delete[] direccion;
        delete[] posicionOjo;
        delete[] puntoDeVista;

}
