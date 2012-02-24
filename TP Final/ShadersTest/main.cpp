#include <iostream>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "..\Superficies\SuperficieDeRevolucion.h"
#include "..\Superficies\SuperficieDeBarrido.h"
#include "..\Curvas\BSpline.h"
#include "..\Curvas\Bezier.h"
#include "..\Superficies\Emparchador.h"
#include "GLSLProgram.h"
#include "TextureLoader.h"
using namespace std;

// Variables asociadas a única fuente de luz de la escena
bool luzPrendida = false;
vec4 luzPosicion = vec4(-3.0, -3.0, 5.0, 1.0);
vec3 luzAmb = vec3(0.1, 0.1, 0.1);
vec3 luzDif = vec3(0.9, 0.9, 0.9);
vec3 luzEspec = vec3(1.0, 1.0, 1.0);

TextureLoader* texLoader = new TextureLoader();

Bezier* perfilBotella;
SuperficieDeRevolucion* superficieBotella;
GLSLProgram* GLSLBotella;
glTexture etiquetaCoca;
glTexture tapaCoca;
bool tieneEtiqueta = false;
bool tieneTapa = false;
float porcentajeDeLlenado = 0.0;


BSpline* formaCintaTransportadora;
BSpline* caminoCintaTransportadora;
SuperficieDeBarrido* superficieCintaTransportadora;
GLSLProgram* GLSLCintaTransportadora;
glTexture cintaTransportadora;

// Variables de control
bool view_grid = true;
bool view_axis = true;
bool edit_panel = false;
bool verBotella = true;
bool verCintaTransportadora = false;
bool actualizar = false;

// Handle para el control de las Display Lists
GLuint dl_handle;
#define DL_AXIS (dl_handle+0)
#define DL_GRID (dl_handle+1)
#define DL_AXIS2D_TOP (dl_handle+2)

#define DL_BOTELLA (dl_handle+3)
#define DL_CINTA_TRANSPORTADORA (dl_handle+4)

GLuint DL_SELECCIONADA;

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


void inicializarSuperficieBotella(){
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
	perfilBotella = new Bezier(4);
	perfilBotella->incluirPunto(bezierP1);
	perfilBotella->incluirPunto(bezierP2);
	perfilBotella->incluirPunto(bezierP3);
	perfilBotella->incluirPunto(bezierP4);
	perfilBotella->incluirPunto(bezierP5);
	perfilBotella->incluirPunto(bezierP6);
	perfilBotella->incluirPunto(bezierP7);
	perfilBotella->incluirPunto(bezierP8);
	perfilBotella->incluirPunto(bezierP9);
	perfilBotella->incluirPunto(bezierP10);
	perfilBotella->incluirPunto(bezierP11);
	perfilBotella->incluirPunto(bezierP12);
	perfilBotella->incluirPunto(bezierP13);
	superficieBotella = new SuperficieDeRevolucion(perfilBotella);
	superficieBotella->discretizar(10, 36);
}
void inicializarSuperficieCintaTransportadora(){
	//Curva borde
	vec3 bordeP1 = vec3(6.5, 0.0, 2.5); 
	vec3 bordeP2 = vec3(6.0, 0.0, 2.0);
	vec3 bordeP3 = vec3(6.0, 0.0, 2.0);
	vec3 bordeP4 = vec3(5.5, 0.0, 2.0);
	vec3 bordeP5 = vec3(5.0, 0.0, 2.0); 
	vec3 bordeP6 = vec3(5.0, 0.0, 2.0);
	vec3 bordeP7 = vec3(4.5, 0.0, 2.5);
	formaCintaTransportadora = new BSpline(7);
	formaCintaTransportadora->incluirPunto(bordeP1);
	formaCintaTransportadora->incluirPunto(bordeP2);
	formaCintaTransportadora->incluirPunto(bordeP3);
	formaCintaTransportadora->incluirPunto(bordeP4);
	formaCintaTransportadora->incluirPunto(bordeP5);
	formaCintaTransportadora->incluirPunto(bordeP6);
	formaCintaTransportadora->incluirPunto(bordeP7);
	//Curva camino
	vec3 caminoP1 = vec3(5.5, -1.5, 2.0);
	vec3 caminoP2 = vec3(5.5, 1.5, 2.0);
	vec3 caminoP3 = vec3(5.5, 4.5, 2.0);
	vec3 caminoP4 = vec3(2.5, 4.5, 2.0);
	vec3 caminoP5 = vec3(-0.5, 4.5, 2.0);
	vec3 caminoP6 = vec3(-0.5, 7.5, 2.0);
	vec3 caminoP7 = vec3(-0.5, 10.5, 2.0);
	vec3 caminoP8 = vec3(-0.5, 13.5, 2.0);
	caminoCintaTransportadora = new BSpline(8);
	caminoCintaTransportadora->incluirPunto(caminoP1);
	caminoCintaTransportadora->incluirPunto(caminoP2);
	caminoCintaTransportadora->incluirPunto(caminoP3);
	caminoCintaTransportadora->incluirPunto(caminoP4);
	caminoCintaTransportadora->incluirPunto(caminoP5);
	caminoCintaTransportadora->incluirPunto(caminoP6);
	caminoCintaTransportadora->incluirPunto(caminoP7);
	caminoCintaTransportadora->incluirPunto(caminoP8);
	superficieCintaTransportadora = new SuperficieDeBarrido(formaCintaTransportadora, caminoCintaTransportadora);
	superficieCintaTransportadora->discretizar(5, 10);
}
void inicializarSupeficies(){
	//Superficies
	inicializarSuperficieBotella();
	inicializarSuperficieCintaTransportadora();
	
}
void inicializarGLSL(){
	GLSLBotella = new GLSLProgram("botella.vert", "botella.frag");
	GLSLCintaTransportadora = new GLSLProgram("cintaTransportadora.vert", "cintaTransportadora.frag");
}
void incializarTexturas(){
	texLoader->SetMipMapping(true);
	texLoader->LoadTextureFromDisk("etiquetaCoca.bmp", &etiquetaCoca);
	texLoader->LoadTextureFromDisk("tapaCoca.bmp", &tapaCoca);
	texLoader->LoadTextureFromDisk("cintaTransportadora.bmp", &cintaTransportadora);
}

