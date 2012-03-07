#pragma once
#include "Superficie.h"

class SuperficieDeRevolucion :	public Superficie{
public:
	SuperficieDeRevolucion(Curva* curvaBorde, float anguloEnGrados = 360, vec3 ejeDeRotacion = vec3(0.0, 0.0, 1.0));
	
	SuperficieDiscretizada* discretizar(int discretizacionBorde, int discretizacionAvance);
private:
	float angulo;
	vec3 ejeDeRotacion;

	bool invertirEjeDeRotacionParaLaNormal(vec3 v, vec3 tg); 
};

