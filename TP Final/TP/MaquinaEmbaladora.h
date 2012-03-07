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

	void definirMateriales();

	int cantBotellas(){ return contadorBotellas; }
	void reiniciarContadorBotellas();
	btRigidBody* cuerpoRigidoRampa();
	btVector3 posicionInicialCajon();

	~MaquinaEmbaladora(void);

private:
	void aplicarShader();
	void detenerShader();

	void graficarRampa();

	int contadorBotellas;

};

 