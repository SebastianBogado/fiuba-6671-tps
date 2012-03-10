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
	static Iluminacion* getInstancia();
	~Iluminacion(void);

	void setPosicionDeLasLuces(int i, vec3 posicion);

	struct propLuz{
		bool prendida;
		vec4 posicion;
		vec4 direccion;
	};

	//Devuelve la cantidad de luces que hay
	int cantidadDeLuces();

	//Devuelve las propiedades de la luz iésima, con la posición y dirección según la cámara
	propLuz luz(int i);
private:
	propLuz* luces;
	static Camara* camara;
	int cantDeLuces;

	/* Singleton */
	
	//Arma el vector luces
	Iluminacion();
	static Iluminacion* instancia;
};

