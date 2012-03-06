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
	this->impulsoInicialCajon = btVector3(0.,10,0);

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

	nuevoCajon->applyForce(this->impulsoInicialCajon,btVector3(0.,0.,0.));
	this->motorFisica->agregarCuerpoRigido(nuevoCajon);

}


ManejadorDeCajones::~ManejadorDeCajones(void)
{
}
