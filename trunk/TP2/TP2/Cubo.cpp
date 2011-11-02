#include "Cubo.h"

Cubo::Cubo(){
    this->lado = 1;
	this->paso=16;
    this->construir();
}
Cubo::Cubo(float lado, int paso){
    this->lado = lado;
    this->paso = paso;
    this->construir();
}


void Cubo::construir(){
    this->tengoTapas = true;
    this->altura = lado;
    this->puntosEnAlto = paso;
    this->curvaBorde = new Cuadrado(lado, paso);
}
