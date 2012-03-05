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

	////////////////////////////////////////////////
	//Metodos para cambiar los estados de la botella
	////////////////////////////////////////////////
	void etiquetar();
	void llenar();
	void tapar();
	


	void reiniciarAtributos();

	virtual ~Botella(void);


	//Solo para test de Cinta
	void cambiarColor(){ this->inicializarVector(_testColor,_testColor[0] + 0.3,_testColor[1] + 0.2, _testColor[2] + 0.1);}

private:

	void aplicarShader();
	void detenerShader();

	bool tieneEtiqueta;
	float porcentajeDeLlenado;

	float _testColor[3];

};

