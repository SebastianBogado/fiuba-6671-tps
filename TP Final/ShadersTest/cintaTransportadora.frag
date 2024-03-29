uniform sampler2D cintaText;

varying vec2 vTexCoord;
varying vec3 normal;
varying vec3 posicion;

struct propExternasLuz{
	bool prendida;
	vec3 posicion;
	vec3 direccion;
};

struct propInternasLuz{
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
uniform propExternasLuz luzE1;
uniform propExternasLuz luzE2;
uniform propExternasLuz luzE3;
uniform propExternasLuz luzE4;
uniform propExternasLuz luzE5;
uniform propExternasLuz luzE6;

propInternasLuz luzI = propInternasLuz( 
		70.0,
		3.0,
		vec3(0.01), 
		vec3(0.8),
		vec3(0.9)
	);
vec3 iluminacionBase = vec3(0.05);
propMaterial material;

vec3 Phong(){
	vec3 color = iluminacionBase * material.colorAmb;
	vec3 luzAmb =  (luzI.amb * material.colorAmb);
	vec3 luzDif = luzI.dif * material.colorDif;
	vec3 luzEspec = luzI.espec * material.colorEspec;
	float k, LdotDirLuz, angulo; 
	vec3 n = normalize(normal);
	if (! gl_FrontFacing)
		n = -n;
	vec3 v = normalize(-posicion);
	vec3 r, l;

	// Primera luz
	l = normalize(posicion - luzE1.posicion);
	LdotDirLuz = dot(l, normalize( luzE1.direccion));
	angulo = degrees(acos(LdotDirLuz));
	if (luzE1.prendida){
		if (angulo > luzI.angulo)
			color += luzAmb;
		else{
			//Factor de decrecimiento
			k = pow(LdotDirLuz, luzI.k); 
			r = reflect(l, n);
			color += k * ((luzDif * max( dot(-l, n), 0.0 )) +
					      (luzEspec * pow(max(dot(r,v),0.0), material.brillo )));
		}
	}

	// Segunda luz
	l = normalize(posicion - luzE2.posicion);
	LdotDirLuz = dot(l, normalize( luzE2.direccion));
	angulo = degrees(acos(LdotDirLuz));
	if (luzE2.prendida){
		if (angulo > luzI.angulo)
			color += luzAmb;
		else{
			//Factor de decrecimiento
			k = pow(LdotDirLuz, luzI.k); 
			r = reflect(l, n);
			color += k * ((luzDif * max( dot(-l, n), 0.0 )) +
					      (luzEspec * pow(max(dot(r,v),0.0), material.brillo )));
		}
	}

	// Tercera luz
	l = normalize(posicion - luzE3.posicion);
	LdotDirLuz = dot(l, normalize( luzE3.direccion));
	angulo = degrees(acos(LdotDirLuz));
	if (luzE3.prendida){
		if (angulo > luzI.angulo)
			color += luzAmb;
		else{
			//Factor de decrecimiento
			k = pow(LdotDirLuz, luzI.k); 
			r = reflect(l, n);
			color += k * ((luzDif * max( dot(-l, n), 0.0 )) +
					      (luzEspec * pow(max(dot(r,v),0.0), material.brillo )));
		}
	}

	// Cuarta luz
	l = normalize(posicion - luzE4.posicion);
	LdotDirLuz = dot(l, normalize( luzE4.direccion));
	angulo = degrees(acos(LdotDirLuz));
	if (luzE4.prendida){
		if (angulo > luzI.angulo)
			color += luzAmb;
		else{
			//Factor de decrecimiento
			k = pow(LdotDirLuz, luzI.k); 
			r = reflect(l, n);
			color += k * ((luzDif * max( dot(-l, n), 0.0 )) +
					      (luzEspec * pow(max(dot(r,v),0.0), material.brillo )));
		}
	}

	// Quinta luz
	l = normalize(posicion - luzE5.posicion);
	LdotDirLuz = dot(l, normalize( luzE5.direccion));
	angulo = degrees(acos(LdotDirLuz));
	if (luzE5.prendida){
		if (angulo > luzI.angulo)
			color += luzAmb;
		else{
			//Factor de decrecimiento
			k = pow(LdotDirLuz, luzI.k); 
			r = reflect(l, n);
			color += k * ((luzDif * max( dot(-l, n), 0.0 )) +
					      (luzEspec * pow(max(dot(r,v),0.0), material.brillo )));
		}
	}

	// Sexta luz
	l = normalize(posicion - luzE6.posicion);
	LdotDirLuz = dot(l, normalize( luzE6.direccion));
	angulo = degrees(acos(LdotDirLuz));
	if (luzE6.prendida){
		if (angulo > luzI.angulo)
			color += luzAmb;
		else{
			//Factor de decrecimiento
			k = pow(LdotDirLuz, luzI.k); 
			r = reflect(l, n);
			color += k * ((luzDif * max( dot(-l, n), 0.0 )) +
					      (luzEspec * pow(max(dot(r,v),0.0), material.brillo )));
		}
	}

	return color;
}

vec3 BlinnPhong(){
	vec3 color = iluminacionBase * material.colorAmb;
	vec3 luzAmb = luzI.amb * material.colorAmb;
	vec3 luzDif = luzI.dif * material.colorDif;
	vec3 luzEspec = luzI.espec * material.colorEspec;
	float k, LdotDirLuz, angulo; 
	vec3 n = normalize(normal);
	if (! gl_FrontFacing)
		n = -n;
	vec3 v = normalize(-posicion);
	vec3 h, l;

	// Primera luz
	l = normalize(posicion - luzE1.posicion);
	LdotDirLuz = dot(l, normalize( luzE1.direccion));
	angulo = degrees(acos(LdotDirLuz));
	if (luzE1.prendida){
		if (angulo > luzI.angulo)
			color += luzAmb;
		else{
			//Factor de decrecimiento
			k = pow(LdotDirLuz, luzI.k); 
			h = normalize(v - l);
			color += k * ((luzDif * max( dot(-l, n), 0.0 )) +
					      (luzEspec * pow(max(dot(h,n),0.0), material.brillo )));
		}
	}

	//Segunda luz
	l = normalize(posicion - luzE2.posicion);
	LdotDirLuz = dot(l, normalize( luzE2.direccion));
	angulo = degrees(acos(LdotDirLuz));
	if (luzE2.prendida){
		if (angulo > luzI.angulo)
			color += luzAmb;
		else{
			//Factor de decrecimiento
			k = pow(LdotDirLuz, luzI.k); 
			h = normalize(v - l);
			color += k * ((luzDif * max( dot(-l, n), 0.0 )) +
					      (luzEspec * pow(max(dot(h,n),0.0), material.brillo )));
		}
	}

	//Tercera luz
	l = normalize(posicion - luzE3.posicion);
	LdotDirLuz = dot(l, normalize( luzE3.direccion));
	angulo = degrees(acos(LdotDirLuz));
	if (luzE3.prendida){
		if (angulo > luzI.angulo)
			color += luzAmb;
		else{
			//Factor de decrecimiento
			k = pow(LdotDirLuz, luzI.k); 
			h = normalize(v - l);
			color += k * ((luzDif * max( dot(-l, n), 0.0 )) +
					      (luzEspec * pow(max(dot(h,n),0.0), material.brillo )));
		}
	}

	//Cuarta luz
	l = normalize(posicion - luzE4.posicion);
	LdotDirLuz = dot(l, normalize( luzE4.direccion));
	angulo = degrees(acos(LdotDirLuz));
	if (luzE4.prendida){
		if (angulo > luzI.angulo)
			color += luzAmb;
		else{
			//Factor de decrecimiento
			k = pow(LdotDirLuz, luzI.k); 
			h = normalize(v - l);
			color += k * ((luzDif * max( dot(-l, n), 0.0 )) +
					      (luzEspec * pow(max(dot(h,n),0.0), material.brillo )));
		}
	}

	//Quinta luz
	l = normalize(posicion - luzE5.posicion);
	LdotDirLuz = dot(l, normalize( luzE5.direccion));
	angulo = degrees(acos(LdotDirLuz));
	if (luzE5.prendida){
		if (angulo > luzI.angulo)
			color += luzAmb;
		else{
			//Factor de decrecimiento
			k = pow(LdotDirLuz, luzI.k); 
			h = normalize(v - l);
			color += k * ((luzDif * max( dot(-l, n), 0.0 )) +
					      (luzEspec * pow(max(dot(h,n),0.0), material.brillo )));
		}
	}

	//Sexta luz
	l = normalize(posicion - luzE6.posicion);
	LdotDirLuz = dot(l, normalize( luzE6.direccion));
	angulo = degrees(acos(LdotDirLuz));
	if (luzE6.prendida){
		if (angulo > luzI.angulo)
			color += luzAmb;
		else{
			//Factor de decrecimiento
			k = pow(LdotDirLuz, luzI.k); 
			h = normalize(v - l);
			color += k * ((luzDif * max( dot(-l, n), 0.0 )) +
					      (luzEspec * pow(max(dot(h,n),0.0), material.brillo )));
		}
	}

	return color;
}

void main (void){
	vec4 color =  texture2D(cintaText, vTexCoord);

	material.colorAmb = color.xyz;
	material.colorDif = color.xyz;
	material.colorEspec = vec3(0.2, 0.2, 0.2);
	material.brillo = 2.0;

	gl_FragColor = vec4(BlinnPhong(), 1.0);
}