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

enum TipoTexturaBoton{

	objEsfera, objCubo , objToroide, objCilindro,
	matBrillante, matTexturado, matReflectivo, matSemimate,
	efecRetorcer, efecRuido, efecDoblar, efecEsferizar

};



class AdministradorTexturas
{
private:
	
	
	glTexture textMate,textLadrillos,textSolido,textMetalica;
	glTexture objTexture[4];
	glTexture matTexture[4];
	glTexture efecTexture[4];
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
	void generarCoordTextBoton(float u,float v);
	void generarCoordText();
	void generarCoordTextTapa();
	void elegirTextura(TipoTextura tipo);
	void elegirTexturaBoton(TipoTexturaBoton tipoBoton);
	~AdministradorTexturas(void);
};


static bool instanciado = false;
static AdministradorTexturas* instancia;