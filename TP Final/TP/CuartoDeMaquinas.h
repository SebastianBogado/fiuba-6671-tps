#pragma once
#include "ObjetoGraficoCubico.h"

class CuartoDeMaquinas :
	public ObjetoGraficoCubico
{
public:
	CuartoDeMaquinas(void);

	void graficar();

	void actualizarAtributos();

	~CuartoDeMaquinas(void);

private:

	void aplicarShader();
	void detenerShader();

};

