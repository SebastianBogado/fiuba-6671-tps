#pragma once
#include "ObjetoGrafico.h"

class ObjetoGraficoCubico :
	public ObjetoGrafico
{
public:
	ObjetoGraficoCubico(void);
	void definirParametros(float ancho,float largo,float alto);
	~ObjetoGraficoCubico(void);
protected:
	void inicializarVertices();
	void actualizarVertices();

	float **vertices;
	float ancho,largo,alto;
	int cantidadVertices;

};

