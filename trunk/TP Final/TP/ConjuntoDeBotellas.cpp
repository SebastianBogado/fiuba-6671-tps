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

void ConjuntoDeBotellas::inicializar()
{
	this->botellas = new Botella*[cantBotellas];
	
	for (int i=0 ; i < cantBotellas ; i++)
		this->botellas[i] = new Botella();

}


void ConjuntoDeBotellas::graficar()
{

	//aqui es donde se Enciende el manejo de Shaders
	this->aplicarShader();

	for (int i=0; i < this->cantBotellas ; i++)
	{
		this->botellas[i]->graficar();
	}

	this->detenerShader();
	
}


void ConjuntoDeBotellas::aplicarShader()
{


}

void ConjuntoDeBotellas::detenerShader()
{


}


void ConjuntoDeBotellas::actualizarAtributos()
{
	for (int i=0; i < this->cantBotellas ; i++)
		this->botellas[i]->actualizarAtributos();
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
}
