#include "Iluminacion.h"

Camara* Iluminacion::camara = Camara::getInstancia();
Iluminacion* Iluminacion::instancia = NULL;


Iluminacion* Iluminacion::getInstancia(){
	if (! instancia)
		instancia = new Iluminacion();
	return instancia;
}

Iluminacion::Iluminacion(){
	this->cantDeLuces = 6;
	this->luces = new propLuz[cantDeLuces];
	propLuz luz = { 
		true,
		vec4(0.0), 
		vec4(0.0, 0.0, -1.0, 0.0),
	};
	for (int i = 0; i < cantDeLuces; i++)
		luces[i] = luz;
}


Iluminacion::~Iluminacion(void){
	delete []luces;
}

void Iluminacion::setPosicionDeLasLuces(int i, vec3 posicion){
	this->luces[i].posicion = vec4(posicion, 1.0);
}

int Iluminacion::cantidadDeLuces(){ return cantDeLuces; }

Iluminacion::propLuz Iluminacion::luz(int i){ 
	propLuz luzSolicitada;
	luzSolicitada.prendida = luces[i].prendida;

	mat4 matrizDeLaCamara = glm::lookAt(camara->eye(),
										camara->at(),
										camara->up());	
	luzSolicitada.posicion = matrizDeLaCamara * luces[i].posicion;
	luzSolicitada.direccion = matrizDeLaCamara * luces[i].direccion;

	return luzSolicitada;
}