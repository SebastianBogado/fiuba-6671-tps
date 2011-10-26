#include "Curva.h"

Curva::~Curva(){
            for(int i = 0; i < cantidadDePuntos; i++){
                delete this->puntos[i];
            }
            delete[] this->puntos;
        }

float Curva::Xn(int n){ return this->puntos[n]->X(); }
float Curva::Yn(int n){ return this->puntos[n]->Y(); }

int Curva::cantDePuntos(){ return this->cantidadDePuntos; }
