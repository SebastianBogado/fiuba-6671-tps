#include "MaquinaDeLlenado.h"


MaquinaDeLlenado::MaquinaDeLlenado(void)
{

		///solo para test
	this->_pasoTest = 0.01;

	this->posicionObjeto = new float[3];
	this->inicializarVector(posicionObjeto,2.0,22.0,0.0);

	this->posDeObjetoAnimado = new float [3];
	this->inicializarVector(posDeObjetoAnimado,23.0,6.5,0.0);
	
	this->AnimacionIniciada = false;

}


MaquinaDeLlenado::~MaquinaDeLlenado(void)
{
	delete[] this->posicionObjeto;
	delete[] this->posDeObjetoAnimado;

}


void MaquinaDeLlenado::graficar()
{
	float color[3] = {0.6,0.3,0.1};

	glDisable(GL_LIGHTING);
	aplicarPhong();
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

	detenerPhong();
}

void MaquinaDeLlenado::actualizarAtributos()
{
		//solo para test

	if (this->AnimacionIniciada)
	{
		this->_testAnimacion += this->_pasoTest;

		//Seria como el tiempo de animacion

		this->AnimacionIniciada = _testAnimacion < 1.0;

	}

}

void MaquinaDeLlenado::aplicarShader()
{
}

void MaquinaDeLlenado::detenerShader()
{


}



void MaquinaDeLlenado::iniciarAnimacion(Botella* botella)
{	


	//Solo para test
	botella->etiquetar();

	this->AnimacionIniciada = true;

	this->_testAnimacion = 0.0;
	
}


bool MaquinaDeLlenado::animacionFinalizada()
{
	return !(this->AnimacionIniciada);

}