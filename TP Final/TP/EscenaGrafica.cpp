#include "EscenaGrafica.h"


EscenaGrafica::EscenaGrafica(void)
{
	this->cantidadObjetos = 1;

	this->objetos = new ObjetoGrafico*[this->cantidadObjetos];

	this->objetos[0] = new MaquinaDeBotellas();

}


void EscenaGrafica::graficar(){


	for (int i=0; i < this->cantidadObjetos; i++)
		this->objetos[i]->graficar();

}

EscenaGrafica::~EscenaGrafica(void)
{
	for (int i=0; i < this->cantidadObjetos; i++)
		delete objetos[i];

	delete[] this->objetos;

}
