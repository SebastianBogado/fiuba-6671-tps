#pragma once

#include <iostream>
using namespace std;
#include <glm\glm.hpp>
using glm::vec3;
#include "..\ShadersTest\SOIL\SOIL.h"
#include "..\ShadersTest\GLSLProgram.h"
#include "propMaterial.h"
#include "..\Superficies\SuperficieDeRevolucion.h"
#include "..\Superficies\SuperficieDeBarrido.h"
#include "..\Superficies\Emparchador.h"
#include "..\Curvas\BSpline.h"
#include "..\Curvas\Bezier.h"
#include "..\Curvas\Circunferencia.h"
#include <GL\freeglut.h>


class ObjetoGrafico
{
public:
	ObjetoGrafico(void);


	/*
		Metodo que dibuja al objeto en la escena
	*/

	virtual void graficar()=0;


	/*
		Metodo que actualiza el estado del objeto para el proxima vez que sea dibujado
	*/

	virtual void actualizarAtributos()=0;

	/*
		Define la posicion de donde se graficara el Objeto
	*/
	void posicionar(float *nuevaPosicion);

	void posicionar(const float& x,const float& y,const float& z);

	inline float* vectorPosicion(){ return posicionObjeto;}

	void* devolverPuntero(){ return (reinterpret_cast<void*>(this));}

	virtual ~ObjetoGrafico(void);

protected:

	/*
		Funciones para el manejo de shader del objeto
	*/
	void aplicarShader();
	void detenerShader();
	void aplicarPhong();
	void detenerPhong();


	

	/*
		... y mas cosas que faltan definir (como texturas, etc)
	*/

	void inicializarVector(float *vector,float x,float y, float z);


	void dibujarPiramide(float *color);

	//////////////////////
	//Atributos de Clase//
	//////////////////////

	float *posicionObjeto;
	string rutaTextura;
	GLuint texturaID;
	string rutaShaderDeVertices,rutaShaderDeFragmentos;
	GLuint dl_handle;

	GLSLProgram* shaders;
	//Para los materiales que no tienen ninguna particularidad, se usa un phong genérico
	static GLSLProgram* phong; 
	propMaterial material;
};

