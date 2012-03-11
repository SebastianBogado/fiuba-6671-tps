#pragma once
#include "objetografico.h"
#include "Maquina.h"

class EscenaGrafica;

class MaquinaDeLlenado :
	public ObjetoGrafico,
	public Maquina
{
public:
	MaquinaDeLlenado(void);
	void ini();

	//Interfaz de ObjetoGrafico
	void graficar(); //No grafica el tanque, centro de reflexión.
	void actualizarAtributos();


	//Interfaz de Maquina
	void iniciarAnimacion(Botella* botella);
	bool animacionFinalizada();
	TipoMaquina tipo(){ return TipoMaquina::Llenado; }

	//Interfaz de MaterialReflectivo, si existiera :P
	void actualizarReflexion(EscenaGrafica* escena);
	void graficarParteReflectiva();
	
	virtual ~MaquinaDeLlenado(void);

private:
	//Materiales
	void definirMateriales();
	propMaterial materialTubito;
	propMaterial materialBase;

	//DL
	GLuint DL_TANQUE, DL_BASE, DL_SOPORTE_DEL_TUBITO, DL_TUBITO;

	float alturaDelCentro; //Para tomar como centro de reflexión
	GLuint ladoTextura; //Son cuadradas, ancho y alto son iguales
};

