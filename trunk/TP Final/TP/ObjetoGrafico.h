#pragma once

#include <GL\freeglut.h>
#include <iostream>

using namespace std;

class ObjetoGrafico
{
public:
	ObjetoGrafico(void);


	/*
		Metodo que dibuja al objeto en la escena
	*/

	virtual void graficar()=0;


	/*
		Metodo que actualiza el estado del objeto para el proxima vez que sea dibujado
	*/

	virtual void actualizarAtributos()=0;

	/*
		Define la posicion de donde se graficara el Objeto
	*/
	void posicionar(float *nuevaPosicion);

	void posicionar(const float& x,const float& y,const float& z);

	inline float* vectorPosicion(){ return posicionObjeto;}

	virtual ~ObjetoGrafico(void);

protected:

	/*
		Funciones para el manejo de shader del objeto
	*/
	virtual void aplicarShader()=0;
	virtual void detenerShader()=0;

	

	/*
		... y mas cosas que faltan definir (como texturas, etc)
	*/

	void inicializarVector(float *vector,float x,float y, float z);

	//////////////////////
	//Atributos de Clase//
	//////////////////////

	float *posicionObjeto;
	string rutaTextura;
	string rutaShaderDeVertices,rutaShaderDeFragmentos;
	
};

