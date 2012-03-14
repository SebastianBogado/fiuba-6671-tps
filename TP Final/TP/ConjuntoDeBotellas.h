#pragma once
#include "Botella.h"

class ConjuntoDeBotellas :
	public ObjetoGrafico
{
public:
	ConjuntoDeBotellas(void);
	ConjuntoDeBotellas(int cantidadBotellas);


	void graficar();

	void graficarBotellasEnCajon();

	void aplicarShaderParaBotellas();

	void detenerShaderParaBotellas();

	Botella** devolverBotellasDeCajon();

	int cantidadDeBotellasEnCajon();

	
	void actualizarAtributos();

	Botella** devolverBotellas();

	int cantidadDeBotellas();

	virtual ~ConjuntoDeBotellas(void);

	
private:

	void inicializar();
	void definirMateriales();

	Botella** botellas;
	int cantBotellas;

	int cantBotellasEnCajon;
	Botella** botellasDeCajon;

	string rutaTexturaTapa;
	GLuint tapaCoca;

	static vec3 puntosPerfil[];
	static int cantidadDePuntosPerfil;
};

