///
/// 66.71 Sistemas Graficos
/// Framework de trabajo para el TP1
/// 2do Cuatrimestre 2011
///
/// info@sg6671.com.ar
///

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>
#include "SuperficieDeRevolucion.h"
#include "SuperficieDeBarrido.h"
#include "..\Curvas\BSpline.h"
#include "..\Curvas\Bezier.h"
#include "Emparchador.h"


// Variables asociadas a única fuente de luz de la escena
float light_color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
float light_position[3] = {10.0f, 10.0f, 8.0f};
float light_ambient[4] = {0.05f, 0.05f, 0.05f, 1.0f};


// Variables de control
bool view_grid = true;
bool view_axis = true;
bool edit_panel = false;
bool verSuperficie = true;
bool verNormales = true;

//Superficies, como variables globales
Superficie* superficieSeleccionada;
SuperficieDeRevolucion* pruebaRevolucionConBSpline;
SuperficieDeRevolucion* pruebaRevolucionConBezier;
SuperficieDeBarrido* pruebaBarridoConBSplineBSpline;
SuperficieDeBarrido* pruebaBarridoConBSplineBezier;
SuperficieDeBarrido* pruebaBarridoConBezierBezier;
SuperficieDeBarrido* pruebaBarridoConBezierBSpline;

