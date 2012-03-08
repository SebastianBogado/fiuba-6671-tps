#pragma once
#include "ObjetoGrafico.h"
#include <glm\glm.hpp>
#include "..\BulletPhysics\src\btBulletDynamicsCommon.h"

using namespace glm;

class ObjetoGraficoCubico :
	public ObjetoGrafico
{
public:
	ObjetoGraficoCubico(void);
	void definirParametros(float ancho,float largo,float alto);

	void graficarBase();

	float valorAltura();
	float valorAncho();
	float valorLargo();


	float valorLargoEnX();
	float valorLargoEnY();

	virtual ~ObjetoGraficoCubico(void);
protected:
	void inicializarVertices();
	void actualizarVertices();
	
	void posicionarObjeto();

	float **vertices;
	float ancho,largo,alto;
	int cantidadVertices;

	///////////////////////////////////////////////////////////////
	//Dibuja una pared con triangulos desde los vertices v1...v4,
	//se interpreta como dos rectas; v1 y v2 es una, y v3 y v4 forma la otra.
	//A partir de estas dos rectas se grafica un rectangulo.
	//v1...v4 son los indices de los vertices del cubo base
	////////////////////////////////////////////////////////////////
	void dibujarPared(float* normal,int v1,int v2,int v3,int v4);
	void dibujarParedHueca(float* normal,int v1,int v2,int v3,int v4,float largoHoyo,float anchoHoyo,vec2 posHoyo,float profundidad);
	

private:
	
	void dibujarHoyo(float *n,btVector3 &x0,btVector3 &x1,btVector3 &y0,btVector3 &y1,float &profundidad);

	void dibujarFranja(float* normal,btVector3 &x0,btVector3 &x1,btVector3 &y0,btVector3 &y1);
	

	bool discretizacionPorDefecto;
	int pasosDeDiscretizacion;	

};

