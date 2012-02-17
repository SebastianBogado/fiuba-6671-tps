#pragma once
#include "ObjetoGrafico.h"
class MaquinaDeBotellas :
	public ObjetoGrafico
{
public:
	MaquinaDeBotellas(void);

	void graficar();

protected:

	void aplicarShader();
	void detenerShader();

	void inicializarVertices();

	float **vertices;
	float ancho,largo,alto;
	int cantidadVertices;
	~MaquinaDeBotellas(void);
};

