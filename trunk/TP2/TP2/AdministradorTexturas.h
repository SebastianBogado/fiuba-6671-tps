#pragma once
#include "TextureLoader.h"
#include <GL/freeglut.h>
#include <gl\gl.h>
#include <gl\glu.h>

enum TipoTextura {
	Mate,
	Metalica,
	Ladrillos,
	Solido

};




class AdministradorTexturas
{
private:
	
	
	glTexture textMate,textLadrillos,textSolido,textMetalica;
	TextureLoader textLoader;
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
	void generarCoordTextTapa();
	void elegirTextura(TipoTextura tipo);

	int getID(TipoTextura tipo);

	~AdministradorTexturas(void);
};


static bool instanciado = false;
static AdministradorTexturas* instancia;