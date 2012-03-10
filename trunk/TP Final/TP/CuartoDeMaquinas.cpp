#include "CuartoDeMaquinas.h"


CuartoDeMaquinas::CuartoDeMaquinas(void)
{

	this->posicionObjeto = new float[3];

	posicionObjeto[0] = 0.0;
	posicionObjeto[1] = 0.0;
	posicionObjeto[2] = 0.0;

	this->ancho = 40.0;
	this->largo = 30.0;
	this->alto = 12.0;

	this->inicializarVertices();

}

void CuartoDeMaquinas::graficar(){

	this->graficarBase();

}


void CuartoDeMaquinas::actualizarAtributos(){ }

void CuartoDeMaquinas::definirMateriales(){}

btRigidBody* CuartoDeMaquinas::cuerpoRigido()
{


	float *posPiso = this->vectorPosicion();
	float largoX = this->valorLargoEnX();
	float largoY = this->valorLargoEnY();
	btScalar masaInfinita = 0.0;



	//btCollisionShape* formaDelPiso = new btBoxShape(btVector3(50.,50.,1.));
	btCollisionShape* formaDelPiso = new btStaticPlaneShape(btVector3(0,0,1),btScalar(0.));

	btCollisionShape* formaDePared1 = new btStaticPlaneShape(btVector3(-1,0,0),-btScalar(this->valorLargoEnX()+this->vectorPosicion()[0]));
	btCollisionShape* formaDePared2 = new btStaticPlaneShape(btVector3(1,0,0),btScalar(this->vectorPosicion()[0]));

	btCollisionShape* formaDePared3 = new btStaticPlaneShape(btVector3(0,-1,0),-btScalar(this->valorLargoEnY()+this->vectorPosicion()[1]));
	btCollisionShape* formaDePared4 = new btStaticPlaneShape(btVector3(0,1,0),btScalar(this->vectorPosicion()[1]));

	btCollisionShape* formaDelTecho = new btStaticPlaneShape(btVector3(0,0,-1),-btScalar(this->valorAltura()) );

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

	btRigidBody *cuerpoRigidoDeHabitacion = new btRigidBody(infoCuerpoRigido);

	cuerpoRigidoDeHabitacion->setFriction(btScalar(0.35));

	return cuerpoRigidoDeHabitacion;

	//this->mundoDinamico->addRigidBody(cuerpoRigidoDelPiso);

}


CuartoDeMaquinas::~CuartoDeMaquinas(void)
{
	delete[] this->posicionObjeto;
}
