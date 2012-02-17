//Esta clase modela el ente ideal matem�tico

#ifndef __SUPERFICIE_H__
#define __SUPERFICIE_H__

#include "..\Curvas\Curva.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "SuperficieDiscretizada.h"
#include <iostream>
using namespace std;


class Superficie{
    public:
		Superficie(Curva* curvaBorde);
        virtual ~Superficie();

		//El segundo par�metro se refiere al paso de la revoluci�n o el barrido; no se me ocurri� nombre mejor
		virtual void discretizar(int discretizacionBorde, int discretizacionAvance) = 0;

        vec3 getPunto(int Xn, int Yn);		
        vec3 getNormal(int Xn, int Yn);
		
		/*//Adem�s de devolver si alg�n punto es o no una arista, devuelve tambi�n true
        //para aquellos puntos que merecen trato especial como el primer y �ltimo puntos de la esfera
        virtual bool esArista(int Xn, int Yn);

        virtual int getPaso();
        bool tieneTapas();*/
        int cantidadDePuntosBorde();
        int cantidadDePuntosEnAlto();

    protected:
        Curva* curvaBorde;
		SuperficieDiscretizada* miDiscretizacion;
		bool discretizada;

        /*bool tengoTapas;
        virtual void construir() = 0;
        virtual float Xn(int n);
        virtual float Yn(int n);
        virtual float Zn(int n);
		
        float* calcularNormal(float* p, float* q, float* r);
        virtual float* getNormalArista(int Xn, int Yn, int Zn);*/
};
		

#endif // __SUPERFICIE_H__
