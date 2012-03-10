#include "EscenaGrafica.h"

Iluminacion* EscenaGrafica::iluminacion = Iluminacion::getInstancia();

EscenaGrafica::EscenaGrafica(void)
{
	/*
	this->cantidadObjetos = 4;

	this->objetos = new ObjetoGrafico*[this->cantidadObjetos];

	CuartoDeMaquinas *cuarto = new CuartoDeMaquinas();

	this->objetos[0] = cuarto;
	this->objetos[1] = new MaquinaDeBotellas();
	this->objetos[2] = new MaquinaEmbaladora();
	this->objetos[3] = new LamparaDeTecho(cuarto);
	*/
}

void EscenaGrafica::agregarObjetosGraficos(int cantObjetos,ObjetoGrafico** objetos)
{
	if(objetos)
	{
		this->objetos = objetos;
		this->cantidadObjetos = cantObjetos;

	}
}

void EscenaGrafica::graficar(){


	for (int i=0; i < this->cantidadObjetos; i++)
		this->objetos[i]->graficar();
}


void EscenaGrafica::actualizarEscena()
{

	for (int i=0; i < this->cantidadObjetos ; i++)
		this->objetos[i]->actualizarAtributos();

}

void EscenaGrafica::posicionarLucesEnIluminacion(LamparaDeTecho* lamparas){
	vec3 aux;
	for (int j = 0; j < iluminacion->cantidadDeLuces(); j++){
		aux = lamparas->posicionDeLuz(j);
		aux.z -= 0.5;
		iluminacion->setPosicionDeLasLuces(j, aux);
	}
}

EscenaGrafica::~EscenaGrafica(void)
{
	for (int i=0; i < this->cantidadObjetos; i++)
		delete objetos[i];

	delete[] this->objetos;

}
