#pragma once
#include "ConjuntoDeBotellas.h"
#include "InterfazMotorDeFisica.h"

class CajonesDeBotellas :
	public ObjetoGrafico
{
public:
	CajonesDeBotellas(void);

	void graficar();

	void actualizarAtributos();


	//Metodos Particulares
	int botellasPorCajon();

	btRigidBody* nuevoCuerpoRigidoCajon(btVector3 &posicionInicial);

	virtual ~CajonesDeBotellas(void);

private:
	
	void graficarCajon();

	void inicializarPosicionesDeBotellas();

	void aplicarShader();
	void detenerShader();


	ConjuntoDeBotellas* botellas;

	int cantBotellasEnCajon;
	int cantCajones;

	float distanciaEntreBotellas;

	//Atributos de Motor De Fisica
	btAlignedObjectArray<btRigidBody*> cajones;
	float masaCajon;
	btVector3 dimensionesFormaCajon;
};

