#pragma once
#include "objetografico.h"
class CintaTransportadora :
	public ObjetoGrafico
{
public:
	CintaTransportadora(void);

	void graficar();

	void actualizarAtributos();

	virtual ~CintaTransportadora(void);

private:

	void aplicarShader();
	void detenerShader();
};

