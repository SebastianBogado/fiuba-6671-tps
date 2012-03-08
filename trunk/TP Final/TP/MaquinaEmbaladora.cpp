#include "MaquinaEmbaladora.h"


MaquinaEmbaladora::MaquinaEmbaladora(void)
{	

	// quiere decir que la animacion se realizara al final de la cinta
	this->posTramoEnCinta = 1.0;

	this->ancho = 6.0;
	this->largo = 4.0;
	this->alto = 9.0;

	this->posicionObjeto = new float[3];
	this->inicializarVector(posicionObjeto,7.5,25.0,0.0);

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

	float altoHoyoEntrada = 2.8 ,anchoHoyoEntrada = 2.2;
	float altoHoyoSalida =2.2 , anchoHoyoSalida = 5.2;

	vec2 posHent = vec2(0.5,0.35);
	vec2 posHsal = vec2(0.5,0.85);



	//this->graficarBase();

	float normal[3];

	this->definirMateriales();

	glPushMatrix();
	//glTranslatef(posicionObjeto[0],posicionObjeto[1],posicionObjeto[2]);
	this->posicionarObjeto(); 

	glEnable(GL_LIGHTING);

		this->inicializarVector(normal,0.0,-1.0,0.0);
	//	this->dibujarPared(normal,0,1,4,5);
		this->dibujarParedHueca(normal,0,1,4,5,altoHoyoEntrada,anchoHoyoEntrada,posHent,0.6);

		this->inicializarVector(normal,1.0,0.0,0.0);
//		this->dibujarPared(normal,1,2,5,6);
		this->dibujarParedHueca(normal,1,2,5,6,altoHoyoSalida,anchoHoyoSalida,posHsal,0.8);


		this->inicializarVector(normal,0.0,1.0,0.0);
	//	this->dibujarParedHueca(normal,2,3,6,7,altoHoyoSalida,anchoHoyoSalida,vec2(0.5,0.8),0.8);
		this->dibujarPared(normal,2,3,6,7);

		this->inicializarVector(normal,-1.0,0.0,0.0);
	//	this->dibujarParedHueca(normal,3,0,7,4,altoHoyoEntrada,anchoHoyoEntrada,vec2(0.5,0.4),0.8);
		this->dibujarPared(normal,3,0,7,4);

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
	botella->etiquetar();
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
