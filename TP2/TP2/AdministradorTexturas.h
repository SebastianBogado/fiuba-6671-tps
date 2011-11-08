#pragma once
#include "TextureLoader.h"
#include "AritmeticaTrig.h"
#include <GL/freeglut.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <glm/glm.hpp>

enum TipoTextura {
	Mate,
	Metalica,
	Ladrillos,
	Solido,
	Caja_Cielo

};


using namespace glm;

class AdministradorTexturas
{
private:
	
	
	glTexture textCaja_Cielo,textLadrillos;
	TextureLoader textLoader,textLoader2;

	AritmeticaTrig aritmTrig;

	GLfloat coordX,coordY;
	int numero_Punto;

	GLfloat incremento,incX,incY;


	bool primerPuntoTapa,primerPunto;
	vec2 puntoCentroTapa;
	vec2 dirActual,dirAnt; 

	void sumarVecSup();
	void sumarVecInf();
	void comprobarPuntos();

	void cargarParametrosTextura();
	
public:
	AdministradorTexturas(void);

	static AdministradorTexturas* getInstancia();

	void CargarTexturas();
	void generarCoordText();
	void generarCoordText(float* punto);
	void generarCoordTextTapa(float *punto);
	void elegirTextura(TipoTextura tipo);

	void reiniciar();

	int getID(TipoTextura tipo);

	~AdministradorTexturas(void);
};


static bool instanciado = false;
static AdministradorTexturas* instancia;