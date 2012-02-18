#pragma once
#include "ObjetoGrafico.h"
class MaquinaDeBotellas :
	public ObjetoGrafico
{
public:
	MaquinaDeBotellas(void);

	void graficar();

	void definirParametros(float ancho,float largo,float alto);

protected:

	void aplicarShader();
	void detenerShader();

	void inicializarVertices();
	void actualizarVertices();

	float **vertices;
	float ancho,largo,alto;
	int cantidadVertices;
	virtual ~MaquinaDeBotellas(void);
};

