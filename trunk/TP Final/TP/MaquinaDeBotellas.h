#pragma once
#include "ObjetoGraficoCubico.h"
#include "Maquina.h"
class MaquinaDeBotellas :
	public ObjetoGraficoCubico,
	public Maquina
{
public:
	MaquinaDeBotellas(void);
	//Interfaz de ObjetoGrafico
	void graficar();

	void actualizarAtributos();


	//Interfaz de Maquina
	void iniciarAnimacion(Botella* botella);

	bool animacionFinalizada();

	TipoMaquina tipo(){ return TipoMaquina::Expendedora; }


	void definirMateriales();


	virtual ~MaquinaDeBotellas(void);

protected:
	
};

