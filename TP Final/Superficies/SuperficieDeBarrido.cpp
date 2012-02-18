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

	int tramosBorde = this->curvaBorde->cantidadDeTramos();
	int puntosBorde = tramosBorde * discretizacionBorde +1;
	int tramosCamino = this->curvaCamino->cantidadDeTramos();
	int puntosEnAlto = tramosCamino * discretizacionAvance +1;
	this->miDiscretizacion = new SuperficieDiscretizada(puntosBorde, puntosEnAlto);
	
	float pasoBorde = 1.0/discretizacionBorde;
	float pasoCamino = 1.0/discretizacionAvance;
	float u = 0; 
	float t = 0; //u y t son las variables de cada parametrizaci�n
	mat4 transladora = mat4(1.0f);
	mat4 rotadora = mat4(1.0f);
	for (int k = 0; k < puntosEnAlto; k++){
		t = k*pasoCamino;
		vec3 puntoCamino = curvaCamino->evaluar(t);
		transladora = translate(mat4(1.0f), puntoCamino - curvaCamino->evaluar(0)); 
		rotadora = calcularRealineacion(t);
		for (int i = 0; i < puntosBorde; i++){
			u = i*pasoBorde;
			vec3 puntoBaseBorde = curvaBorde->evaluar(u);
			//Si no es el primer punto (k=0), entonces eval�o la translaci�n restando el punto actual con el anterior
			
			vec4 p = rotadora * vec4(puntoBaseBorde, 1.0); //Punto transladado
			p = transladora * p; //Punto rotado
			miDiscretizacion->agregarPunto(vec3(p.x, p.y, p.z), i, k);
			//cout << "( " << p[0] << ", " << p[1] << ", " << p[2] << " ). i = " << i << "; u = " << u <<"; k = " << k << endl;
			//Para conseguir la normal, hago el producto vectorial entre la tangente de cada curva
			vec3 tgBorde = curvaBorde->tangente(u);
			vec3 tgCamino = curvaCamino->tangente(t);
			vec3 n = cross(tgCamino, tgBorde); 
			/*
			vec4 tangente = vec4(tg, 1.0);
			mat4 rot = rotate(rotadora, float(90), ejeDeRot);
			vec4 n = rot * tangente;*/
			vec3 normalizada = normalize(vec3(n.x, n.y, n.z));
			miDiscretizacion->agregarNormal(normalizada, i, k);
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

	return rotate(I, degrees(angulo), ejeDeRotacion);
}