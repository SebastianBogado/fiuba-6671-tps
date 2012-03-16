#include <iostream>
#include "TestBaseBSpline.h"
#include "TestBSpline.h"
#include "TestBaseBerstein.h"
#include "TestBezier.h"
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Delineador.h"

using namespace std;

// Variables asociadas a única fuente de luz de la escena
float light_color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
float light_position[3] = {10.0f, 10.0f, 8.0f};
float light_ambient[4] = {0.05f, 0.05f, 0.05f, 1.0f};

Delineador* delineador;
BSpline* bsplineRevol;
Bezier* bezierRevol;

BSpline* bsplineBarridoBorde1;
BSpline* bsplineBarridoCamino1;

BSpline* bsplineBarridoBorde2;
Bezier* bezierBarridoCamino2;

Bezier* bezierBarridoBorde3;
Bezier* bezierBarridoCamino3;

Bezier* bezierBarridoBorde4;
BSpline* bsplineBarridoCamino4;

// Variables de control
bool view_grid = true;
bool view_axis = true;
bool edit_panel = false;
bool verPuntos = true;
bool verCurvas = true;


// Handle para el control de las Display Lists
GLuint dl_handle;
#define DL_AXIS (dl_handle+0)
#define DL_GRID (dl_handle+1)
#define DL_AXIS2D_TOP (dl_handle+2)

#define DL_BSPLINE_REVOL (dl_handle+3)
#define DL_PUNTOS_BSPLINE_REVOL (dl_handle+4)
#define DL_BEZIER_REVOL (dl_handle+5)
#define DL_PUNTOS_BEZIER_REVOL (dl_handle+6)

#define DL_CURVAS_BARRIDO_BSPLINE_BSPLINE (dl_handle+7)
#define DL_PUNTOS_CURVAS_BARRIDO_BSPLINE_BSPLINE (dl_handle+8)

#define DL_CURVAS_BARRIDO_BSPLINE_BEZIER (dl_handle+9)
#define DL_PUNTOS_CURVAS_BARRIDO_BSPLINE_BEZIER (dl_handle+10)

#define DL_CURVAS_BARRIDO_BEZIER_BEZIER (dl_handle+11)
#define DL_PUNTOS_CURVAS_BARRIDO_BEZIER_BEZIER (dl_handle+12)

#define DL_CURVAS_BARRIDO_BEZIER_BSPLINE (dl_handle+13)
#define DL_PUNTOS_CURVAS_BARRIDO_BEZIER_BSPLINE (dl_handle+14)

GLuint DL_CURVA_SELECCIONADA;

// Tamaño de la ventana
GLfloat window_size[2];
#define W_WIDTH window_size[0]
#define W_HEIGHT window_size[1]

#define TOP_VIEW_POSX	((int)((float)W_WIDTH*0.60f))
#define TOP_VIEW_W		((int)((float)W_WIDTH*0.40f))
#define TOP_VIEW_POSY	((int)((float)W_HEIGHT*0.60f))
#define TOP_VIEW_H		((int)((float)W_HEIGHT*0.40f))


// Variables que controlan la ubicación de la cámara en la Escena 3D
float eye[3] = {15.0, 15.0, 5.0};
float at[3]  = { 0.0,  0.0, 0.0};
float up[3]  = { 0.0,  0.0, 1.0};
//Para el movimiento de la cámara
float anguloTheta=3.14/4.0;
float anguloPhi=3.14/4.0;
float difAnguloX=3.14/30.0;
float difAnguloY;
float RadioEsfera=5;
float deltaRadio=0.5;

float norma3(float* p){
    float resultado=0;

    resultado+=p[0]*p[0];
    resultado+=p[1]*p[1];
    resultado+=p[2]*p[2];

    resultado=sqrt(resultado);

    return resultado;
}

void redimensionar(){
	float norma=norma3(eye);

    eye[0]=cos(anguloPhi)*cos(anguloTheta)*norma;
    eye[1]=cos(anguloPhi)*sin(anguloTheta)*norma;
    eye[2]=sin(anguloPhi)*norma;

    RadioEsfera=norma;
}

