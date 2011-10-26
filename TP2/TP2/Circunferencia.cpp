#include "../include/Circunferencia.h"

Circunferencia::Circunferencia(){
    this->paso = 32;
    this->radio = 0.5;
    this->construir();
}

Circunferencia::Circunferencia(float radio, int paso){
    this->paso = paso;
    this->radio = radio;
    this->construir();
}

void Circunferencia::construir(){
    this->cantidadDePuntos = paso;
    this->puntos = new Punto*[cantidadDePuntos];
    for(int i = 0; i < cantidadDePuntos; i++){
        float incremento = (float)i/paso;
        float x = radio * cos(2 * M_PI * incremento);
        float y = radio * sin(2 * M_PI * incremento);
        this->puntos[i] = new Punto(x,y);
    }
}
