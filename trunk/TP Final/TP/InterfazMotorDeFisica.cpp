#include "InterfazMotorDeFisica.h"



InterfazMotorDeFisica::InterfazMotorDeFisica(void)
{
	this->inicializar();
	this->ultimoPasoHecho = false;
	this->simulacionIniciada = false;

	ms = 166666.;
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

	//if (!this->ultimoPasoHecho && this->simulacionIniciada)
	//{
		this->mundoDinamico->stepSimulation(ms);// / 10.f);
	//	this->ultimoPasoHecho = true;
	//}
	//else
	//{
	//	this->ultimoPasoHecho = false;
	//}
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

		this->simulacionIniciada = true;
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
