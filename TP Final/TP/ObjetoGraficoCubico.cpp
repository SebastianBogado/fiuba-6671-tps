#include "ObjetoGraficoCubico.h"


ObjetoGraficoCubico::ObjetoGraficoCubico(void)
{
}

void ObjetoGraficoCubico::inicializarVertices(){

	this->cantidadVertices = 8;

	this->vertices = new float*[cantidadVertices];

	for (int i=0; i < cantidadVertices ; i++)
		this->vertices[i] = new float[3]; 

	
	this->actualizarVertices();

}

void ObjetoGraficoCubico::definirParametros(float ancho,float largo,float alto){

	this->ancho = ancho;
	this->largo = largo;
	this->alto = alto;

	this->actualizarVertices();

}

void ObjetoGraficoCubico::actualizarVertices(){

	this->inicializarVector(vertices[0],0.0,0.0,0.0);
	this->inicializarVector(vertices[1],largo,0.0,0.0);
	this->inicializarVector(vertices[2],largo,ancho,0.0);
	this->inicializarVector(vertices[3],0.0,ancho,0.0);

	this->inicializarVector(vertices[4],0.0,0.0,alto);
	this->inicializarVector(vertices[5],largo,0.0,alto);
	this->inicializarVector(vertices[6],largo,ancho,alto);
	this->inicializarVector(vertices[7],0.0,ancho,alto);
}



ObjetoGraficoCubico::~ObjetoGraficoCubico(void)
{
	for(int i=0;i < cantidadVertices;i++)
		delete[] this->vertices[i];

	delete[] this->vertices;

}
