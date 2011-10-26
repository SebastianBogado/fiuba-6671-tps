#include "../include/Superficie.h"

Superficie::~Superficie(){ delete this->curvaBorde; }

float* Superficie::getPunto(int Xn, int Yn, int Zn){
    float* punto = new float[3];
    punto[0] = this->Xn(Xn);
    punto[1] = this->Yn(Yn);
    punto[2] = this->Zn(Zn);

    return punto;
}

float Superficie::Xn(int n){ return this->curvaBorde->Xn(n); }
float Superficie::Yn(int n){ return this->curvaBorde->Yn(n); }
float Superficie::Zn(int n){ return ((float)n * (this->altura / this->paso)); }

bool Superficie::tieneTapas(){ return this->tengoTapas; }

float Superficie::getAltura(){ return this->altura; }

int Superficie::getPaso(){ return this->paso; }

int Superficie::cantidadDePuntosBorde(){ return this->curvaBorde->cantDePuntos(); }
int Superficie::cantidadDePuntosEnAlto(){ return this->puntosEnAlto; }
