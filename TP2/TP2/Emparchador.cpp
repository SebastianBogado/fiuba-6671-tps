#include "Emparchador.h"
#include "AdministradorTexturas.h"
#include <iostream>

#include <windows.h>
#include <stdio.h>
using namespace std;


extern bool verMaterialReflectivo;
bool &verCaja_Cielo=verMaterialReflectivo;

void Emparchador::emparchar(Superficie* superficie){
    float* puntoInferior;
    float* puntoSuperior;
    float* normal;

	AdministradorTexturas *adminTex= AdministradorTexturas::getInstancia();
	glEnable(GL_TEXTURE_2D);

	//adminTex->elegirTextura(Ladrillos);
    glEnable(GL_DEPTH_TEST);
    for (int i = 0; i < superficie->cantidadDePuntosEnAlto(); i++){
        glBegin(GL_TRIANGLE_STRIP);
            for (int j = 0; j <= superficie->cantidadDePuntosBorde(); j++){
                puntoInferior = superficie->getPunto(j, j, i);
                normal = superficie->getNormal(j, j, i);

				glNormal3fv(normal);
				adminTex->generarCoordText();
                glVertex3fv(puntoInferior);
				//glVertex3f(puntoInferior[0]+normal[0],puntoInferior[1]+normal[1],puntoInferior[2]+normal[2]);
                
				delete []puntoInferior;
				delete [] normal;


				//Para punto Superior
				puntoSuperior= superficie->getPunto(j, j, i+1);
                normal = superficie->getNormal(j, j, i+1);
                
				glNormal3fv(normal);
				adminTex->generarCoordText();
                glVertex3fv(puntoSuperior);
                //glVertex3f(puntoSuperior[0]+normal[0],puntoSuperior[1]+normal[1],puntoSuperior[2]+normal[2]);
                delete []puntoSuperior;
                delete []normal;
            }
		glEnd();
    }
    if (superficie->tieneTapas())
        this->emparcharTapas(superficie);
}

void Emparchador::emparchar2(Superficie* superficie){
    float* puntoInferior;
    float* puntoSuperior;
    float* ultimoPuntoInferior;
    float* ultimoPuntoSuperior;
    float* normal;

	AdministradorTexturas *adminTex= AdministradorTexturas::getInstancia();
	
	glEnable(GL_TEXTURE_2D);
	adminTex->elegirTextura(Caja_Cielo);
	//adminTex->elegirTextura(Ladrillos);
    glEnable(GL_DEPTH_TEST);

    for (int i = 0; i < superficie->cantidadDePuntosEnAlto(); i++){
        glBegin(GL_TRIANGLE_STRIP);
            for (int j = 0; j <= superficie->cantidadDePuntosBorde(); j++){
                puntoInferior = superficie->getPunto(j, j, i);
                puntoSuperior = superficie->getPunto(j, j, i+1);

                normal = superficie->getNormal(j, j, i);
                glNormal3fv(normal);
				adminTex->generarCoordText(puntoInferior);
                glVertex3fv(puntoInferior);
                delete [] normal;


				//Para punto Superior
                normal = superficie->getNormal(j, j, i+1);
                glNormal3fv(normal);
				adminTex->generarCoordText(puntoSuperior);
                glVertex3fv(puntoSuperior);
                delete []puntoInferior;
                delete []puntoSuperior;
                delete []normal;
            }
		glEnd();
    }

}

void Emparchador::verNormales(Superficie* superficie){
	float* punto;
    float* normal;
	glEnable(GL_DEPTH_TEST);
	glLineWidth(2.0);
	
    for (int i = 0; i <= superficie->cantidadDePuntosEnAlto(); i++){
		for (int j = 0; j <= superficie->cantidadDePuntosBorde(); j++){
			punto = superficie->getPunto(j, j, i);
            normal = superficie->getNormal(j, j, i);
			glBegin(GL_LINES);
			    glVertex3fv(punto);
				glVertex3f(punto[0]+normal[0],punto[1]+normal[1],punto[2]+normal[2]);
			glEnd();    
			delete []punto;
			delete []normal;
		}
	}
}

void Emparchador::emparcharTapas(Superficie* superficie){
    float* centroTapa;
    float* puntoBorde;
   // float* ultimoPuntoBorde;
    float* normal = new float[3];

	AdministradorTexturas *adminTex=AdministradorTexturas::getInstancia();

    normal[0] = 0;
    normal[1] = 0;
	
    for (int i = 0; i <= superficie->cantidadDePuntosEnAlto(); i += superficie->cantidadDePuntosEnAlto()){
		adminTex->reiniciar();
		glBegin(GL_TRIANGLE_STRIP);
		//glBegin(GL_LINE_STRIP);
			
			centroTapa = superficie->getPunto(0, 0, i);
			if ( i == 0)
				normal[2] = -1;
			else
				normal[2] = 1;
/*
			glNormal3fv(normal);
			adminTex->generarCoordTextTapa(centroTapa);
			glVertex3f(0.0, 0.0, centroTapa[2]);
			*/
            
            for (int j = 0; j <= superficie->cantidadDePuntosBorde(); j++){

                puntoBorde = superficie->getPunto(j, j, i);

                glNormal3fv(normal);
				adminTex->generarCoordTextTapa(puntoBorde);
                glVertex3fv(puntoBorde);


				glNormal3fv(normal);
				adminTex->generarCoordTextTapa(centroTapa);
				glVertex3f(0.0, 0.0, centroTapa[2]);

                delete []puntoBorde;
            }

        /*    ultimoPuntoBorde = superficie->getPunto(0, 0, i);

            glNormal3fv(normal);
			
			adminTex->generarCoordTextTapa(ultimoPuntoBorde);
            glVertex3fv(ultimoPuntoBorde);
            delete []centroTapa;
            delete []ultimoPuntoBorde;*/
        glEnd();
    }
	delete []normal;
}
