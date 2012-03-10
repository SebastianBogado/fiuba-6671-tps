#include <iostream>
#include <stdarg.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "..\Superficies\SuperficieDeRevolucion.h"
#include "..\Superficies\SuperficieDeBarrido.h"
#include "..\Curvas\BSpline.h"
#include "..\Curvas\Bezier.h"
#include "..\Curvas\Circunferencia.h"
#include "..\Superficies\Emparchador.h"
#include "GLSLProgram.h"
#include "TextureLoader.h"
#include "SOIL\SOIL.h"
#include "..\TP\propMaterial.h"
using namespace std;

//Para los FPS. Idea tomada del código de Ali BaderEddin
int frames = 0; //Número de frames contados
float fps = 0;
int tiempoActual = 0, tiempoAnterior = 0; //Para calcular el tiempo que pasó entre un frame y el siguiente

struct propLuz{
	bool prendida;
	vec4 posicion;
	vec4 direccion;
	float angulo;
	//Constante para calcular el decrecimiento de la intensidad de la luz
	//según se aleja del centro, como el brillo en un material
	float k; 
	vec3 amb;
	vec3 dif;
	vec3 espec;
};

const int cantidadDeLuces = 6;
propLuz luces[cantidadDeLuces];

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
float desplazamientoDeCinta = 0.0;


BSpline* perfilTanqueDeCoca;
SuperficieDeRevolucion* superficieTanqueDeCoca;
BSpline* caminoTuboDelTanqueDeCoca;
SuperficieDeBarrido * superficieTuboDelTanqueDeCoca;
GLSLProgram* GLSLTanqueDeCoca;
GLuint skyBox;
glTexture skyBoxPosX, skyBoxNegX, skyBoxPosY, skyBoxNegY, skyBoxPosZ, skyBoxNegZ;

GLSLProgram* GLSLPhongSpot; //Estos shaders son para los materiales que solamente son iluminados, sin textura ni alguna particularidad.

// Variables de control
bool view_grid = true;
bool view_axis = true;
bool edit_panel = false;
bool verBotella = false;
bool verCintaTransportadora = false;
bool verTanqueDeCoca = false;
bool verPruebaSpot = true;
bool actualizar = false;
float tiempo = 0.0;
bool avanzarEnElTiempo = true;

// Handle para el control de las Display Lists
GLuint dl_handle;
#define DL_AXIS (dl_handle+0)
#define DL_GRID (dl_handle+1)
#define DL_AXIS2D_TOP (dl_handle+2)

