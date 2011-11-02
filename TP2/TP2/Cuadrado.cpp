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

void Cuadrado::construir(){
    this->cantidadDePuntos = 4 * (paso+1); //cuatro puntos extra para repetir las aristas
    this->puntos = new Punto*[cantidadDePuntos];
    float incremento = lado / (float)paso;
    for(int i = 0; i < 4; i++){
        for (int j = 0; j < paso+1; j++){
            switch(i){
                case 0:
                    this->puntos[i*(paso+1) + j] = new Punto(lado/2.0 - j*incremento, lado/2.0);
                    break;
                case 1:
                    this->puntos[i*(paso+1) + j] = new Punto(-lado/2.0, lado/2.0 - j*incremento);
                    break;
                case 2:
                    this->puntos[i*(paso+1) + j] = new Punto(-lado/2.0 + j*incremento, -lado/2.0);
                    break;
                case 3:
                    this->puntos[i*(paso+1) + j] = new Punto(lado/2.0, -lado/2.0 + j*incremento);
                    break;
                default:
                    break;
            }
        }
    }
}

