#include "Esfera.h"

Esfera::Esfera(){
    this->radio = 1;
    this->paso = 32;
    this->construir();
}

Esfera::Esfera(float radio, int paso){
    this->radio = radio;
    this->paso = paso;
    this->construir();
}

void Esfera::construir(){
    this->tengoTapas = false;
    this->puntosEnAlto = paso;
    this->altura = 2*this->radio;
    this->curvaBorde = new Circunferencia(radio, paso);
}

float Esfera::calcularRadioSegunAltura(float altura){
        return sqrt(pow(radio, 2) - pow(altura, 2)); //Pitágoras
}

float* Esfera::getPunto(int Xn, int Yn, int Zn){
    float* punto = new float[3];
    float razonRadial = this->calcularRadioSegunAltura(this->Zn(Zn) - this->radio) / this->radio;
    punto[0] = this->Xn(Xn);
    punto[0] *= razonRadial;
    punto[1] = this->Yn(Yn);
    punto[1] *= razonRadial;
    punto[2] = this->Zn(Zn) - this->radio;
    return punto;
}
