#include "MaquinaDeBotellas.h"


MaquinaDeBotellas::MaquinaDeBotellas(void)
{	

	this->posicionObjeto = new float[3];

	posicionObjeto[0] = 4.0;
	posicionObjeto[1] = 5.0;
	posicionObjeto[2] = 0.0;

	this->ancho = 4.0;
	this->largo = 2.0;
	this->alto = 5.0;

	this->alturaDeMaquina = alto;

	this->inicializarVertices();

	this->posDeObjetoAnimado = new float[3];
	this->inicializarVector(this->posDeObjetoAnimado,
							posicionObjeto[0]+5,
							posicionObjeto[1],
							posicionObjeto[2]);
														

}




void MaquinaDeBotellas::graficar(){

	this->graficarBase();

	if (this->AnimacionIniciada)
	{
		float color[3]={1.0,0.0,0.0};
		glPushMatrix();
		glTranslatef(this->posicionObjeto[0],this->posicionObjeto[1],this->posicionObjeto[2]+this->alto);
		this->dibujarPiramide(color);

		glPopMatrix();
	}

	/*
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glDisable(GL_LIGHTING);
		glTranslatef(posicionObjeto[0],posicionObjeto[1],posicionObjeto[2]);
		
		glBegin(GL_QUADS);
			
			//Se dibuja la MAquina
			glColor3f(1.0,0.0,0.0);
			glVertex3fv(vertices[1]);
			glVertex3fv(vertices[2]);
			glVertex3fv(vertices[6]);
			glVertex3fv(vertices[5]);

			glColor3f(0.0,1.0,0.0);
			glVertex3fv(vertices[2]);
			glVertex3fv(vertices[3]);
			glVertex3fv(vertices[7]);
			glVertex3fv(vertices[6]);

			glColor3f(0.0,0.0,1.0);
			glVertex3fv(vertices[3]);
			glVertex3fv(vertices[0]);
			glVertex3fv(vertices[4]);
			glVertex3fv(vertices[7]);

			//4ta tapa
			glColor3f(1.0,1.0,0.0);
			glVertex3fv(vertices[0]);
			glVertex3fv(vertices[4]);
			glVertex3fv(vertices[5]);
			glVertex3fv(vertices[1]);

			//5ta tapa
			glColor3f(1.0,0.0,1.0);
			glVertex3fv(vertices[6]);
			glVertex3fv(vertices[7]);
			glVertex3fv(vertices[4]);
			glVertex3fv(vertices[5]);

			//6ta tapa la del piso, no parece necesaria

		glEnd();
	glPopMatrix();*/

}

void MaquinaDeBotellas::aplicarShader(){


}

void MaquinaDeBotellas::detenerShader(){



}

void MaquinaDeBotellas::actualizarAtributos(){

	if (this->AnimacionIniciada)
	{
		this->_testAnimacion += this->_pasoTest;

		this->AnimacionIniciada = this->_testAnimacion > 100.0;
	}

}



void MaquinaDeBotellas::iniciarAnimacion(Botella* botella)
{
	this->AnimacionIniciada = true;

	this->_pasoTest = 1.0;
	this->_testAnimacion = 0.0;



}

bool MaquinaDeBotellas::animacionFinalizada()
{

	return !this->AnimacionIniciada;

}


MaquinaDeBotellas::~MaquinaDeBotellas(void)
{

	delete[] this->posicionObjeto;
	delete[] this->posDeObjetoAnimado;

}
