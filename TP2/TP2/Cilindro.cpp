#include "Cilindro.h"

 Cilindro::Cilindro(){
    this->radio = 1;
    this->altura = 1;
	this->paso=16;
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

float* Cilindro::getNormalArista(int Xn, int Yn, int Zn){
    float* normal = new float[3];
    normal[0] = 1;
    normal[1] = 0;
    normal[2] = 0;
    return normal;
}
bool Cilindro::esArista(int Xn, int Yn, int Zn){
	//es arista en techo y piso

	return false;
}
