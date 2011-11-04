#pragma once
#include "TextureLoader.h"
#include "AritmeticaTrig.h"
#include <GL/freeglut.h>
#include <gl\gl.h>
#include <gl\glu.h>

enum TipoTextura {
	Mate,
	Metalica,
	Ladrillos,
	Solido,
	Caja_Cielo

};




class AdministradorTexturas
{
private:
	
	
	glTexture textCaja_Cielo,textLadrillos;
	TextureLoader textLoader,textLoader2;

	AritmeticaTrig aritmTrig;

	GLfloat coordX,coordY;
	int numero_Punto;

	GLfloat incremento,incX,incY;

	void sumarVecSup();
	void sumarVecInf();
	void comprobarPuntos();
	
public:
	AdministradorTexturas(void);

	static AdministradorTexturas* getInstancia();

	void CargarTexturas();
	void generarCoordText();
	void generarCoordText(float* punto);
	void generarCoordTextTapa();
	void elegirTextura(TipoTextura tipo);

	int getID(TipoTextura tipo);

	~AdministradorTexturas(void);
};


static bool instanciado = false;
static AdministradorTexturas* instancia;