// Handle para el control de las Display Lists
GLuint dl_handle;
#define DL_AXIS (dl_handle+0)
#define DL_GRID (dl_handle+1)
#define DL_AXIS2D_TOP (dl_handle+2)
#define DL_VER_SUPERFICIE_REVOL_BSPLINE (dl_handle+3)
#define DL_VER_NORMALES_REVOL_BSPLINE (dl_handle+4)
#define DL_VER_SUPERFICIE_REVOL_BEZIER (dl_handle+5)
#define DL_VER_NORMALES_REVOL_BEZIER (dl_handle+6)
#define DL_VER_SUPERFICIE_BARRIDO_BSPLINE_BSPLINE (dl_handle+7)
#define DL_VER_NORMALES_BARRIDO_BSPLINE_BSPLINE (dl_handle+8)
#define DL_VER_SUPERFICIE_BARRIDO_BSPLINE_BEZIER (dl_handle+9)
#define DL_VER_NORMALES_BARRIDO_BSPLINE_BEZIER (dl_handle+10)
#define DL_VER_SUPERFICIE_BARRIDO_BEZIER_BEZIER (dl_handle+11)
#define DL_VER_NORMALES_BARRIDO_BEZIER_BEZIER (dl_handle+12)
#define DL_VER_SUPERFICIE_BARRIDO_BEZIER_BSPLINE (dl_handle+13)
#define DL_VER_NORMALES_BARRIDO_BEZIER_BSPLINE (dl_handle+14)
GLuint DL_SUP_SELECCIONADA;

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
void inicializarSupRevolucionConBSpline(){
	vec3 bsplineP1 = vec3(3.0, 0.0, 0.0); 
	vec3 bsplineP2 = vec3(3.0, 0.0, 3.0);
	vec3 bsplineP3 = vec3(1.0, 0.0, 4.0);
	vec3 bsplineP4 = vec3(4.0, 0.0, 5.0);
	vec3 bsplineP5 = vec3(2.0, 0.0, 6.0);
	BSpline* bsplinePrueba = new BSpline(5);
	bsplinePrueba->incluirPunto(bsplineP1);
	bsplinePrueba->incluirPunto(bsplineP2);
	bsplinePrueba->incluirPunto(bsplineP3);
	bsplinePrueba->incluirPunto(bsplineP4);
	bsplinePrueba->incluirPunto(bsplineP5);
	pruebaRevolucionConBSpline = new SuperficieDeRevolucion(bsplinePrueba, 180);
	pruebaRevolucionConBSpline->discretizar(30, 36);
	DL_SUP_SELECCIONADA = DL_VER_SUPERFICIE_REVOL_BSPLINE;
}
void inicializarSupRevolucionConBezier(){
	vec3 bezierP1 = vec3(3.0, 0.0, 0.0); 
	vec3 bezierP2 = vec3(3.0, 0.0, 3.0);
	vec3 bezierP3 = vec3(1.0, 0.0, 2.0);
	vec3 bezierP4 = vec3(4.0, 0.0, 3.0);
	Bezier* bezierPrueba = new Bezier(1);
	bezierPrueba->incluirPunto(bezierP1);
	bezierPrueba->incluirPunto(bezierP2);
	bezierPrueba->incluirPunto(bezierP3);
	bezierPrueba->incluirPunto(bezierP4);
	pruebaRevolucionConBezier = new SuperficieDeRevolucion(bezierPrueba, 70);
	pruebaRevolucionConBezier->discretizar(30, 36);
}
void inicializarSupBarridoConBSplineBSpline(){
	//Curva borde
	vec3 bordeP1 = vec3(3.0, 0.0, 0.0); 
	vec3 bordeP2 = vec3(3.0, 0.0, 3.0);
	vec3 bordeP3 = vec3(1.0, 0.0, 4.0);
	vec3 bordeP4 = vec3(4.0, 0.0, 5.0);
	vec3 bordeP5 = vec3(2.0, 0.0, 6.0);
	BSpline* borde = new BSpline(5);
	borde->incluirPunto(bordeP1);
	borde->incluirPunto(bordeP2);
	borde->incluirPunto(bordeP3);
	borde->incluirPunto(bordeP4);
	borde->incluirPunto(bordeP5);
	//Curva camino
	vec3 caminoP1 = vec3(2.0, 0.0, 6.0);
	vec3 caminoP2 = vec3(3.0, 3.0, 6.0);
	vec3 caminoP3 = vec3(3.0, 4.0, 4.0);
	vec3 caminoP4 = vec3(4.0, 6.0, 5.0);
	BSpline* camino = new BSpline(4);
	camino->incluirPunto(caminoP1);
	camino->incluirPunto(caminoP2);
	camino->incluirPunto(caminoP3);
	camino->incluirPunto(caminoP4);
	pruebaBarridoConBSplineBSpline = new SuperficieDeBarrido(borde, camino);
	pruebaBarridoConBSplineBSpline->discretizar(30, 30);
}
void inicializarSupBarridoConBSplineBezier(){

}
void inicializarSupBarridoConBezierBezier(){

}
void inicializarSupBarridoConBezierBSpline(){

}
void inicializarSuperficies(){
	inicializarSupRevolucionConBSpline();
	inicializarSupRevolucionConBezier();
	inicializarSupBarridoConBSplineBSpline();
	inicializarSupBarridoConBSplineBezier();
	inicializarSupBarridoConBezierBezier();
	inicializarSupBarridoConBezierBSpline();

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

	inicializarSuperficies();

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


	//Superficies de revolución
	glNewList(DL_VER_SUPERFICIE_REVOL_BSPLINE, GL_COMPILE);
		Emparchador::emparchar(pruebaRevolucionConBSpline);
	glEndList();
	glNewList(DL_VER_NORMALES_REVOL_BSPLINE, GL_COMPILE);
		Emparchador::verNormales(pruebaRevolucionConBSpline);
	glEndList();
	glNewList(DL_VER_SUPERFICIE_REVOL_BEZIER, GL_COMPILE);
		Emparchador::emparchar(pruebaRevolucionConBezier);
	glEndList();
	glNewList(DL_VER_NORMALES_REVOL_BEZIER, GL_COMPILE);
		Emparchador::verNormales(pruebaRevolucionConBezier);
	glEndList();


	//Superficies de barrido
	glNewList(DL_VER_SUPERFICIE_BARRIDO_BSPLINE_BSPLINE, GL_COMPILE);
		Emparchador::emparchar(pruebaBarridoConBSplineBSpline);
	glEndList();
	glNewList(DL_VER_NORMALES_BARRIDO_BSPLINE_BSPLINE, GL_COMPILE);
		Emparchador::verNormales(pruebaBarridoConBSplineBSpline);
	glEndList();
	/*
	glNewList(DL_VER_SUPERFICIE_BARRIDO_BSPLINE_BEZIER, GL_COMPILE);
		Emparchador::emparchar(pruebaBarridoConBSplineBezier);
	glEndList();
	glNewList(DL_VER_NORMALES_BARRIDO_BSPLINE_BEZIER, GL_COMPILE);
		Emparchador::verNormales(pruebaBarridoConBSplineBezier);
	glEndList();

	glNewList(DL_VER_SUPERFICIE_BARRIDO_BEZIER_BEZIER, GL_COMPILE);
		Emparchador::emparchar(pruebaBarridoConBezierBezier);
	glEndList();
	glNewList(DL_VER_NORMALES_BARRIDO_BEZIER_BEZIER, GL_COMPILE);
		Emparchador::verNormales(pruebaBarridoConBezierBezier);
	glEndList();

	glNewList(DL_VER_SUPERFICIE_BARRIDO_BEZIER_BSPLINE, GL_COMPILE);
		Emparchador::emparchar(pruebaBarridoConBezierBSpline);
	glEndList();
	glNewList(DL_VER_NORMALES_BARRIDO_BEZIER_BSPLINE, GL_COMPILE);
		Emparchador::verNormales(pruebaBarridoConBezierBSpline);
	glEndList();
	*/
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

	if (verSuperficie)
		glCallList(DL_SUP_SELECCIONADA);
	if (verNormales)
		glCallList(DL_SUP_SELECCIONADA+1);


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
	key = tolower(key);
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
	  case 'n':
		  verNormales = !verNormales; break;
	  case 'm':
		  verSuperficie = !verSuperficie; break;
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
		  DL_SUP_SELECCIONADA = DL_VER_SUPERFICIE_REVOL_BSPLINE; break;
	  case '5':
		  DL_SUP_SELECCIONADA = DL_VER_SUPERFICIE_REVOL_BEZIER; break;
  	  case '6':
		  DL_SUP_SELECCIONADA = DL_VER_SUPERFICIE_BARRIDO_BSPLINE_BSPLINE; break;
  	  case '7':
		  DL_SUP_SELECCIONADA = DL_VER_SUPERFICIE_BARRIDO_BSPLINE_BEZIER; break;
  	  case '8':
		  DL_SUP_SELECCIONADA = DL_VER_SUPERFICIE_BARRIDO_BEZIER_BEZIER; break;
  	  case '9':
		  DL_SUP_SELECCIONADA = DL_VER_SUPERFICIE_BARRIDO_BEZIER_BSPLINE; break;
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

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (1024, 768); 
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
