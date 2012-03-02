#pragma once
#include "objetografico.h"
#include "Maquina.h"


class MaquinaDeLlenado :
	public ObjetoGrafico,
	public Maquina
{
public:
	MaquinaDeLlenado(void);

	//Interfaz de ObjetoGrafico
	void graficar();
	void actualizarAtributos();


	//Interfaz de Maquina
	void iniciarAnimacion(Botella* botella);
	bool animacionFinalizada();
	TipoMaquina tipo(){ return TipoMaquina::Llenado; }


	virtual ~MaquinaDeLlenado(void);

private:

	void aplicarShader();
	void detenerShader();
};

