#pragma once

#include "MaquinaDeBotellas.h"
#include "CuartoDeMaquinas.h"
#include "MaquinaEmbaladora.h"

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