void dibujarBotella(){
	glDisable(GL_LIGHTING);
	//glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if (actualizar){
		delete GLSLBotella;
		GLSLBotella = new GLSLProgram("botella.vert", "botella.frag");
		actualizar = false;
	}
	
	if (!GLSLBotella->isLinked())
		GLSLBotella->link();
	GLSLBotella->usar();
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, etiquetaCoca.TextureID);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tapaCoca.TextureID);
	
	GLSLBotella->setUniform("etiquetaText", 0);
	GLSLBotella->setUniform("tapaText", 1);
	GLSLBotella->setUniform("porcentajeDeLlenado", porcentajeDeLlenado);
	GLSLBotella->setUniform("tieneEtiqueta", tieneEtiqueta);
	GLSLBotella->setUniform("tieneTapa", tieneTapa);
	GLSLBotella->setUniform("luzPrendida", luzPrendida);
	GLSLBotella->setUniform("luz.posicion", luzPosicion);
	GLSLBotella->setUniform("luz.amb", luzAmb);
	GLSLBotella->setUniform("luz.dif", luzDif);
	GLSLBotella->setUniform("luz.espec", luzEspec);

	Emparchador::emparchar(superficieBotella);

	GLSLBotella->cerrar();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	//glDepthMask(GL_TRUE);
}

void dibujarCintaTransportadora(){
	glDisable(GL_LIGHTING);

	if (actualizar){
		delete GLSLCintaTransportadora;
		GLSLCintaTransportadora = new GLSLProgram("cintaTransportadora.vert", "cintaTransportadora.frag");
		actualizar = false;
	}
	
	if (!GLSLCintaTransportadora->isLinked())
		GLSLCintaTransportadora->link();
	GLSLCintaTransportadora->usar();
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, cintaTransportadora.TextureID);
	
	GLSLCintaTransportadora->setUniform("cintaText", 0);
	GLSLCintaTransportadora->setUniform("luzPrendida", luzPrendida);
	GLSLCintaTransportadora->setUniform("luz.posicion", luzPosicion);
	GLSLCintaTransportadora->setUniform("luz.amb", luzAmb);
	GLSLCintaTransportadora->setUniform("luz.dif", luzDif);
	GLSLCintaTransportadora->setUniform("luz.espec", luzEspec);

	Emparchador::emparchar(superficieCintaTransportadora, 14 );

	GLSLCintaTransportadora->cerrar();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}
void init(void) 
{
	dl_handle = glGenLists(3);

	glClearColor (0.02f, 0.02f, 0.04f, 0.0f);
    glShadeModel (GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
	
	inicializarSupeficies();
	inicializarGLSL();
	incializarTexturas();

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
	if (verBotella)
		dibujarBotella();
	if (verCintaTransportadora)
		dibujarCintaTransportadora();
	

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
	  case 'n':
		  tieneEtiqueta = !tieneEtiqueta; break;
	  case 'm':
		  tieneTapa = !tieneTapa; break;
	  case 'b':
		  luzPrendida = !luzPrendida; break;
	  case '+':
		  porcentajeDeLlenado += 0.05; break;
	  case '-':
		  porcentajeDeLlenado -= 0.05; break;
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
		  verBotella = true;
		  verCintaTransportadora = false; break;
	  case '5':
		  verBotella = false;
		  verCintaTransportadora = true; break;
     default:
         break;
   }
}

void teclasParticulares(int key, int x, int y){
	switch(key) {
		case GLUT_KEY_F5 :
			actualizar = true;
			break;
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
	glewInit();
	init ();
	glutDisplayFunc(display); 
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(teclasParticulares);
   	glutMouseFunc(mouse);
	glutMotionFunc(mouseEnMovimiento);
	glutMouseWheelFunc(rueditaDelMouse);
	glutIdleFunc(OnIdle);
	glutMainLoop();
	return 0;
}
