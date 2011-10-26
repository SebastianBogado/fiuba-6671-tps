#pragma once

#include <GL/glut.h>
#include "Boton.h"

class MenuDeCuatroBotones{
public:
	MenuDeCuatroBotones(int ventana, int posicionX, int posicionY, int ancho, int alto, Boton* botones);
	~MenuDeCuatroBotones(void);

	void resize(int nuevoX, int nuevoY, int nuevoAncho, int nuevoAlto);

	//Devuelve el identificador �nico de cada bot�n
	int getHandle(int i);
	
private:
	int handle[4];
	int ventana;
	int posicionX, posicionY;
	int ancho, alto;
	Boton* botones;

	void posicionarBotones();
};

