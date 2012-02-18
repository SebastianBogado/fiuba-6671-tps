#include "EscenaGrafica.h"


EscenaGrafica::EscenaGrafica(void)
{
	this->cantidadObjetos = 3;

	this->objetos = new ObjetoGrafico*[this->cantidadObjetos];


	this->objetos[0] = new CuartoDeMaquinas();
	this->objetos[1] = new MaquinaDeBotellas();
	this->objetos[2] = new MaquinaEmbaladora();
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
