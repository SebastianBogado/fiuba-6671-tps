#include "Botella.h"


Botella::Botella(void)
{
	this->posicionObjeto = new float[3];
	
	this->inicializarVector(posicionObjeto,0.0,0.0,0.0);
	this->inicializarVector(_testColor,0.1,0.1,0.3);

}


void Botella::graficar(){

	//float colorBotella[3] = { 0.8, 0.8, 0.8};

	glPushMatrix();
		glTranslatef(posicionObjeto[0],posicionObjeto[1],posicionObjeto[2]);
		this->dibujarPiramide(_testColor);
	glPopMatrix();
}

void Botella::actualizarAtributos(){

}


void Botella::desplazar(vec3 direccion){

	this->posicionObjeto[0] += direccion.x; 
	this->posicionObjeto[1] += direccion.y;
	this->posicionObjeto[2] += direccion.z;
}


void Botella::reiniciarAtributos(){


	//Solo para test
	this->inicializarVector(this->_testColor,0.1,0.1,0.3);

}

void Botella::aplicarShader(){


}

void Botella::detenerShader(){


}

Botella::~Botella(void)
{

	delete[] posicionObjeto;
}
