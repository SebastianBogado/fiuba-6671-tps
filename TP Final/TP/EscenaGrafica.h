#pragma once

#include "MaquinaDeBotellas.h"


class EscenaGrafica
{
public:
	EscenaGrafica(void);

	void graficar();

	~EscenaGrafica(void);

private:
	ObjetoGrafico **objetos;
	int cantidadObjetos;

};

