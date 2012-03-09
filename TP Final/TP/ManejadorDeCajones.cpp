#include "ManejadorDeCajones.h"


ManejadorDeCajones::ManejadorDeCajones(void)
{
	this->inicializar();
}


ManejadorDeCajones::ManejadorDeCajones(MaquinaEmbaladora* maquina,CajonesDeBotellas* cajones)
{
	this->inicializar();

	this->definirCajones(cajones);
	this->definirMaquina(maquina);

}




void ManejadorDeCajones::inicializar()
{
	this->maqAgregada = false;
	this->cajonesAgregados = false;	
	this->impulsoInicialCajon = btVector3(100.,0.,0.);

}


void ManejadorDeCajones::definirCajones(CajonesDeBotellas* cajones)
{
	if (!this->cajonesAgregados && cajones)
	{

		this->cajones = cajones;
		this->cajonesAgregados = true;

		this->cantBotellasEnCajones = this->cajones->botellasPorCajon();
	}
}

void ManejadorDeCajones::definirInterfaz(InterfazMotorDeFisica *interfaz)
{
	if(interfaz)
	{
		this->motorFisica = interfaz;
	}

}

void ManejadorDeCajones::definirMaquina(MaquinaEmbaladora* maquina){

	if(!this->maqAgregada && maquina)
	{
		this->maqEmbaladora = maquina;

		this->maqAgregada = true;

		this->posicionInicialCajon = this->maqEmbaladora->posicionInicialCajon();
		//this->posicionInicialCajon = btVector3(15,20,9.0);
	}

}


void ManejadorDeCajones::comprobarCajones()
{
	this->comprobarEstadoDeMaquina();
}

void ManejadorDeCajones::comprobarEstadoDeMaquina()
{
	if ( this->maqEmbaladora->cantBotellas() >=  this->cantBotellasEnCajones)
	{

		btRigidBody *nuevoCajon = this->cajones->nuevoCuerpoRigidoCajon(this->posicionInicialCajon);

		this->maqEmbaladora->reiniciarContadorBotellas();

		this->agregarNuevoCajon(nuevoCajon);


	}

}


void ManejadorDeCajones::agregarNuevoCajon(btRigidBody *nuevoCajon)
{

	//Aqui se coloca la posicion inicial tambien

	//nuevoCajon->translate(this->maqEmbaladora->posicionInicialCajon());

	this->motorFisica->agregarCuerpoRigido(nuevoCajon);
	nuevoCajon->applyForce(this->impulsoInicialCajon,btVector3(0.,0.,0.));

}


ManejadorDeCajones::~ManejadorDeCajones(void)
{
}
