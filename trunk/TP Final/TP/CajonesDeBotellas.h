#pragma once
#include "ConjuntoDeBotellas.h"
#include "InterfazMotorDeFisica.h"

class CajonesDeBotellas :
	public ObjetoGrafico
{
public:
	CajonesDeBotellas(ConjuntoDeBotellas* conjBotellas);

	void graficar();

	void actualizarAtributos();


	//Metodos Particulares
	int botellasPorCajon();

	btRigidBody* nuevoCuerpoRigidoCajon(btVector3 &posicionInicial);

	virtual ~CajonesDeBotellas(void);

private:
	
	void graficarCajon();
	void dibujarCajonDePlastico();
	void dibujarCuerpoRigido();

	void inicializarPosicionesDeBotellas();

	void definirMaterial();


	ConjuntoDeBotellas* botellas;

	int cantBotellasEnCajon;
	int cantCajones;

	float distanciaEntreBotellas;
	float posZdeBotellas;

	//Atributos de Motor De Fisica
	btAlignedObjectArray<btRigidBody*> cajones;
	float masaCajon;
	btVector3 dimensionesFormaCajon;
};

