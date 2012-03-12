#pragma once

#include "MaquinaDeBotellas.h"
#include "CuartoDeMaquinas.h"
#include "MaquinaEmbaladora.h"
#include "LamparaDeTecho.h"
#include "CintaTransportadora.h"
#include "MaquinaDeLlenado.h"
#include "MaquinaEtiquetadora.h"
#include "MaquinaTapadora.h"

class EscenaGrafica
{
public:
	EscenaGrafica(void);

	void agregarObjetosGraficos(int cantObjetos,ObjetoGrafico** objetos);

	//Grafica toda la escena
	void graficar();
	//Grafica sin los materiales reflectivos
	void graficarParaReflexion();

	void actualizarEscena();

	void posicionarLucesEnIluminacion(LamparaDeTecho* lamparas);
	void fijarObjetosReflectivos(MaquinaDeLlenado* tanque);

	//Niega el booleano actualizarReflexion
	void cambiarActualizarReflexion();

	~EscenaGrafica(void);

private:
	ObjetoGrafico **objetos;
	int cantidadObjetos;
	static Iluminacion* iluminacion;

	bool actualizarReflexion, primeraLlamada;
	MaquinaDeLlenado* tanque;
};

