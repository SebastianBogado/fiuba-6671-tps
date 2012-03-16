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
		virtual SuperficieDiscretizada* discretizar(int discretizacionBorde, int discretizacionAvance) = 0;

        vec3 getPunto(int Xn, int Yn);		
        vec3 getNormal(int Xn, int Yn);
		

        int cantidadDePuntosBorde();
        int cantidadDePuntosEnAlto();

    protected:
        Curva* curvaBorde;
		SuperficieDiscretizada* miDiscretizacion;
		bool discretizada;
		int discretizacionBordeActual;
		int discretizacionAvanceActual;
};
		

#endif // __SUPERFICIE_H__
