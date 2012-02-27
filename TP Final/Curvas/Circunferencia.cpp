#include "Circunferencia.h"


Circunferencia::Circunferencia(float radio, vec3 centro) : Bezier(4){
	float k = 0.5522847498; //http://www.whizkidtech.redprince.net/bezier/circle/
	float l = radio * k;

	vec3 p1  = vec3(  radio + centro.x,	0.0 + centro.y,    0.0 + centro.z);
	vec3 p2  = vec3(  radio + centro.x,	0.0 + centro.y,      l + centro.z);
	vec3 p3  = vec3(      l + centro.x,	0.0 + centro.y,  radio + centro.z);
	vec3 p4  = vec3(    0.0 + centro.x,	0.0 + centro.y,  radio + centro.z);
	vec3 p5  = vec3(     -l + centro.x,	0.0 + centro.y,  radio + centro.z);
	vec3 p6  = vec3( -radio + centro.x,	0.0 + centro.y,      l + centro.z);
	vec3 p7  = vec3( -radio + centro.x,	0.0 + centro.y,    0.0 + centro.z);
	vec3 p8  = vec3( -radio + centro.x,	0.0 + centro.y,     -l + centro.z);
	vec3 p9  = vec3(     -l + centro.x,	0.0 + centro.y, -radio + centro.z);
	vec3 p10 = vec3(    0.0 + centro.x,	0.0 + centro.y, -radio + centro.z);
	vec3 p11 = vec3(      l + centro.x,	0.0 + centro.y, -radio + centro.z);
	vec3 p12 = vec3(  radio + centro.x,	0.0 + centro.y,     -l + centro.z);
	vec3 p13 = vec3(  radio + centro.x,	0.0 + centro.y,    0.0 + centro.z);
	
	this->incluirPunto(p1);
	this->incluirPunto(p2);
	this->incluirPunto(p3);
	this->incluirPunto(p4);
	this->incluirPunto(p5);
	this->incluirPunto(p6);
	this->incluirPunto(p7);
	this->incluirPunto(p8);
	this->incluirPunto(p9);
	this->incluirPunto(p10);
	this->incluirPunto(p11);
	this->incluirPunto(p12);
	this->incluirPunto(p13);
}


Circunferencia::~Circunferencia(void)
{
}
