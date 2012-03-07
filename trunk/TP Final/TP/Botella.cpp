#include "Botella.h"

Botella::Botella(void){
	this->posicionObjeto = new float[3];
	
	this->inicializarVector(posicionObjeto,0.0,0.0,0.0);
	this->inicializarVector(_testColor,0.1,0.1,0.3);
	
	tieneEtiqueta = false;
	tieneTapa = false;
	porcentajeDeLlenado = 0.0;
}

void Botella::graficar(){}
void Botella::graficar(GLSLProgram* shaderss){
	glTranslatef(posicionObjeto[0],posicionObjeto[1],posicionObjeto[2]);
	shaderss->setUniform("porcentajeDeLlenado", porcentajeDeLlenado);
	shaderss->setUniform("tieneEtiqueta", tieneEtiqueta);
	shaderss->setUniform("tieneTapa", tieneTapa);
}

void Botella::actualizarAtributos(){
	
}

void Botella::etiquetar(){ this->tieneEtiqueta = true; }

void Botella::tapar(){ this->tieneTapa = true; }


void Botella::desplazar(vec3 direccion){

	this->posicionObjeto[0] += direccion.x; 
	this->posicionObjeto[1] += direccion.y;
	this->posicionObjeto[2] += direccion.z;
}


void Botella::reiniciarAtributos(){

	this->tieneEtiqueta = false;
	this->tieneTapa = false;

	this->porcentajeDeLlenado = 0.0;

	//Solo para test
	//this->inicializarVector(this->_testColor,0.1,0.1,0.3);

}


Botella::~Botella(void)
{
	delete[] posicionObjeto;
}
