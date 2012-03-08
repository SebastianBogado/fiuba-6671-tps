#include "MaquinaEtiquetadora.h"


MaquinaEtiquetadora::MaquinaEtiquetadora(void)
{	

	this->posTramoEnCinta = 0.39;

	this->ancho = 1.5;
	this->largo = 1.5;
	this->alto = 5.0;

	this->posicionObjeto = new float[3];
	this->inicializarVector(posicionObjeto,10.,10.5,0.0);

	this->posDeObjetoAnimado = new float[3];
	//this->inicializarVector(posDeObjetoAnimado,0.0,0.0,0.0);
	this->pasoDeAnimacion = 0.1;
	this->acumuladorEnAnimacion = 0.0;
	

	this->inicializarVertices();

}

void MaquinaEtiquetadora::definirMateriales()
{


}

void MaquinaEtiquetadora::graficar(){

	float normal[3];
	this->definirMateriales();

	glPushMatrix();
	//glTranslatef(posicionObjeto[0],posicionObjeto[1],posicionObjeto[2]);
	this->posicionarObjeto(); 

	glEnable(GL_LIGHTING);

		this->inicializarVector(normal,0.0,-1.0,0.0);
		this->dibujarPared(normal,0,1,4,5);
	//	this->dibujarParedHueca(normal,0,1,4,5,altoHoyoEntrada,anchoHoyoEntrada,posHent,0.6);

		this->inicializarVector(normal,1.0,0.0,0.0);
		this->dibujarPared(normal,1,2,5,6);
	//	this->dibujarParedHueca(normal,1,2,5,6,altoHoyoSalida,anchoHoyoSalida,posHsal,0.8);


		this->inicializarVector(normal,0.0,1.0,0.0);
	//	this->dibujarParedHueca(normal,2,3,6,7,altoHoyoSalida,anchoHoyoSalida,vec2(0.5,0.8),0.8);
		this->dibujarPared(normal,2,3,6,7);

		this->inicializarVector(normal,-1.0,0.0,0.0);
	//	this->dibujarParedHueca(normal,3,0,7,4,altoHoyoEntrada,anchoHoyoEntrada,vec2(0.5,0.4),0.8);
		this->dibujarPared(normal,3,0,7,4);

		this->inicializarVector(normal,0.0,0.0,1.0);
		this->dibujarPared(normal,4,5,7,6);


	glPopMatrix();


	/*
	//Solo para test
	float color[3] = {0.1,0.3,0.9};

	glPushMatrix();
		glTranslatef(posicionObjeto[0],posicionObjeto[1],posicionObjeto[2]);
		//glPushMatrix();
			glScalef(1.3,1.0,2.0);	
			this->dibujarPiramide(color);


		//glPopMatrix();
		glTranslatef(0.0,0.0,3.0);
		glRotatef(180,0.0,1.0,0.0);
		this->dibujarPiramide(color);
			
	glPopMatrix();*/

}


void MaquinaEtiquetadora::actualizarAtributos(){ 


	if (this->AnimacionIniciada)
	{

		this->acumuladorEnAnimacion += this->pasoDeAnimacion;

		//Seria como el tiempo de animacion
		if(acumuladorEnAnimacion > 2.5)
		{
			this->AnimacionIniciada = false;
			this->acumuladorEnAnimacion = 0.0;
		}
			

	}
	
}

void MaquinaEtiquetadora::aplicarShader(){ }

void MaquinaEtiquetadora::detenerShader(){ }


void MaquinaEtiquetadora::iniciarAnimacion(Botella* botella){

	//botella->cambiarColor();
	botella->etiquetar();

	this->AnimacionIniciada = true;

	this->acumuladorEnAnimacion = 0.0;

	//this->_testAnimacion = 0.0;
	
}


bool MaquinaEtiquetadora::animacionFinalizada()
{
	return !(this->AnimacionIniciada);

}


MaquinaEtiquetadora::~MaquinaEtiquetadora(void)
{
}
