#include "ObjetoGrafico.h"


GLSLProgram* ObjetoGrafico::phong = NULL;
TextureLoader* ObjetoGrafico::cargadorDeTexturas = NULL;

ObjetoGrafico::ObjetoGrafico(void){
	if (! phong)
		phong = new GLSLProgram( "..\\ShadersTest\\PhongSpot.vert", "..\\ShadersTest\\PhongSpot.frag");
	if(! cargadorDeTexturas)
		cargadorDeTexturas = new TextureLoader();

}


void ObjetoGrafico::posicionar(float *nuevaPosicion){

	if (this->posicionObjeto != NULL)
		this->posicionar(nuevaPosicion[0],nuevaPosicion[1],nuevaPosicion[2]);	
	
}

void ObjetoGrafico::posicionar(const float& x,const float& y,const float& z){

		posicionObjeto[0] = x;
		posicionObjeto[1] = y;
		posicionObjeto[2] = z;
	
}


void ObjetoGrafico::inicializarVector(float *vector,float x,float y, float z){

	if (vector!= NULL){
		vector[0] = x;
		vector[1] = y;
		vector[2] = z;
	}
}

void ObjetoGrafico::dibujarPiramide(float *color){

	glDisable(GL_LIGHTING);

	glBegin(GL_TRIANGLE_FAN);

		glColor3fv(color);

		glVertex3f(0.0,0.0,3.0);

		glVertex3f(1.0,1.0,0.0);
		glVertex3f(-1.0,1.0,0.0);

		glVertex3f(-1.0,1.0,0.0);
		glVertex3f(-1.0,-1.0,0.0);

		glVertex3f(-1.0,-1.0,0.0);
		glVertex3f(1.0,-1.0,0.0);

		glVertex3f(1.0,-1.0,0.0);
		glVertex3f(1.0,1.0,0.0);

	glEnd();
}

void ObjetoGrafico::aplicarShader(){
	if (!shaders->isLinked())
		shaders->link();
	shaders->usar();
}
void ObjetoGrafico::detenerShader(){
	shaders->cerrar();
}
void ObjetoGrafico::aplicarPhong(){
	if (!phong->isLinked())
		phong->link();
	phong->usar();
}
void ObjetoGrafico::detenerPhong(){
	phong->cerrar();
}

ObjetoGrafico::~ObjetoGrafico(void){
	delete phong;
	delete shaders;
}
