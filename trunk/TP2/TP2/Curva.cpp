#include "Curva.h"

Curva::~Curva(){
    for(int i = 0; i < cantidadDePuntos; i++){
        delete this->puntos[i];
    }
    delete[] this->puntos;
}

float Curva::Xn(int n){
    if (n >= cantidadDePuntos)
        return Xn(n-cantidadDePuntos);
	if (n < 0)
        return Xn(n+cantidadDePuntos);
    return this->puntos[n]->X();
}

float Curva::Yn(int n){
    if (n >= cantidadDePuntos)
        return Yn(n-cantidadDePuntos);
	if (n < 0)
        return Yn(n+cantidadDePuntos);
    return this->puntos[n]->Y();
}

int Curva::cantDePuntos(){ return this->cantidadDePuntos; }
