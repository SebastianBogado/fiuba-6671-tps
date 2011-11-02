#include "Emparchador.h"
#include "AdministradorTexturas.h"
#include <iostream>

#include <windows.h>
#include <stdio.h>
using namespace std;

void Emparchador::emparchar(Superficie* superficie){
    float* puntoInferior;
    float* puntoSuperior;
    float* ultimoPuntoInferior;
    float* ultimoPuntoSuperior;
    float* normal;

	AdministradorTexturas *adminTex= AdministradorTexturas::getInstancia();
	adminTex->elegirTextura(Ladrillos);
    glEnable(GL_DEPTH_TEST);

    for (int i = 0; i < superficie->cantidadDePuntosEnAlto(); i++){
        glBegin(GL_TRIANGLE_STRIP);
            for (int j = 0; j <= superficie->cantidadDePuntosBorde(); j++){
                puntoInferior = superficie->getPunto(j, j, i);
                puntoSuperior = superficie->getPunto(j, j, i+1);

                normal = superficie->getNormal(j, j, i);
                glNormal3fv(normal);
				adminTex->generarCoordText();
                glVertex3fv(puntoInferior);
                delete [] normal;

                normal = superficie->getNormal(j, j, i+1);
                glNormal3fv(normal);
				adminTex->generarCoordText();
                glVertex3fv(puntoSuperior);
                delete []puntoInferior;
                delete []puntoSuperior;
                delete []normal;
            }
		glEnd();
    }
    if (superficie->tieneTapas())
        this->emparcharTapas(superficie);
}


void Emparchador::emparcharTapas(Superficie* superficie){
    float* centroTapa;
    float* puntoBorde;
    float* ultimoPuntoBorde;
    float* normal = new float[3];
    normal[0] = 0;
    normal[1] = 0;
    for (int i = 0; i <= superficie->cantidadDePuntosEnAlto(); i += superficie->cantidadDePuntosEnAlto()){
        glBegin(GL_TRIANGLE_FAN);
            centroTapa = superficie->getPunto(0, 0, i);
            if (i == 0)
                normal[2] = -1;
            else
                normal[2] = 1;

            glNormal3fv(normal);
            glVertex3f(0.0, 0.0, centroTapa[2]);
            for (int j = 0; j < superficie->cantidadDePuntosBorde(); j++){

                puntoBorde = superficie->getPunto(j, j, i);

                glNormal3fv(normal);
                glVertex3fv(puntoBorde);
                delete []puntoBorde;
            }
            ultimoPuntoBorde = superficie->getPunto(0, 0, i);

            glNormal3fv(normal);
            glVertex3fv(ultimoPuntoBorde);
            delete []centroTapa;
            delete []ultimoPuntoBorde;
        glEnd();
    }
}
