#include "Toroide.h"


Toroide::Toroide()
{
	this->radioInt=0.3;
	this->radioExt=1.0;
	this->construir();
}


Toroide::Toroide(float radioInterior,float radioExterior, int paso){

	this->radioInt = radioInterior;
	this->radioExt = radioExterior;
	this->paso= paso;

	this->construir();
}


void Toroide::construir(){
	this->PI=3.1415926535897932;
	this->tengoTapas=false;
	this->puntosEnAlto=this->paso;
	this->curvaBorde=new Circunferencia(this->radioInt,this->paso);
	this->curvaExterna= new Circunferencia(this->radioExt,this->paso);

}



float* Toroide::getPunto(int Xn, int Yn, int Zn){

	float* punto=new float[3];

	glm::vec3 puntoPrimeraFase = this->rotarEnX(glm::vec3(this->curvaBorde->Xn(Xn),this->curvaBorde->Yn(Yn),0.0));

	float angulo = this->PI * 2.0 *(float(Zn)/float(this->curvaExterna->cantDePuntos()));

	glm::vec3 puntoSegundaFase = this->rotarEnZ(angulo,puntoPrimeraFase);


	//glm::vec3 posicionCentroCurva = glm::vec3(this->curvaExterna->Xn(Zn),this->curvaExterna->Yn(Zn),0.0);
	glm::vec3 posicionCentroCurva = this->rotarEnZ(angulo,glm::vec3(this->radioExt,0.0,0.0));
	puntoSegundaFase+= posicionCentroCurva;
	
	punto[0]= puntoSegundaFase.x;
	punto[1]= puntoSegundaFase.y;
	punto[2]= puntoSegundaFase.z;

	return punto;
}

glm::vec3 Toroide::rotarEnX(glm::vec3 posicion){

	float angulo=this->gradosARadianes(-90.0);

	float cosAngulo = cos(angulo);
	float sinAngulo = sin(angulo);

	glm::mat3x3 matrizRotacionX(0.0);

	matrizRotacionX[0] = glm::vec3(1.0,0.0,0.0);
	matrizRotacionX[1] = glm::vec3(0.0,cosAngulo,-sinAngulo);
	matrizRotacionX[2] = glm::vec3(0.0,sinAngulo,cosAngulo);


	glm::vec3 resultado = matrizRotacionX * posicion;

	return resultado;
}



glm::vec3 Toroide::rotarEnZ(float angulo,glm::vec3 posicion){

	float cosAngulo = cos(angulo);
	float sinAngulo = sin(angulo);
	
	glm::mat3x3 matrizRotacionZ(0.0);

	matrizRotacionZ[0] = glm::vec3(cosAngulo,-sinAngulo,0.0);

	matrizRotacionZ[1] = glm::vec3(sinAngulo,cosAngulo,0.0);

	matrizRotacionZ[2] = glm::vec3(0.0,0.0,1.0);

	glm::vec3 resultado = matrizRotacionZ * posicion;

	return resultado;

}

float Toroide::gradosARadianes(float grados){

	float radianes = grados * this->PI / 180.0 ;
	
	return radianes;

}

Toroide::~Toroide(void)
{
	delete this->curvaExterna;

}
