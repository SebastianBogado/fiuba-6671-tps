#pragma once

#include "../BulletPhysics/src/btBulletDynamicsCommon.h"
#include "ObjetoGraficoCubico.h"
#include "CajonesDeBotellas.h"

class InterfazMotorDeFisica
{
public:
	InterfazMotorDeFisica(void);


	void pasoDeSimulacion();


	void definirHabitacion(ObjetoGraficoCubico *habitacion);

	//void definirCajonesDeBotellas(CajonesDe *cajonBotellas);

	void definirMaquinaEmbaladora(ObjetoGrafico *maquinaEmbaladora);

	void agregarMaquina(ObjetoGrafico *maquina);

	void agregarCuerpoRigido(btRigidBody* cuerpoRigido);

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


	///////////////////////
	//Atributos de Objetos
	///////////////////////
	float friccionPiso,fricionCuerpoRigido;

};

