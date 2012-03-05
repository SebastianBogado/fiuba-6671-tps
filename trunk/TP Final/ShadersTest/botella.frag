uniform sampler2D etiquetaText, tapaText;
uniform float porcentajeDeLlenado;
uniform bool tieneEtiqueta;
uniform bool tieneTapa;

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
	vec4 plastico = vec4(0.65, 0.65, 0.65, 0.2);
	vec4 liquido = vec4(0.1719, 0.0, 0.0, 0.95);
	vec4 etiqueta =  texture2D(etiquetaText, vTexCoord);
	vec4 tapa =  texture2D(tapaText, vTexCoord);
	if (vTexCoord.t > porcentajeDeLlenado)
		liquido.a = 0.0;
	vec4 color = mix(plastico, liquido, liquido.a);
	
	if ((tieneEtiqueta) && (etiqueta.a != 0.0))
		color = etiqueta;
	
	if ((tieneTapa) && (tapa.a != 0.0))
		color = tapa;

	if (!luz.prendida)
		gl_FragColor = color;
	else{
		material.colorAmb = color.xyz;
		material.colorDif = color.xyz;
		material.colorEspec = vec3(0.7, 0.7, 0.7);
		material.brillo = 4.0;
	
		gl_FragColor = vec4(BlinnPhong(), color.a);
	}
}