#include "CuartoDeMaquinas.h"


CuartoDeMaquinas::CuartoDeMaquinas(void)
{

	this->posicionObjeto = new float[3];

	posicionObjeto[0] = 0.0;
	posicionObjeto[1] = 0.0;
	posicionObjeto[2] = 0.0;

	this->ancho = 20.0;
	this->largo = 40.0;
	this->alto = 10.0;

	this->inicializarVertices();

}

void CuartoDeMaquinas::graficar(){

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

			//6ta tapa la del piso, que resultaria el piso
			glColor3f(0.8,0.8,0.8);
			glVertex3fv(vertices[0]);
			glVertex3fv(vertices[1]);
			glVertex3fv(vertices[2]);
			glVertex3fv(vertices[3]);

		glEnd();
	glPopMatrix();*/

}

void CuartoDeMaquinas::actualizarAtributos(){ }

void CuartoDeMaquinas::aplicarShader(){ }

void CuartoDeMaquinas::detenerShader(){ }

CuartoDeMaquinas::~CuartoDeMaquinas(void)
{
	delete[] this->posicionObjeto;
}
