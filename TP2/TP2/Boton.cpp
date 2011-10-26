#include "Boton.h"


void* pBotonActual; //variable global para ejcutar el callback con wrapper
extern GLfloat window_size[2];


Boton::Boton(string pathTextura, void (*mouseCallback)(int, int, int, int)){
	/*
	 linkear textura, en la función display
	 */
	pMouse = mouseCallback;
}


Boton::~Boton(void){

}

void Boton::display(){
	glEnable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	//hacer un simple cuadrado, y pegar la textura
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
		glVertex2f(1, 1);
		glVertex2f(1, 1);
		glVertex2f(1, -1);
		glVertex2f(-1, -1);
	glEnd();
	glColor3f(0, 1.0, 0);
	//un sub cuadrado, con una cruz, para probar
	glBegin(GL_LINE_STRIP);
		glVertex2f(-0.25, 0.25);
		glVertex2f(0.25, 0.25);
		glVertex2f(0.25, -0.25);
		glVertex2f(-0.25, -0.25);
		glVertex2f(-0.25, 0.25);
		glVertex2f(0.25, -0.25);
		glVertex2f(0.25, 0.25);
		glVertex2f(-0.25, -0.25);
	glEnd();
	glEnable(GL_DEPTH_TEST);
	glutPostRedisplay();
	glutSwapBuffers();
}

void Boton::displayWrapper(){
	Boton* yo = (Boton*) pBotonActual;
	yo->display();
}

Boton::mouse Boton::getMouseCallback(){ return this->pMouse; }