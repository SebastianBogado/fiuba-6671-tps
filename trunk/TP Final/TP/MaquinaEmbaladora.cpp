#include "MaquinaEmbaladora.h"


MaquinaEmbaladora::MaquinaEmbaladora(void)
{

	this->posicionObjeto = new float[3];

	posicionObjeto[0] = 1.0;
	posicionObjeto[1] = 6.0;
	posicionObjeto[2] = 0.0;

	this->ancho = 2.0;
	this->largo = 2.0;
	this->alto = 3.0;

	this->inicializarVertices();
}



void MaquinaEmbaladora::graficar(){

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

void MaquinaEmbaladora::actualizarAtributos(){ }

void MaquinaEmbaladora::aplicarShader(){

}

void MaquinaEmbaladora::detenerShader(){
}

MaquinaEmbaladora::~MaquinaEmbaladora(void)
{
	delete[] this->posicionObjeto;
}
