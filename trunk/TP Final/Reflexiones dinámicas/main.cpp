///
/// 66.71 Sistemas Graficos
/// Framework de trabajo para el TP
/// 2do Cuatrimestre 2011
///
/// info@sg6671.com.ar
///
#pragma comment (lib, "glew32.lib")
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>
#include "GLSLProgram.h"
#include "SOIL\SOIL.h"
#include <iostream>
#include <sstream>

//Para los FPS. Idea tomada del código de Ali BaderEddin
int frames = 0; //Número de frames contados
float fpsAcumulados = 0; //Para sacar un promedio al final
int segundos = 0;
float fps = 0;
int tiempoActual = 0, tiempoAnterior = 0; //Para calcular el tiempo que pasó entre un frame y el siguiente

// Variables asociadas a única fuente de luz de la escena
struct propLuz{
	vec4 posicion;
	vec3 amb;
	vec3 dif;
	vec3 espec;
	bool prendida;
};

propLuz luz = { 
	vec4(-3.0, -3.0, 5.0, 1.0), 
	vec3(0.1, 0.1, 0.1), 
	vec3(0.9, 0.9, 0.9),
	vec3(1.0, 1.0, 1.0),
	false
};

struct propMaterial{
	vec3 colorAmb;
	vec3 colorDif;
	vec3 colorEspec;
	float brillo;
};


// Variables de control
bool view_grid = true;
bool view_axis = true;
bool edit_panel = false;
bool actualizar = false;
bool verEsfera = false;
bool verXPos = false;
bool verXNeg = false;
bool verYPos = false;
bool verYNeg = false;
bool verZPos = false;
bool verZNeg = false;


GLSLProgram* GLSLTanqueDeCoca;
GLuint skybox;

// Handle para el control de las Display Lists
GLuint dl_handle;
#define DL_AXIS (dl_handle+0)
#define DL_GRID (dl_handle+1)
#define DL_AXIS2D_TOP (dl_handle+2)
#define DL_REFERENCIA (dl_handle+3)
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
void calcularFPS(){
    frames++;

    tiempoActual = glutGet(GLUT_ELAPSED_TIME);

    int deltaTiempo = tiempoActual - tiempoAnterior;

    if(deltaTiempo > 1000){ //Pasó un segundo
        fps = frames / (deltaTiempo / 1000.0f);
        tiempoAnterior = tiempoActual;
        frames = 0;
		cout << "FPS: " << fps << endl;
		fpsAcumulados += fps;
		segundos++;
    }
}
void OnIdle (void)
{	
	calcularFPS();
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
void inicializarGLSL(){
	GLSLTanqueDeCoca = new GLSLProgram("tanqueDeCoca.vert", "tanqueDeCoca.frag");
}
void inicializarTexturas(){
	glGenTextures(1, &skybox);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox);
	for (int i=0;i<6;++i)
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	GLclampf prioridad = 1.0;
	glPrioritizeTextures(1, &skybox, &prioridad);
}

