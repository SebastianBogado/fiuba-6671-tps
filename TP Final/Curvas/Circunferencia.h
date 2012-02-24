#pragma once
#include "bezier.h"

/* Una excelente aproximaci�n de una circunferencia media curvas de Bezier */
class Circunferencia :
	public Bezier
{
public:
	Circunferencia(float radio);
	~Circunferencia(void);
};