#define DL_BOTELLA (dl_handle+3)
#define DL_CINTA_TRANSPORTADORA (dl_handle+4)
#define DL_TANQUE_DE_COCA (dl_handle+5)
#define DL_TUBO_DEL_TANQUE_DE_COCA (dl_handle+6)

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
void calcularFPS(){
    frames++;

    tiempoActual = glutGet(GLUT_ELAPSED_TIME);

    int deltaTiempo = tiempoActual - tiempoAnterior;

    if(deltaTiempo > 1000){ //Pasó un segundo
        fps = frames / (deltaTiempo / 1000.0f);
        tiempoAnterior = tiempoActual;
        frames = 0;
		cout << "FPS: " << fps << endl;
    }
}
void OnIdle (void)
{	
	calcularFPS();

	desplazamientoDeCinta +=  0.01;

	if ( desplazamientoDeCinta > 20.0)
		desplazamientoDeCinta = 0.0;
	if (avanzarEnElTiempo)
		tiempo += 0.05;
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
}
void inicializarSuperficieTanqueDeCoca(){
	//Cuerpo del tanque
	vec3 bsplineP1 = vec3(-1.0, 0.0, 1.0); 
	vec3 bsplineP2 = vec3(1.0, 0.0, 1.0);
	vec3 bsplineP3 = vec3(1.0, 0.0, 2.5);
	vec3 bsplineP4 = vec3(1.0, 0.0, 4.0); 
	vec3 bsplineP5 = vec3(-1.0, 0.0, 4.0);
	BSpline* perfilTanqueDeCoca = new BSpline(5);
	perfilTanqueDeCoca->incluirPunto(bsplineP1);
	perfilTanqueDeCoca->incluirPunto(bsplineP2);
	perfilTanqueDeCoca->incluirPunto(bsplineP3);
	perfilTanqueDeCoca->incluirPunto(bsplineP4);
	perfilTanqueDeCoca->incluirPunto(bsplineP5);
	superficieTanqueDeCoca = new SuperficieDeRevolucion(perfilTanqueDeCoca);
	
	//Tubito que llena las botellas
	//Curva borde
	Circunferencia* borde = new Circunferencia(0.1, vec3(0.0, 0.0, 4.5));
	//Curva camino
	vec3 caminoP1 = vec3( 0.0,  -0.25, 4.5);
	vec3 caminoP2 = vec3( 0.0,   0.25, 4.5);
	vec3 caminoP3 = vec3( 0.0,   1.0, 4.5);
	vec3 caminoP4 = vec3( 0.0,   1.5, 4.5);
	vec3 caminoP5 = vec3( 0.0,  1.75, 4.25);
	vec3 caminoP6 = vec3( 0.0,  1.75, 4.0);
	caminoTuboDelTanqueDeCoca = new BSpline(6);
	caminoTuboDelTanqueDeCoca->incluirPunto(caminoP1);
	caminoTuboDelTanqueDeCoca->incluirPunto(caminoP2);
	caminoTuboDelTanqueDeCoca->incluirPunto(caminoP3);
	caminoTuboDelTanqueDeCoca->incluirPunto(caminoP4);
	caminoTuboDelTanqueDeCoca->incluirPunto(caminoP5);
	caminoTuboDelTanqueDeCoca->incluirPunto(caminoP6);
	superficieTuboDelTanqueDeCoca = new SuperficieDeBarrido(borde, caminoTuboDelTanqueDeCoca);
}
void inicializarSupeficies(){
	//Superficies
	inicializarSuperficieBotella();
	inicializarSuperficieCintaTransportadora();
	inicializarSuperficieTanqueDeCoca();	
}
void inicializarGLSL(){
	GLSLBotella = new GLSLProgram("botella.vert", "botella.frag");
	GLSLCintaTransportadora = new GLSLProgram("cintaTransportadora.vert", "cintaTransportadora.frag");
	GLSLTanqueDeCoca = new GLSLProgram("tanqueDeCoca.vert", "tanqueDeCoca.frag");
	GLSLPhongSpot = new GLSLProgram("PhongSpot.vert", "PhongSpot.frag");
}
void inicializarTexturas(){
	texLoader->SetMipMapping(true);
	texLoader->LoadTextureFromDisk("etiquetaCoca.bmp", &etiquetaCoca);
	texLoader->LoadTextureFromDisk("tapaCoca.bmp", &tapaCoca);
	texLoader->LoadTextureFromDisk("cintaTransportadora.bmp", &cintaTransportadora);
	skyBox = SOIL_load_OGL_cubemap("cubemap_blue_sofa_positive_x.bmp",
								   "cubemap_blue_sofa_negative_x.bmp",
								   "cubemap_blue_sofa_positive_y.bmp",
								   "cubemap_blue_sofa_negative_y.bmp", 
								   "cubemap_blue_sofa_positive_z.bmp",
								   "cubemap_blue_sofa_negative_z.bmp",
								   SOIL_LOAD_RGB,
								   SOIL_CREATE_NEW_ID,
								   SOIL_FLAG_MIPMAPS);
	cout << SOIL_last_result() << endl;
	/*glGenTextures(1, &skyBox);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyBox);
	for (int i=0;i<6;++i)
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);*/
}
void inicializarLuces(){
	propLuz luz = { 
		true,
		vec4(0.0, -5.0, 5.0, 1.0), 
		vec4(0.0, 0.0, -1.0, 0.0),
		35,
		10,
		vec3(0.1, 0.1, 0.1), 
		vec3(0.9, 0.9, 0.9),
		vec3(1.0, 1.0, 1.0),
	};

	for (int i = 0; i < cantidadDeLuces; i++){
		propLuz luzAux = luz;
		if (i < cantidadDeLuces/2)
			luzAux.posicion[1] += 5.0 * i;
		else{
			luzAux.posicion[0] += 5.0;
			luzAux.posicion[1] += 5.0 * (i - cantidadDeLuces/2);
		}
		luces[i] = luzAux;
	}
}

