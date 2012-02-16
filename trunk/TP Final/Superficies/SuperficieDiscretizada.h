#pragma once
#include "Superficie.h"

//Sólo contiene los puntos y normales de la superficie ideal según cierta discretización en una matriz
class SuperficieDiscretizada
{
public:
	SuperficieDiscretizada(int cantidadDePuntosBorde, int cantidadDePuntosEnAlto);
	~SuperficieDiscretizada(void);

	void agregarPunto(vec3 puntoNuevo, int Xn, int Yn);
	void agregarNormal(vec3 normalNueva, int Xn, int Yn);

	vec3 getPunto(int Xn, int Yn);
	vec3 getNormal(int Xn, int Yn);
	
	int cantidadDePuntosBorde();
    int cantidadDePuntosEnAlto();
private:
	vec3** puntos;
	vec3** normales;
	int cantDePuntosBorde;
    int cantDePuntosEnAlto;
};

