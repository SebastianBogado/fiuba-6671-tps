#pragma once
#include "objetografico.h"
#include "Maquina.h"

class CintaTransportadora :
	public ObjetoGrafico,
	public Maquina
{
public:
	CintaTransportadora(void);

	/////////////////////////////
	//Interfaz de ObjetoGrafico//
	/////////////////////////////
	void graficar();

	void actualizarAtributos();

	////////////////////////
	//Interfaz de Maquina//
	///////////////////////
	TipoMaquina tipo(){ return TipoMaquina::Transportadora;}

	void iniciarAnimacion(Botella* botella){};

	bool animacionFinalizada(){ return true;};

	/////////////////////////////////
	//Metodos Particulares de Clase//
	/////////////////////////////////
	void desplazarCinta();
	void detenerCinta();


	float definirPosicionEnTramos(float posicionRelativa);

	void aumentarDiscretizacionDeCinta();
	void disminuirDiscretizacionDeCinta();

	bool cintaActiva(){ return this->cintaEnMovimiento; }

	float nuevaPosicionDeTramo(float posicion);
	void nuevaPosicion(float posicionDeTramo,float* posicion);

	virtual ~CintaTransportadora(void);

private:
	void definirMateriales();
	void graficarCinta();

	void inicializarAtributos();
	void inicializarCurvas();

	float pasoDeDiscretizacionGeneral;
	float desplazamientoDeCinta;
	bool cintaEnMovimiento;


	BSpline* formaCintaTransportadora;
	BSpline* caminoCintaTransportadora;
	SuperficieDeBarrido* superficieCintaTransportadora;
	static vec3 puntosForma[];
	static vec3 puntosCamino[];
	static int cantidadDePuntosForma;
	static int cantidadDePuntosCamino;

	int discretAvance,discretBorde;

	vec3 posicionInicialEnCinta;

	float _testLargoCinta;

};

