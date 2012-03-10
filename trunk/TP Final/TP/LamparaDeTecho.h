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

	vec3 posicionDeLuz(int indice);

	int cantidadDeLuces();
	
	virtual ~LamparaDeTecho(void);

private:

	void graficarLamparaSimple();

	void inicializarVertices();
	void actualizarVertices();
	
	void definirMaterial();

	ObjetoGraficoCubico *cuarto;
	float ladoMayorCuarto,ladoMenorCuarto;

	bool rotarCamaras;

	float largo,ancho,grosor,alturaCampana;
	int cantVertices;
	float **vertices;

};

