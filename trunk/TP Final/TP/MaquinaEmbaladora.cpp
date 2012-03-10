#include "MaquinaEmbaladora.h"
#include <math.h>

MaquinaEmbaladora::MaquinaEmbaladora(void)
{	

	// quiere decir que la animacion se realizara al final de la cinta
	this->posTramoEnCinta = 1.0;

	this->ancho = 6.0;
	this->largo = 4.0;
	this->alto = 9.0;

	this->alturaDeMaquina = alto;

	altoHoyoEntrada = 2.8; anchoHoyoEntrada = 2.2;
	altoHoyoSalida =2.2; anchoHoyoSalida = 5.2;

	posHent = vec2(0.5,0.35);
	posHsal = vec2(0.5,0.85);


	this->distanciaDeRampaPlana = 6.55;

	this->posicionObjeto = new float[3];
	this->inicializarVector(posicionObjeto,7.5,25.0,0.0);

	this->posDeObjetoAnimado = new float[3];
	this->inicializarVector(posDeObjetoAnimado,0.0,0.0,0.0);

	this->inicializarVertices();
	this->reiniciarContadorBotellas();
	this->definirMateriales();
}

void MaquinaEmbaladora::reiniciarContadorBotellas()
{
	this->contadorBotellas = 0;

}


void MaquinaEmbaladora::definirMateriales(){
	material.colorAmb = vec3(0.44, 0.57, 0.75);		
	material.colorDif = vec3(0.44, 0.57, 0.75);
	material.colorEspec = vec3(0.1, 0.15, 0.2);
	material.brillo = 4.0;
}

void MaquinaEmbaladora::graficar(){

	/*
	float altoHoyoEntrada = 2.8 ,anchoHoyoEntrada = 2.2;
	float altoHoyoSalida =2.2 , anchoHoyoSalida = 5.2;

	vec2 posHent = vec2(0.5,0.35);
	vec2 posHsal = vec2(0.5,0.85);

	*/

	//this->graficarBase();

	float normal[3];
	
	glPushMatrix();
	//glTranslatef(posicionObjeto[0],posicionObjeto[1],posicionObjeto[2]);
	this->posicionarObjeto(); 

	glDisable(GL_LIGHTING);
	aplicarPhong();

		this->inicializarVector(normal,0.0,-1.0,0.0);
	//	this->dibujarPared(normal,0,1,4,5);
		this->dibujarParedHueca(normal,0,1,4,5,altoHoyoEntrada,anchoHoyoEntrada,posHent,0.6);

		this->inicializarVector(normal,1.0,0.0,0.0);
//		this->dibujarPared(normal,1,2,5,6);
		this->dibujarParedHueca(normal,1,2,5,6,altoHoyoSalida,anchoHoyoSalida,posHsal,0.8);


		this->inicializarVector(normal,0.0,1.0,0.0);
	//	this->dibujarParedHueca(normal,2,3,6,7,altoHoyoSalida,anchoHoyoSalida,vec2(0.5,0.8),0.8);
		this->dibujarPared(normal,2,3,6,7);

		this->inicializarVector(normal,-1.0,0.0,0.0);
	//	this->dibujarParedHueca(normal,3,0,7,4,altoHoyoEntrada,anchoHoyoEntrada,vec2(0.5,0.4),0.8);
		this->dibujarPared(normal,3,0,7,4);

		this->inicializarVector(normal,0.0,0.0,1.0);
		this->dibujarPared(normal,4,5,7,6);

		this->dibujarRampa();

	glPopMatrix();
	detenerPhong();

	////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////
	/////////PARA TESTEAR LA UBICACION DE LA RAMPA//////////////
	////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////
	/*

	btVector3 pos;
	btVector3 ejeRot; 
	btScalar anguloRot;
	btQuaternion rotacion;
	btTransform transformacion;


	
	glPushMatrix();

		pos = this->crRampa->getCenterOfMassPosition();

		glTranslatef(pos.m_floats[0],pos.m_floats[1],pos.m_floats[2]);

		transformacion = this->crRampa->getCenterOfMassTransform();

		
		rotacion = transformacion.getRotation();
		
		ejeRot = rotacion.getAxis();
		anguloRot = rotacion.getAngle();

		glRotatef(anguloRot * 180 / 3.14,ejeRot.m_floats[0],ejeRot.m_floats[1],ejeRot.m_floats[2]);


		glScalef(2.0*dimensionDeRampa.x(),2.0*dimensionDeRampa.y(),2.0*dimensionDeRampa.z());

		glDisable(GL_LIGHTING);
		this->dibujarCuboUnitario();
		glEnable(GL_LIGHTING);

		
		

	glPopMatrix();

	*/
}

