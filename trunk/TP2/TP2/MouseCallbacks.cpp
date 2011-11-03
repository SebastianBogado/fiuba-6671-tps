#include "MouseCallbacks.h"

extern bool verEsfera;
extern bool verCubo;
extern bool verToroide;
extern bool verCilindro;

extern bool verMaterialSombreadoBrillante;
extern bool verMaterialSombreadoTexturado;
extern bool verMaterialReflectivo;
extern bool verMaterialSombreadoSemimate;

extern bool verRetorcer;
extern bool verRuido;
extern bool verDoblar;
extern bool verEsferizar;

extern float arista;


MouseCallbacks::mousee MouseCallbacks::getCallback(int boton){
	switch(boton){
	case BOTON_ESFERA:
		return &botonEsfera;
		break;
	case BOTON_CUBO:
		return &botonCubo;
		break;
	case BOTON_TOROIDE:
		return &botonToroide;
		break;
	case BOTON_CILINDRO:
		return &botonCilindro;
		break;

	case BOTON_MATERIAL_SOMBREADO_BRILLANTE:
		return &botonMaterialSombreadoBrillante;
		break;
	case BOTON_MATERIAL_SOMBREADO_TEXTURADO:
		return &botonMaterialSombreadoTexturado;
		break;
	case BOTON_MATERIAL_REFLECTIVO:
		return &botonMaterialReflectivo;
		break;
	case BOTON_MATERIAL_SOMBREADO_SEMIMATE:
		return &botonMaterialSombreadoSemimate;
		break;

	case BOTON_RETORCER:
		return &botonRetorcer;
		break;
	case BOTON_RUIDO:
		return &botonRuido;
		break;
	case BOTON_DOBLAR:
		return &botonDoblar;
		break;
	case BOTON_ESFERIZAR:
		return &botonEsferizar;
		break;
	default:
		return 0;
		break;
	}
}

void MouseCallbacks::botonEsfera(int button, int state, int x, int y){
	verEsfera = true;
	verCubo = false;
	verToroide = false;
	verCilindro = false;
	glutPostRedisplay();
}
void MouseCallbacks::botonCubo(int button, int state, int x, int y){
	verEsfera = false;
	verCubo = true;
	verToroide = false;
	verCilindro = false;
	glutPostRedisplay();
}
void MouseCallbacks::botonToroide(int button, int state, int x, int y){
	verEsfera = false;
	verCubo = false;
	verToroide = true;
	verCilindro = false;
	glutPostRedisplay();
}
void MouseCallbacks::botonCilindro(int button, int state, int x, int y){
	verEsfera = false;
	verCubo = false;
	verToroide = false;
	verCilindro = true;
	glutPostRedisplay();
}
void MouseCallbacks::botonMaterialSombreadoBrillante(int button, int state, int x, int y){
	verMaterialSombreadoBrillante = true;
	verMaterialSombreadoTexturado = false;
	verMaterialReflectivo = false;
	verMaterialSombreadoSemimate = false;
	glutPostRedisplay();
}
void MouseCallbacks::botonMaterialSombreadoTexturado(int button, int state, int x, int y){
	verMaterialSombreadoBrillante = false;
	verMaterialSombreadoTexturado = true;
	verMaterialReflectivo = false;
	verMaterialSombreadoSemimate = false;
	glutPostRedisplay();
}
void MouseCallbacks::botonMaterialReflectivo(int button, int state, int x, int y){
	verMaterialSombreadoBrillante = false;
	verMaterialSombreadoTexturado = false;
	verMaterialReflectivo = true;
	verMaterialSombreadoSemimate = false;
	glutPostRedisplay();
}
void MouseCallbacks::botonMaterialSombreadoSemimate(int button, int state, int x, int y){
	verMaterialSombreadoBrillante = false;
	verMaterialSombreadoTexturado = false;
	verMaterialReflectivo = false;
	verMaterialSombreadoSemimate = true;
	glutPostRedisplay();
}
void MouseCallbacks::botonRetorcer(int button, int state, int x, int y){
	verRetorcer = true;
	verRuido = false;
	verDoblar = false;
	verEsferizar = false;
	glutPostRedisplay();
}
void MouseCallbacks::botonRuido(int button, int state, int x, int y){
	verRetorcer = false;
	verRuido = true;
	verDoblar = false;
	verEsferizar = false;
	glutPostRedisplay();
}
void MouseCallbacks::botonDoblar(int button, int state, int x, int y){
	verRetorcer = false;
	verRuido = false;
	verDoblar = true;
	verEsferizar = false;
	glutPostRedisplay();
}
void MouseCallbacks::botonEsferizar(int button, int state, int x, int y){
	verRetorcer = false;
	verRuido = false;
	verDoblar = false;
	verEsferizar = true;
	glutPostRedisplay();
}