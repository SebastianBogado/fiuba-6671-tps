varying vec3 normal;
varying vec3 posicion;


struct propLuz{
	bool prendida;
	vec3 posicion;
	vec3 direccion;
	float angulo;
	float k; 
	vec3 amb;
	vec3 dif;
	vec3 espec;
};

struct propMaterial{
	vec3 colorAmb;
	vec3 colorDif;
	vec3 colorEspec;
	float brillo;
};

//Resulta que no puedo pasar como uniforms arrays de structs...
uniform propLuz luzCero;
uniform propLuz luzUno;
uniform propLuz luzDos;
uniform propLuz luzTres;
uniform propLuz luzCuatro;
uniform propLuz luzCinco; 
propLuz luces[6];
uniform propMaterial material;

void ini(){
	luces[0] = luzCero;
	luces[1] = luzUno;
	luces[2] = luzDos;
	luces[3] = luzTres;
	luces[4] = luzCuatro;
	luces[5] = luzCinco;
}
vec3 Phong(){
	vec3 n = normalize(normal);
	vec3 v = normalize(-posicion);
	vec3 resultante = vec3(0.0, 0.0, 0.0);
	int i= 0;
//	for (int i = 0; i < 6; i++){
		resultante += luces[i].amb * material.colorAmb;
		if (luces[i].prendida){
			vec3 l = normalize(posicion - luces[i].posicion);
			float LdotDirLuz = dot(l, normalize( luces[i].direccion));
			float angulo = degrees(acos(LdotDirLuz));
			if (angulo < luces[i].angulo){
				//Factor de decrecimiento
				float k = pow(LdotDirLuz, luces[i].k); 
				vec3 r = reflect(l, n);
				resultante += k * ((luces[i].dif * material.colorDif * max( dot(-l, n), 0.0 )) +
								   (luces[i].espec * material.colorEspec * pow(max(dot(r,v),0.0), material.brillo )));
			}
		}
	//}
	return resultante;
}

vec3 BlinnPhong(){int i = 0;
	vec3 l = normalize(posicion - luces[i].posicion);
	float LdotDirLuz = dot(l, normalize( luces[i].direccion));
	float angulo = degrees(acos(LdotDirLuz));
	if (angulo > luces[i].angulo)
		return (luces[i].amb * material.colorAmb);

	//Factor de decrecimiento
	float k = pow(LdotDirLuz, luces[i].k); 
	vec3 n = normalize(normal);
	vec3 v = normalize(vec3(-posicion));
	vec3 h = normalize(v - l);
	return ((luces[i].amb * material.colorAmb) +
		    k * ((luces[i].dif * material.colorDif * max( dot(-l, n), 0.0 )) +
		         (luces[i].espec * material.colorEspec * pow(max(dot(h,n),0.0), material.brillo ))));
}

void main (void){
	//ini();
	luces[0] = luzCero;
	gl_FragColor = vec4(Phong(), 1.0);
}