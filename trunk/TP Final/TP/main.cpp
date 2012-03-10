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

// Variables asociadas a única fuente de luz de la escena
float light_color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
float light_position[3] = {10.0f, 10.0f, 8.0f};
float light_ambient[4] = {0.05f, 0.05f, 0.05f, 1.0f};

// Handle para el control de las Display Lists
GLuint dl_handle;
#define DL_AXIS (dl_handle+0)
#define DL_GRID (dl_handle+1)

// Tamaño de la ventana
GLfloat window_size[2];
#define W_WIDTH window_size[0]
#define W_HEIGHT window_size[1]


void DrawAxis()
{
	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
		// X
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(15.0, 0.0, 0.0);
		// Y
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 15.0, 0.0);
		// Z
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 0.0, 0.0);
		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 15.0);
	glEnd();
	glEnable(GL_LIGHTING);
}


void DrawXYGrid()
{
	int i;
	glDisable(GL_LIGHTING);
	glColor3f(0.25f, 0.2f, 0.2f);
	glBegin(GL_LINES);
	for(i=-20; i<21; i++)
	{
		glVertex3f((float)i, -20.0f, 0.0f);
		glVertex3f((float)i,  20.0f, 0.0f);
		glVertex3f(-20.0f, (float)i, 0.0f);
		glVertex3f( 20.0f, (float)i, 0.0f);
	}
	glEnd();
	glEnable(GL_LIGHTING);
}
void Set3DEnv()
{
	glViewport (0, 0, (GLsizei) W_WIDTH, (GLsizei) W_HEIGHT);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(60.0, (GLfloat) W_WIDTH/(GLfloat) W_HEIGHT, 0.10, 100.0);
}


void init(void)
{
	dl_handle = glGenLists(3);

	glClearColor (0.02f, 0.02f, 0.04f, 0.0f);
    glShadeModel (GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);

	// Generación de las Display Lists
	glNewList(DL_AXIS, GL_COMPILE);
		DrawAxis();
	glEndList();
	glNewList(DL_GRID, GL_COMPILE);
		DrawXYGrid();
	glEndList();

	control = new Control(debug);
}



void escena(void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Set3DEnv();
	
	control->dibujarEscena();

	glCallList(DL_AXIS);
	glCallList(DL_GRID);

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
	//glutSpecialFunc(teclasParticulares);
	glutMouseFunc(control->mouse);
	glutMotionFunc(control->mouseMov);
	//glutMouseWheelFunc(rueditaDelMouse);
	glutIdleFunc(control->actualizarDatos);
	glutMainLoop();
    return 0;
}