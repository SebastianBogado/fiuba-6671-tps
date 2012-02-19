#include "SuperficieDeBarrido.h"


SuperficieDeBarrido::SuperficieDeBarrido(Curva* curvaBorde, Curva* curvaCamino) : Superficie(curvaBorde){
	this->curvaCamino = curvaCamino;
}


SuperficieDeBarrido::~SuperficieDeBarrido(void){
	delete curvaCamino;
}

void SuperficieDeBarrido::discretizar(int discretizacionBorde, int discretizacionAvance){
	if (discretizada)
		delete miDiscretizacion;

	int puntosBorde = this->curvaBorde->cantidadDeTramos() * discretizacionBorde +1;
	int puntosEnAlto = this->curvaCamino->cantidadDeTramos() * discretizacionAvance +1;
	this->miDiscretizacion = new SuperficieDiscretizada(puntosBorde, puntosEnAlto);
	
	float pasoBorde = 1.0/discretizacionBorde;
	float pasoCamino = 1.0/discretizacionAvance;
	float u = 0; 
	float t = 0; //u y t son las variables de cada parametrización
	mat4 transladora = mat4(1.0f);
	mat4 rotadora = mat4(1.0f);
	vec3 primerPuntoCamino = curvaCamino->evaluar(0);
	for (int k = 0; k < puntosEnAlto; k++){
		t = k*pasoCamino;
		vec3 puntoCamino = curvaCamino->evaluar(t); //vec3 a = puntoCamino - curvaCamino->evaluar(0);
		vec3 tgCamino = curvaCamino->tangente(t); //cout << "Translacion: (" <<a.x<<", "<<a.y<<", "<<a.z<<"); t = " << t << endl;
		transladora = translate(mat4(1.0f), puntoCamino - primerPuntoCamino); 
		rotadora = calcularRealineacion(t);
		for (int i = 0; i < puntosBorde; i++){
			u = i*pasoBorde;
			vec3 puntoBaseBorde = curvaBorde->evaluar(u);
			puntoBaseBorde -= primerPuntoCamino; //Alineo el eje de rotación con el cero
			vec4 p = rotadora * vec4(puntoBaseBorde, 1.0); //Roto el punto
			p += vec4(primerPuntoCamino, 0.0); //Devuelvo al punto a su posición original, y queda rotado como debe
			p = transladora * p; //Punto transladado
			miDiscretizacion->agregarPunto(vec3(p.x, p.y, p.z), i, k);
			//cout << "( " << p[0] << ", " << p[1] << ", " << p[2] << " ). i = " << i << "; u = " << u <<"; k = " << k << endl;
			
			//Para conseguir la normal, roto la tangente de la curva borde según la mat4 rotadora
			//y hago el producto vectorial con la tangente del camino
			vec3 tgBorde = curvaBorde->tangente(u);
			vec4 tgBordeAux = rotadora * vec4(tgBorde, 1.0);
			vec3 n = cross(tgCamino, vec3(tgBordeAux.x, tgBordeAux.y, tgBordeAux.z)); 
			n = normalize(n);
			miDiscretizacion->agregarNormal(n, i, k);
		}
	}

	this->discretizada = true;
}

mat4 SuperficieDeBarrido::calcularRealineacion(float t){
	vec3 tgActual = curvaCamino->tangente(t);
	vec3 tgPrimera = curvaCamino->tangente(0);
	vec3 ejeDeRotacion = cross(tgPrimera, tgActual);
	mat4 I = mat4(1.0f);
	if ((ejeDeRotacion.x == 0) && (ejeDeRotacion.y == 0) && (ejeDeRotacion.z == 0))
		return I;
	tgActual = normalize(tgActual);
	tgPrimera = normalize(tgPrimera);

	float angulo = acos(dot(tgPrimera, tgActual));
	//cout << "Realineacion: " << degrees(angulo) << "; t = " << t << endl;
	return rotate(I, degrees(angulo), ejeDeRotacion);
}