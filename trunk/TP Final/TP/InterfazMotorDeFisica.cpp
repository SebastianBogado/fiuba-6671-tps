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


	this->mundoDinamico->setGravity(btVector3(0.,0.,-5.));
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
	float *posPiso = habitacion->vectorPosicion();
	float largoX = habitacion->valorLargoEnX();
	float largoY = habitacion->valorLargoEnY();
	btScalar masaInfinita = 0.0;


	//////////////////////////
	//Se instancia el Piso
	//////////////////////////
	/*
	//btCollisionShape* formaPiso = new btBoxShape(btVector3(largoX/2,largoY/2,1));
	btCollisionShape* formaPiso = new btStaticPlaneShape(btVector3(0,0,1),btScalar(0.0));

	btTransform transformador;
	transformador.setIdentity();
	transformador.setOrigin(btVector3(0.0,0.0,0.0));
//	transformador.setOrigin(btVector3(posPiso[0] + largoX / 2. ,
	//									posPiso[1] + largoY / 2. ,
		//								posPiso[2] - 0.5));
										
	btVector3 inerciaLocal(0,0,0);

	formaPiso->calculateLocalInertia(masaInfinita,inerciaLocal);

	btDefaultMotionState* estadoMovPiso = new btDefaultMotionState(transformador);
	btRigidBody::btRigidBodyConstructionInfo infoCuerpoRigido(masaInfinita,estadoMovPiso,formaPiso,inerciaLocal);

	btRigidBody *cuerpoRigidoPiso = new btRigidBody(infoCuerpoRigido);

	cuerpoRigidoPiso->setFriction(1.);

	this->mundoDinamico->addRigidBody(cuerpoRigidoPiso);
	*/

		//btCollisionShape* formaDelPiso = new btBoxShape(btVector3(50.,50.,1.));
	btCollisionShape* formaDelPiso = new btStaticPlaneShape(btVector3(0,0,1),btScalar(0.));

	btCollisionShape* formaDePared1 = new btStaticPlaneShape(btVector3(-1,0,0),-btScalar(habitacion->valorLargoEnX()+habitacion->vectorPosicion()[0]));
	btCollisionShape* formaDePared2 = new btStaticPlaneShape(btVector3(1,0,0),btScalar(habitacion->vectorPosicion()[0]));

	btCollisionShape* formaDePared3 = new btStaticPlaneShape(btVector3(0,-1,0),-btScalar(habitacion->valorLargoEnY()+habitacion->vectorPosicion()[1]));
	btCollisionShape* formaDePared4 = new btStaticPlaneShape(btVector3(0,1,0),btScalar(habitacion->vectorPosicion()[1]));

	btCollisionShape* formaDelTecho = new btStaticPlaneShape(btVector3(0,0,-1),-btScalar(habitacion->valorAltura()) );

//	this->objetosDeColision.push_back(formaDelPiso);

	btTransform transformador;
	transformador.setIdentity();
	transformador.setOrigin(btVector3(0,0,0));

	btCompoundShape* formaHabitacion = new btCompoundShape();

	formaHabitacion->addChildShape(transformador,formaDelPiso);
	formaHabitacion->addChildShape(transformador,formaDePared1);
	formaHabitacion->addChildShape(transformador,formaDePared2);
	formaHabitacion->addChildShape(transformador,formaDePared3);
	formaHabitacion->addChildShape(transformador,formaDePared4);
	formaHabitacion->addChildShape(transformador,formaDelTecho);





	btScalar masa(0.);

	btVector3 inerciaLocal(0,0,0);

	btDefaultMotionState* estadoMovPiso = new btDefaultMotionState(transformador);

	//btRigidBody::btRigidBodyConstructionInfo infoCuerpoRigido(masa,estadoMovPiso,formaDelPiso,inerciaLocal);
	btRigidBody::btRigidBodyConstructionInfo infoCuerpoRigido(masa,estadoMovPiso,formaHabitacion,inerciaLocal);

	btRigidBody *cuerpoRigidoDelPiso = new btRigidBody(infoCuerpoRigido);

	cuerpoRigidoDelPiso->setFriction(btScalar(0.5));


	this->mundoDinamico->addRigidBody(cuerpoRigidoDelPiso);

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
