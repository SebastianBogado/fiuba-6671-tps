#include "MaquinaDeBotellas.h"


MaquinaDeBotellas::MaquinaDeBotellas(void)
{
	this->posicionObjeto = new float[3];

	posicionObjeto[0] = 1.0;
	posicionObjeto[1] = 1.0;
	posicionObjeto[2] = 0.0;

	this->ancho = 1.0;
	this->largo = 2.0;
	this->alto = 3.0;

	this->inicializarVertices();

}

void MaquinaDeBotellas::definirParametros(float ancho,float largo,float alto){

	this->ancho = ancho;
	this->largo = largo;
	this->alto = alto;

	this->actualizarVertices();

}

void MaquinaDeBotellas::inicializarVertices(){

	this->cantidadVertices = 8;

	this->vertices = new float*[cantidadVertices];

	for (int i=0; i < cantidadVertices ; i++)
		this->vertices[i] = new float[3]; 

	
	this->actualizarVertices();

}

void MaquinaDeBotellas::actualizarVertices(){

	this->inicializarVector(vertices[0],0.0,0.0,0.0);
	this->inicializarVector(vertices[1],largo,0.0,0.0);
	this->inicializarVector(vertices[2],largo,ancho,0.0);
	this->inicializarVector(vertices[3],0.0,ancho,0.0);

	this->inicializarVector(vertices[4],0.0,0.0,alto);
	this->inicializarVector(vertices[5],largo,0.0,alto);
	this->inicializarVector(vertices[6],largo,ancho,alto);
	this->inicializarVector(vertices[7],0.0,ancho,alto);
}



void MaquinaDeBotellas::graficar(){


	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		
		glTranslatef(posicionObjeto[0],posicionObjeto[1],posicionObjeto[2]);
		
		glBegin(GL_QUADS);
			
			//Se dibuja la MAquina
			glVertex3fv(vertices[1]);
			glVertex3fv(vertices[2]);
			glVertex3fv(vertices[6]);
			glVertex3fv(vertices[5]);


			glVertex3fv(vertices[2]);
			glVertex3fv(vertices[3]);
			glVertex3fv(vertices[7]);
			glVertex3fv(vertices[6]);


			glVertex3fv(vertices[3]);
			glVertex3fv(vertices[0]);
			glVertex3fv(vertices[4]);
			glVertex3fv(vertices[7]);

			//4ta tapa
			glVertex3fv(vertices[0]);
			glVertex3fv(vertices[4]);
			glVertex3fv(vertices[5]);
			glVertex3fv(vertices[1]);

			//5ta tapa

			glVertex3fv(vertices[6]);
			glVertex3fv(vertices[7]);
			glVertex3fv(vertices[4]);
			glVertex3fv(vertices[5]);

			//6ta tapa la del piso, no parece necesaria

		glEnd();
	glPopMatrix();

}

void MaquinaDeBotellas::aplicarShader(){


}

void MaquinaDeBotellas::detenerShader(){



}

MaquinaDeBotellas::~MaquinaDeBotellas(void)
{

	delete[] this->posicionObjeto;

	for(int i=0;i < cantidadVertices;i++)
		delete[] this->vertices[i];

	delete[] this->vertices;

}
