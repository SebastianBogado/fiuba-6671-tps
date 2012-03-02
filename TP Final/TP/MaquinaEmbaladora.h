#pragma once
#include "ObjetoGraficoCubico.h"
#include "Maquina.h"

class MaquinaEmbaladora :
	public ObjetoGraficoCubico,
	public Maquina
{
public:
	MaquinaEmbaladora(void);

	//Interfaz de ObjetoGrafico
	void graficar();
	void actualizarAtributos();

	//Interfaz de Maquina
	void iniciarAnimacion(Botella* botella);
	bool animacionFinalizada();
	TipoMaquina tipo(){ return TipoMaquina::Embaladora; }


	~MaquinaEmbaladora(void);

private:
	void aplicarShader();
	void detenerShader();

};

