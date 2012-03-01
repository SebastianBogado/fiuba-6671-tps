#include "InterfazMotorDeFisica.h"


InterfazMotorDeFisica::InterfazMotorDeFisica(void)
{
	this->inicializar();

}


void InterfazMotorDeFisica::inicializar()
{
	///////////////////////////////////////////
	///Inicializacion de Parametros Generales//
	///////////////////////////////////////////

	this->configColision = new btDefaultCollisionConfiguration();

	this->despachadorDeColisiones = new btCollisionDispatcher(this->configColision);

	this->faseGeneral = new btDbvtBroadphase();

	this->solucionadorRestricciones = new btSequentialImpulseConstraintSolver();

	this->mundoDinamico = new btDiscreteDynamicsWorld(	this->despachadorDeColisiones,
														this->faseGeneral,
														this->solucionadorRestricciones,
														this->configColision);



	//////////////////
	//
	/////////////////
}

InterfazMotorDeFisica::~InterfazMotorDeFisica(void)
{
}
