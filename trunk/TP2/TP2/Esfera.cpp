#include "Esfera.h"

Esfera::Esfera(){
    this->radio = 1;
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

float* Esfera::getNormalArista(int Xn, int Yn, int Zn){
    float* normal = new float[3];

    //Punto de arriba de todo
    normal[0] = 0;
    normal[1] = 0;

    if (Zn == 0) //Punto de abajo
        normal[2] = -1;
    else // Punto de arriba
        normal[2] = 1;

    return normal;
}

bool Esfera::esArista(int Xn, int Yn, int Zn){
    //Si es primer o último punto
    if ((Zn == 0) || (Zn == cantidadDePuntosEnAlto()))
         return true;

    return false;
}