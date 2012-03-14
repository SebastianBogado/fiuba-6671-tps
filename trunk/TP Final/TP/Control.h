#pragma once

#include "ObjetoGrafico.h"
#include "..\Camara\Camara.h"

#include <GL\freeglut.h>
#include "EscenaGrafica.h"
#include "ManejadorDeBotellas.h"
#include "ManejadorDeBotellasEnCinta.h"
#include "ManejadorDeCajones.h"
#include "ConjuntoDeBotellas.h"

static bool aplicacionCorriendo;

class Control{
public:
	Control(bool debug, vec2& tamañoVentana);
	~Control();
	static void teclado(unsigned char tecla, int x, int y);
	static void mouse(int button, int dir, int x, int y);
	static void mouseMov(int x, int y);
	static void rueditaMouse(int button, int state, int x, int y);

	static void dibujarEscena();
	
	//Suplantaria a la funcion OnIdle
	static void actualizarDatos();
	
	static vec2 getTamañoVentana();
private:
	static Camara* camara;
	static EscenaGrafica* escena;


	void inicializar();
	static void reiniciarAplicacion();
	static void liberarMemoria();

	ObjetoGrafico** inicializarMaquinas();
	ObjetoGrafico** inicializarObjetosGraficos();
	ObjetoGrafico**	inicializarBotellas();

	int cantObjetosTotales,cantMaquinas,cantObjetos,cantBotellas;
	ObjetoGrafico** objetosGraficos;

	static vec2 tamañoVentana;
	bool debug;
};