#include "StdAfx.h"
#include "ModeloFisica.h"


ModeloFisica::ModeloFisica(void)
{

	this->inicializarVerticesCubo();
	this->inicializar();
}


void ModeloFisica::inicializar(){


	this->configColision = new btDefaultCollisionConfiguration();

	this->despachadorDeColisiones = new btCollisionDispatcher(this->configColision);

	this->faseGeneral = new btDbvtBroadphase();

	this->solucionadorRestricciones = new btSequentialImpulseConstraintSolver();

	this->mundoDinamico = new btDiscreteDynamicsWorld(	this->despachadorDeColisiones,
														this->faseGeneral,
														this->solucionadorRestricciones,
														this->configColision);

	
	this->mundoDinamico->setGravity(btVector3(0,0,-10));

	//btCollisionShape* formaDelPiso = new btBoxShape(btVector3(50.,50.,1.));
	btCollisionShape* formaDelPiso = new btStaticPlaneShape(btVector3(0,0,1),btScalar(0.));


	this->objetosDeColision.push_back(formaDelPiso);

	btTransform pisoTransformador;

	pisoTransformador.setIdentity();
	pisoTransformador.setOrigin(btVector3(0,0,0));

	btScalar masa(0.);

	btVector3 inerciaLocal(0,0,0);

	btDefaultMotionState* estadoMovPiso = new btDefaultMotionState(pisoTransformador);

	btRigidBody::btRigidBodyConstructionInfo infoCuerpoRigido(masa,estadoMovPiso,formaDelPiso,inerciaLocal);

	btRigidBody *cuerpoRigidoDelPiso = new btRigidBody(infoCuerpoRigido);

	cuerpoRigidoDelPiso->setFriction(btScalar(1.));


	this->mundoDinamico->addRigidBody(cuerpoRigidoDelPiso);

	this->inicializarRampa();
	//Se cre el cubo...

	this->inicializarCubo();



}

void ModeloFisica::inicializarRampa()
{

	btCollisionShape* formaDeRampa = new btStaticPlaneShape(btVector3(-1,0,1),btScalar(0.));


	this->objetosDeColision.push_back(formaDeRampa);

	btTransform Transformador;

	Transformador.setIdentity();
	Transformador.setOrigin(btVector3(0,0,0));

	btScalar masa(0.);

	btVector3 inerciaLocal(0,0,0);

	btDefaultMotionState* estadoMovRampa = new btDefaultMotionState(Transformador);

	btRigidBody::btRigidBodyConstructionInfo infoCuerpoRigido(masa,estadoMovRampa,formaDeRampa,inerciaLocal);

	btRigidBody *cuerpoRigidoDeRampa = new btRigidBody(infoCuerpoRigido);

	cuerpoRigidoDeRampa->setFriction(btScalar(1.));


	this->mundoDinamico->addRigidBody(cuerpoRigidoDeRampa);

}
void ModeloFisica::inicializarCubo(){

	this->cantCubos = 20;

	this->cubo = new btRigidBody*[cantCubos];

	float raiz_2 = 1.41;

	btVector3 origen(-1,0,10);
	btVector3 despl(1.2,0,3);

	for(int i=0; i< cantCubos; i++,origen+=despl)
	{
	btCollisionShape* formaDeCubo = new btBoxShape(btVector3(1,1,1));

	this->objetosDeColision.push_back(formaDeCubo);

	btScalar masaCubo(0.5f);

	btVector3 inerciaLocalCubo(0,0,0);

	formaDeCubo->calculateLocalInertia(masaCubo,inerciaLocalCubo);

	btTransform transformador;

	transformador.setIdentity();

	transformador.setOrigin(origen);

	//btQuaternion rotacion(btVector3(0,1,0),45);
	//transformador.setRotation(rotacion);

	btDefaultMotionState* estadoMovimientoCubo= new btDefaultMotionState(transformador);

	btRigidBody::btRigidBodyConstructionInfo infoCubo(masaCubo,estadoMovimientoCubo,formaDeCubo,inerciaLocalCubo);

	this->cubo[i] = new btRigidBody(infoCubo);
	this->cubo[i]->setFriction(btScalar(0.1));

	this->mundoDinamico->addRigidBody(this->cubo[i]);

	}
	//this->cubo->applyForce(btVector3(-1,-1,-1),btVector3(0,0,-1));


}

void ModeloFisica::inicializarVerticesCubo(){

	this->cantidadVertices = 8;
	this->ladoCubo = 2.0;

	this->vertices = new float*[cantidadVertices];

	for (int i=0; i < cantidadVertices ; i++)
		this->vertices[i] = new float[3]; 

	this->inicializarVector(vertices[0],0.0,0.0,0.0);
	this->inicializarVector(vertices[1],ladoCubo,0.0,0.0);
	this->inicializarVector(vertices[2],ladoCubo,ladoCubo,0.0);
	this->inicializarVector(vertices[3],0.0,ladoCubo,0.0);

	this->inicializarVector(vertices[4],0.0,0.0,ladoCubo);
	this->inicializarVector(vertices[5],ladoCubo,0.0,ladoCubo);
	this->inicializarVector(vertices[6],ladoCubo,ladoCubo,ladoCubo);
	this->inicializarVector(vertices[7],0.0,ladoCubo,ladoCubo);


}

