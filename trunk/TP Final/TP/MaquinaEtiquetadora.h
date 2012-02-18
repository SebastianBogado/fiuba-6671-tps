#pragma once
#include "ObjetoGrafico.h"
class MaquinaEtiquetadora :
	public ObjetoGrafico
{
public:
	MaquinaEtiquetadora(void);

	void graficar();

private:

	void aplicarShader();
	void detenerShader();

	virtual ~MaquinaEtiquetadora(void);
};

