#pragma once

#include "ObjetoGrafico.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
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

	void inicializarEstaticos();

	bool tieneEtiqueta;
	bool tieneTapa;
	float porcentajeDeLlenado;

	static string rutaTexturaEtiqueta;
	static string rutaTexturaTapa;
	static string rutaShaderDeVertices,rutaShaderDeFragmentos;
	static GLSLProgram* shaderss;
	static GLuint etiquetaCoca, tapaCoca;
	static GLuint DL_BOTELLA;
	static bool inicializada;

	float _testColor[3];

};


