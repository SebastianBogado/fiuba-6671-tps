uniform sampler2D cintaText;

//agregada por Migue
uniform float desplazamientoDeCinta;

varying vec2 vTexCoord;
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

uniform propLuz luz;
propMaterial material;

vec3 Phong(){
	vec3 l = normalize(posicion - luz.posicion);
	float LdotDirLuz = dot(l, normalize( luz.direccion));
	float angulo = degrees(acos(LdotDirLuz));
	if (angulo > luz.angulo)
		return (luz.amb * material.colorAmb);
	
	//Factor de decrecimiento
	float k = pow(LdotDirLuz, luz.k); 
	vec3 n = normalize(normal);
	vec3 v = normalize(vec3(-posicion));
	vec3 r = reflect(l, n);
	return ((luz.amb * material.colorAmb) + 
		    k * ((luz.dif * material.colorDif * max( dot(-l, n), 0.0 )) +
				 (luz.espec * material.colorEspec * pow(max(dot(r,v),0.0), material.brillo ))));
}

vec3 BlinnPhong(){
	vec3 l = normalize(posicion - luz.posicion);
	float LdotDirLuz = dot(l, normalize( luz.direccion));
	float angulo = degrees(acos(LdotDirLuz));
	if (angulo > luz.angulo)
		return (luz.amb * material.colorAmb);

	//Factor de decrecimiento
	float k = pow(LdotDirLuz, luz.k); 
	vec3 n = normalize(normal);
	vec3 v = normalize(vec3(-posicion));
	vec3 h = normalize(v - l);
	return ((luz.amb * material.colorAmb) +
		    k * ((luz.dif * material.colorDif * max( dot(-l, n), 0.0 )) +
		         (luz.espec * material.colorEspec * pow(max(dot(h,n),0.0), material.brillo ))));
}

void main (void){
	//Agregado por Migue
	vTexCoord.x += desplazamientoDeCinta;

	vec4 color =  texture2D(cintaText, vTexCoord);
	if (color.a == 0.0)
		color = vec4(0.2, 0.2, 0.2, 1.0);

	if (!luz.prendida)
		gl_FragColor = color;
	else{
		material.colorAmb = color.xyz;
		material.colorDif = color.xyz;
		material.colorEspec = vec3(0.2, 0.2, 0.2);
		material.brillo =2.0;
	
		gl_FragColor = vec4(BlinnPhong(), 1.0);
	}
}