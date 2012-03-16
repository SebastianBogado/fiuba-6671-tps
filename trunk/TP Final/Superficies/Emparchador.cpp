#include "Emparchador.h"
#include <iostream>

#include <windows.h>
#include <stdio.h>
using namespace std;

void Emparchador::emparchar(SuperficieDiscretizada* superficie, int repeticionesDeLaTexturaS, int repeticionesDeLaTexturaT){
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

				//Para punto Superior
				punto= superficie->getPunto(j, i+1);
                normal = superficie->getNormal(j, i+1);
                
				glTexCoord2f(s + pasoTexS,t);
				glNormal3fv(&normal[0]);
                glVertex3fv(&punto[0]);

				t += pasoTexT;
				if (t > 1.0) t -= 1.0;
			}
		glEnd();
		t = 0.0;
		s += pasoTexS; 
		if (s > 1.0) s -= 1.0;
    }
}

void Emparchador::verNormales(SuperficieDiscretizada* superficie){
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
