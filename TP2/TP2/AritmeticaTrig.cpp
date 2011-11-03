#include "AritmeticaTrig.h"


AritmeticaTrig::AritmeticaTrig(void)
{

	this->PI=3.14; // faltan mas digitos...
	this->Dos_PI=2.0*this->PI;

	this->puntoAnterior[0]=0.0;
	this->puntoAnterior[1]=0.0;
	this->puntoAnterior[2]=0.0;

	this->radio=0.0;
	this->radioCargado=false;

	this->thetaAnt=0.0;
	this->phiAnt=0.0;

	this->phi=0.0;
	this->theta=0.0;
	this->punto_actual;

}

void AritmeticaTrig::reiniciar(){

	this->puntoAnterior[0]=0.0;
	this->puntoAnterior[1]=0.0;
	this->puntoAnterior[2]=0.0;

	this->radio=0.0;
	this->radioCargado=false;

	this->thetaAnt=0.0;
	this->phiAnt=0.0;

	this->phi=0.0;
	this->theta=0.0;
}

void AritmeticaTrig::puntoActual(float* punto){

	this->punto_actual=punto;

	if (!this->radioCargado){
		this->radio=this->calcularRadio();
		this->radioCargado=true;
	}

}


float AritmeticaTrig::calcularRadio(){

	float resultado = 0.0;

	for (int i=0;i<3;i++)
		resultado += this->punto_actual[i] * this->punto_actual[i];

	resultado = sqrt (resultado); 

	return resultado;

}

float AritmeticaTrig::calcularPhi(){

	if(this->puntoAnterior[2]==this->punto_actual[2])
		this->phi=this->phiAnt;	
	else
		this->phi= acos (this->punto_actual[2] / this->radio);

	return this->phi;

}

float AritmeticaTrig::calcularTheta(){

	float sinPhi = sin(this->phi);

	float acosAngulo;

	if ( sinPhi > 0.0) {
			acosAngulo = acos( this->punto_actual[0] / (sinPhi * this->radio) );
	}else{
		if (this->punto_actual[1]>=0.0)
			acosAngulo = this->thetaAnt;
		else 
			acosAngulo = this->Dos_PI - this->thetaAnt;
	}

	if (this->punto_actual[1]>=0.0)
		this->theta = acosAngulo;
	else 
		this->theta = this->Dos_PI - acosAngulo;

	
	this->guardarCambios();

	return this->theta;

}

float AritmeticaTrig::pi(){	return this->PI; }

float AritmeticaTrig::dos_pi(){	return this->Dos_PI;}


void AritmeticaTrig::guardarCambios(){

	this->phiAnt=this->phi;
	this->thetaAnt=this->theta;

	for(int i=0;i<3;i++)
		this->puntoAnterior[i]=this->punto_actual[i];

}

AritmeticaTrig::~AritmeticaTrig(void)
{
}
