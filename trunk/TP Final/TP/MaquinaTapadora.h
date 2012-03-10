#pragma once
#include "objetograficocubico.h"
#include "Maquina.h"
class MaquinaTapadora :
	public ObjetoGraficoCubico,
	public Maquina
{
public:
	MaquinaTapadora(void);

	void graficar();

	void actualizarAtributos();
	

	//Interfaz de Clase Maquina

	void iniciarAnimacion(Botella* botella);

	bool animacionFinalizada();

	TipoMaquina tipo(){ return TipoMaquina::Tapadora; }

	virtual ~MaquinaTapadora(void);


private:

	void inicializarAtributos();
	
	void definirMaterial();

	//void inicializarCurvas();

	void dibujarBrazoMovil();
	Circunferencia* curvaPiezaBrazoMovil;

	bool sentidoDeBrazoMovilCambiado;
	float desplazamientoBrazoMovil;
	float pasoDesplazamientoDeBrazo;
	Botella* botellaActual;

	
};