void redimensionarRadio(){
	eye[0]=cos(anguloPhi)*cos(anguloTheta)*RadioEsfera;
    eye[1]=cos(anguloPhi)*sin(anguloTheta)*RadioEsfera;
    eye[2]=sin(anguloPhi)*RadioEsfera;
}

void OnIdle (void)
{
	glutPostRedisplay();
}

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

void DrawAxis2DTopView()
{
	glDisable(GL_LIGHTING);
	glBegin(GL_LINE_LOOP);
		// X
		glColor3f(0.0f, 0.5f, 1.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
	glEnd();
	glBegin(GL_QUADS);
		glColor3f(0.1f, 0.1f, 0.1f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
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

void SetPanelTopEnv()
{
	glViewport (TOP_VIEW_POSX, TOP_VIEW_POSY, (GLsizei) TOP_VIEW_W, (GLsizei) TOP_VIEW_H); 
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
	gluOrtho2D(-0.10, 1.05, -0.10, 1.05);
}

void dibujarPuntosDeControl(Curva* curva){
	glMatrixMode (GL_MODELVIEW);
   
	for (int i = 0; i < curva->cantidadDePuntos(); i++){
		 glPushMatrix();
		 glTranslatef(curva->verPunto(i).x, curva->verPunto(i).y, curva->verPunto(i).z);
		 gluSphere(gluNewQuadric(), 0.15, 6, 6);
		 glPopMatrix();
	}
}
void inicializarBSplineRevol(){/* Estos puntos son buenos para una superficie que verifique luces
	vec3 bsplineP1 = vec3(3.0, 0.0, 0.0); 
	vec3 bsplineP2 = vec3(3.0, 0.0, 3.0);
	vec3 bsplineP3 = vec3(1.0, 0.0, 4.0);
	vec3 bsplineP4 = vec3(4.0, 0.0, 5.0);
	vec3 bsplineP5 = vec3(2.0, 0.0, 6.0);*/

	vec3 bsplineP1 = vec3(-1.0, 0.0, 1.0); 
	vec3 bsplineP2 = vec3(1.0, 0.0, 1.0);
	vec3 bsplineP3 = vec3(1.0, 0.0, 2.5);
	vec3 bsplineP4 = vec3(1.0, 0.0, 4.0); 
	vec3 bsplineP5 = vec3(-1.0, 0.0, 4.0);
	bsplineRevol = new BSpline(5);
	bsplineRevol->incluirPunto(bsplineP1);
	bsplineRevol->incluirPunto(bsplineP2);
	bsplineRevol->incluirPunto(bsplineP3);
	bsplineRevol->incluirPunto(bsplineP4);
	bsplineRevol->incluirPunto(bsplineP5);
	DL_CURVA_SELECCIONADA = DL_BSPLINE_REVOL;
}
void inicializarBezierRevol(){
	vec3 bezierP1 = vec3(0.0, 0.0, 0.0); 
	vec3 bezierP2 = vec3(0.9, 0.0, 0.0);
	vec3 bezierP3 = vec3(0.5, 0.0, 0.4);
	vec3 bezierP4 = vec3(0.5, 0.0, 1.0);
	vec3 bezierP5 = vec3(0.5, 0.0, 1.6); 
	vec3 bezierP6 = vec3(0.6, 0.0, 1.8);
	vec3 bezierP7 = vec3(0.4, 0.0, 2.2);
	vec3 bezierP8 = vec3(0.2, 0.0, 2.6);
	vec3 bezierP9 = vec3(0.2, 0.0, 2.8); 
	vec3 bezierP10 = vec3(0.2, 0.0, 3.0); 
	vec3 bezierP11 = vec3(0.2, 0.0, 3.2); 
	vec3 bezierP12 = vec3(0.2, 0.0, 3.2); 
	vec3 bezierP13 = vec3(0.0, 0.0, 3.2);
	bezierRevol = new Bezier(4);
	bezierRevol->incluirPunto(bezierP1);
	bezierRevol->incluirPunto(bezierP2);
	bezierRevol->incluirPunto(bezierP3);
	bezierRevol->incluirPunto(bezierP4);
	bezierRevol->incluirPunto(bezierP5);
	bezierRevol->incluirPunto(bezierP6);
	bezierRevol->incluirPunto(bezierP7);
	bezierRevol->incluirPunto(bezierP8);
	bezierRevol->incluirPunto(bezierP9);
	bezierRevol->incluirPunto(bezierP10);
	bezierRevol->incluirPunto(bezierP11);
	bezierRevol->incluirPunto(bezierP12);
	bezierRevol->incluirPunto(bezierP13);

}
void inicializarCurvasBarridoBSplineBSpline(){
	//Curva borde
	vec3 bordeP1 = vec3(6.5, 0.0, 2.5); 
	vec3 bordeP2 = vec3(6.0, 0.0, 2.0);
	vec3 bordeP3 = vec3(6.0, 0.0, 2.0);
	vec3 bordeP4 = vec3(5.5, 0.0, 2.0);
	vec3 bordeP5 = vec3(5.0, 0.0, 2.0); 
	vec3 bordeP6 = vec3(5.0, 0.0, 2.0);
	vec3 bordeP7 = vec3(4.5, 0.0, 2.5);
	bsplineBarridoBorde1 = new BSpline(7);
	bsplineBarridoBorde1->incluirPunto(bordeP1);
	bsplineBarridoBorde1->incluirPunto(bordeP2);
	bsplineBarridoBorde1->incluirPunto(bordeP3);
	bsplineBarridoBorde1->incluirPunto(bordeP4);
	bsplineBarridoBorde1->incluirPunto(bordeP5);
	bsplineBarridoBorde1->incluirPunto(bordeP6);
	bsplineBarridoBorde1->incluirPunto(bordeP7);
	//Curva camino
	vec3 caminoP1 = vec3(5.5, -1.5, 2.0);
	vec3 caminoP2 = vec3(5.5, 1.5, 2.0);
	vec3 caminoP3 = vec3(5.5, 4.5, 2.0);
	vec3 caminoP4 = vec3(2.5, 4.5, 2.0);
	vec3 caminoP5 = vec3(-0.5, 4.5, 2.0);
	vec3 caminoP6 = vec3(-0.5, 7.5, 2.0);
	vec3 caminoP7 = vec3(-0.5, 10.5, 2.0);
	vec3 caminoP8 = vec3(-0.5, 13.5, 2.0);
	vec3 caminoP9 = vec3(-0.5, 15.5, 2.0);
	bsplineBarridoCamino1 = new BSpline(9);
	bsplineBarridoCamino1->incluirPunto(caminoP1);
	bsplineBarridoCamino1->incluirPunto(caminoP2);
	bsplineBarridoCamino1->incluirPunto(caminoP3);
	bsplineBarridoCamino1->incluirPunto(caminoP4);
	bsplineBarridoCamino1->incluirPunto(caminoP5);
	bsplineBarridoCamino1->incluirPunto(caminoP6);
	bsplineBarridoCamino1->incluirPunto(caminoP7);
	bsplineBarridoCamino1->incluirPunto(caminoP8);
	bsplineBarridoCamino1->incluirPunto(caminoP9);
}
void inicializarCurvasBarridoBSplineBezier(){
	//Curva borde
	vec3 bordeP1 = vec3(0.0, 0.0, 0.0); 
	vec3 bordeP2 = vec3(5.0, 0.0, 5.0);
	vec3 bordeP3 = vec3(0.0, 0.0, 8.0);
	bsplineBarridoBorde2 = new BSpline(3);
	bsplineBarridoBorde2->incluirPunto(bordeP1);
	bsplineBarridoBorde2->incluirPunto(bordeP2);
	bsplineBarridoBorde2->incluirPunto(bordeP3);
	//Curva camino
	vec3 caminoP1 = vec3(0.0, 0.0, 5.0);
	vec3 caminoP2 = vec3(0.0, 3.0, 6.0);
	vec3 caminoP3 = vec3(0.0, 6.0, 3.0);
	vec3 caminoP4 = vec3(4.0, 6.0, 3.0);
	bezierBarridoCamino2 = new Bezier(1);
	bezierBarridoCamino2->incluirPunto(caminoP1);
	bezierBarridoCamino2->incluirPunto(caminoP2);
	bezierBarridoCamino2->incluirPunto(caminoP3);
	bezierBarridoCamino2->incluirPunto(caminoP4);
}
void inicializarCurvasBarridoBezierBezier(){
	//Curva borde
	vec3 bordeP1 = vec3(3.0, 0.0, 0.0); 
	vec3 bordeP2 = vec3(3.0, -3.0, 0.0);
	vec3 bordeP3 = vec3(-3.0, -3.0, 0.0);
	vec3 bordeP4 = vec3(-3.0, 0.0, 0.0);
	vec3 bordeP5 = vec3(-3.0, 3.0, 0.0);
	vec3 bordeP6 = vec3(3.0, 3.0, 0.0);
	vec3 bordeP7 = vec3(3.0, 0.0, 0.0);
	bezierBarridoBorde3 = new Bezier(2);
	bezierBarridoBorde3->incluirPunto(bordeP1);
	bezierBarridoBorde3->incluirPunto(bordeP2);
	bezierBarridoBorde3->incluirPunto(bordeP3);
	bezierBarridoBorde3->incluirPunto(bordeP4);
	bezierBarridoBorde3->incluirPunto(bordeP5);
	bezierBarridoBorde3->incluirPunto(bordeP6);
	bezierBarridoBorde3->incluirPunto(bordeP7);
	//Curva camino
	vec3 caminoP1 = vec3(0.0, 0.0, 0.0);
	vec3 caminoP2 = vec3(0.0, 0.0, 4.0);
	vec3 caminoP3 = vec3(0.0, 4.0, 4.0);
	vec3 caminoP4 = vec3(0.0, 8.0, 4.0);
	vec3 caminoP5 = vec3(0.0, 12.0, 4.0);
	vec3 caminoP6 = vec3(0.0, 12.0, 8.0);
	vec3 caminoP7 = vec3(0.0, 12.0, 12.0);
	bezierBarridoCamino3 = new Bezier(2);
	bezierBarridoCamino3->incluirPunto(caminoP1);
	bezierBarridoCamino3->incluirPunto(caminoP2);
	bezierBarridoCamino3->incluirPunto(caminoP3);
	bezierBarridoCamino3->incluirPunto(caminoP4);
	bezierBarridoCamino3->incluirPunto(caminoP5);
	bezierBarridoCamino3->incluirPunto(caminoP6);
	bezierBarridoCamino3->incluirPunto(caminoP7);
}
void inicializarCurvasBarridoBezierBSpline(){
	//Curva borde
	vec3 bordeP1 = vec3(3.0, 0.0, 0.0); 
	vec3 bordeP2 = vec3(4.0, -3.0, 3.0);
	vec3 bordeP3 = vec3(2.0, -1.0, 5.0);
	vec3 bordeP4 = vec3(1.0, 3.0, 7.0);
	bezierBarridoBorde4 = new Bezier(1);
	bezierBarridoBorde4->incluirPunto(bordeP1);
	bezierBarridoBorde4->incluirPunto(bordeP2);
	bezierBarridoBorde4->incluirPunto(bordeP3);
	bezierBarridoBorde4->incluirPunto(bordeP4);
	//Curva camino
	vec3 caminoP1 = vec3(0.0, 0.0, 0.0);
	vec3 caminoP2 = vec3(5.0, 5.0, 5.0);
	vec3 caminoP3 = vec3(0.0, 0.0, 4.0);
	vec3 caminoP4 = vec3(0.0, 0.0, 10.0);
	vec3 caminoP5 = vec3(12.0, 12.0, 12.0);
	bsplineBarridoCamino4 = new BSpline(5);
	bsplineBarridoCamino4->incluirPunto(caminoP1);
	bsplineBarridoCamino4->incluirPunto(caminoP2);
	bsplineBarridoCamino4->incluirPunto(caminoP3);
	bsplineBarridoCamino4->incluirPunto(caminoP4);
	bsplineBarridoCamino4->incluirPunto(caminoP5);
}
void inicializarCurvas(){
	inicializarBSplineRevol();
	inicializarBezierRevol();
	inicializarCurvasBarridoBSplineBSpline();
	inicializarCurvasBarridoBSplineBezier();
	inicializarCurvasBarridoBezierBezier();
	inicializarCurvasBarridoBezierBSpline();
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
	
	inicializarCurvas();

	// Generación de las Display Lists
	glNewList(DL_AXIS, GL_COMPILE);
		DrawAxis();
	glEndList();
	glNewList(DL_GRID, GL_COMPILE);
		DrawXYGrid();
	glEndList();
	glNewList(DL_AXIS2D_TOP, GL_COMPILE);
		DrawAxis2DTopView();
	glEndList();

	//Curvas de las superficies de revolución
	glNewList(DL_BSPLINE_REVOL, GL_COMPILE);
		delineador->delinear(bsplineRevol, 30);
	glEndList();
	glNewList(DL_PUNTOS_BSPLINE_REVOL, GL_COMPILE);
		dibujarPuntosDeControl(bsplineRevol);
	glEndList();
 	glNewList(DL_BEZIER_REVOL, GL_COMPILE);
		delineador->delinear(bezierRevol, 30);
	glEndList();
	glNewList(DL_PUNTOS_BEZIER_REVOL, GL_COMPILE);
		dibujarPuntosDeControl(bezierRevol);
	glEndList();
	
	//Curvas de las superficies de barrido
	glNewList(DL_CURVAS_BARRIDO_BSPLINE_BSPLINE, GL_COMPILE);
		delineador->delinear(bsplineBarridoBorde1, 30);
		delineador->delinear(bsplineBarridoCamino1, 30);
	glEndList();
	glNewList(DL_PUNTOS_CURVAS_BARRIDO_BSPLINE_BSPLINE, GL_COMPILE);
		dibujarPuntosDeControl(bsplineBarridoBorde1);
		dibujarPuntosDeControl(bsplineBarridoCamino1);
	glEndList();

	glNewList(DL_CURVAS_BARRIDO_BSPLINE_BEZIER, GL_COMPILE);
		delineador->delinear(bsplineBarridoBorde2, 30);
		delineador->delinear(bezierBarridoCamino2, 30);
	glEndList();
	glNewList(DL_PUNTOS_CURVAS_BARRIDO_BSPLINE_BEZIER, GL_COMPILE);
		dibujarPuntosDeControl(bsplineBarridoBorde2);
		dibujarPuntosDeControl(bezierBarridoCamino2);
	glEndList();

	glNewList(DL_CURVAS_BARRIDO_BEZIER_BEZIER, GL_COMPILE);
		delineador->delinear(bezierBarridoBorde3, 30);
		delineador->delinear(bezierBarridoCamino3, 30);
	glEndList();
	glNewList(DL_PUNTOS_CURVAS_BARRIDO_BEZIER_BEZIER, GL_COMPILE);
		dibujarPuntosDeControl(bezierBarridoBorde3);
		dibujarPuntosDeControl(bezierBarridoCamino3);
	glEndList();

	glNewList(DL_CURVAS_BARRIDO_BEZIER_BSPLINE, GL_COMPILE);
		delineador->delinear(bezierBarridoBorde4, 30);
		delineador->delinear(bsplineBarridoCamino4, 30);
	glEndList();
	glNewList(DL_PUNTOS_CURVAS_BARRIDO_BEZIER_BSPLINE, GL_COMPILE);
		dibujarPuntosDeControl(bezierBarridoBorde4);
		dibujarPuntosDeControl(bsplineBarridoCamino4);
	glEndList();
}



void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	///////////////////////////////////////////////////
	// Escena 3D
	Set3DEnv();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt (eye[0], eye[1], eye[2], at[0], at[1], at[2], up[0], up[1], up[2]);
   
	if (view_axis)
		 glCallList(DL_AXIS);
	
	if (view_grid)
		 glCallList(DL_GRID);
	//
	///////////////////////////////////////////////////

    ///////////////////////////////////////////////////
	//
	// Draw here
	//
	if (verCurvas)
		glCallList(DL_CURVA_SELECCIONADA);
	if (verPuntos)
		glCallList(DL_CURVA_SELECCIONADA+1);
	
	

	//
	///////////////////////////////////////////////////


	///////////////////////////////////////////////////
	// Panel 2D para la vista superior
	if (edit_panel)
	{
		SetPanelTopEnv();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt (0, 0, 0.5, 0, 0, 0, 0, 1, 0);
		glCallList(DL_AXIS2D_TOP);
	}
	//
	///////////////////////////////////////////////////
	
	

	glutSwapBuffers();
}

void reshape (int w, int h)
{
   	W_WIDTH  = (float)w;
	W_HEIGHT = (float)h;
}

void keyboard (unsigned char key, int x, int y)
{
	key	= tolower(key);
   switch (key) {
      case 'q':
         exit(0);
         break;

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

	  case 'p':
		  verPuntos = !verPuntos; break;
	  case 'o':
		  verCurvas = !verCurvas; break;

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
	  case '4':
		  DL_CURVA_SELECCIONADA = DL_BSPLINE_REVOL; break;
	  case '5':
		  DL_CURVA_SELECCIONADA = DL_BEZIER_REVOL; break;
  	  case '6':
		  DL_CURVA_SELECCIONADA = DL_CURVAS_BARRIDO_BSPLINE_BSPLINE; break;
  	  case '7':
		  DL_CURVA_SELECCIONADA = DL_CURVAS_BARRIDO_BSPLINE_BEZIER; break;
  	  case '8':
		  DL_CURVA_SELECCIONADA = DL_CURVAS_BARRIDO_BEZIER_BEZIER; break;
  	  case '9':
		  DL_CURVA_SELECCIONADA = DL_CURVAS_BARRIDO_BEZIER_BSPLINE; break;
     default:
         break;
   }
}


int xOrigen, yOrigen;
void mouse(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_UP) {
			xOrigen = -1;
			yOrigen = -1;
		}
		else  {
			xOrigen = x;
			yOrigen = y;
		}
	}
}

