#pragma once
#include "ObjetoGraficoCubico.h"
class MaquinaEmbaladora :
	public ObjetoGraficoCubico
{
public:
	MaquinaEmbaladora(void);

	void graficar();
	void actualizarAtributos();

	~MaquinaEmbaladora(void);

private:
	void aplicarShader();
	void detenerShader();

};

