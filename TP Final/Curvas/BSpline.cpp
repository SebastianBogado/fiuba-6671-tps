#include "BSpline.h"
#include <iostream>

using namespace glm;
using namespace std;

BSpline::BSpline(int cantPuntos)
{
    if(cantPuntos >= 3){
        this->puntos = new vec3[cantPuntos];
        this->bases = new BaseBSpline[cantPuntos];
        this->cantidadPuntos = cantPuntos;

        this->contadorPuntos=0;

        float nuevoPiso,nuevoTecho;
        for (int i=0; i < cantPuntos ; i++){

            nuevoPiso=(float)(i-2);
            nuevoTecho=(float)(i+1);
            this->bases[i].redefinirIntervalo(nuevoPiso,nuevoTecho);
        }
    }
}



vec3 BSpline::evaluar(Flotante x){

    vec3 res(0.0);

    for(int i=0; i< this->cantidadPuntos ; i++){

       // cout<<" i: "<<i<<" cant:"<<this->cantidadPuntos<<endl;

        res = res + (this->bases[i].evaluar(x) )* this->puntos[i];
    }

    return res;

}


vec3 BSpline::tangente(Flotante x){

    vec3 res;

    for(int i=0; i< this->cantidadPuntos ; i++){

        res += this->bases[i].derivada(x) * this->puntos[i];

    }

    return res;

}

int BSpline::cantidadDePuntos(){ return this->cantidadPuntos; }
int BSpline::cantidadDeTramos(){ return (this->cantidadPuntos - 3); }

BSpline::~BSpline()
{

    delete[] this->puntos;
    delete[] this->bases;
}
