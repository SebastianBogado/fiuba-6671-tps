#pragma once
#include "superficie.h"
class SuperficieDeBarrido :	public Superficie{
public:
	SuperficieDeBarrido(Curva* curvaBorde, Curva* curvaCamino);
	~SuperficieDeBarrido(void);

	void discretizar(int discretizacionBorde, int discretizacionAvance);
private:
	Curva* curvaCamino;
	mat4 calcularRealineacion(float t);
};

