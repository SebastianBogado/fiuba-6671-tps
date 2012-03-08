#include "CintaTransportadora.h"


CintaTransportadora::CintaTransportadora(void)
{	
	this->rutaShaderDeFragmentos = "..\\ShadersTest\\cintaTransportadora.frag";
	this->rutaShaderDeVertices = "..\\ShadersTest\\cintaTransportadora.vert";
	this->rutaTextura = "..\\ShadersTest\\cintaTransportadora.bmp";
	ini();

	this->discretBorde = 5;
	this->discretAvance = 10;

	this->alturaDeMaquina = 1.0;
	this->posicionObjeto = new float[3];
	this->inicializarVector(posicionObjeto,8.0,8.0,0.0);
//	this->inicializarVector(posicionObjeto,0.0,0.0,0.0);

	this->cintaEnMovimiento = true;
	this->desplazamientoDeCinta = 0.0;
	this->pasoDeDiscretizacionGeneral = 0.03;

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

	//Emparchador::emparchar(superficieCintaTransportadora->discretizar(discretBorde, discretAvance), 15);
	
	glCallList(dl_handle);
	
	this->detenerShader();

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);

}

void CintaTransportadora::inicializarCurvas()
{

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
	//vec3 caminoP0 = vec3(5.5, -4.5, 2.0);
	vec3 caminoP1 = vec3(5.5, -1.5, 2.0);
	vec3 caminoP2 = vec3(5.5, 1.5, 2.0);
	vec3 caminoP3 = vec3(5.5, 4.5, 2.0);
	vec3 caminoP4 = vec3(2.5, 4.5, 2.0);
	vec3 caminoP5 = vec3(-0.5, 4.5, 2.0);
	vec3 caminoP6 = vec3(-0.5, 7.5, 2.0);
	vec3 caminoP7 = vec3(-0.5, 10.5, 2.0);
	vec3 caminoP8 = vec3(-0.5, 13.5, 2.0);
	vec3 caminoP9 = vec3(-0.5, 15.5, 2.0);
	caminoCintaTransportadora = new BSpline(9);
	//caminoCintaTransportadora->incluirPunto(caminoP0);
	caminoCintaTransportadora->incluirPunto(caminoP1);
	caminoCintaTransportadora->incluirPunto(caminoP2);
	caminoCintaTransportadora->incluirPunto(caminoP3);
	caminoCintaTransportadora->incluirPunto(caminoP4);
	caminoCintaTransportadora->incluirPunto(caminoP5);
	caminoCintaTransportadora->incluirPunto(caminoP6);
	caminoCintaTransportadora->incluirPunto(caminoP7);
	caminoCintaTransportadora->incluirPunto(caminoP8);
	caminoCintaTransportadora->incluirPunto(caminoP9);
	superficieCintaTransportadora = new SuperficieDeBarrido(formaCintaTransportadora, caminoCintaTransportadora);

}

void CintaTransportadora::actualizarAtributos(){

	if (this->cintaEnMovimiento)
	{	
		this->desplazamientoDeCinta -= 0.003;

		if(this->desplazamientoDeCinta < -1.0)
			this->desplazamientoDeCinta = 0.0;

		//this->_testAnimacion += this->_pasoTest;

		//if(_testAnimacion >= this->_testLargoCinta)
			//this->_testAnimacion = 0.0;
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
