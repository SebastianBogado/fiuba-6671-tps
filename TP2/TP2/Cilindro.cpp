#include "Cilindro.h"

 Cilindro::Cilindro(){
    this->radio = 1;
    this->altura = 1;
    this->paso = 32;
    this->construir();
}
Cilindro::Cilindro(float radio, float altura, int paso){
    this->radio = radio;
    this->altura = altura;
    this->paso = paso;
    this->construir();
}

void Cilindro::construir(){
    this->tengoTapas = true;
    this->puntosEnAlto = paso;
    this->curvaBorde = new Circunferencia(radio, paso);
}
