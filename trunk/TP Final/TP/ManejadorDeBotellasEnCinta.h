#pragma once
#include <vector>
#include "CintaTransportadora.h"
#include "Botella.h"
///////////////////////////////////////////////////////
///Clase que define las posiciones de las Botellas	///
///en la Cinta Transportadora						///
///////////////////////////////////////////////////////


class ManejadorDeBotellasEnCinta
{
public:
	ManejadorDeBotellasEnCinta(void);

	void agregarBotellas(vector<Botella*> &botellas);

	void definirCintaTransportadora(CintaTransportadora* cinta);



	void desplazarCinta();

	void detenerCinta();

	void actualizarPosicionesDeBotellas();

	~ManejadorDeBotellasEnCinta(void);

private:


	void inicializar();
	void inicializarPoscionesDeBotellas();

	float calcularDistancia(float p1, float p2);

	//////////////////////
	//Atributos de Clase//
	//////////////////////
	vector<Botella*> botellas;
	bool botellasAgregadas;
	float* posDeTramosDeBotellas;

	float distanciaMinimaEntreBotellas; 

	CintaTransportadora* cinta;
	//bool cintaEnMovimiento;

};

