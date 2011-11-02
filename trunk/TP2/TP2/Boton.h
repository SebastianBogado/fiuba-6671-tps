#pragma once

#include <GL/glut.h>
#include <iostream>
#include "AdministradorTexturas.h"
using std::string;

static bool primeroEnSalir=false;

class Boton{
public:
	Boton();
	Boton(char* pathText, void (*mouseCallback)(int, int, int, int));
	Boton(int tipo, void (*mouseCallback)(int, int, int, int));
	~Boton(void);

	//un arreglo para poder hacer el callback correctamente
	static void displayWrapper();

	typedef void (*mouse)(int, int, int, int);
	
	mouse getMouseCallback();

	void cargarTextura();

private:
	void display();
	mouse pMouse;

	TextureLoader texLoader;
	glTexture textura;
	bool texturaCargada;
	char* pathTextura;
	int tipoBoton;
	
};

