#pragma once
#include "ObjetoGraficoCubico.h"



class CuartoDeMaquinas :
	public ObjetoGraficoCubico
{
public:
	CuartoDeMaquinas(void);

	void graficar();

	void actualizarAtributos();

	btRigidBody* cuerpoRigido();

	~CuartoDeMaquinas(void);

private:

	void definirMateriales();

	GLuint texturaIDPared;



};

