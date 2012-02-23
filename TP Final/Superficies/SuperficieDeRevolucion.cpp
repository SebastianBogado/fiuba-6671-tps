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
	float u = 0; //u es la variable de la parametrización
	for (int k = 0; k < puntosEnAlto; k++){
		for (int i = 0; i < puntosBorde; i++){
			u = i*paso;
			vec3 puntoBase = curvaBorde->evaluar(u);
			mat4 rotadora = rotate(mat4(1.0f), k*pasoAngulo, ejeDeRotacion);
			vec4 p = rotadora * vec4(puntoBase, 1.0); //Punto rotado
			miDiscretizacion->agregarPunto(vec3(p.x, p.y, p.z), i, k);
			//cout << "( " << p[0] << ", " << p[1] << ", " << p[2] << " ). i = " << i << "; u = " << u <<"; k = " << k << endl;
			//Para conseguir la normal, roto 90° respecto del eje formado por el
			//producto vectorial entre la tangente y el eje de rotación de la superficie
			vec3 tg = curvaBorde->tangente(u);
			vec4 n;
			vec3 ejeDeRot = cross(ejeDeRotacion, tg);
			bool tangenteEsParalelaAlEje = (ejeDeRot.x == 0) && (ejeDeRot.y == 0) && (ejeDeRot.z == 0);
			if (tangenteEsParalelaAlEje)		//Esto resuelve el problema de cuando el producto vectorial es nulo
				n = vec4(p.x, p.y, 0.0, 1.0);	// y no se puede calcular la normal con este método
			else{
				vec4 tangente = vec4(tg, 1.0);
				if (invertirEjeDeRotacionParaLaNormal(ejeDeRotacion, tg))
					ejeDeRot = -ejeDeRot;
				mat4 rot = rotate(rotadora, float(90), ejeDeRot);
				n = rot * tangente;
			}
			vec3 normalizada = normalize(vec3(n.x, n.y, n.z));
			miDiscretizacion->agregarNormal(normalizada, i, k);
		}
	}

	this->discretizada = true;
}

bool SuperficieDeRevolucion::invertirEjeDeRotacionParaLaNormal(vec3 v, vec3 tg){
	/*bool invertir = false;
	bool productoInternoEsPositivo = dot(v, tg) >= 0; //si es positivo, el ángulo está en el [0,90]U[270,360] grados
	
	return invertir;
	*/
	return (tg.x < 0);//Solución temporal. Sirve para el caso en que el eje de rotación es el z, y la curva es plana, contenida en el y=0
}