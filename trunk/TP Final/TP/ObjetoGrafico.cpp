#include "ObjetoGrafico.h"


ObjetoGrafico::ObjetoGrafico(void)
{
}


void ObjetoGrafico::posicionar(float *nuevaPosicion){

	if (this->posicionObjeto != NULL)
		this->posicionar(nuevaPosicion[0],nuevaPosicion[1],nuevaPosicion[2]);	
	
}

void ObjetoGrafico::posicionar(const float& x,const float& y,const float& z){

		posicionObjeto[0] = x;
		posicionObjeto[1] = y;
		posicionObjeto[2] = z;
	
}


void ObjetoGrafico::inicializarVector(float *vector,float x,float y, float z){

	if (vector!= NULL){
		vector[0] = x;
		vector[1] = y;
		vector[2] = z;
	}
}

void ObjetoGrafico::dibujarPiramide(float *color){

	glDisable(GL_LIGHTING);

	glBegin(GL_TRIANGLE_FAN);

		glColor3fv(color);

		glVertex3f(0.0,0.0,3.0);

		glVertex3f(1.0,1.0,0.0);
		glVertex3f(-1.0,1.0,0.0);

		glVertex3f(-1.0,1.0,0.0);
		glVertex3f(-1.0,-1.0,0.0);

		glVertex3f(-1.0,-1.0,0.0);
		glVertex3f(1.0,-1.0,0.0);

		glVertex3f(1.0,-1.0,0.0);
		glVertex3f(1.0,1.0,0.0);

	glEnd();
}


ObjetoGrafico::~ObjetoGrafico(void)
{
}
