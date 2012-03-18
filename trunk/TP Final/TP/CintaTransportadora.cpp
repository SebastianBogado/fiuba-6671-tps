#include "CintaTransportadora.h"

vec3 CintaTransportadora::puntosForma[] = {
	vec3(6.5, 0.0, 2.5),
	vec3(6.0, 0.0, 2.0),
	vec3(6.0, 0.0, 2.0),
	vec3(5.5, 0.0, 2.0),
	vec3(5.0, 0.0, 2.0), 
	vec3(5.0, 0.0, 2.0),
	vec3(4.5, 0.0, 2.5)
};
vec3 CintaTransportadora::puntosCamino[] = {
	vec3(5.5, -1.5, 2.0),
	vec3(5.5, 1.5, 2.0),
	vec3(5.5, 4.5, 2.0),
	vec3(2.5, 4.5, 2.0),
	vec3(-0.5, 4.5, 2.0),
	vec3(-0.5, 7.5, 2.0),
	vec3(-0.5, 10.5, 2.0),
	vec3(-0.5, 13.5, 2.0),
	vec3(-0.5, 15.5, 2.0)
};
int CintaTransportadora::cantidadDePuntosForma = 7;
int CintaTransportadora::cantidadDePuntosCamino = 9;

CintaTransportadora::CintaTransportadora(void)
{	
	this->rutaShaderDeFragmentos = ".\\shaders\\cintaTransportadora.frag";
	this->rutaShaderDeVertices = ".\\shaders\\cintaTransportadora.vert";
	this->rutaTextura = ".\\Recursos\\cintaTransportadora.bmp";
	ini();

	this->discretBorde = 5;
	this->discretAvance = 5;

	this->alturaDeMaquina = 1.0;
	this->posicionObjeto = new float[3];
	this->inicializarVector(posicionObjeto,8.0,8.0,0.0);
//	this->inicializarVector(posicionObjeto,0.0,0.0,0.0);

	this->cintaEnMovimiento = true;
	this->desplazamientoDeCinta = 0.0;
	this->pasoDeDiscretizacionGeneral = 0.15;

	//Para probar funcionamiento
	/*
	this->_testLargoCinta = 25.0;
	this->_pasoTest = 0.05;
	this->_testAnimacion = 3.0;
	*/
	this->inicializarAtributos();

	//this->posicionInicialEnCinta = this->caminoCintaTransportadora->evaluar(0.0);
	this->posicionInicialEnCinta.x = this->posicionObjeto[0];
	this->posicionInicialEnCinta.y = this->posicionObjeto[1];
	this->posicionInicialEnCinta.z = 0.0;
	//this->posicionInicialEnCinta.z += this->posicionObjeto[2] - 2;

}

float CintaTransportadora::definirPosicionEnTramos(float posicionRelativa)
{

	return this->caminoCintaTransportadora->cantidadDeTramos() * posicionRelativa;

}


void CintaTransportadora::aumentarDiscretizacionDeCinta()
{

	if (this->discretAvance < 25)
		this->discretAvance++;

	if (this->discretBorde < 20)
		this->discretBorde++;
}

void CintaTransportadora::disminuirDiscretizacionDeCinta()
{
	if (this->discretAvance > 1)
		this->discretAvance--;

	if(this->discretBorde > 1)
		this->discretBorde--;

}

void CintaTransportadora::graficar(){

	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();

	glTranslatef(posicionObjeto[0],posicionObjeto[1],posicionObjeto[2]);
		this->graficarCinta();


	glPopMatrix();
	/*
	//Codigo para Test
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(posicionObjeto[0],posicionObjeto[1],posicionObjeto[2]);

		glBegin(GL_QUADS);
			glColor3f(0.5,0.8,0.5);

			glVertex3f(0.0,0.0,0.0);
			glVertex3f(_testLargoCinta,0.0,0.0);
			glVertex3f(_testLargoCinta,3.0,0.0);
			glVertex3f(0.0,3.0,0.0);
		glEnd();


		glTranslatef(_testAnimacion,0.0,0.0);
		glBegin(GL_QUADS);
			

			glColor3f(0.3,0.2,1.0);

			glVertex3f(0.0,0.0,0.1);
			glVertex3f(1,0.0,0.1);
			glVertex3f(1,3.0,0.1);
			glVertex3f(0.0,3.0,0.1);

		glEnd();

		

	glPopMatrix();
	*/
}

void CintaTransportadora::inicializarAtributos()
{
	this->inicializarCurvas();
	
	glNewList(dl_handle, GL_COMPILE);
		Emparchador::emparchar(superficieCintaTransportadora->discretizar(discretBorde, discretAvance), 15);
	glEndList();
}


void CintaTransportadora::graficarCinta()
{
	glDisable(GL_LIGHTING);
	/*
	if (actualizar){
		delete GLSLCintaTransportadora;
		GLSLCintaTransportadora = new GLSLProgram("cintaTransportadora.vert", "cintaTransportadora.frag");
		actualizar = false;
	}
	*/
	

	this->aplicarShader();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texturaID);
	
	shaders->setUniform("cintaText", 0);
	shaders->setUniform("desplazamientoDeCinta",desplazamientoDeCinta);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

	//Emparchador::emparchar(superficieCintaTransportadora->discretizar(discretBorde, discretAvance), 15);
	
	glCallList(dl_handle);
	
	this->detenerShader();

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);

}

void CintaTransportadora::inicializarCurvas()
{
	//Curva borde
	formaCintaTransportadora = new BSpline(cantidadDePuntosForma);
	for (int i = 0; i < cantidadDePuntosForma; i++)
		formaCintaTransportadora->incluirPunto(puntosForma[i]);

	//Curva camino
	caminoCintaTransportadora = new BSpline(cantidadDePuntosCamino);
	for (int i = 0; i < cantidadDePuntosCamino; i++)
		caminoCintaTransportadora->incluirPunto(puntosCamino[i]);
	superficieCintaTransportadora = new SuperficieDeBarrido(formaCintaTransportadora, caminoCintaTransportadora);
}

void CintaTransportadora::actualizarAtributos(){

	if (this->cintaEnMovimiento)
	{	
		this->desplazamientoDeCinta -= this->pasoDeDiscretizacionGeneral;

		if(this->desplazamientoDeCinta < -10.0)
			this->desplazamientoDeCinta = 0.0;


	}
}


void CintaTransportadora::nuevaPosicion(float posicionDeTramo,float* posicion)
{	

	vec3 pos = this->caminoCintaTransportadora->evaluar(posicionDeTramo);

	pos += this->posicionInicialEnCinta;

	this->inicializarVector(posicion,pos.x,pos.y,pos.z);

	//Solo para el Test
	//this->inicializarVector(posicion, 5.0 + posicionDeTramo,	6.5 ,this->alturaDeMaquina);
}

float CintaTransportadora::nuevaPosicionDeTramo(float posicion)
{	

	float res = posicion + this->pasoDeDiscretizacionGeneral* 5.0 / 12.0;

	if (res >= this->caminoCintaTransportadora->cantidadDeTramos())
		res = 0.0;

	//Solo para el Test
	//float res=0.0;

	//res = posicion + this->_pasoTest;

	//if (res > this->_testLargoCinta)
		//res =0.0;

	return res;

}


void CintaTransportadora::desplazarCinta()
{ 
	this->cintaEnMovimiento = true;
}

void CintaTransportadora::detenerCinta()
{
	this->cintaEnMovimiento = false;

}

CintaTransportadora::~CintaTransportadora(void)
{
}

void CintaTransportadora::definirMateriales(){}