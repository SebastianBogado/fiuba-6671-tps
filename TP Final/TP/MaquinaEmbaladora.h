#pragma once
#include "ObjetoGraficoCubico.h"
#include "Maquina.h"
#include "..\BulletPhysics\src\btBulletDynamicsCommon.h"
class MaquinaEmbaladora :
	public ObjetoGraficoCubico,
	public Maquina
{
public:
	MaquinaEmbaladora(void);

	//Interfaz de ObjetoGrafico
	void graficar();
	void actualizarAtributos();

	//Interfaz de Maquina
	void iniciarAnimacion(Botella* botella);
	bool animacionFinalizada();
	TipoMaquina tipo(){ return TipoMaquina::Embaladora; }


	//Metodos particulares

	int cantBotellas(){ return contadorBotellas; }
	void reiniciarContadorBotellas();

	btRigidBody* cuerpoRigidoRampa();
	btRigidBody* cuerpoRigidoMaquina();
	btVector3 posicionInicialCajon();

	~MaquinaEmbaladora(void);

private:
	void definirMaterial();
	
	void dibujarRampa();

	int contadorBotellas;


	float altoHoyoEntrada ,anchoHoyoEntrada;
	float altoHoyoSalida , anchoHoyoSalida;

	vec2 posHent;
	vec2 posHsal;

	float distanciaDeRampaPlana;

	btRigidBody* crRampa;
	btVector3 dimensionDeRampa;

};

 