#pragma once

#include "../BulletPhysics/src/btBulletDynamicsCommon.h"
#include "ObjetoGraficoCubico.h"

class InterfazMotorDeFisica
{
public:
	InterfazMotorDeFisica(void);

	void pasoDeSimulacion();


	void definirHabitacion(ObjetoGraficoCubico *habitacion);

	void definirCajonDeBotellas(ObjetoGrafico *cajonBotellas);

	void definirMaquinaEmbaladora(ObjetoGrafico *maquinaEmbaladora);

	void agregarMaquina(ObjetoGrafico *maquina);


	virtual ~InterfazMotorDeFisica(void);

private:

	void inicializar();
	

	///////////////////////////////////
	///Atributos del Motor de Fisica///
	///////////////////////////////////
	btDiscreteDynamicsWorld* mundoDinamico;
	btAlignedObjectArray<btCollisionShape*> objetosDeColision;
	btBroadphaseInterface* faseGeneral;
	btCollisionDispatcher* despachadorDeColisiones;
	btConstraintSolver* solucionadorRestricciones;
	btDefaultCollisionConfiguration* configColision;

};

