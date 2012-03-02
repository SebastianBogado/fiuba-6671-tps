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

	bool cintaActiva(){ return this->cintaEnMovimiento; }

	float nuevaPosicionDeTramo(float posicion);
	void nuevaPosicion(float posicionDeTramo,float* posicion);

	virtual ~CintaTransportadora(void);

private:

	void aplicarShader();
	void detenerShader();

	float pasoDeDiscretizacionGeneral;
	bool cintaEnMovimiento;

	float _testLargoCinta;

};

