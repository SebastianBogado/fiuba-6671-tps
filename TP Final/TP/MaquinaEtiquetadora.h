#pragma once
#include "ObjetoGrafico.h"
#include"Maquina.h"

class MaquinaEtiquetadora :
	public ObjetoGrafico,
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

	virtual ~MaquinaEtiquetadora(void);

private:
	
	void aplicarShader();
	void detenerShader();

	
};

