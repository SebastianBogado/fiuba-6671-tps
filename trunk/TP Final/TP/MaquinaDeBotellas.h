#pragma once
#include "ObjetoGraficoCubico.h"
class MaquinaDeBotellas :
	public ObjetoGraficoCubico
{
public:
	MaquinaDeBotellas(void);

	void graficar();

	void actualizarAtributos();

	virtual ~MaquinaDeBotellas(void);

protected:

	void aplicarShader();
	void detenerShader();
	
};