void setearLucesUniform(GLSLProgram* GLSLenUso = GLSLPhongSpot){
	mat4 matrizDeLaCamara = glm::lookAt(vec3(eye[0], eye[1], eye[2]),
										vec3(at[0], at[1], at[2]),
										vec3(up[0], up[1], up[2]));
 
	string l[] = { "luzE1", "luzE2", "luzE3", "luzE4", "luzE5", "luzE6"};
	for (int i = 0; i < cantidadDeLuces; i++){
		std::string aux = l[i];
		vec4 posicionDeLaLuz = matrizDeLaCamara * luces[i].posicion;
		vec4 direccionDeLaLuz = matrizDeLaCamara * luces[i].direccion;

		GLSLenUso->setUniform(aux.append(".prendida").c_str(), luces[i].prendida);			aux = l[i];
		GLSLenUso->setUniform(aux.append(".posicion").c_str(), vec3(posicionDeLaLuz));		aux = l[i];
		GLSLenUso->setUniform(aux.append(".direccion").c_str(), vec3(direccionDeLaLuz));
	}
}
void setearMaterial(propMaterial material, GLSLProgram* GLSLenUso = GLSLPhongSpot){
	GLSLenUso->setUniform("material.colorAmb", material.colorAmb);
	GLSLenUso->setUniform("material.colorDif", material.colorDif);
	GLSLenUso->setUniform("material.colorEspec", material.colorEspec);
	GLSLenUso->setUniform("material.brillo", material.brillo);
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
	setearLucesUniform(GLSLBotella);

	glCallList(DL_BOTELLA);

	GLSLBotella->cerrar();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
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
	GLSLCintaTransportadora->setUniform("desplazamientoDeCinta", desplazamientoDeCinta);
	setearLucesUniform(GLSLCintaTransportadora);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

	//glMatrixMode(GL_TEXTURE);
	//glTranslatef(desplazamientCinta,desplazamientCinta,desplazamientCinta);
	//glScalef(desplazamientCinta,desplazamientCinta,desplazamientCinta);
	//glPushMatrix();
	

	//	Emparchador::emparchar(superficieCintaTransportadora->discretizar(5, 10), 14);
	
	glCallList(DL_CINTA_TRANSPORTADORA);

	//glPopMatrix();

	GLSLCintaTransportadora->cerrar();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}