void setearLucesUniform(GLSLProgram* GLSLenUso = GLSLTanqueDeCoca){
	GLSLenUso->setUniform("luz.prendida", luz.prendida);
	GLSLenUso->setUniform("luz.posicion", luz.posicion);
	GLSLenUso->setUniform("luz.amb", luz.amb);
	GLSLenUso->setUniform("luz.dif", luz.dif);
	GLSLenUso->setUniform("luz.espec", luz.espec);
}
void setearMaterial(propMaterial material, GLSLProgram* GLSLenUso = GLSLTanqueDeCoca){
	GLSLenUso->setUniform("material.colorAmb", material.colorAmb);
	GLSLenUso->setUniform("material.colorDif", material.colorDif);
	GLSLenUso->setUniform("material.colorEspec", material.colorEspec);
	GLSLenUso->setUniform("material.brillo", material.brillo);
}
void dibujarReferencias(){
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix(); //Plano rojo en la cara X+
		glTranslatef(15.0, 0.0, 0.0);
		glColor3f(1.0, 0.0, 0.0);
		glCallList(DL_REFERENCIA);
	glPopMatrix();
	glPushMatrix(); //Plano verde en la cara X-
		glTranslatef(-15.0, 0.0, 0.0);
		glColor3f(0.0, 1.0, 0.0);
		glCallList(DL_REFERENCIA);
	glPopMatrix();
	glPushMatrix(); //Plano azul en la cara Y+
		glTranslatef(0.0, 15.0, 0.0);
		glRotatef(90, 0.0, 0.0, 1.0);
		glColor3f(0.0, 0.0, 1.0);
		glCallList(DL_REFERENCIA);
	glPopMatrix();
	glPushMatrix(); //Plano celeste en la cara Y-
		glTranslatef(0.0, -15.0, 0.0);
		glRotatef(90, 0.0, 0.0, 1.0);		
		glColor3f(0.0, 1.0, 1.0);
		glCallList(DL_REFERENCIA);
	glPopMatrix();
	glPushMatrix(); //Plano violeta en la cara Z+
		glTranslatef(0.0, 0.0, 15.0);
		glRotatef(90, 0.0, 1.0, 0.0);
		glColor3f(1.0, 0.0, 1.0);
		glCallList(DL_REFERENCIA);
	glPopMatrix();
	glPushMatrix(); //Plano amarillo en la cara Z-
		glTranslatef(0.0, 0.0, -15.0);
		glRotatef(90, 0.0, 1.0, 0.0);		
		glColor3f(1.0, 1.0, 0.0);
		glCallList(DL_REFERENCIA);
	glPopMatrix();
}
void actualizarReflexion(){
	float CubeMapRots[6][4] = {			
		{	-90.0f,		0.0f,	1.0f,	0.0f	},
		{	90.0f,		0.0f,	1.0f,	0.0f	},

		{	-90.0f,		1.0f,	0.0f,	0.0f	},
		{	90.0f,		1.0f,	0.0f,	0.0f	},

		{	180.0f,		1.0f,	0.0f,	0.0f	},
		{	180.0f,		0.0f,	0.0f,	1.0f	},
	};

	int origenXY[6][2] = {
		{	(W_HEIGHT - 256)/2,	(W_WIDTH - 256)/2},
		{	(W_WIDTH - 256)/2,		(W_HEIGHT - 256)/2},

		{	-90,	0},
		{	90,		0},

		{	-90,	0},
		{	90,		0},
	};
	
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

	int origenX = (W_WIDTH - 256)/2;
	int origenY = (W_HEIGHT - 256)/2;
	glEnable(GL_SCISSOR_TEST); 
	glViewport(origenX, origenY, 256, 256);//glViewport(0, 0, W_WIDTH, W_HEIGHT);
	glScissor(origenX, origenY, 256, 256);

	gluPerspective (90, 1.0f, 1, 5000);

	glMatrixMode(GL_MODELVIEW);
	
	glClearColor (1.0, 0.0, 0.0, 1.0f);	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glScissor(origenX+1, origenY+1, 256-2, 256-2);
	glClearColor (0.1, 0.1, 0.1, 1.0f);
	
	for(GLuint i = 0; i < 6; i++){
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		glRotatef(CubeMapRots[i][0], CubeMapRots[i][1], CubeMapRots[i][2], CubeMapRots[i][3]);
		if(i == 0  ||  i == 1)		glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
		dibujarReferencias();
		glBindTexture(GL_TEXTURE_CUBE_MAP, skybox); 
		glCopyTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0, 0, 0, origenX, origenY, 256, 256);
		glFlush();
	}
	glClearColor (0.0, 0.0, 0.0, 1.0f);
	glDisable(GL_SCISSOR_TEST);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, W_WIDTH, W_HEIGHT);

}
void dibujarMaterialReflectivo(){
	glDisable(GL_LIGHTING);
	

	if (actualizar){
		delete GLSLTanqueDeCoca;
		GLSLTanqueDeCoca = new GLSLProgram("tanqueDeCoca.vert", "tanqueDeCoca.frag");
		actualizar = false;
	}
	
	if (!GLSLTanqueDeCoca->isLinked())
		GLSLTanqueDeCoca->link();
	GLSLTanqueDeCoca->usar();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox);
	propMaterial tanque = {
		vec3(0.44, 0.57, 0.75),
		vec3(0.44, 0.57, 0.75),
		vec3(0.1, 0.15, 0.2),
		32.0
	};
	setearMaterial(tanque, GLSLTanqueDeCoca);
	setearLucesUniform(GLSLTanqueDeCoca);
	GLSLTanqueDeCoca->setUniform("skyBoxTex", 0);
	GLSLTanqueDeCoca->setUniform("posicionDelOjo", vec3(eye[0], eye[1], eye[2]));

	if (verEsfera)
		glutSolidSphere(5.0, 50, 50);
	else
		glutSolidCube(5.0);

	GLSLTanqueDeCoca->cerrar();
}
void verCaraI(int i){
	float CubeMapRots[6][4] = {			
		{	-90.0f,		0.0f,	1.0f,	0.0f	},
		{	90.0f,		0.0f,	1.0f,	0.0f	},

		{	-90.0f,		1.0f,	0.0f,	0.0f	},
		{	90.0f,		1.0f,	0.0f,	0.0f	},

		{	180.0f,		1.0f,	0.0f,	0.0f	},
		{	180.0f,		0.0f,	0.0f,	1.0f	},
	};
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);		
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

	glEnable(GL_SCISSOR_TEST); 
	int origenX = (W_WIDTH - 256)/2;
	int origenY = (W_HEIGHT - 256)/2;
	glViewport(origenX, origenY, 256, 256);
	glScissor(origenX, origenY, 256, 256);
	/*glViewport(0, 0, 256, 256);
	glScissor(0, 0, 256, 256);*/
	gluPerspective (90, 1.0f, 1, 5000);

	glMatrixMode(GL_MODELVIEW);
	
	glClearColor (1.0, 0.0, 0.0, 1.0f);	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glScissor(origenX+1, origenY+1, 256-2, 256-2);
	glClearColor (0.1, 0.1, 0.1, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(CubeMapRots[i][0], CubeMapRots[i][1], CubeMapRots[i][2], CubeMapRots[i][3]);
	if(i == 0  ||  i == 1)		glRotatef(180.0f, 0.0f, 0.0f, 1.0f); 
	dibujarReferencias();
	glFlush();
	glClearColor (0.0, 0.0, 0.0, 1.0f);
	glDisable(GL_SCISSOR_TEST);
}
void init(void) 
{
	dl_handle = glGenLists(4);

	glClearColor (0.02f, 0.02f, 0.04f, 0.0f);
    glShadeModel (GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	inicializarGLSL();
	inicializarTexturas();
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
	glNewList(DL_REFERENCIA, GL_COMPILE);
		/*glBegin(GL_QUADS);
			glVertex3f(0, -8, -8);
			glVertex3f(0, 8, -8);
			glVertex3f(0, 8, 8);
			glVertex3f(0, -8, 8);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f(0, -8, 0);
			glVertex3f(0, 0, 8);
			glVertex3f(0, 8, 0);
			glVertex3f(0, 0, -4);
		glEnd();*/
		glBegin(GL_TRIANGLES);
			glVertex3f(0, -8, 0);
			glVertex3f(0, 0, 8);
			glVertex3f(0, 8, 0);
		glEnd();
	glEndList();
}


void display(void){
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (!(verXPos || verXNeg || verYPos || verYNeg || verZPos || verZNeg))
		actualizarReflexion();
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
	if (!(verXPos || verXNeg || verYPos || verYNeg || verZPos || verZNeg)){
		dibujarMaterialReflectivo();
		dibujarReferencias();
	}
	else{
		if (verXPos)	verCaraI(0);
		if (verXNeg)	verCaraI(1);
		if (verYPos)	verCaraI(2);
		if (verYNeg)	verCaraI(3);
		if (verZPos)	verCaraI(4);
		if (verZNeg)	verCaraI(5);
	}
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
{	key = tolower(key);
	std::string aux = "FPS promedio: ";
	std::ostringstream oss;
	oss << (fpsAcumulados/segundos);
   switch (key) {
      case 'q':
		  aux.append(oss.str());
		  MessageBox(NULL,aux.c_str(),"FPS Promedio",MB_OK); 
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
	  case '4': verEsfera = !verEsfera; 
				verXPos = false;
				verXNeg = false;
				verYPos = false;
				verYNeg = false;
				verZPos = false;
				verZNeg = false;
				break;
	  case '5':	verXPos = true;
				verXNeg = false;
				verYPos = false;
				verYNeg = false;
				verZPos = false;
				verZNeg = false;
				break;
	  case '6':	verXPos = false;
				verXNeg = true;
				verYPos = false;
				verYNeg = false;
				verZPos = false;
				verZNeg = false;
				break;
	  case '7':	verXPos = false;
				verXNeg = false;
				verYPos = true;
				verYNeg = false;
				verZPos = false;
				verZNeg = false;
				break;
	  case '8':	verXPos = false;
				verXNeg = false;
				verYPos = false;
				verYNeg = true;
				verZPos = false;
				verZNeg = false;
				break;
	  case '9':	verXPos = false;
				verXNeg = false;
				verYPos = false;
				verYNeg = false;
				verZPos = true;
				verZNeg = false;
				break;
	  case '0':	verXPos = false;
				verXNeg = false;
				verYPos = false;
				verYNeg = false;
				verZPos = false;
				verZNeg = true;
				break;
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
	glutInitWindowSize (800, 640); 
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
