#include "MenuDeCuatroBotones.h"
#include <iostream>
using namespace std;
extern void* pBotonActual;

MenuDeCuatroBotones::MenuDeCuatroBotones(int ventana, int posicionX, int posicionY, int ancho, int alto, Boton* botones){
	this->ventana = ventana;
	this->posicionX = posicionX;
	this->posicionY = posicionY;
	this->ancho = ancho;
	this->alto = alto;
	this->botones = botones;
	for (int i = 0; i < 4; i++)
		this->handle[i] = 0;
	this->posicionarBotones();
}


MenuDeCuatroBotones::~MenuDeCuatroBotones(void){
	delete botones;
}

void MenuDeCuatroBotones::posicionarBotones(){
	if (this->alto > this->ancho){
		//menú vertical
		int separacion = this->alto / 4;
		int altoBoton = this->alto / 4;
		int anchoBoton = this->ancho;
		for (int i = 0; i < 4; i++){
			if (this->handle[i] == 0){//si no fueron inicializados
				this->handle[i] = glutCreateSubWindow(this->ventana, 
					this->posicionX, this->posicionY + i*separacion, 
					anchoBoton, altoBoton);
				pBotonActual = (void*) &botones[i];
				botones[i].cargarTextura();
				glutDisplayFunc(Boton::displayWrapper);
				glutMouseFunc(botones[i].getMouseCallback());
			}
			else{//si ya fueron inicializados, entonces los reposiciona
				glutSetWindow(this->handle[i]);
				glutPositionWindow(this->posicionX, this->posicionY + i*separacion);
				glutReshapeWindow(anchoBoton, altoBoton);
			}
		}
	}
	else{//menú horizontal; no hay menúes cuadrados en este programa
		int separacion = ancho / 4;
		int altoBoton = this->alto; 
		int anchoBoton = this->ancho/4; 
		for (int i = 0; i < 4; i++){
			if (this->handle[i] == 0){//si no fueron inicializados
				this->handle[i] = glutCreateSubWindow(this->ventana, 
					this->posicionX + i*separacion, this->posicionY, 
					anchoBoton, altoBoton); 
				pBotonActual = (void*) &botones[i];
				botones[i].cargarTextura();
				glutDisplayFunc(Boton::displayWrapper);
				glutMouseFunc(botones[i].getMouseCallback());
			}
			else{//si ya fueron inicializados, entonces los reposiciona
				glutSetWindow(this->handle[i]);
				glutPositionWindow(this->posicionX + i*separacion, this->posicionY);
				glutReshapeWindow(anchoBoton, altoBoton);
			}
		}
	}
}

void MenuDeCuatroBotones::resize(int nuevoX, int nuevoY, int nuevoAncho, int nuevoAlto){
	this->posicionX = nuevoX;
	this->posicionY = nuevoY;
	this->ancho = nuevoAncho;
	this->alto = nuevoAlto;
	this->posicionarBotones();
}
int MenuDeCuatroBotones::getHandle(int i){ return this->handle[i]; }