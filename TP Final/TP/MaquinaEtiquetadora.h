#pragma once
#include "ObjetoGrafico.h"
class MaquinaEtiquetadora :
	public ObjetoGrafico
{
public:
	MaquinaEtiquetadora(void);

	void graficar();

	void actualizarAtributos();

private:

	void aplicarShader();
	void detenerShader();

	virtual ~MaquinaEtiquetadora(void);
};

