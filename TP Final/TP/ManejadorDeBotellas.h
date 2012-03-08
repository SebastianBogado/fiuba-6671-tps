#pragma once
#include <vector>
#include "Botella.h"
#include "ManejadorDeBotellasEnCinta.h"
///////////////////////////////////////////////////////////////////
///Clase que se encarga de manejar el movimiento de las botellas///
///y determina que cuando comienza la animacion de cada maquina ///
///para cada botella.											///
///////////////////////////////////////////////////////////////////

class ManejadorDeBotellas
{
public:
	ManejadorDeBotellas();

	ManejadorDeBotellas(int cantBotellas, Botella** botellas,int cantMaquinas,Maquina** maquinas);

	void agregarBotellas(int cantBotellas,Botella** botellas);
	void agregarMaquinas(int cantMaquinas,Maquina** maquinas);


	void comprobarEstadoDeBotellas();	

	~ManejadorDeBotellas(void);

private:

	void inicializar();
	
	void comprobarAnimaciones();

	void inicializarPosicionesDeAnimacion();

	void asignarProximaBotella(int numMaquina);

	float calcularDistanciaPlana(float* pos1,float* pos2);



	//////////////////////
	//Atributos de Clase//
	//////////////////////
	vector<Botella*> botellas; 
	vector<Maquina*> maquinas;

	//Esta variable es un vector de int donde en la posicion i, corresponde a la proxima botella 
	//que recivira la maquina i(denominada asi por su posicione en el vector de Maquinas).
	int *indiceBotellasProximas;


	bool  botellasAgregadas,maquinasAgregadas;	

	bool hayAnimacionesActivas;
	float distanciaMaximaParaAnimacion;

	ManejadorDeBotellasEnCinta *manejadorDeCinta;
};

