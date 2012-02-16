#include "SuperficieDeRevolucion.h"


SuperficieDeRevolucion::SuperficieDeRevolucion(Curva* curvaBorde, 
											   float anguloEnGrados, 
											   vec3 ejeDeRotacion) : Superficie(curvaBorde){
	this->angulo = anguloEnGrados;
	this->ejeDeRotacion = ejeDeRotacion;
}

void SuperficieDeRevolucion::discretizar(int discretizacionBorde, int discretizacionAvance){
	if (discretizada)
		delete miDiscretizacion;

	int tramos = this->curvaBorde->cantidadDeTramos();
	int puntosBorde = tramos * discretizacionBorde +1;
	int puntosEnAlto = discretizacionAvance+1;
	this->miDiscretizacion = new SuperficieDiscretizada(puntosBorde, puntosEnAlto);
	
	float paso = 1.0/discretizacionBorde;
	float pasoAngulo = angulo/discretizacionAvance;
	float u = 0;
	for (int k = 0; k < discretizacionAvance; k++){
		for (int i = 0; i < puntosBorde; i++){
			u = i*paso;
			vec3 puntoBase = curvaBorde->evaluar(u);
			mat4 rotadora = rotate(mat4(1.0f), k*pasoAngulo, ejeDeRotacion);
			vec4 p = rotadora * vec4(puntoBase, 1.0); //Punto rotado
			miDiscretizacion->agregarPunto(vec3(p.x, p.y, p.z), i, k);
			//cout << "( " << p[0] << ", " << p[1] << ", " << p[2] << " ). i = " << i << "; u = " << u << endl;
			//Para conseguir la normal, roto 90° respecto del eje formado por el
			//producto vectorial entre la tangente y el eje de rotación de la superficie
			vec3 tg = curvaBorde->tangente(u);
			vec4 tangente = vec4(tg, 1.0);
			mat4 rot = rotate(mat4(1.0f), float(90), cross(ejeDeRotacion, tg));
			vec4 n = rot * tangente;
			vec3 normalizada = normalize(vec3(n.x, n.y, n.z));
			miDiscretizacion->agregarNormal(normalizada, i, k);
		}
		//miDiscretizacion->agregarPunto(curvaBorde->evaluar(curvaBorde->cantidadDeTramos()));
	}

	this->discretizada = true;
}