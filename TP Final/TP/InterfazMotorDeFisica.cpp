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


	this->mundoDinamico->setGravity(btVector3(0.,0.,-10.));
	//this->mundoDinamico->setGravity(btVector3(0.,0.,0.));
	//////////////////
	//
	/////////////////

	this->fricionCuerpoRigido = 1.0;
	this->friccionPiso = 1.0;
}


void InterfazMotorDeFisica::pasoDeSimulacion()
{

	float ms = 16666.;

	this->mundoDinamico->stepSimulation(ms / 100000.f);
}


void InterfazMotorDeFisica::definirHabitacion(ObjetoGraficoCubico* habitacion)
{	


	btRigidBody *cuerpoRigidoDeHabitacion =((CuartoDeMaquinas*)habitacion)->cuerpoRigido();

	this->mundoDinamico->addRigidBody(cuerpoRigidoDeHabitacion);


}


void InterfazMotorDeFisica::agregarCuerpoRigido(btRigidBody* cuerpoRigido){

	if (cuerpoRigido)
	{

		//cuerpoRigido->setFriction(this->fricionCuerpoRigido);
		this->mundoDinamico->addRigidBody(cuerpoRigido);

	}


}


void InterfazMotorDeFisica::definirMaquinaEmbaladora(MaquinaEmbaladora *maquina)
{
	this->agregarCuerpoRigido(maquina->cuerpoRigidoRampa());

	this->agregarCuerpoRigido(maquina->cuerpoRigidoMaquina());

}

InterfazMotorDeFisica::~InterfazMotorDeFisica(void)
{
}
