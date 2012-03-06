#include "CajonesDeBotellas.h"


CajonesDeBotellas::CajonesDeBotellas(void)
{

	cajones.clear();
	this->cantBotellasEnCajon = 4;
	this->masaCajon = 1.0;
	this->dimensionesFormaCajon = btVector3(1,2,1);


	this->cantCajones = 0;

}

void CajonesDeBotellas::actualizarAtributos()
{


}


void CajonesDeBotellas::graficar()
{
	btVector3 pos;
	btVector3 ejeRot; 
	btScalar anguloRot;
	btQuaternion rotacion;
	btTransform transformacion;


	for( int i=0; i < this->cajones.size() ; i++)
	{
		glPushMatrix();

		pos = this->cajones[i]->getCenterOfMassPosition();

		glTranslatef(pos.m_floats[0],pos.m_floats[1],pos.m_floats[2]);

		//btDefaultMotionState *estMov = (btDefaultMotionState*)this->cajones[i]->getMotionState();

		transformacion = this->cajones[i]->getCenterOfMassTransform();

		
		rotacion = transformacion.getRotation();
		
		ejeRot = rotacion.getAxis();
		anguloRot = rotacion.getAngle();

		glRotatef(anguloRot * 180 / 3.14,ejeRot.m_floats[0],ejeRot.m_floats[1],ejeRot.m_floats[2]);

		this->graficarCajon();

		glPopMatrix();

	}


}


void CajonesDeBotellas::graficarCajon(){


}


btRigidBody* CajonesDeBotellas::nuevoCuerpoRigidoCajon(btVector3 &posicionInicial)
{


	btCollisionShape* formaCajon = new btBoxShape(this->dimensionesFormaCajon); 

	btVector3 inerciaLocalCajon = btVector3(0,0,0);

	formaCajon->calculateLocalInertia(this->masaCajon,inerciaLocalCajon);

	btTransform transformador;
	transformador.setIdentity();
	transformador.setOrigin(posicionInicial);

	btDefaultMotionState* estadoMovimientoCajon= new btDefaultMotionState(transformador);
	btRigidBody::btRigidBodyConstructionInfo infoCajon(masaCajon,estadoMovimientoCajon,formaCajon,inerciaLocalCajon);

	btRigidBody *cuerpoRigidoCajon = new btRigidBody(infoCajon);

	this->cantCajones++;

	this->cajones.push_back(cuerpoRigidoCajon);



	return cuerpoRigidoCajon;

}


void CajonesDeBotellas::aplicarShader()
{
}

int CajonesDeBotellas::botellasPorCajon(){
	return this->cantBotellasEnCajon;
}

void CajonesDeBotellas::detenerShader()
{
}

CajonesDeBotellas::~CajonesDeBotellas(void)
{

	for(int i = 0; i < this->cajones.size() ; i++)
	{
		btRigidBody *cr;

		cr = cajones[i];

		cajones.remove(cr);
		
		//delete cr;
	}

}
