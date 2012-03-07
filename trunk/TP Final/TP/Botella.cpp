#include "Botella.h"


//Mover los archivos de texturas al TP raíz, y que los demás proyectos referencien sus direcciones a él
string Botella::rutaTexturaEtiqueta = "..\\ShadersTest\\etiquetaCoca.bmp";
string Botella::rutaTexturaTapa = "..\\ShadersTest\\tapaCoca.bmp";
string Botella::rutaShaderDeVertices = "..\\ShadersTest\\botella.vert";
string Botella::rutaShaderDeFragmentos = "..\\ShadersTest\\botella.frag";
GLSLProgram* Botella::shaderss = NULL;
bool Botella::inicializada = false;
GLuint Botella::etiquetaCoca = 0;
GLuint Botella::tapaCoca = 0;
GLuint Botella::DL_BOTELLA = 0;
	

Botella::Botella(void){

	this->posicionObjeto = new float[3];
	
	this->inicializarVector(posicionObjeto,0.0,0.0,0.0);
	this->inicializarVector(_testColor,0.1,0.1,0.3);
	
	tieneEtiqueta = false;
	tieneTapa = false;
	porcentajeDeLlenado = 0.0;

	if (! inicializada)
		inicializarEstaticos();
}

void Botella::inicializarEstaticos(){
	//GLSL
	shaderss = new GLSLProgram(rutaShaderDeVertices.c_str(), rutaShaderDeFragmentos.c_str());

	//Texturas
	etiquetaCoca = SOIL_load_OGL_texture(rutaTexturaEtiqueta.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
										SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	if (! etiquetaCoca)
		cout << SOIL_last_result() << endl;

	tapaCoca = SOIL_load_OGL_texture(rutaTexturaEtiqueta.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
										SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	if (! tapaCoca)
		cout << SOIL_last_result() << endl;
	
	//Superficie
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
	Bezier* perfilBotella = new Bezier(4);
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
	SuperficieDeRevolucion* superficieBotella = new SuperficieDeRevolucion(perfilBotella);
	
	//Display list
	DL_BOTELLA = glGenLists(1);
	glNewList(DL_BOTELLA, GL_COMPILE);
		Emparchador::emparchar(superficieBotella->discretizar(10, 36));
	glEndList();

	inicializada = true;
}

void Botella::graficar(){

	//float colorBotella[3] = { 0.8, 0.8, 0.8};

	glPushMatrix();
		glTranslatef(posicionObjeto[0],posicionObjeto[1],posicionObjeto[2]);
		glDisable(GL_LIGHTING);
		glEnable(GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		aplicarShader();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, etiquetaCoca);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, tapaCoca);
	
		shaderss->setUniform("etiquetaText", 0);
		shaderss->setUniform("tapaText", 1);
		shaderss->setUniform("porcentajeDeLlenado", porcentajeDeLlenado);
		shaderss->setUniform("tieneEtiqueta", tieneEtiqueta);
		shaderss->setUniform("tieneTapa", tieneTapa);
		//shaders->setLuces(iluminacion);
		//Por ahora, uso estas variables forzadas
		//Como la clase iluminacion devuelve las posiciones y dirección como deben,
		//no será necesaria esta tramoya de la cámara. Además, sólo funciona en la posición por defecto
		
		mat4 matrizDeLaCamara = glm::lookAt(vec3(15, 15, 5), vec3(0,0,0),vec3(0,0,1));
		vec4 posicionDeLaLuz = matrizDeLaCamara * vec4(0.0, 0.0, 10.0, 1.0);
		vec4 direccionDeLaLuz = matrizDeLaCamara * vec4(0.0, 0.0, -1.0, 0.0);

		shaderss->setUniform("luz.prendida", true);
		shaderss->setUniform("luz.posicion", vec3(posicionDeLaLuz));
		shaderss->setUniform("luz.direccion", vec3(direccionDeLaLuz));
		shaderss->setUniform("luz.angulo", 35);
		shaderss->setUniform("luz.k", 10);
		shaderss->setUniform("luz.amb", vec3(0.1, 0.1, 0.1));
		shaderss->setUniform("luz.dif", vec3(0.9, 0.9, 0.9));
		shaderss->setUniform("luz.espec", vec3(1.0, 1.0, 1.0));			

		glCallList(DL_BOTELLA);
	
		detenerShader();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
		glEnable(GL_LIGHTING);
	glPopMatrix();
}

void Botella::actualizarAtributos(){
	
}

void Botella::etiquetar()
{
	this->tieneEtiqueta = true;
}

void Botella::tapar()
{
	this->tapaCoca = true;
}


void Botella::desplazar(vec3 direccion){

	this->posicionObjeto[0] += direccion.x; 
	this->posicionObjeto[1] += direccion.y;
	this->posicionObjeto[2] += direccion.z;
}


void Botella::reiniciarAtributos(){

	this->tieneEtiqueta = false;
	this->tieneTapa = false;

	this->porcentajeDeLlenado = 0.0;

	//Solo para test
	//this->inicializarVector(this->_testColor,0.1,0.1,0.3);

}

void Botella::aplicarShader(){
	if (!shaderss->isLinked())
		shaderss->link();
	shaderss->usar();
}

void Botella::detenerShader(){
	shaders->cerrar();
}

Botella::~Botella(void)
{

	delete[] posicionObjeto;
}
