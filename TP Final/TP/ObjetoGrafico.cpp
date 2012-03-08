#include "ObjetoGrafico.h"


GLSLProgram* ObjetoGrafico::phong = NULL;

ObjetoGrafico::ObjetoGrafico(void){
	if (! phong)
		phong = new GLSLProgram( "..\\ShadersTest\\PhongSpot.vert", "..\\ShadersTest\\PhongSpot.frag");
}

void ObjetoGrafico::ini(){
	//GLSL
	shaders = new GLSLProgram(rutaShaderDeVertices, rutaShaderDeFragmentos);
	//Textura
	texturaID = SOIL_load_OGL_texture(rutaTextura, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID,
										SOIL_FLAG_INVERT_Y | SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	if (! texturaID)
		cout << SOIL_last_result() << endl;
	//DL
	dl_handle = glGenLists(1);
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
