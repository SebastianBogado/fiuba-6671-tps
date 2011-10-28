///
/// 66.71 Sistemas Graficos
/// Framework de trabajo para el TP1
/// 2do Cuatrimestre 2011
///
/// info@sg6671.com.ar
///

#ifndef _DEBUG
#pragma comment(linker,"/subsystem:\"windows\" /entry:\"mainCRTStartup\"") //evitar consola en modo Release
#endif

#include <GL/glew.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <iostream>
using namespace std;
#include "HUD.h"
#include "ShaderManager.h"
#include "Emparchador.h"
#include "Esfera.h"
#include "Cubo.h"
//#include "Toroide.h"
#include "Cilindro.h"


// Tamaño de la ventana
GLfloat window_size[2];
#define W_WIDTH window_size[0]
#define W_HEIGHT window_size[1]

HUD* hud;
ShaderManager* shaderManager;


// Variables que controlan la ubicación de la cámara en la Escena 3D
float eye[3] = {3.0, 3.0, 2.0};
float at[3]  = { 0.0,  0.0, 0.0};
float up[3]  = { 0.0,  0.0, 1.0};

//Variables de control
extern bool verEsfera;
extern bool verCubo;
extern bool verToroide;
extern bool verCilindro;

extern bool verMaterialSombreadoBrillante;
extern bool verMaterialSombreadoTexturado;
extern bool verMaterialReflectivo;
extern bool verMaterialSombreadoSemimate;

extern bool verRetorcer;
extern bool verRuido;
extern bool verDoblar;
extern bool verEsferizar;
/*
// Variables asociadas a única fuente de luz de la escena
float light_color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
float light_position[3] = {10.0f, 10.0f, 8.0f};
float light_ambient[4] = {0.05f, 0.05f, 0.05f, 1.0f};
*/


// Handle para el control de las Display Lists
GLuint dl_handle;
#define DL_ESFERA (dl_handle+0)
#define DL_CUBO (dl_handle+1)
#define DL_TOROIDE (dl_handle+2)
#define DL_CILINDRO (dl_handle+3)


void Set3DEnv()
{
	glViewport (10, -80, (GLsizei) W_WIDTH, (GLsizei) W_HEIGHT); 
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(60.0, (GLfloat) W_WIDTH/(GLfloat) W_HEIGHT, 0.10, 100.0);
}

void init(void) 
{
	Emparchador emparchador;
    Superficie* superficie;

	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);

	dl_handle = glGenLists(4);

	//DLs para las superficies
	glNewList(DL_ESFERA, GL_COMPILE);
	    superficie = new Esfera;
        emparchador.emparchar(superficie);
        delete superficie;
	glEndList();
	
	glNewList(DL_CUBO, GL_COMPILE);
        superficie = new Cubo;
        emparchador.emparchar(superficie);
        delete superficie;
    glEndList();

	/* implementar toroide
	glNewList(DL_TOROIDE, GL_COMPILE);
        superficie = new Toroide;
		emparchador.emparchar(Superficie);
		delete superficie;
	glEndList();
	*/

	glNewList(DL_CILINDRO, GL_COMPILE);
        superficie = new Cilindro(.7,1.5,32);
        emparchador.emparchar(superficie);
        delete superficie;
	glEndList();



	/*
	glClearColor (0.02f, 0.02f, 0.04f, 0.0f);
    glShadeModel (GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
	*/

}


void OnIdle (void)
{
	//hacer algo
    glutPostRedisplay();
}
void escena(void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Set3DEnv();
	gluLookAt (eye[0], eye[1], eye[2], at[0], at[1], at[2], up[0], up[1], up[2]);

	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_LIGHTING);
	glColor3f(0.0, 0.25, 0.75);

	//selección de primitiva
	if (verEsfera)
		glCallList(DL_ESFERA);
	if (verCubo)
		glCallList(DL_CUBO);
    if (verToroide)
		glCallList(DL_TOROIDE);
   	if (verCilindro)
		glCallList(DL_CILINDRO);
	glEnable(GL_LIGHTING);

	//selección del material
	if (verMaterialSombreadoBrillante)
		shaderManager->setFragmenShader(MATERIAL_SOMBREADO_BRILLANTE);
	if (verMaterialSombreadoTexturado)
		shaderManager->setFragmenShader(MATERIAL_SOMBREADO_TEXTURADO);
    if (verMaterialReflectivo)
		shaderManager->setFragmenShader(MATERIAL_REFLECTIVO);
   	if (verMaterialSombreadoSemimate)
		shaderManager->setFragmenShader(MATERIAL_SOMBREADO_SEMIMATE);
	
	//selección de la deformación
	if (verRetorcer)
		shaderManager->setVertexShader(RETORCER);
	if (verRuido)
		shaderManager->setVertexShader(RUIDO);
    if (verDoblar)
		shaderManager->setVertexShader(DOBLAR);
   	if (verEsferizar)
		shaderManager->setVertexShader(ESFERIZAR);

	//aplicar shaders
	//shaderManager->usarPrograma();
	
	glutSwapBuffers();
	glutPostRedisplay();
}



void reshape (int w, int h)
{
   	W_WIDTH  = (float)w;
	W_HEIGHT = (float)h;
	
	hud->resize(W_WIDTH, W_HEIGHT);

}


void mouse(int button, int state, int x, int y){
//mover cámara
}

void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
      case 'q':
         exit(0);
         break;
/*
	  case 'g':
		  view_grid = !view_grid;
		  glutPostRedisplay();
		  break;

	  case 'a':
		  view_axis = !view_axis;
		  glutPostRedisplay();
		  break;

	  case 'e':
		  edit_panel = !edit_panel;
		  glutPostRedisplay();
		  break;

	  case '2':
		  eye[0] = 0.0;
		  eye[1] = 0.0;
		  eye[2] = 15.0;

		  at[0] = 0.0;
		  at[1] = 0.0;
		  at[2] = 0.0;

		  up[0] = 0.0;
		  up[1] = 1.0;
		  up[2] = 0.0;
		  glutPostRedisplay();
		  break;

	  case '3':
		  eye[0] = 15.0;
		  eye[1] = 15.0;
		  eye[2] = 5.0;

		  at[0] = 0.0;
		  at[1] = 0.0;
		  at[2] = 0.0;

		  up[0] = 0.0;
		  up[1] = 0.0;
		  up[2] = 1.0;
		  glutPostRedisplay();
		  break;
		  */
     default:
         break;
   }
}

int main(int argc, char** argv){	
	int ancho = 800;
	int alto = 600;
	int ventanaPrincipal;

	glutInit(&argc, argv);
    glutInitWindowPosition (10, 10);
    glutInitWindowSize (ancho, alto); 
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    //glutFullScreen();
   
	ventanaPrincipal = glutCreateWindow("66.71 - TP2");
    glutDisplayFunc(escena); 
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutIdleFunc(OnIdle);
	init ();

	hud = new HUD(ventanaPrincipal, ancho, alto);
	glewInit();

	shaderManager = new ShaderManager();
	
		
	//loop principal
	glutMainLoop();
    return 0;
}
