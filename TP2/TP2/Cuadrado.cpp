#include "Cuadrado.h"

Cuadrado::Cuadrado(){
    this->paso = 1;
    this->lado = 1.0;
    this->construir();
}

Cuadrado::Cuadrado(float lado, int paso){
    this->paso = paso;
    this->lado = lado;
    this->construir();
}
//
//Cuadrado::~Cuadrado(){
//    for(int i = 0; i < cantidadDePuntos; i++){
//        delete this->puntos[i];
//    }
//    delete[] this->puntos;
//}
//
//float Cuadrado::Xn(int n){ return this->puntos[n]->X(); }
//float Cuadrado::Yn(int n){ return this->puntos[n]->Y(); }

void Cuadrado::construir(){
    this-> cantidadDePuntos = 4 * paso;
    this->puntos = new Punto*[cantidadDePuntos];
    this->puntos[0] = new Punto(lado/2.0, lado/2.0);
    float incremento = lado / (float)paso;
    for(int i = 0; i < 4; i++){
        for (int j = 0; j < paso; j++){
            switch(i){
                case 0:
                    this->puntos[i*paso + j] = new Punto(lado/2.0 - j*incremento, lado/2.0);
                    break;
                case 1:
                    this->puntos[i*paso + j] = new Punto(-lado/2.0, lado/2.0 - j*incremento);
                    break;
                case 2:
                    this->puntos[i*paso + j] = new Punto(-lado/2.0 + j*incremento, -lado/2.0);
                    break;
                case 3:
                    this->puntos[i*paso + j] = new Punto(lado/2.0, -lado/2.0 + j*incremento);
                    break;
                default:
                    break;
            }
        }
    }
}

