#include "ObjetoGrafico.h"


GLSLProgram* ObjetoGrafico::phong = NULL;

ObjetoGrafico::ObjetoGrafico(void){
	if (! phong)
		phong = new GLSLProgram( ".\\shaders\\PhongSpot.vert", ".\\shaders\\PhongSpot.frag");
}

void ObjetoGrafico::ini(){
	//GLSL
	if ( (rutaShaderDeVertices != "") && (rutaShaderDeFragmentos != "") )
		shaders = new GLSLProgram(rutaShaderDeVertices, rutaShaderDeFragmentos);
	//Textura
	if (rutaTextura != "") {
		texturaID = SOIL_load_OGL_texture(rutaTextura, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID,
										SOIL_FLAG_INVERT_Y | SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_TEXTURE_REPEATS);
		if (! texturaID)
			cout << SOIL_last_result() << endl;
	}
	//DL
	dl_handle = glGenLists(1);
	//Material
	definirMateriales();
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
	shaders->setLuces();
}
void ObjetoGrafico::detenerShader(){
	shaders->cerrar();
}
void ObjetoGrafico::aplicarPhong(){
	if (!phong->isLinked())
		phong->link();
	phong->usar();
	phong->setLuces();
	phong->setMaterial(material);
	phong->setUniform("texturado", false);
	phong->setUniform("tieneNormalMap", false);
}
void ObjetoGrafico::detenerPhong(){
	phong->cerrar();
}
void ObjetoGrafico::aplicarPhongTexturado(){
	if (!phong->isLinked())
		phong->link();
	phong->usar();
	phong->setLuces();
	phong->setMaterial(material);
	phong->setUniform("texturado", true);
	phong->setUniform("textura", 0);
	phong->setUniform("tieneNormalMap", false);
}
void ObjetoGrafico::detenerPhongTexturado(){
	phong->cerrar();
}

ObjetoGrafico::~ObjetoGrafico(void){
	delete phong;
	delete shaders;
}


void ObjetoGrafico::dibujarCuboUnitario()
{

	glBegin(GL_TRIANGLE_STRIP);
		
		glColor3f(1.0,0.0,0.0);
		glVertex3f(0.5,0.5,0.5);
		glVertex3f(0.5,0.5,-0.5);

		glColor3f(0.0,1.0,0.0);
		glVertex3f(-0.5,0.5,0.5);
		glVertex3f(-0.5,0.5,-0.5);

		glColor3f(0.0,0.0,1.0);
		glVertex3f(-0.5,-0.5,0.5);
		glVertex3f(-0.5,-0.5,-0.5);

		glColor3f(1.0,1.0,0.0);
		glVertex3f(0.5,-0.5,0.5);
		glVertex3f(0.5,-0.5,-0.5);

		glColor3f(0.0,1.0,1.0);
		glVertex3f(0.5,0.5,0.5);
		glVertex3f(0.5,0.5,-0.5);

	glEnd();


	glBegin(GL_TRIANGLE_STRIP);
		
		glColor3f(0.0,0.0,0.0);
		glVertex3f(0.5,0.5,0.5);
		glVertex3f(-0.5,0.5,0.5);

		glColor3f(1.0,1.0,1.0);
		glVertex3f(0.5,-0.5,0.5);
		glVertex3f(-0.5,-0.5,0.5);

	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
		
		glColor3f(0.0,0.0,0.0);
		glVertex3f(0.5,0.5,-0.5);
		glVertex3f(-0.5,0.5,-0.5);

		glColor3f(1.0,0.0,1.0);
		glVertex3f(0.5,-0.5,-0.5);
		glVertex3f(-0.5,-0.5,-0.5);

	glEnd();

}


void ObjetoGrafico::dibujarAristasCuboUnitario()
{

	for (int i=0; i < 2 ; i++){
		glBegin(GL_LINE_STRIP);
		
			glColor3f(1.0,0.0,0.0);
			glVertex3f(0.5,-0.5,-0.5);//0
			glVertex3f(0.5,-0.5,0.5);//0,1

			glColor3f(0.0,1.0,0.0);
			glVertex3f(0.5,0.5,0.5);//1,2
			glVertex3f(0.5,0.5,-0.5);//2,3

			glColor3f(0.0,0.0,1.0);
			glVertex3f(-0.5,0.5,-0.5);//3,4
			glVertex3f(-0.5,0.5,0.5);//4,5

			glColor3f(1.0,1.0,0.0);
			glVertex3f(0.5,0.5,0.5);//5,6
			glVertex3f(0.5,0.5,-0.5);//6,7

			glColor3f(0.0,1.0,1.0);
			glVertex3f(0.5,-0.5,-0.5);//7,8
			//glVertex3f(0.5,0.5,-0.5);//8,9

		glEnd();

		glRotatef(180.0,0.,0.,1.);

	}


}
