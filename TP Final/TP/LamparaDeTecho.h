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
	
	void getPosicion();
	virtual ~LamparaDeTecho(void);

private:

	void graficarLamparaSimple();

	void inicializarVertices();
	void actualizarVertices();

	void aplicarShader();
	void detenerShader();

	ObjetoGraficoCubico *cuarto;
	float ladoMayorCuarto,ladoMenorCuarto;

	bool rotarCamaras;

	float largo,ancho,grosor,alturaCampana;
	int cantVertices;
	float **vertices;

};
