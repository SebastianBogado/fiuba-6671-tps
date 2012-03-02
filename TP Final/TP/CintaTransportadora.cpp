#include "CintaTransportadora.h"


CintaTransportadora::CintaTransportadora(void)
{
	this->alturaDeMaquina = 1.0;
	this->posicionObjeto = new float[3];
	this->inicializarVector(posicionObjeto,5.0,5.0,this->alturaDeMaquina);

	this->cintaEnMovimiento = true;

	this->pasoDeDiscretizacionGeneral = 0.1;

	//Para probar funcionamiento
	this->_testLargoCinta = 25.0;
	this->_pasoTest = 0.01;
	this->_testAnimacion = 3.0;

}


void CintaTransportadora::graficar(){



	//Codigo para Test
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(posicionObjeto[0],posicionObjeto[1],posicionObjeto[2]);

		glBegin(GL_QUADS);
			glColor3f(0.5,0.8,0.5);

			glVertex3f(0.0,0.0,0.0);
			glVertex3f(_testLargoCinta,0.0,0.0);
			glVertex3f(_testLargoCinta,3.0,0.0);
			glVertex3f(0.0,3.0,0.0);
		glEnd();


		glTranslatef(_testAnimacion,0.0,0.0);
		glBegin(GL_QUADS);
			

			glColor3f(0.3,0.2,1.0);

			glVertex3f(0.0,0.0,0.1);
			glVertex3f(1,0.0,0.1);
			glVertex3f(1,3.0,0.1);
			glVertex3f(0.0,3.0,0.1);

		glEnd();

		

	glPopMatrix();

}


void CintaTransportadora::actualizarAtributos(){

	if (this->cintaEnMovimiento)
	{
		this->_testAnimacion += this->_pasoTest;

		if(_testAnimacion >= this->_testLargoCinta)
			this->_testAnimacion = 0.0;
	}
}


void CintaTransportadora::nuevaPosicion(float posicionDeTramo,float* posicion)
{	

	//Solo para el Test
	this->inicializarVector(posicion, 5.0 + posicionDeTramo,	6.5 ,this->alturaDeMaquina);
}

float CintaTransportadora::nuevaPosicionDeTramo(float posicion)
{	


	//Solo para el Test
	float res=0.0;

	res = posicion + this->_pasoTest;

	if (res > this->_testLargoCinta)
		res =0.0;

	return res;

}


void CintaTransportadora::desplazarCinta()
{ 
	this->cintaEnMovimiento = true;
}

void CintaTransportadora::detenerCinta()
{
	this->cintaEnMovimiento = false;

}

void CintaTransportadora::aplicarShader(){

}

void CintaTransportadora::detenerShader(){

}

CintaTransportadora::~CintaTransportadora(void)
{
}
