#pragma once
#include "Botella.h"

class ConjuntoDeBotellas :
	public ObjetoGrafico
{
public:
	ConjuntoDeBotellas(void);
	ConjuntoDeBotellas(int cantidadBotellas);


	void graficar();
	
	void actualizarAtributos();

	Botella** devolverBotellas();

	int cantidadDeBotellas();

	virtual ~ConjuntoDeBotellas(void);

	
private:
	void aplicarShader();
	void detenerShader();

	void inicializar();

	Botella** botellas;
	int cantBotellas;

};

