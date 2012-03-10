#include "ConjuntoDeBotellas.h"


ConjuntoDeBotellas::ConjuntoDeBotellas(void)
{
	this->cantBotellas = 10;
	this->inicializar();
}


ConjuntoDeBotellas::ConjuntoDeBotellas(int cantidadBotellas)
{
	this->cantBotellas = cantidadBotellas;
	this->inicializar();
}

int ConjuntoDeBotellas::cantidadDeBotellasEnCajon()
{
	return this->cantBotellasEnCajon;
}

Botella** ConjuntoDeBotellas::devolverBotellasDeCajon()
{ 
	return this->botellasDeCajon;
}
void ConjuntoDeBotellas::inicializar()
{
	this->botellas = new Botella*[cantBotellas];
	
	for (int i=0 ; i < cantBotellas ; i++)
		this->botellas[i] = new Botella();

	//Se instancian las botellas para el cajon

	this->cantBotellasEnCajon = 4;

	this->botellasDeCajon = new Botella*[this->cantBotellasEnCajon];

	for(int i=0; i < this->cantBotellasEnCajon ; i++)
		this->botellasDeCajon[i] = new Botella();
	
	//Mover los archivos de texturas al TP raíz, y que los demás proyectos referencien sus direcciones a él
	//Rutas de archivos
	rutaTextura = "..\\ShadersTest\\etiquetaCoca.png";
	rutaTexturaTapa = "..\\ShadersTest\\tapaCoca.png";
	rutaShaderDeVertices = "..\\ShadersTest\\botella.vert";
	rutaShaderDeFragmentos = "..\\ShadersTest\\botella.frag";
	ini();
	tapaCoca = SOIL_load_OGL_texture(rutaTexturaTapa.c_str(), SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID,
										SOIL_FLAG_INVERT_Y | SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
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
	float escalado = 0.5;
	glNewList(dl_handle, GL_COMPILE);
		glScalef(escalado,escalado,escalado);
		Emparchador::emparchar(superficieBotella->discretizar(10, 36));
	glEndList();
}


void ConjuntoDeBotellas::graficar()
{	

	

	this->aplicarShader();
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texturaID);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tapaCoca);
	
	shaders->setUniform("etiquetaText", 0);
	shaders->setUniform("tapaText", 1);
	//glPushMatrix();
	//glScalef(escalado,escalado,escalado);


	for (int i=0; i < this->cantBotellas ; i++){
		glPushMatrix();
			this->botellas[i]->graficar(shaders);
			glCallList(dl_handle);
		glPopMatrix();
	}

	//glPopMatrix();
	this->detenerShader();
	
}



void ConjuntoDeBotellas::graficarCajon()
{
	//Para graficar el cajon se implementa de la misma forma que el graficar normal, pero solo temporalmente
	
	this->aplicarShader();
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texturaID);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tapaCoca);
	
	shaders->setUniform("etiquetaText", 0);
	shaders->setUniform("tapaText", 1);
	//shaders->setLuces(iluminacion);
	//Por ahora, uso estas variables forzadas
	//Como la clase iluminacion devuelve las posiciones y dirección como deben,
	//no será necesaria esta tramoya de la cámara. Además, sólo funciona en la posición por defecto
		
	mat4 matrizDeLaCamara = glm::lookAt(vec3(15, 15, 5), vec3(0,0,0),vec3(0,0,1));
	vec4 posicionDeLaLuz = matrizDeLaCamara * vec4(0.0, 0.0, 10.0, 1.0);
	vec4 direccionDeLaLuz = matrizDeLaCamara * vec4(0.0, 0.0, -1.0, 0.0);

	shaders->setUniform("luz.prendida", true);
	shaders->setUniform("luz.posicion", vec3(posicionDeLaLuz));
	shaders->setUniform("luz.direccion", vec3(direccionDeLaLuz));
	shaders->setUniform("luz.angulo", 35);
	shaders->setUniform("luz.k", 10);
	shaders->setUniform("luz.amb", vec3(0.1, 0.1, 0.1));
	shaders->setUniform("luz.dif", vec3(0.9, 0.9, 0.9));
	shaders->setUniform("luz.espec", vec3(1.0, 1.0, 1.0));		
	
	//glPushMatrix();
	//glScalef(escalado,escalado,escalado);


	for (int i=0; i < this->cantBotellasEnCajon ; i++){
		glPushMatrix();
			this->botellasDeCajon[i]->graficar(shaders);
			glCallList(dl_handle);
		glPopMatrix();
	}

	//glPopMatrix();
	this->detenerShader();

}


void ConjuntoDeBotellas::actualizarAtributos()
{
	for (int i=0; i < this->cantBotellas ; i++)
		this->botellas[i]->actualizarAtributos();

	for(int i=0; i <this->cantBotellasEnCajon ; i++)
		this->botellasDeCajon[i]->actualizarAtributos();
}



Botella** ConjuntoDeBotellas::devolverBotellas()
{
	return this->botellas;

}


int ConjuntoDeBotellas::cantidadDeBotellas()
{
	return this->cantBotellas;
}

ConjuntoDeBotellas::~ConjuntoDeBotellas(void)
{

	for(int i=0; i < cantBotellas ; i ++)
		delete this->botellas[i];

	delete[] this->botellas;


	for(int i=0; i < cantBotellasEnCajon ; i ++)
		delete this->botellasDeCajon[i];

	delete[] this->botellasDeCajon;
}

void ConjuntoDeBotellas::definirMaterial(){}