void dibujarTanqueDeCoca(){
	glDisable(GL_LIGHTING);

	if (actualizar){
		delete GLSLTanqueDeCoca;
		GLSLTanqueDeCoca = new GLSLProgram("tanqueDeCoca.vert", "tanqueDeCoca.frag");
		delete GLSLPhongSpot;
		GLSLPhongSpot = new GLSLProgram("PhongSpot.vert", "PhongSpot.frag");
		actualizar = false;
	}
	
	if (!GLSLTanqueDeCoca->isLinked())
		GLSLTanqueDeCoca->link();
	GLSLTanqueDeCoca->usar();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyBox);
	propMaterial tanque = {
		vec3(0.44, 0.57, 0.75),
		vec3(0.44, 0.57, 0.75),
		vec3(0.1, 0.15, 0.2),
		32.0
	};
	setearMaterial(tanque, GLSLTanqueDeCoca);
	setearLucesUniform(GLSLTanqueDeCoca);
	GLSLTanqueDeCoca->setUniform("skyBoxTex", 0);

	glCallList(DL_TANQUE_DE_COCA);

	GLSLTanqueDeCoca->cerrar();

	if (!GLSLPhongSpot->isLinked())
		GLSLPhongSpot->link();
	GLSLPhongSpot->usar();
	propMaterial material = {
		vec3(0.3, 0.3, 0.3),
		vec3(0.3, 0.3, 0.3),
		vec3(0.1, 0.1, 0.1),
		1.0
	};
	setearLucesUniform();
	setearMaterial(material);

	glBegin(GL_QUADS);
		glNormal3f(1.0, 0.0, 0.0);
		glVertex3f(0.375, -0.375, 0.0);
		glVertex3f(0.375,  0.375, 0.0);	
		glVertex3f(0.375,  0.375, 1.25);
		glVertex3f(0.375, -0.375, 1.25);

		glNormal3f( 0.0,  1.0, 0.0);
		glVertex3f( 0.375, 0.375, 0.0);
		glVertex3f(-0.375, 0.375, 0.0);
		glVertex3f(-0.375, 0.375, 1.25);
		glVertex3f( 0.375, 0.375, 1.25);

		glNormal3f(-1.0,  0.0,  0.0);
		glVertex3f(-0.375, 0.375, 0.0);
		glVertex3f(-0.375, -0.375, 0.0);	
		glVertex3f(-0.375, -0.375, 1.25);
		glVertex3f(-0.375, 0.375, 1.25);	

		glNormal3f(0.0,  -1.0,  0.0);
		glVertex3f(-0.375, -0.375, 0.0);
		glVertex3f(0.375,  -0.375, 0.0);
		glVertex3f(0.375,  -0.375, 1.25);
		glVertex3f(-0.375, -0.375, 1.25);		

	glEnd();

	GLSLPhongSpot->cerrar();
	//Esto se dibuja en momentos distintos porque lo que viene ahora es
	//el tubo que llena la Coca, que se mueve, mientras el resto del tanque permanece quieto

	GLSLTanqueDeCoca->usar();
	propMaterial tubo = {
		vec3(0.9, 0.9, 0.28),
		vec3(0.9, 0.9, 0.28),
		vec3(0.3, 0.3, 0.1),
		32.0
	};
	setearMaterial(tubo, GLSLTanqueDeCoca);
	setearLucesUniform(GLSLTanqueDeCoca);
	
	glCallList(DL_TUBO_DEL_TANQUE_DE_COCA);

	GLSLTanqueDeCoca->cerrar();

	GLSLPhongSpot->usar();
	setearLucesUniform(GLSLTanqueDeCoca);
	setearMaterial(material);
	glBegin(GL_QUADS);
		glNormal3f(1.0, 0.0, 0.0);
		glVertex3f(0.2, -0.2, 3.75);
		glVertex3f(0.2,  0.2, 3.75);
		glVertex3f(0.2,  0.2, 4.75);
		glVertex3f(0.2, -0.2, 4.75);

		glNormal3f( 0.0,  1.0, 0.0);
		glVertex3f( 0.2, 0.2, 3.75);
		glVertex3f(-0.2, 0.2, 3.75);
		glVertex3f(-0.2, 0.2, 4.75);
		glVertex3f( 0.2, 0.2, 4.75);

		glNormal3f(-1.0,  0.0,  0.0);
		glVertex3f(-0.2, 0.2, 3.75);
		glVertex3f(-0.2, -0.2, 3.75);
		glVertex3f(-0.2, -0.2, 4.75);
		glVertex3f(-0.2, 0.2, 4.75);

		glNormal3f(0.0,  -1.0,  0.0);
		glVertex3f(-0.2, -0.2, 3.75);
		glVertex3f(0.2,  -0.2, 3.75);
		glVertex3f(0.2,  -0.2, 4.75);
		glVertex3f(-0.2, -0.2, 4.75);

		glNormal3f(0.0,   0.0, 1.0);
		glVertex3f( 0.2, -0.2, 4.75);
		glVertex3f( 0.2,  0.2, 4.75);
		glVertex3f(-0.2,   0.2, 4.75);
		glVertex3f(-0.2,  -0.2, 4.75);

	glEnd();
	
	GLSLPhongSpot->cerrar();
}
void dibujarPlanoYToroide(){
	//Propiedades del material y luces
	glDisable(GL_LIGHTING);
	if (actualizar){
		delete GLSLPhongSpot;
		GLSLPhongSpot = new GLSLProgram("PhongSpot.vert", "PhongSpot.frag");
		actualizar = false;
	}
	
	if (!GLSLPhongSpot->isLinked())
		GLSLPhongSpot->link();
	GLSLPhongSpot->usar();
	setearLucesUniform();
	
	propMaterial piso = {
		vec3(0.3, 0.3, 0.3),
		vec3(0.3, 0.3, 0.3),
		vec3(0.1, 0.1, 0.1),
		1.0
	};
	propMaterial toroide = {
		vec3(0.9, 0.9, 0.28),
		vec3(0.9, 0.9, 0.28),
		vec3(0.3, 0.3, 0.1),
		32.0
	};
	setearMaterial(piso);
	
	glPushMatrix();
		glRotatef(45*sin(tiempo), 1.0, 0.0, 0.0);
		glBegin(GL_QUADS);
			glNormal3f(0.0, 0.0, 1.0);
			glVertex3f(25, -25, 0);
			glVertex3f(25,  25, 0);
			glVertex3f(-25, 25, 0);
			glVertex3f(-25, -25, 0);
		glEnd();
		setearMaterial(toroide);
		glPushMatrix();
			glTranslatef(2.0, 0.0, 1.0);
			glutSolidTorus(1.0, 2.5, 30, 36);
		glPopMatrix();
	glPopMatrix();
	GLSLPhongSpot->cerrar();
}
void init(void) 
{
	dl_handle = glGenLists(7);

	glClearColor (0.02f, 0.02f, 0.04f, 0.0f);
    glShadeModel (GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
	
	inicializarSupeficies();
	inicializarGLSL();
	inicializarTexturas();
	inicializarLuces();

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
	glNewList(DL_BOTELLA, GL_COMPILE);
		Emparchador::emparchar(superficieBotella->discretizar(10, 36));
	glEndList();
	glNewList(DL_CINTA_TRANSPORTADORA, GL_COMPILE);

		Emparchador::emparchar(superficieCintaTransportadora->discretizar(5, 10), 14);

	glEndList();
	glNewList(DL_TANQUE_DE_COCA, GL_COMPILE);
		Emparchador::emparchar(superficieTanqueDeCoca->discretizar(30, 36));
	glEndList();
	glNewList(DL_TUBO_DEL_TANQUE_DE_COCA, GL_COMPILE);
		Emparchador::emparchar(	superficieTuboDelTanqueDeCoca->discretizar(10, 10));
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
	if (verCintaTransportadora){


		dibujarCintaTransportadora();

	}
	if (verTanqueDeCoca)
		dibujarTanqueDeCoca();
	if (verPruebaSpot)
		dibujarPlanoYToroide();
	

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
		  avanzarEnElTiempo = !avanzarEnElTiempo; break;
	  case 'n':
		  tieneEtiqueta = !tieneEtiqueta; break;
	  case 'm':
		  tieneTapa = !tieneTapa; break;
	  case '<':
		  luces[0].prendida = !luces[0].prendida; break;
	  case 'z':
		  luces[1].prendida = !luces[1].prendida; break;
	  case 'x':
		  luces[2].prendida = !luces[2].prendida; break;
	  case 'c':
		  luces[3].prendida = !luces[3].prendida; break;
	  case 'v':
		  luces[4].prendida = !luces[4].prendida; break;
	  case 'b':
		  luces[5].prendida = !luces[5].prendida; break;
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
		  verCintaTransportadora = false; 
		  verTanqueDeCoca = false;  
		  verPruebaSpot = false;break;
	  case '5':
		  verBotella = false;
		  verCintaTransportadora = true; 
		  verTanqueDeCoca = false;  
		  verPruebaSpot = false;break;
	  case '6':
		  verBotella = false;
		  verCintaTransportadora = false; 
		  verTanqueDeCoca = true;  
		  verPruebaSpot = false;break;
	  case '7':
		  verBotella = false;
		  verCintaTransportadora = false; 
		  verTanqueDeCoca = false; 
		  verPruebaSpot = true; break;
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
