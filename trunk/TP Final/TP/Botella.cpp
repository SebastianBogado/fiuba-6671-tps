#include "Botella.h"


Botella::Botella(void)
{
	this->posicionObjeto = new float[3];
}


void Botella::graficar(){


}

void Botella::actualizarAtributos(){

}


void Botella::desplazar(vec3 direccion){

	this->posicionObjeto[0] += direccion.x; 
	this->posicionObjeto[1] += direccion.y;
	this->posicionObjeto[2] += direccion.z;
}


void Botella::aplicarShader(){


}

void Botella::detenerShader(){


}

Botella::~Botella(void)
{

	delete[] posicionObjeto;
}
