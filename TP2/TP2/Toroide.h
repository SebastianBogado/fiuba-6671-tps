#pragma once
#include "superficie.h"
#include "Circunferencia.h"
#include <glm/glm.hpp>
class Toroide :
	public Superficie
{
private:
	float PI;
	float radioInt,radioExt;
	Curva* curvaExterna;

	glm::vec3 rotarEnZ(float radianes,glm::vec3);
	glm::vec3 rotarEnX(glm::vec3);
	glm::vec3 transformarPunto(float radianes);
	void construir();


public:
	Toroide();
	Toroide(float radioInterno,float radioExterno, int paso);
	virtual float* getPunto(int Xn, int Yn, int Zn);

	float gradosARadianes(float grados);

	virtual ~Toroide(void);
};

