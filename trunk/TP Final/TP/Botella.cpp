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

void Botella::graficarEnCajon(GLSLProgram* shaderss){
	//glTranslatef(posicionObjeto[0],posicionObjeto[1],posicionObjeto[2]);
	shaderss->setUniform("porcentajeDeLlenado", porcentajeDeLlenado);
	shaderss->setUniform("tieneEtiqueta", tieneEtiqueta);
	shaderss->setUniform("tieneTapa", tieneTapa);
}


float abs(float &x){

	if (x < 0)
		return -x;
	else
		return x;
}

void Botella::actualizarAtributos(){

	//Para depurar
	/*
	static float posAnt[3]={posicionObjeto[0],posicionObjeto[1],posicionObjeto[2]};
	
	float error = 0.1;
	bool errorEncontrado = false;


	if (	abs(posAnt[0] - posicionObjeto[0]) < error &&
			abs(posAnt[1] - posicionObjeto[1]) < error &&
			abs(posAnt[2] - posicionObjeto[2]) < error )
			errorEncontrado = true;
	

	*/
	

	
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

void Botella::botellaTerminada()
{
	this->tieneEtiqueta = true;
	this->tieneTapa = true;

	this->porcentajeDeLlenado = 0.65;
}


Botella::~Botella(void)
{
	delete[] posicionObjeto;
}

void Botella::definirMateriales(){}