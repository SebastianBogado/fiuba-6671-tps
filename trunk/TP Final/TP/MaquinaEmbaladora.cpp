#include "MaquinaEmbaladora.h"


MaquinaEmbaladora::MaquinaEmbaladora(void)
{

	this->posicionObjeto = new float[3];
	this->inicializarVector(posicionObjeto,28.0,5.0,0.0);

	this->posDeObjetoAnimado = new float[3];
	this->inicializarVector(posDeObjetoAnimado,0.0,0.0,0.0);


	this->ancho = 4.0;
	this->largo = 4.0;
	this->alto = 5.0;

	this->inicializarVertices();
}



void MaquinaEmbaladora::graficar(){


	this->graficarBase();

	/*
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glDisable(GL_LIGHTING);
		
		glTranslatef(posicionObjeto[0],posicionObjeto[1],posicionObjeto[2]);
		
		glBegin(GL_QUADS);
			
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

void MaquinaEmbaladora::actualizarAtributos(){ }

void MaquinaEmbaladora::aplicarShader(){

}

void MaquinaEmbaladora::detenerShader(){
}


void MaquinaEmbaladora::iniciarAnimacion(Botella* botella)
{


}

bool MaquinaEmbaladora::animacionFinalizada()
{

	return true;
}

MaquinaEmbaladora::~MaquinaEmbaladora(void)
{
	delete[] this->posicionObjeto;
}
