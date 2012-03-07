#pragma once
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using glm::vec3; 
using glm::vec4;
using glm::mat4;
#include "..\Camara\Camara.h"
#include <iostream>

class Iluminacion{
public:
	//Arma el vector luces
	Iluminacion(void);
	~Iluminacion(void);

	struct propLuz{
		bool prendida;
		vec4 posicion;
		vec4 direccion;
		float angulo;
		//Constante para calcular el decrecimiento de la intensidad de la luz
		//según se aleja del centro, como el brillo en un material
		float k; 
		vec3 amb;
		vec3 dif;
		vec3 espec;
	};

	//Devuelve la cantidad de luces que hay
	int cantidadDeLuces();

	//Devuelve las propiedades de la luz iésima, con la posición y dirección según la cámara
	propLuz luz(int i);
private:
	propLuz* luces;
	Camara* camara;
	int cantDeLuces;
};

