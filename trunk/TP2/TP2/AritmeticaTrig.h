#include <iostream>
//#include <math.h>
#include <glm\glm.hpp>


#pragma once
class AritmeticaTrig
{
private:
	float puntoAnterior[3];
	float phiAnt,thetaAnt;
	float radio;
	bool radioCargado;

	float phi,theta,*punto_actual;
	
	

	float PI;
	float Dos_PI;


	float calcularRadio();
	void guardarCambios();

public:
	AritmeticaTrig(void);
	void puntoActual(float* punto);
	float calcularPhi();
	float calcularTheta();
	float pi();
	float dos_pi();
	void reiniciar();
	~AritmeticaTrig(void);
};

