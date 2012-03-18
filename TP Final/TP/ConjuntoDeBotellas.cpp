#include "ConjuntoDeBotellas.h"

vec3 ConjuntoDeBotellas::puntosPerfil[] = {
	vec3(0.0, 0.0, 0.0),
	vec3(0.9, 0.0, 0.0),
	vec3(0.5, 0.0, 0.4),
	vec3(0.5, 0.0, 1.0),
	vec3(0.5, 0.0, 1.6), 
	vec3(0.6, 0.0, 1.8),
	vec3(0.4, 0.0, 2.2),
	vec3(0.2, 0.0, 2.6),
	vec3(0.2, 0.0, 2.8), 
	vec3(0.2, 0.0, 3.0), 
	vec3(0.2, 0.0, 3.2), 
	vec3(0.2, 0.0, 3.2), 
	vec3(0.0, 0.0, 3.2)
};
int ConjuntoDeBotellas::cantidadDePuntosPerfil = 13;

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
	texLoader = new TextureLoader();
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
	rutaTextura = ".\\Recursos\\etiquetaCoca.png";
	rutaTexturaTapa = ".\\Recursos\\tapaCoca.png";
	rutaShaderDeVertices = ".\\shaders\\botella.vert";
	rutaShaderDeFragmentos = ".\\shaders\\botella.frag";
	ini();
	texLoader->SetMipMapping(true);
	texLoader->LoadTextureFromDisk(".\\Recursos\\etiquetaCoca.bmp", &etiquetaCoca);
	tapaCoca = SOIL_load_OGL_texture(rutaTexturaTapa.c_str(), SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID,
										SOIL_FLAG_INVERT_Y | SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB );
	if (! tapaCoca)
		cout << SOIL_last_result() << endl;

	//Superficie
	Bezier* perfilBotella = new Bezier(( cantidadDePuntosPerfil - 1) / 3);
	for (int i = 0; i < cantidadDePuntosPerfil; i++)
		perfilBotella->incluirPunto(puntosPerfil[i]);
	SuperficieDeRevolucion* superficieBotella = new SuperficieDeRevolucion(perfilBotella);
	
	//Display list
	float escalado = 0.5;
	glNewList(dl_handle, GL_COMPILE);
		glScalef(escalado,escalado,escalado);
		//Emparchador::emparchar(superficieBotella->discretizar(10, 36)); es la original
		Emparchador::emparchar(superficieBotella->discretizar(5, 18));
	glEndList();
}


void ConjuntoDeBotellas::graficar()
{	

	

	this->aplicarShader();
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,  etiquetaCoca.TextureID);
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

void ConjuntoDeBotellas::aplicarShaderParaBotellas()
{
	this->aplicarShader();
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, etiquetaCoca.TextureID);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tapaCoca);
	
	shaders->setUniform("etiquetaText", 0);
	shaders->setUniform("tapaText", 1);

}

void ConjuntoDeBotellas::graficarBotellasEnCajon()
{
	//Para graficar el cajon se implementa de la misma forma que el graficar normal, pero solo temporalmente
	
	
	
	//glPushMatrix();
	//glScalef(escalado,escalado,escalado);

	for (int i=0; i < this->cantBotellasEnCajon ; i++){
		glPushMatrix();
			this->botellasDeCajon[i]->graficar(shaders);
			glCallList(dl_handle);
		glPopMatrix();
	}

	//glPopMatrix();

}

void ConjuntoDeBotellas::detenerShaderParaBotellas()
{
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

void ConjuntoDeBotellas::definirMateriales(){}