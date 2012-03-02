#pragma once

#include "..\Camara\Camara.h"

#include <GL\freeglut.h>
#include "EscenaGrafica.h"
#include "ManejadorDeBotellas.h"
#include "ManejadorDeBotellasEnCinta.h"

static bool aplicacionCorriendo;

class Control{
public:
	Control(bool debug);
	~Control();
	static void teclado(unsigned char tecla, int x, int y);
	static void mouse(int button, int state, int x, int y);
	static void mouseMov(int x, int y);

	static void dibujarEscena();
	
	//Suplantaria a la funcion OnIdle
	static void actualizarDatos();

	static float atPorDefecto[3];
	static float posicionPorDefecto[3];
	static float upPorDefecto[3];

	
private:
	static Camara* camara;
	static EscenaGrafica* escena;


	void inicializar();
	static void liberarMemoria();

	ObjetoGrafico** inicializarMaquinas();
	ObjetoGrafico** inicializarObjetosGraficos();
	ObjetoGrafico**	inicializarBotellas();

	int cantObjetosTotales,cantMaquinas,cantObjetos,cantBotellas;
	ObjetoGrafico** objetosGraficos;

	
	bool debug;
};