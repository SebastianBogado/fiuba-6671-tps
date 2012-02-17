//Esta clase modela el ente ideal matemático

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

		//El segundo parámetro se refiere al paso de la revolución o el barrido; no se me ocurrió nombre mejor
		virtual void discretizar(int discretizacionBorde, int discretizacionAvance) = 0;

        vec3 getPunto(int Xn, int Yn);		
        vec3 getNormal(int Xn, int Yn);
		
		/*//Además de devolver si algún punto es o no una arista, devuelve también true
        //para aquellos puntos que merecen trato especial como el primer y último puntos de la esfera
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
