#pragma once
#include "objetografico.h"
class PaqueteDeBotellas :
	public ObjetoGrafico
{
public:
	PaqueteDeBotellas(void);

	void graficar();
	void actualizarAtributos();

	virtual ~PaqueteDeBotellas(void);

private:

	void aplicarShader();
	void detenerShader();
};

