#include "MaquinaEtiquetadora.h"


MaquinaEtiquetadora::MaquinaEtiquetadora(void)
{

	///solo para test
	this->_pasoTest = 0.01;

	this->posicionObjeto = new float[3];
	this->inicializarVector(posicionObjeto,2.0,15.0,0.0);

	this->posDeObjetoAnimado = new float [3];
	this->inicializarVector(posDeObjetoAnimado,16.0,6.5,0.0);


}


void MaquinaEtiquetadora::graficar(){




	//Solo para test
	float color[3] = {0.1,0.3,0.9};

	glPushMatrix();
		glTranslatef(posicionObjeto[0],posicionObjeto[1],posicionObjeto[2]);
		//glPushMatrix();
			glScalef(1.3,1.0,2.0);	
			this->dibujarPiramide(color);
		//glPopMatrix();
		glTranslatef(0.0,0.0,3.0);
		glRotatef(180,0.0,1.0,0.0);
		this->dibujarPiramide(color);
			
	glPopMatrix();

}


void MaquinaEtiquetadora::actualizarAtributos(){ 


	//solo para test

	if (this->AnimacionIniciada)
	{
		this->_testAnimacion += this->_pasoTest;

		//Seria como el tiempo de animacion

		this->AnimacionIniciada = _testAnimacion < 1.5;

	}
	
}

void MaquinaEtiquetadora::aplicarShader(){ }

void MaquinaEtiquetadora::detenerShader(){ }


void MaquinaEtiquetadora::iniciarAnimacion(Botella* botella){

	//botella->cambiarColor();
	botella->etiquetar();

	this->AnimacionIniciada = true;

	this->_testAnimacion = 0.0;
	
}


bool MaquinaEtiquetadora::animacionFinalizada()
{
	return !(this->AnimacionIniciada);

}


MaquinaEtiquetadora::~MaquinaEtiquetadora(void)
{
}