void MaquinaEmbaladora::dibujarRampa()
{

	float altoBorde = 0.1;

	vec3 vInclinacionA(0.0,-0.0,0.9);
	vec3 vInclinacionB(0.0,0.0,0.9);

	vec3 v0 = vec3( 0.0 ,- this->anchoHoyoSalida / 2.0  ,  this->posHsal.y * alto - altoHoyoSalida / 2.0);
	vec3 v1 = vec3( this->distanciaDeRampaPlana , -this->anchoHoyoSalida / 2.0  , 0.0);

	vec3 v2 = vec3(0.0 , this->anchoHoyoSalida / 2.0 ,  this->posHsal.y * alto - altoHoyoSalida / 2.0);
	vec3 v3 = vec3( this->distanciaDeRampaPlana , this->anchoHoyoSalida / 2.0  , 0.0);
	

	glTranslatef(this->valorLargoEnX(),this->valorLargoEnY() / 2.0, 0.0);

	glBegin(GL_TRIANGLE_STRIP);
		
		glVerticeVec3(v0 + vInclinacionA);
		glVerticeVec3(v1 + vInclinacionA);

		glVerticeVec3(v0);
		glVerticeVec3(v1);
		glVerticeVec3(v2);
		glVerticeVec3(v3);

		glVerticeVec3(v2 + vInclinacionB);
		glVerticeVec3(v3 + vInclinacionB);

	glEnd();







}

btRigidBody* MaquinaEmbaladora::cuerpoRigidoRampa()
{

	float _largo;
	float inclinacion;
	float _altura = (alto * posHsal.y - altoHoyoSalida /2.0);


	_largo = _altura*_altura + distanciaDeRampaPlana*distanciaDeRampaPlana;

	_largo = pow((float)_largo,(float)0.5);

	if (distanciaDeRampaPlana > 0.0)
	{
		inclinacion = acos((float) distanciaDeRampaPlana / _largo);

	}
	
	this->dimensionDeRampa = btVector3(_largo /  2.0, anchoHoyoSalida /2.0, 0.5);
	btCollisionShape *formaDeRampa = new btBoxShape(this->dimensionDeRampa); 

	btScalar masaRampa(0.0);
	btVector3 inerciaLocal(0.,0.,0.);
	
	btTransform transformador;
	transformador.setIdentity();


	//Se define la posicion inicial y la rotacion
	transformador.setOrigin(btVector3(0,0,0));
	btQuaternion rotacion;
	rotacion.setRotation(btVector3(0.,1.0,0.),inclinacion);

	transformador.setRotation(rotacion);
	transformador.setOrigin(btVector3(	posicionObjeto[0] + this->valorLargoEnX()/2.0 + this->distanciaDeRampaPlana /2.0 -0.25 ,
										posicionObjeto[1],// + this->valorLargoEnY()/2.0,
										posicionObjeto[2] + _altura / 2.0  - 0.5 ));



	btDefaultMotionState* estadoMovRampa = new btDefaultMotionState(transformador);
	btRigidBody::btRigidBodyConstructionInfo infoCuerpoRigido(masaRampa,estadoMovRampa,formaDeRampa,inerciaLocal);



	btRigidBody *cuerpoRigidoDeRampa = new btRigidBody(infoCuerpoRigido);

	cuerpoRigidoDeRampa->setFriction(btScalar(0.));


	this->crRampa = cuerpoRigidoDeRampa;

	return cuerpoRigidoDeRampa;


}

btRigidBody* MaquinaEmbaladora::cuerpoRigidoMaquina()
{

	btCollisionShape *formaMaquina = new btBoxShape(btVector3(	this->valorLargoEnX() /2.0,
																this->valorLargoEnY() / 2.0,
																(this->alto * posHsal.y - altoHoyoSalida /2.0)/2.0));

	btScalar masa(0.0);
	btVector3 inerciaLocal(0.,0.,0.);

	btTransform transformador;
	transformador.setIdentity();

	transformador.setOrigin(btVector3(	posicionObjeto[0],// + valorLargoEnX() / 2.0 ,
										posicionObjeto[1],// + valorLargoEnY() / 2.0 ,
										posicionObjeto[2] + (this->alto * posHsal.y - altoHoyoSalida /2.0)/2.0));



	btDefaultMotionState* estadoMovMaq = new btDefaultMotionState(transformador);
	btRigidBody::btRigidBodyConstructionInfo infoCuerpoRigido(masa,estadoMovMaq,formaMaquina,inerciaLocal);



	btRigidBody *cuerpoRigidoDeMaq = new btRigidBody(infoCuerpoRigido);

	cuerpoRigidoDeMaq->setFriction(btScalar(0.));


	return cuerpoRigidoDeMaq;

}


btVector3 MaquinaEmbaladora::posicionInicialCajon()
{
	btVector3 res(	posicionObjeto[0], //+ this->valorLargoEnX() / 2.0, 
					posicionObjeto[1], //+ this->valorLargoEnY() / 2.0,
					posicionObjeto[2] + this->alto * posHsal.y  );


	return res;
}

void MaquinaEmbaladora::actualizarAtributos(){ }

void MaquinaEmbaladora::iniciarAnimacion(Botella* botella)
{	
	//botella->etiquetar();
	this->contadorBotellas++;

}

bool MaquinaEmbaladora::animacionFinalizada()
{
	return true;
}

MaquinaEmbaladora::~MaquinaEmbaladora(void)
{
	delete[] this->posicionObjeto;
	delete[] this->posDeObjetoAnimado;
}
