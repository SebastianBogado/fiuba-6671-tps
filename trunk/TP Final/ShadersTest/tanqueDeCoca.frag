varying vec3 direccionDeReflejo;
varying vec3 normal;
varying vec3 posicion;

struct propLuz{
	vec4 posicion;
	vec3 amb;
	vec3 dif;
	vec3 espec;
	bool prendida;
};

struct propMaterial{
	vec3 colorAmb;
	vec3 colorDif;
	vec3 colorEspec;
	float brillo;
};

uniform propLuz luz;
uniform propMaterial material;
uniform samplerCube skyBoxTex;

vec3 Phong(){
	vec3 n = normalize(normal);
	vec3 l = normalize(vec3(luz.posicion) - posicion );
	vec3 v = normalize(vec3(-posicion));
	vec3 r = reflect(-l, n);
	return ((luz.amb * material.colorAmb) +
		    (luz.dif * material.colorDif * max( dot(l, n), 0.0 )) +
		    (luz.espec * material.colorEspec * pow(max(dot(r,v),0.0), material.brillo )));
}

vec3 BlinnPhong(){
	vec3 n = normalize(normal);
	vec3 l = normalize(vec3(luz.posicion) - posicion );
	vec3 v = normalize(vec3(-posicion));
	vec3 h = normalize(v + l);
	return ((luz.amb * material.colorAmb) +
		    (luz.dif * material.colorDif * max( dot(l, n), 0.0 )) +
		    (luz.espec * material.colorEspec * pow(max(dot(h,n),0.0), material.brillo )));
}
void main (void){   
	vec3 reflejo = textureCube(skyBoxTex, direccionDeReflejo).xyz;

	if (!luz.prendida)
		gl_FragColor = vec4( mix( material.colorAmb, reflejo, 0.92), 1.0);
	else
		gl_FragColor = vec4( mix( BlinnPhong(), reflejo, 0.2), 1.0);
}