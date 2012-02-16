#include "SuperficieDeRevolucion.h"


SuperficieDeRevolucion::SuperficieDeRevolucion(Curva* curvaBorde, 
											   float anguloEnGrados = 360, 
											   vec3 ejeDeRotacion = vec3(0.0, 0.0, 1.0)) : Superficie(curvaBorde){
	this->angulo = anguloEnGrados;
	this->ejeDeRotacion = ejeDeRotacion;
}

void SuperficieDeRevolucion::discretizar(int discretizacionBorde, int discretizacionAvance){
	if (discretizada)
		delete miDiscretizacion;

	int puntosBorde = this->curvaBorde->cantidadDeTramos() * discretizacionBorde;
	int puntosEnAlto = discretizacionAvance;
	this->miDiscretizacion = new SuperficieDiscretizada(puntosBorde, puntosEnAlto+1);
	
	float paso = 1.0/discretizacionBorde;
	float pasoAngulo = angulo/discretizacionAvance;
	for (int k = 0; k <= discretizacionAvance; k++){
		for (int i = 0; i < curvaBorde->cantidadDeTramos(); i++)
			for (float j = 0; j < 1; j+= paso){
				int numeroDePunto = i*curvaBorde->cantidadDeTramos() + j*discretizacionBorde;
				
				vec3 puntoBase = curvaBorde->evaluar(i+j);
				mat4 rotadora = rotate(mat4(1.0f), k*pasoAngulo, ejeDeRotacion);
				vec4 p = rotadora * vec4(puntoBase, 1.0); //Punto rotado
				miDiscretizacion->agregarPunto(vec3(p.x, p.y, p.z), numeroDePunto, k);
				
				//Para conseguir la normal, roto 90° respecto del eje formado por el
				//producto vectorial entre la tangente y el eje de rotación de la superficie
				vec4 tangente = vec4(curvaBorde->tangente(i+j), 1.0);
				mat4 rot = rotate(mat4(1.0f), float(90), cross(ejeDeRotacion, curvaBorde->tangente(i+j));
				vec4 n = rot * tangente;
				vec3 normalizada = normalize(vec3(n.x, n.y, n.z));
				miDiscretizacion->agregarNormal(normalizada, numeroDePunto, k);
			}
		//miDiscretizacion->agregarPunto(curvaBorde->evaluar(curvaBorde->cantidadDeTramos()));
	}

	this->discretizada = true;
}