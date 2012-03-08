#pragma once
#include "ObjetoGraficoCubico.h"
#include"Maquina.h"

class MaquinaEtiquetadora :
	public ObjetoGraficoCubico,
	public Maquina

{
public:
	MaquinaEtiquetadora(void);

	void graficar();

	void actualizarAtributos();

	//Interfaz de Maquina
	void iniciarAnimacion(Botella* botella);
	bool animacionFinalizada();
	TipoMaquina tipo(){ return TipoMaquina::Etiquetadora; }

	//Metodos Particulares
	void definirMateriales();

	virtual ~MaquinaEtiquetadora(void);
	
private:
	
	void aplicarShader();
	void detenerShader();

	void dibujarBrazoMovil();
	 
	float desplazamientoBrazoMovil;
};

