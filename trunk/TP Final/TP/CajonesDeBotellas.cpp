#include "CajonesDeBotellas.h"


CajonesDeBotellas::CajonesDeBotellas(ConjuntoDeBotellas* conjBotellas)
{

	cajones.clear();
	this->cantBotellasEnCajon = conjBotellas->cantidadDeBotellasEnCajon();
	this->masaCajon = 0.5;
	this->dimensionesFormaCajon = btVector3(0.75,0.75,0.75);

	//this->botellas = new ConjuntoDeBotellas(this->cantBotellasEnCajon);
	this->botellas = conjBotellas;

	this->cantCajones = 0;
	this->distanciaEntreBotellas = 0.75;
	this->posZdeBotellas = - 0.75;

	this->inicializarPosicionesDeBotellas();

}

void CajonesDeBotellas::actualizarAtributos()
{


}


void CajonesDeBotellas::inicializarPosicionesDeBotellas()
{

	Botella** _botellas = this->botellas->devolverBotellasDeCajon();

	for (int i=0; i < this->cantBotellasEnCajon ; i++)
		_botellas[i]->botellaTerminada();

	if(this->botellas->cantidadDeBotellasEnCajon()>= this->cantBotellasEnCajon ){

		_botellas[0]->posicionar(distanciaEntreBotellas / 2.0, distanciaEntreBotellas / 2.0 , posZdeBotellas);
		_botellas[1]->posicionar(-distanciaEntreBotellas / 2.0, distanciaEntreBotellas / 2.0 , posZdeBotellas);
		_botellas[2]->posicionar(distanciaEntreBotellas / 2.0, -distanciaEntreBotellas / 2.0 , posZdeBotellas);
		_botellas[3]->posicionar(-distanciaEntreBotellas / 2.0, -distanciaEntreBotellas / 2.0 , posZdeBotellas);

	}
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
		
		this->dibujarCajonDePlastico();
		this->dibujarCuerpoRigido();

		this->graficarCajon();

		glPopMatrix();

	}


}


void CajonesDeBotellas::dibujarCajonDePlastico()
{	
	float dist = this->distanciaEntreBotellas + 0.1;
	float altura = 0.5;

	glDisable(GL_LIGHTING);
	glBegin(GL_LINE_STRIP);

		glColor3f(1.0,0.0,0.0);
		glVertex3f(dist / 2.0, dist / 2.0 , altura);
		glVertex3f(-dist / 2.0, dist / 2.0 , altura);
		
		glVertex3f(-dist / 2.0, -dist / 2.0 , altura);
		glVertex3f(dist / 2.0, -dist / 2.0 , altura);

		glVertex3f(dist / 2.0, dist / 2.0 , altura);

	glEnd();
	glEnable(GL_LIGHTING);
}

void CajonesDeBotellas::dibujarCuerpoRigido()
{

	glPushMatrix();

	glScaled(this->dimensionesFormaCajon.x() *2.0 ,dimensionesFormaCajon.y()*2.0 ,dimensionesFormaCajon.z() * 2.0);

	this->dibujarAristasCuboUnitario();

	glPopMatrix();

}

void CajonesDeBotellas::graficarCajon(){

	this->botellas->graficarCajon();
	
	/*
	glPushMatrix();
		glScaled(2.0*dimensionesFormaCajon.x(),2.0*dimensionesFormaCajon.y(),2.0*dimensionesFormaCajon.z());
		this->dibujarCuboUnitario();
	glPopMatrix();
	*/
	
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


	delete this->botellas;
}
