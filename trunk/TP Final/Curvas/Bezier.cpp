#include "Bezier.h"

#include <iostream>

using namespace std;

Bezier::Bezier(int cantidadTramos)
{
    if (cantidadTramos > 0){

        this->cantTramos = cantidadTramos;
        this->contadorPuntos = 0;

        this->cantidadPuntos = 2 *this->cantTramos + this->cantTramos + 1;

        this->base = new BaseBerstein();

        this->puntos = new vec3[this->cantidadPuntos];

    }else{

        this->base = NULL;
        this->puntos = NULL;
    }
}


vec3 Bezier::evaluar(Flotante x){

        vec3 res(0.0);

        int numTramo = this->truncar(x);


        if ((numTramo >= 0 && numTramo < this->cantTramos) || ( numTramo == cantTramos && x ==  cantTramos ) ){

                int indice = 3 * numTramo;
                float valorX = x - (float)(numTramo);


                for (int i=0; i<4; i++)
                        res += this->base->evaluar(i,valorX) * this->puntos[indice + i];

        }

        return res;

}

Bezier::~Bezier()
{
        if ( puntos == NULL || base == NULL){
            delete[] puntos;
            delete base;
        }
}
