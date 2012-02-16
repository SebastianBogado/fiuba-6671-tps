#pragma once
#include "superficie.h"
//Revoluci�n al rededor del eje z
class SuperficieDeRevolucion :	public Superficie{
public:
	SuperficieDeRevolucion(Curva* curvaBorde, float anguloEnGrados = 360, vec3 ejeDeRotacion = vec3(0.0, 0.0, 1.0));
	
	void discretizar(int discretizacionBorde, int discretizacionAvance);
private:
	float angulo;
	vec3 ejeDeRotacion;
};

