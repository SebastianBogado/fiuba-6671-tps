#include "Control.h"


float Control::posicionPorDefecto[3] = {15.0, 15.0, 5.0};
float Control::atPorDefecto[3] = { 0.0,  0.0, 0.0};
float Control::upPorDefecto[3] = { 0.0,  0.0, 1.0}; 

Camara* Control::camara = new Camara(&atPorDefecto[0], &posicionPorDefecto[0], &upPorDefecto[0]);

Control::Control(bool debug){
	this->debug = debug;
}
Control::~Control(){
	delete camara;
}

void Control::teclado(unsigned char tecla, int x, int y){
	tecla = tolower(tecla);
	camara->controladorDeTeclado(tecla);
	//Cualquier otro control inherente al teclado va acá, 
	//junto con la discriminación entre release y debug mode
	switch (tecla){
	case 'q': exit(0); break;
	default: break;
	}
}

void Control::mouse(int button, int state, int x, int y){
	camara->controladorBotonesMouse(button, state, x, y);
	//Cualquier otro control inherente al mouse va acá, 
	//junto con la discriminación entre release y debug mode
}

void Control::mouseMov(int x, int y){
	camara->controladorMovMouse(x, y);
	//Cualquier otro control inherente al mouse en movimiento va acá, 
	//junto con la discriminación entre release y debug mode
}
