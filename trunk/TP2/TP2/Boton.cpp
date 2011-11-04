#include "Boton.h"
#include "AdministradorTexturas.h"
#include "MouseCallbacks.h"


extern char *pathObjEsfera;
extern char *pathObjCubo;
extern char *pathObjToroide;
extern char *pathObjCilindro;

extern char *pathMatBrillante;
extern char *pathMatTexturado;
extern char *pathMatSemimate;
extern char *pathMatReflectivo;

extern char *pathEfecRetorcer;
extern char *pathEfecRuido;
extern char *pathEfecDoblar;
extern char *pathEfecEsferizar;


void* pBotonActual; //variable global para ejecutar el callback con wrapper

/*
Boton::Boton(string pathTextura, void (*mouseCallback)(int, int, int, int)){
	
	 linkear textura, en la función display
	 
	

	pMouse = mouseCallback;
}
*/
Boton::Boton(int tipo,void (*mouseCallback)(int, int, int, int)){

	pMouse = mouseCallback;
	this->tipoBoton=tipo;

}

void Boton::cargarTextura(){

	switch(this->tipoBoton){

	case BOTON_ESFERA: this->pathTextura=pathObjEsfera; break;
	case BOTON_CUBO: this->pathTextura=pathObjCubo; break;
	case BOTON_TOROIDE: this->pathTextura=pathObjToroide; break;
	case BOTON_CILINDRO: this->pathTextura=pathObjCilindro; break;

	case BOTON_MATERIAL_SOMBREADO_BRILLANTE: this->pathTextura=pathMatBrillante; break;
	case BOTON_MATERIAL_SOMBREADO_TEXTURADO: this->pathTextura=pathMatTexturado; break;
	case BOTON_MATERIAL_REFLECTIVO: this->pathTextura=pathMatReflectivo; break;
	case BOTON_MATERIAL_SOMBREADO_SEMIMATE: this->pathTextura=pathMatSemimate; break;

	case BOTON_RETORCER: this->pathTextura=pathEfecRetorcer; break;
	case BOTON_RUIDO: this->pathTextura=pathEfecRuido; break;
	case BOTON_DOBLAR: this->pathTextura=pathEfecDoblar; break;
	case BOTON_ESFERIZAR: this->pathTextura=pathEfecEsferizar; break;

	default: break; this->pathTextura=pathObjEsfera; break;
	}


	glEnable(GL_TEXTURE_2D);
	this->texLoader.LoadTextureFromDisk(this->pathTextura,&this->textura);
	glBindTexture(GL_TEXTURE_2D,this->textura.TextureID);
}

Boton::~Boton(void){

}

void Boton::display(){
	//glEnable(GL_CULL_FACE);
	//glDisable(GL_DEPTH_TEST);

	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);

	glColor3f(1.0, 1.0, 1.0);
	//glBegin(GL_LINE_STRIP);	
	glBegin(GL_TRIANGLE_STRIP);
		//this->adminText->generarCoordTextBoton(1.0,1.0);
		glTexCoord2f(1.0,1.0);
		glVertex2f(1, 1);

		//this->adminText->generarCoordTextBoton(1.0,0.0); 	
		glTexCoord2f(1.0,0.0);
		glVertex2f(1, -1);

		//this->adminText->generarCoordTextBoton(0.0,1.0); 	
		glTexCoord2f(0.0,1.0);
		glVertex2f(-1, 1);

		//this->adminText->generarCoordTextBoton(0.0,0.0);	
		glTexCoord2f(0.0,0.0);
		glVertex2f(-1, -1);

	
	glEnd();


	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glutPostRedisplay();
	glutSwapBuffers();
}

void Boton::displayWrapper(){
	Boton* yo = (Boton*) pBotonActual;
	yo->display();
}

Boton::mouse Boton::getMouseCallback(){ return this->pMouse; }