#include "SuperficieDiscretizada.h"


SuperficieDiscretizada::SuperficieDiscretizada(int cantidadDePuntosBorde, int cantidadDePuntosEnAlto){
	this->cantDePuntosBorde = cantidadDePuntosBorde;
    this->cantDePuntosEnAlto = cantidadDePuntosEnAlto;
	this->puntos = new vec3*[cantidadDePuntosBorde];
	this->normales = new vec3*[cantidadDePuntosBorde];
	for (int i = 0; i < cantDePuntosBorde; i++){
		this->puntos[i] = new vec3[cantDePuntosEnAlto];
		this->normales[i] = new vec3[cantDePuntosEnAlto];
	}
}


SuperficieDiscretizada::~SuperficieDiscretizada(void){
	for (int i = 0; i < cantDePuntosBorde; i++){
		delete []this->puntos[i];
		delete []this->normales[i];
	}
	delete [] this->puntos;
	delete [] this->normales;
}

void SuperficieDiscretizada::agregarPunto(vec3 puntoNuevo, int Xn, int Yn){ this->puntos[Xn][Yn] = puntoNuevo; }
void SuperficieDiscretizada::agregarNormal(vec3 normalNueva, int Xn, int Yn){ this->puntos[Xn][Yn] = normalNueva; }

int SuperficieDiscretizada::cantidadDePuntosBorde(){ return this->cantDePuntosBorde; }
int SuperficieDiscretizada::cantidadDePuntosEnAlto(){ return this->cantDePuntosEnAlto; }