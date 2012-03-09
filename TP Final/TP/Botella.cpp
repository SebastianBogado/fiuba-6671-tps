#include "Botella.h"

Botella::Botella(void){
	this->posicionObjeto = new float[3];
	
	this->inicializarVector(posicionObjeto,0.0,0.0,0.0);
	this->inicializarVector(_testColor,0.1,0.1,0.3);
	
	tieneEtiqueta = false;
	tieneTapa = false;
	porcentajeDeLlenado = 0.0;
}


void Botella::graficar(){}
void Botella::graficar(GLSLProgram* shaderss){
	glTranslatef(posicionObjeto[0],posicionObjeto[1],posicionObjeto[2]);
	shaderss->setUniform("porcentajeDeLlenado", porcentajeDeLlenado);
	shaderss->setUniform("tieneEtiqueta", tieneEtiqueta);
	shaderss->setUniform("tieneTapa", tieneTapa);
}

void Botella::graficarEnCajon(GLSLProgram* shaderss){
	//glTranslatef(posicionObjeto[0],posicionObjeto[1],posicionObjeto[2]);
	shaderss->setUniform("porcentajeDeLlenado", porcentajeDeLlenado);
	shaderss->setUniform("tieneEtiqueta", tieneEtiqueta);
	shaderss->setUniform("tieneTapa", tieneTapa);
}


/*
//<<<<<<< .mine
void Botella::graficar(){

	//float colorBotella[3] = { 0.8, 0.8, 0.8};

	float escalado = 0.5;

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

		

		glScalef(escalado,escalado,escalado);

		glCallList(DL_BOTELLA);
		

		detenerShader();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
		glEnable(GL_LIGHTING);
	glPopMatrix();
}

//=======
//>>>>>>> .r172*/

float abs(float &x){

	if (x < 0)
		return -x;
	else
		return x;
}

void Botella::actualizarAtributos(){

	//Para depurar
	/*
	static float posAnt[3]={posicionObjeto[0],posicionObjeto[1],posicionObjeto[2]};
	
	float error = 0.1;
	bool errorEncontrado = false;


	if (	abs(posAnt[0] - posicionObjeto[0]) < error &&
			abs(posAnt[1] - posicionObjeto[1]) < error &&
			abs(posAnt[2] - posicionObjeto[2]) < error )
			errorEncontrado = true;
	

	*/
	

	
}

void Botella::etiquetar(){ this->tieneEtiqueta = true; }

void Botella::tapar(){ this->tieneTapa = true; }


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

void Botella::botellaTerminada()
{
	this->tieneEtiqueta = true;
	this->tieneTapa = true;

	this->porcentajeDeLlenado = 0.65;
}


Botella::~Botella(void)
{
	delete[] posicionObjeto;
}