void ModeloFisica::inicializarVector(float *vector,float x,float y,float z){

	if (vector){

		vector[0] = x;
		vector[1] = y;
		vector[2] = z;

	}


}


void ModeloFisica::pasoDeSimulacion(){

	float ms = 16666.;

	this->mundoDinamico->stepSimulation(ms / 10000000.f);

}

void ModeloFisica::dibujar(){

	this->dibujarRampa();

	for (int i=0; i < cantCubos; i++){
		glPushMatrix();

		btVector3 pos = this->cubo[i]->getCenterOfMassPosition();

		glTranslatef(pos.m_floats[0],pos.m_floats[1],pos.m_floats[2]);

		btDefaultMotionState *estMov = (btDefaultMotionState*)this->cubo[i]->getMotionState();

		btTransform transformacion = this->cubo[i]->getCenterOfMassTransform();

		btVector3 ejeRot; btScalar anguloRot;
	
		btQuaternion rotacion = transformacion.getRotation();
		
		ejeRot = rotacion.getAxis();
		anguloRot = rotacion.getAngle();

		glRotatef(anguloRot * 180 / 3.14,ejeRot.m_floats[0],ejeRot.m_floats[1],ejeRot.m_floats[2]);
		//glRotatef(1.6,0.0,1.0,0.0);

		this->dibujarCubo();

		glPopMatrix();
	}
	
}



void ModeloFisica::dibujarCubo(){


	glMatrixMode(GL_MODELVIEW);
	glTranslatef(-ladoCubo / 2.0, -ladoCubo / 2.0 , -ladoCubo / 2.0);
	glPushMatrix();
	glDisable(GL_LIGHTING);
				
		glBegin(GL_QUADS);
			
			glColor3f(1.0,0.0,0.0);
			glVertex3fv(vertices[1]);
			glVertex3fv(vertices[2]);
			glVertex3fv(vertices[6]);
			glVertex3fv(vertices[5]);

			glColor3f(0.0,1.0,0.0);
			glVertex3fv(vertices[2]);
			glVertex3fv(vertices[3]);
			glVertex3fv(vertices[7]);
			glVertex3fv(vertices[6]);

			glColor3f(0.0,0.0,1.0);
			glVertex3fv(vertices[3]);
			glVertex3fv(vertices[0]);
			glVertex3fv(vertices[4]);
			glVertex3fv(vertices[7]);

			//4ta tapa
			glColor3f(1.0,1.0,0.0);
			glVertex3fv(vertices[0]);
			glVertex3fv(vertices[4]);
			glVertex3fv(vertices[5]);
			glVertex3fv(vertices[1]);

			//5ta tapa
			glColor3f(1.0,0.0,1.0);
			glVertex3fv(vertices[6]);
			glVertex3fv(vertices[7]);
			glVertex3fv(vertices[4]);
			glVertex3fv(vertices[5]);

			//6ta tapa la del piso, que resultaria el piso
			glColor3f(0.8,0.8,0.8);
			glVertex3fv(vertices[0]);
			glVertex3fv(vertices[1]);
			glVertex3fv(vertices[2]);
			glVertex3fv(vertices[3]);

		glEnd();
	glPopMatrix();



}


void ModeloFisica::dibujarRampa(){


	glDisable(GL_LIGHTING);
				
		glBegin(GL_QUADS);
			glColor3f(0.8,0.8,0.8);
			glVertex3f(0,5,0);
			glVertex3f(0,-5,0);
			glVertex3f(20,-5,20);
			glVertex3f(20,5,20);

		glEnd();



}

void ModeloFisica::reiniciar(){

	this->liberarMemoriaMundo();

	this->inicializar();

}

void ModeloFisica::liberarMemoriaMundo(){
		int i;

	for ( i = this->mundoDinamico->getNumCollisionObjects() -1; i >=0; i--)
	{
		btCollisionObject *obj = mundoDinamico->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);

		if ( body && body->getMotionState())
		{
			delete body->getMotionState();

		}

		mundoDinamico->removeCollisionObject(obj);

	}


	for (int j=0; j < this->objetosDeColision.size() ; j++)
	{

		btCollisionShape* shape = this->objetosDeColision[j];
		delete shape;
	}


	this->objetosDeColision.clear();

	delete this->mundoDinamico;

	delete this->solucionadorRestricciones;

	delete this->faseGeneral;

	delete this->despachadorDeColisiones;

	delete this->configColision;

	delete[] this->cubo;


}

ModeloFisica::~ModeloFisica(void)
{
	this->liberarMemoriaMundo();

	for(int i=0; i < cantidadVertices ; i++)
		delete[] this->vertices[i];

	delete[] this->vertices;


}
