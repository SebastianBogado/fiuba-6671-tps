#pragma once
#include "bezier.h"

/* Una excelente aproximación de una circunferencia en el y = 0 mediante curvas de Bezier */
class Circunferencia :
	public Bezier
{
public:
	Circunferencia(float radio, vec3 centro = vec3(0.0));
	~Circunferencia(void);
};

