#pragma once
#include "Botella.h"

enum TipoMaquina
{
	Embaladora,
	Llenado,
	Expendedora,
	Etiquetadora,
	Transportadora

};

class Maquina
{
public:
	Maquina(void);

	virtual void iniciarAnimacion(Botella* botella)=0;

	virtual bool animacionFinalizada()=0;
	
	virtual TipoMaquina tipo()=0;

	float* posicionPlanaDeObjetoAnimado(){ return posDeObjetoAnimado; };

	inline float altura(){ return alturaDeMaquina;}

	~Maquina(void);
protected:
	float alturaDeMaquina;
	float* posDeObjetoAnimado;

	bool AnimacionIniciada;
	float _testAnimacion,_pasoTest;

};

