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

float* Cilindro::getNormal(int Xn, int Yn, int Zn){
    if (Xn >= cantidadDePuntosBorde())
        return getNormal(Xn-cantidadDePuntosBorde(), Yn-cantidadDePuntosBorde(), Zn);
	if (Xn < 0)
        return getNormal(Xn+cantidadDePuntosBorde(), Yn+cantidadDePuntosBorde(), Zn);

	float* normal = new float[3];
	float* punto = getPunto(Xn, Yn, Zn);
    normal[0] = punto[0];
    normal[1] = punto[1];
    normal[2] = 0;
	
    //Normalizar
    float norma = sqrt(normal[0]*normal[0] + normal[1]*normal[1]);
    normal[0] /= norma;
    normal[1] /= norma;

	delete []punto;
    return normal;
}
float* Cilindro::getNormalArista(int Xn, int Yn, int Zn){
    return getNormal(Xn, Yn, Zn);
}
bool Cilindro::esArista(int Xn, int Yn, int Zn){
	float* p = getPunto(Xn, Yn, Zn);
	if ( ( (Zn == 0) || ( Zn == altura) ) &&
		 ( (p[0]*p[0] + p[1]*p[1] == radio * radio))){
		delete []p;
		return true;
	}
	return false;
}
