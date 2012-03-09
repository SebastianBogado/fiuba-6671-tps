#pragma once
#include "Botella.h"

class ConjuntoDeBotellas :
	public ObjetoGrafico
{
public:
	ConjuntoDeBotellas(void);
	ConjuntoDeBotellas(int cantidadBotellas);


	void graficar();

	void graficarCajon();

	Botella** devolverBotellasDeCajon();

	int cantidadDeBotellasEnCajon();

	
	void actualizarAtributos();

	Botella** devolverBotellas();

	int cantidadDeBotellas();

	virtual ~ConjuntoDeBotellas(void);

	
private:

	void inicializar();

	Botella** botellas;
	int cantBotellas;

	int cantBotellasEnCajon;
	Botella** botellasDeCajon;

	string rutaTexturaTapa;
	GLuint tapaCoca;

};

