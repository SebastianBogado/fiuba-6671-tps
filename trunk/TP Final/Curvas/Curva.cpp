#include "Curva.h"

Curva::Curva()
{
    //ctor
}


int Curva::truncar(Flotante x){

    int valorTruncado;
    //Flotante valorTruncado;

    valorTruncado = (int)(x);
    //valorTruncado = (Flotante)(valorEntero);

    if (valorTruncado > x)
        valorTruncado++;

    return valorTruncado;

}


void Curva::incluirPunto(vec3 punto){


        if (this->contadorPuntos < this->cantidadPuntos){

            this->puntos[this->contadorPuntos]=punto;

            this->contadorPuntos++;

        }

}

void Curva::definirPunto(int num,vec3 punto){


    if (num >= 0 && num < this->cantidadPuntos){

        this->puntos[num] = punto;

    }


}

vec3 Curva::verPunto(int num){

    if(num >= 0 && num < this->cantidadPuntos){

        return this->puntos[num];

    }else{

        return vec3(0.0);
    }


}


Curva::~Curva()
{
    //dtor
}
