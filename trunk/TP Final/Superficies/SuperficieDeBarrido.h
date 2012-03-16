#pragma once
#include "superficie.h"
class SuperficieDeBarrido :	public Superficie{
public:
	SuperficieDeBarrido(Curva* curvaBorde, Curva* curvaCamino);
	~SuperficieDeBarrido(void);

	SuperficieDiscretizada* discretizar(int discretizacionBorde, int discretizacionAvance);
private:
	Curva* curvaCamino;
	mat4 calcularRealineacion(float t);

	//Por errores de redondeo, el punto flotante puede variar mucho en sus últimos decimales
	//Este método está para considerar que dos vectores son iguales si sus componentes
	// coinciden hasta los primeros cuatro decimales
	bool coincidenLosPrimerosCuatroDecimales(vec3 x, vec3 y);
};

