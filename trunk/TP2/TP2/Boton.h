#pragma once

#include <GL/glut.h>
#include <iostream>
#include "AdministradorTexturas.h"
using std::string;

class Boton{
public:
	Boton(string pathTextura, void (*mouseCallback)(int, int, int, int));
	~Boton(void);

	//un arreglo para poder hacer el callback correctamente
	static void displayWrapper();

	typedef void (*mouse)(int, int, int, int);
	
	mouse getMouseCallback();

private:
	void display();
	mouse pMouse;

	AdministradorTexturas *adminText;
};

