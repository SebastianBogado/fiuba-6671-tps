#pragma once
#include "Botella.h"
#include "TextureLoader.h"

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
	glTexture etiquetaCoca;

	static vec3 puntosPerfil[];
	static int cantidadDePuntosPerfil;
	TextureLoader* texLoader; //Agregado porque levanta la etiqueta de Coca mejor y no sé por qué, ja
};

