#pragma once
#include "ObjetoGraficoCubico.h"
class LamparaDeTecho :
	public ObjetoGrafico
{
public:
	LamparaDeTecho(void);

	LamparaDeTecho(ObjetoGraficoCubico *habitacion);

	void graficar();

	void definirHabitacion(ObjetoGraficoCubico *habitacion);

	void actualizarAtributos();

	virtual ~LamparaDeTecho(void);

private:

	void graficarLamparaSimple();

	void inicializarVertices();
	void actualizarVertices();

	void aplicarShader();
	void detenerShader();

	ObjetoGraficoCubico *cuarto;
	float largo,ancho,grosor,alturaCampana;
	int cantVertices;
	float **vertices;

};
