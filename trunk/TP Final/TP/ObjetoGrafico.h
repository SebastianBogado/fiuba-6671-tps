#pragma once

#include <GL\freeglut.h>
#include <iostream>

using namespace std;

class ObjetoGrafico
{
public:
	ObjetoGrafico(void);


	/*
		Funcion que dibuja al objeto en la escena
	*/

	virtual void graficar()=0;


	/*
		Define la posicion de donde se graficara el Objeto
	*/
	void posicionar(float *nuevaPosicion);


protected:

	/*
		Funciones para el manejo de shader del objeto
	*/
	virtual void aplicarShader()=0;
	virtual void detenerShader()=0;

	/*
		... y mas cosas que faltan definir (como texturas, etc)
	*/

	//////////////////////
	//Atributos de Clase//
	//////////////////////

	float *posicionObjeto;
	string rutaTextura;
	string rutaShaderDeVertices,rutaShaderDeFragmentos;


	~ObjetoGrafico(void);
};

