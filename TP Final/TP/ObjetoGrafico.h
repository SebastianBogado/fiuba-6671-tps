#pragma once

#include <GL\freeglut.h>

class ObjetoGrafico
{
public:
	ObjetoGrafico(void);


	/*
		Funcion que dibuja al objeto en la escena
	*/

	virtual void graficar()=0;

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


	//Variables

	float *posicionObjeto;


	~ObjetoGrafico(void);
};