void mouseEnMovimiento(int x, int y){
	if (xOrigen >= 0) {
		difAnguloX = xOrigen - x;
		xOrigen = x;
	}
	if (yOrigen >= 0){
		difAnguloY = y - yOrigen;
		yOrigen = y;
	}
	
	anguloTheta += (0.005* difAnguloX);
	anguloPhi += (0.005 * difAnguloY);
	redimensionar();
}

void rueditaDelMouse(int button, int dir, int x, int y){
	if (dir == 0) return;
	
	if (dir > 0){
		if(RadioEsfera-deltaRadio>0){
			RadioEsfera-=deltaRadio;
			redimensionarRadio();
        }
	}
    else{
		RadioEsfera+=deltaRadio;
        redimensionarRadio();
    }

	glutPostRedisplay();
}

void ejecutarTests(){
	cout << "Hello world!" << endl;
    TestBaseBSpline testBase;
    TestBSpline testCurva;
    TestBaseBerstein testBBerstein;
    TestBezier testCurvaBezier;

    testBase.iniciar();
    testCurva.iniciar();

    testBBerstein.iniciar();
    testCurvaBezier.iniciar();
}

int main(int argc, char** argv)
{
    ejecutarTests();
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (800, 640); 
	glutInitWindowPosition (0, 0);
   
	glutCreateWindow (argv[0]);
	//glutFullScreen();
	init ();
	glutDisplayFunc(display); 
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
   	glutMouseFunc(mouse);
	glutMotionFunc(mouseEnMovimiento);
	glutMouseWheelFunc(rueditaDelMouse);
	glutIdleFunc(OnIdle);
	glutMainLoop();
	return 0;
}
