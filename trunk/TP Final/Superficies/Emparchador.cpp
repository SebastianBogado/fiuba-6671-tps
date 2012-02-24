#include "Emparchador.h"
#include <iostream>

#include <windows.h>
#include <stdio.h>
using namespace std;

void Emparchador::emparchar(Superficie* superficie, int repeticionesDeLaTexturaS, int repeticionesDeLaTexturaT){
    vec3 punto;
    vec3 normal;
	int I_MAX = superficie->cantidadDePuntosEnAlto() - 1;
	int J_MAX = superficie->cantidadDePuntosBorde();
	
	float pasoTexT = repeticionesDeLaTexturaT * (1.0/J_MAX);
	float pasoTexS = repeticionesDeLaTexturaS * (1.0/I_MAX);
	float s = 0;
	float t = 0;
    
	glEnable(GL_DEPTH_TEST);
	
    for (int i = 0; i < I_MAX; i++){
		glBegin(GL_TRIANGLE_STRIP);
            for (int j = 0; j < J_MAX; j++){
				
                //Punto inferior
				punto = superficie->getPunto(j, i);
                normal = superficie->getNormal(j, i);

				glTexCoord2f(s, t);
				glNormal3fv(&normal[0]);
                glVertex3fv(&punto[0]);
				//cout << "( " << punto[0] << ", " << punto[1] << ", " << punto[2] << " ) con ";
				//Para punto Superior
				punto= superficie->getPunto(j, i+1);
                normal = superficie->getNormal(j, i+1);
                
				glTexCoord2f(s + pasoTexS,t);
				glNormal3fv(&normal[0]);
                glVertex3fv(&punto[0]);
				//cout << "( " << punto[0] << ", " << punto[1] << ", " << punto[2] << " ). j = " << j << "; i = " << i << endl;
				t += pasoTexT;
				if (t > 1.0) t -= 1.0;
			}
		glEnd();
		s += pasoTexS; t = 0.0;
		if (s > 1.0) s -= 1.0;
    }
	glDisable(GL_TEXTURE_2D);
  /*  if (superficie->tieneTapas())
        this->emparcharTapas(superficie);*/
}

void Emparchador::verNormales(Superficie* superficie){
	vec3 punto;
    vec3 normal;
	int I_MAX = superficie->cantidadDePuntosEnAlto();
	int J_MAX = superficie->cantidadDePuntosBorde();

	glEnable(GL_DEPTH_TEST);
	glLineWidth(2.0);
	
    for (int i = 0; i < I_MAX; i++){
		for (int j = 0; j < J_MAX; j++){
			punto = superficie->getPunto(j, i);
            normal = superficie->getNormal(j, i);
			glBegin(GL_LINES);
			    glVertex3fv(&punto[0]);
				glVertex3f(punto[0]+0.3*normal[0],punto[1]+0.3*normal[1],punto[2]+0.3*normal[2]);
			glEnd();    
		}
	}
	glLineWidth(1.0);
}

void Emparchador::emparcharTapas(Superficie* superficie){/**
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
            delete []ultimoPuntoBorde;
        glEnd();
    }
	delete []normal;
	*/
}
