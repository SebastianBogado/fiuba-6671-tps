#include "MaquinaEmbaladora.h"


MaquinaEmbaladora::MaquinaEmbaladora(void)
{	

	this->ancho = 4.0;
	this->largo = 6.0;
	this->alto = 7.0;

	this->posicionObjeto = new float[3];
	this->inicializarVector(posicionObjeto,29.0,5.0,0.0);

	this->posDeObjetoAnimado = new float[3];
	this->inicializarVector(posDeObjetoAnimado,0.0,0.0,0.0);

	this->inicializarVertices();
	this->reiniciarContadorBotellas();
}

void MaquinaEmbaladora::reiniciarContadorBotellas()
{
	this->contadorBotellas = 0;

}


void MaquinaEmbaladora::definirMateriales(){


}

void MaquinaEmbaladora::graficar(){

	float altoHoyoEntrada = 3.0 ,anchoHoyoEntrada = 2.5;
	float altoHoyoSalida =2.0 , anchoHoyoSalida = 4.5;

	vec2 posHent = vec2(0.5,0.3);
	vec2 posHsal = vec2(0.5,0.7);



	//this->graficarBase();

	float normal[3];

	this->definirMateriales();

	glPushMatrix();
	//glTranslatef(posicionObjeto[0],posicionObjeto[1],posicionObjeto[2]);
	this->posicionarObjeto(); 

	glEnable(GL_LIGHTING);

		this->inicializarVector(normal,0.0,-1.0,0.0);
		this->dibujarPared(normal,0,1,4,5);

		this->inicializarVector(normal,1.0,0.0,0.0);
		this->dibujarPared(normal,1,2,5,6);


		this->inicializarVector(normal,0.0,1.0,0.0);
		this->dibujarParedHueca(normal,2,3,6,7,altoHoyoSalida,anchoHoyoSalida,vec2(0.5,0.8),0.8);
	//	this->dibujarPared(normal,2,3,6,7);

		this->inicializarVector(normal,-1.0,0.0,0.0);
		this->dibujarParedHueca(normal,3,0,7,4,altoHoyoEntrada,anchoHoyoEntrada,vec2(0.5,0.4),0.8);
		//this->dibujarPared(normal,3,0,7,4);

		this->inicializarVector(normal,0.0,0.0,1.0);
		this->dibujarPared(normal,4,5,7,6);


	glPopMatrix();

}

void MaquinaEmbaladora::actualizarAtributos(){ }

void MaquinaEmbaladora::aplicarShader(){
	
}

void MaquinaEmbaladora::detenerShader(){
}


void MaquinaEmbaladora::iniciarAnimacion(Botella* botella)
{
	this->contadorBotellas++;

}

bool MaquinaEmbaladora::animacionFinalizada()
{
	return true;
}

MaquinaEmbaladora::~MaquinaEmbaladora(void)
{
	delete[] this->posicionObjeto;
}
