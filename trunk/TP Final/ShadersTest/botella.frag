uniform sampler2D etiquetaText, tapaText;
uniform float porcentajeDeLiquido;
uniform bool tieneEtiqueta;
uniform bool tieneTapa;

varying vec2 vTexCoord;
varying vec3 normal;
varying vec3 posicion;

struct propLuz{
	vec4 posicion;
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

propLuz luz;
propMaterial material;

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
	vec4 plastico = vec4(0.9, 0.9, 0.9, 0.2);
	vec4 liquido = vec4(0.1719, 0.0, 0.0, 0.95);
	vec4 etiqueta =  texture2D(etiquetaText, vTexCoord);
	vec4 tapa =  texture2D(tapaText, vTexCoord);
	if (vTexCoord.t > porcentajeDeLiquido)
		liquido.a = 0.0;
	vec4 color = mix(plastico, liquido, liquido.a);
	
	if ((tieneEtiqueta) && (etiqueta.a != 0.0))
		color = etiqueta;
	
	if ((tieneTapa) && (tapa.a != 0.0))
		color = tapa;
	/*
	material.colorAmb = color.xyz;
	material.colorDif = color.xyz;
	material.colorEspec = color.xyz;
	material.brillo = 20.0;*/
	
	material.colorAmb = vec3(0.0, 0.0, 0.0);
	material.colorDif = vec3(0.55, 0.55, 0.55);
	material.colorEspec = vec3(0.7, 0.7, 0.7);
	material.brillo = 32.0;
	luz.posicion = vec4(5.0, 5.0, 5.0, 1.0);
	luz.amb = vec3(1.0, 1.0, 1.0);
	luz.dif = vec3(1.0, 1.0, 1.0);
	luz.espec = vec3(1.0, 1.0, 1.0);
	gl_FragColor = vec4(BlinnPhong(), color.a);
}