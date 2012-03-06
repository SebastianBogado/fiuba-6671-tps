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


void InterfazMotorDeFisica::pasoDeSimulacion()
{

	float ms = 16666.;

	this->mundoDinamico->stepSimulation(ms / 100000.f);
}


void InterfazMotorDeFisica::definirHabitacion(ObjetoGraficoCubico* habitacion)
{
	float *posPiso = habitacion->vectorPosicion();
	float largoX = habitacion->valorLargoEnX();
	float largoY = habitacion->valorLargoEnY();
	btScalar masaInfinita = 0.0;


	//////////////////////////
	//Se instancia el Piso
	//////////////////////////

	btCollisionShape* formaPiso = new btBoxShape(btVector3(largoX/2,largoY/2,1));
	//btCollisionShape* formaPiso = new btStaticPlaneShape(btVector3(0,0,1),btScalar(0.0));

	btTransform transformador;
	transformador.setIdentity();
	transformador.setOrigin(btVector3(	posPiso[0] + largoX / 2. ,
										posPiso[1] + largoY / 2. ,
										posPiso[2] - 0.5));

	btVector3 inerciaLocal(0,0,0);
	btDefaultMotionState* estadoMovPiso = new btDefaultMotionState(transformador);
	btRigidBody::btRigidBodyConstructionInfo infoCuerpoRigido(masaInfinita,estadoMovPiso,formaPiso,inerciaLocal);

	btRigidBody *cuerpoRigidoPiso = new btRigidBody(infoCuerpoRigido);



}


void InterfazMotorDeFisica::agregarCuerpoRigido(btRigidBody* cuerpoRigido){

	if (cuerpoRigido)
	{

		cuerpoRigido->setFriction(this->fricionCuerpoRigido);
		this->mundoDinamico->addRigidBody(cuerpoRigido);

	}


}

InterfazMotorDeFisica::~InterfazMotorDeFisica(void)
{
}
