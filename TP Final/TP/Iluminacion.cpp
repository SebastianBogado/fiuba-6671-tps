#include "Iluminacion.h"

Iluminacion::Iluminacion(void){
	this->cantDeLuces = 6;
	this->luces = new propLuz[cantDeLuces];
	propLuz luz = { 
		true,
		vec4(0.0, -5.0, 5.0, 1.0), 
		vec4(0.0, 0.0, -1.0, 0.0),
		35,
		10,
		vec3(0.02, 0.02, 0.02),
		vec3(0.15, 0.15, 0.15),
		vec3(0.16, 0.16, 0.16),
	};
	for (int i = 0; i < cantDeLuces; i++){
		luces[i] = luz;
		//this->posicionDeLasLuces[i].posicion = vec4(lampara->getPosicion(i), 1.0);
	}
}


Iluminacion::~Iluminacion(void){
	delete []luces;
}

int Iluminacion::cantidadDeLuces(){ return cantDeLuces; }
Iluminacion::propLuz Iluminacion::luz(int i){ 
	mat4 matrizDeLaCamara = glm::lookAt(camara->eye(),
										camara->at(),
										camara->up());	
	luces[i].posicion = matrizDeLaCamara * luces[i].posicion;
	luces[i].direccion = matrizDeLaCamara * luces[i].direccion;

	return luces[i];
}