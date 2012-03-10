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

	void graficar();

	void actualizarEscena();

	//El parámetro i debe ser el que contiene al objeto LamparaDeTecho
	void posicionarLucesEnIluminacion(ObjetoGrafico* lamparas);

	~EscenaGrafica(void);

private:
	ObjetoGrafico **objetos;
	int cantidadObjetos;
	static Iluminacion* iluminacion;
};

