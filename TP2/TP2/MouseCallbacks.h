#pragma once

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

const int BOTON_ESFERA = 1;
const int BOTON_CUBO = 2;
const int BOTON_TOROIDE = 3;
const int BOTON_CILINDRO = 4;

const int BOTON_MATERIAL_SOMBREADO_BRILLANTE = 5;
const int BOTON_MATERIAL_SOMBREADO_TEXTURADO = 6;
const int BOTON_MATERIAL_REFLECTIVO = 7;
const int BOTON_MATERIAL_SOMBREADO_SEMIMATE = 8;

const int BOTON_RETORCER = 9;
const int BOTON_RUIDO = 10;
const int BOTON_DOBLAR = 11;
const int BOTON_ESFERIZAR = 12;

class MouseCallbacks
{
public:
	typedef void (*mousee)(int, int, int, int);
	mousee getCallback(int boton);
private:
	static void botonEsfera(int button, int state, int x, int y);
	static void botonCubo(int button, int state, int x, int y);
	static void botonToroide(int button, int state, int x, int y);
	static void botonCilindro(int button, int state, int x, int y);
	static void botonMaterialSombreadoBrillante(int button, int state, int x, int y);
	static void botonMaterialSombreadoTexturado(int button, int state, int x, int y);
	static void botonMaterialReflectivo(int button, int state, int x, int y);
	static void botonMaterialSombreadoSemimate(int button, int state, int x, int y);
	static void botonRetorcer(int button, int state, int x, int y);
	static void botonRuido(int button, int state, int x, int y);
	static void botonDoblar(int button, int state, int x, int y);
	static void botonEsferizar(int button, int state, int x, int y);
};

