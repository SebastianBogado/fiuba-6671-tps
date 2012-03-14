/*
 * 66.71 Sistemas Graficos
 * TP Final - Modelado de una planta de producción de Coca-Cola
 */


#ifndef _DEBUG
#pragma comment(linker,"/subsystem:\"windows\" /entry:\"mainCRTStartup\"") //evitar consola en modo Release
	bool debug = false;
#else
	bool debug = true;
#endif


#include <GL/glew.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Control.h"
///////////////////////////////////////////////
//////Control del todo la Escena del TP////////
///////////////////////////////////////////////
Control* control;							///
//////////////////////////////////////////////
//////////////////////////////////////////////


// Tamaño de la ventana
GLfloat window_size[2];
#define W_WIDTH window_size[0]
#define W_HEIGHT window_size[1]

void Set3DEnv()
{
	glViewport (0, 0, (GLsizei) W_WIDTH, (GLsizei) W_HEIGHT);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(60.0, (GLfloat) W_WIDTH/(GLfloat) W_HEIGHT, 0.10, 100.0);
}


void init(void)
{
	glClearColor (0.02f, 0.02f, 0.04f, 0.0f);
    glShadeModel (GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);

	control = new Control(debug, vec2(W_WIDTH, W_HEIGHT));
}



void escena(void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Set3DEnv();
	
	control->dibujarEscena();

	glutSwapBuffers();
}

void reshape (int w, int h)
{
   	W_WIDTH  = (float)w;
	W_HEIGHT = (float)h;
}

int main(int argc, char** argv){	
	int ancho = 800;
	int alto = 600;
	int ventanaPrincipal;


	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition (10, 10);
    glutInitWindowSize (ancho, alto); 
		
	ventanaPrincipal = glutCreateWindow("66.71 - TP Final");
	
	//Probablemente había mil formas más elegantes, pero bueno...
	// 73 es "I" en ASCII, o sea, I de "Intel"
	if (glGetString(GL_VENDOR)[0] ==  73)
		glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH); //La placa Intel de la notebook no soporta double buffering
		
	    

	init();
	glutDisplayFunc(escena); 
	glutReshapeFunc(reshape);
	glutKeyboardFunc(control->teclado);
	glutMouseFunc(control->mouse);
	glutMotionFunc(control->mouseMov);
	glutMouseWheelFunc(control->rueditaMouse);
	glutIdleFunc(control->actualizarDatos);
	glutMainLoop();
    return 0;
}