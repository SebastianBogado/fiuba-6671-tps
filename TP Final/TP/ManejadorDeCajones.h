#pragma once
#include "MaquinaEmbaladora.h"
#include "InterfazMotorDeFisica.h"
#include "CajonesDeBotellas.h"

class ManejadorDeCajones
{
public:
	ManejadorDeCajones(void);

	ManejadorDeCajones(MaquinaEmbaladora* maquina,CajonesDeBotellas* cajones);

	void comprobarCajones();

	void definirMaquina(MaquinaEmbaladora* maquina);
	void definirCajones(CajonesDeBotellas* cajones);
	void definirInterfaz(InterfazMotorDeFisica* interfaz);

	virtual ~ManejadorDeCajones(void);

private:

	void inicializar();
	void agregarNuevoCajon(btRigidBody *nuevoCajon);
	void comprobarEstadoDeMaquina();

	int cantBotellasEnCajones;

	bool maqAgregada,cajonesAgregados;
	MaquinaEmbaladora* maqEmbaladora;
	CajonesDeBotellas* cajones;

	btVector3 posicionInicialCajon;
	btVector3 impulsoInicialCajon;

	InterfazMotorDeFisica *motorFisica;
};

