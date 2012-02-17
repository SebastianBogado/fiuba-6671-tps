#include "ObjetoGrafico.h"


ObjetoGrafico::ObjetoGrafico(void)
{
}


void ObjetoGrafico::posicionar(float *nuevaPosicion){

	if (this->posicionObjeto != NULL){
		posicionObjeto[0] = nuevaPosicion[0];
		posicionObjeto[1] = nuevaPosicion[1];
		posicionObjeto[2] = nuevaPosicion[2];		
	}
}


void ObjetoGrafico::inicializarVector(float *vector,float x,float y, float z){

	if (vector!= NULL){
		vector[0] = x;
		vector[1] = y;
		vector[2] = z;
	}
}

ObjetoGrafico::~ObjetoGrafico(void)
{
}
