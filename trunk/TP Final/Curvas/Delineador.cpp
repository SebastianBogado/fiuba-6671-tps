#include "Delineador.h"


void Delineador::delinear(Curva* curva, int discretizacion){
	float paso = 1.0/discretizacion;
	glDisable(GL_LIGHTING);
	glLineWidth(2);
	glBegin(GL_LINE_STRIP);
		glColor3f(0.5, 0.7, 0.7);
		for (int i = 0; i < curva->cantidadDeTramos(); i++)
			for (float j = 0; j < 1; j+= paso)
				glVertex3fv(&curva->evaluar(i+j)[0]);
		glVertex3fv(&curva->evaluar(curva->cantidadDeTramos())[0]);
	glEnd();
	glEnable(GL_LIGHTING);
	glLineWidth(1);
}