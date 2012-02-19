#pragma once

#include "ObjetoGrafico.h"
#include <glm\glm.hpp>

using namespace glm;

class Botella :
	public ObjetoGrafico
{
public:
	Botella(void);

	void graficar();

	/*
	*	Desplaza a la Botella un cierta posicion
	*/

	void desplazar(vec3 direccion);


	void actualizarAtributos();

	virtual ~Botella(void);

private:

	void aplicarShader();
	void detenerShader();

};

