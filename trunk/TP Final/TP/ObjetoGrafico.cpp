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

ObjetoGrafico::~ObjetoGrafico(void)
{
}
