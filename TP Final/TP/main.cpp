/*
 * 66.71 Sistemas Graficos
 * TP Final - Modelado de una planta de producción de Coca-Cola
 */

#ifndef _DEBUG
#pragma comment(linker,"/subsystem:\"windows\" /entry:\"mainCRTStartup\"") //evitar consola en modo Release
#endif

#include <GL/glew.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

int main(int argc, char** argv){	
	int ancho = 800;
	int alto = 600;
	int ventanaPrincipal;

	glutInit(&argc, argv);
    glutInitWindowPosition (10, 10);
    glutInitWindowSize (ancho, alto); 
		
	ventanaPrincipal = glutCreateWindow("66.71 - TP Final");
	
	//Probablemente había mil formas más elegantes, pero bueno...
	// 73 es "I" en ASCII, o sea, I de "Intel"
	if (glGetString(GL_VENDOR)[0] ==  73)
		glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH); //La placa Intel de la notebook no soporta double buffering
	else
		glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	
	glutMainLoop();
    return 0;
}