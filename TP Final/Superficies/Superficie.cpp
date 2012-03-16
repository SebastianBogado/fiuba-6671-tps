#include "Superficie.h"

Superficie::Superficie(Curva* curvaBorde){ 
	this->curvaBorde = curvaBorde; 
	this->discretizada = false;
	this->miDiscretizacion = NULL;
}

Superficie::~Superficie(){ 
	delete this->curvaBorde; 
	delete this->miDiscretizacion;
}

vec3 Superficie::getPunto(int Xn, int Yn){
	if (!discretizada)
		return vec3(0,0,0);

    return miDiscretizacion->getPunto(Xn, Yn);
}

vec3 Superficie::getNormal(int Xn, int Yn){
	if (!discretizada)
		return vec3(0,0,0);

    return miDiscretizacion->getNormal(Xn, Yn);
}

int Superficie::cantidadDePuntosBorde(){ return this->miDiscretizacion->cantidadDePuntosBorde(); }
int Superficie::cantidadDePuntosEnAlto(){ return this->miDiscretizacion->cantidadDePuntosEnAlto(); }