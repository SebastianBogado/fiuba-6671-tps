varying vec3 direccionDeReflejo;
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
		40.0,
		10.0,
		vec3(0.05, 0.05, 0.05), 
		vec3(0.6, 0.6, 0.6),
		vec3(0.8, 0.8, 0.8)
	);
uniform propMaterial material;
uniform samplerCube skyBoxTex;

vec3 Phong(){
	vec3 color = vec3(0.0);
	vec3 luzAmb =  (luzI.amb * material.colorAmb);
	vec3 luzDif = luzI.dif * material.colorDif;
	vec3 luzEspec = luzI.espec * material.colorEspec;
	float k, LdotDirLuz, angulo; 
	vec3 n = normalize(normal);
	vec3 v = normalize(-posicion);
	vec3 r, l;

	// Primera luz
	l = normalize(posicion - luzE1.posicion);
	LdotDirLuz = dot(l, normalize( luzE1.direccion));
	angulo = degrees(acos(LdotDirLuz));
	if ((angulo > luzI.angulo) || (! luzE1.prendida) )
		color += luzAmb;
	else{
		//Factor de decrecimiento
		k = pow(LdotDirLuz, luzI.k); 
		r = reflect(l, n);
		color += (luzAmb +
				k * ((luzDif * max( dot(-l, n), 0.0 )) +
					(luzEspec * pow(max(dot(r,v),0.0), material.brillo ))));
	}

	// Segunda luz
	l = normalize(posicion - luzE2.posicion);
	LdotDirLuz = dot(l, normalize( luzE2.direccion));
	angulo = degrees(acos(LdotDirLuz));
	if ((angulo > luzI.angulo) || (! luzE2.prendida) )
		color += luzAmb;
	else{
		//Factor de decrecimiento
		k = pow(LdotDirLuz, luzI.k); 
		r = reflect(l, n);
		color += (luzAmb +
				k * ((luzDif * max( dot(-l, n), 0.0 )) +
					(luzEspec * pow(max(dot(r,v),0.0), material.brillo ))));
	}

	// Tercera luz
	l = normalize(posicion - luzE3.posicion);
	LdotDirLuz = dot(l, normalize( luzE3.direccion));
	angulo = degrees(acos(LdotDirLuz));
	if ((angulo > luzI.angulo) || (! luzE3.prendida) )
		color += luzAmb;
	else{
		//Factor de decrecimiento
		k = pow(LdotDirLuz, luzI.k); 
		r = reflect(l, n);
		color += (luzAmb +
				k * ((luzDif * max( dot(-l, n), 0.0 )) +
					(luzEspec * pow(max(dot(r,v),0.0), material.brillo ))));
	}

	// Cuarta luz
	l = normalize(posicion - luzE4.posicion);
	LdotDirLuz = dot(l, normalize( luzE4.direccion));
	angulo = degrees(acos(LdotDirLuz));
	if ((angulo > luzI.angulo) || (! luzE4.prendida) )
		color += luzAmb;
	else{
		//Factor de decrecimiento
		k = pow(LdotDirLuz, luzI.k); 
		r = reflect(l, n);
		color += (luzAmb +
				k * ((luzDif * max( dot(-l, n), 0.0 )) +
					(luzEspec * pow(max(dot(r,v),0.0), material.brillo ))));
	}

	// Quinta luz
	l = normalize(posicion - luzE5.posicion);
	LdotDirLuz = dot(l, normalize( luzE5.direccion));
	angulo = degrees(acos(LdotDirLuz));
	if ((angulo > luzI.angulo) || (! luzE5.prendida) )
		color += luzAmb;
	else{
		//Factor de decrecimiento
		k = pow(LdotDirLuz, luzI.k); 
		r = reflect(l, n);
		color += (luzAmb +
				k * ((luzDif * max( dot(-l, n), 0.0 )) +
					(luzEspec * pow(max(dot(r,v),0.0), material.brillo ))));
	}

	// Sexta luz
	l = normalize(posicion - luzE6.posicion);
	LdotDirLuz = dot(l, normalize( luzE6.direccion));
	angulo = degrees(acos(LdotDirLuz));
	if ((angulo > luzI.angulo) || (! luzE6.prendida) )
		color += luzAmb;
	else{
		//Factor de decrecimiento
		k = pow(LdotDirLuz, luzI.k); 
		r = reflect(l, n);
		color += (luzAmb +
				k * ((luzDif * max( dot(-l, n), 0.0 )) +
					(luzEspec * pow(max(dot(r,v),0.0), material.brillo ))));
	}

	return color;
}

vec3 BlinnPhong(){
	vec3 color = vec3(0.0);
	vec3 luzAmb =  (luzI.amb * material.colorAmb);
	vec3 luzDif = luzI.dif * material.colorDif;
	vec3 luzEspec = luzI.espec * material.colorEspec;
	float k, LdotDirLuz, angulo; 
	vec3 n = normalize(normal);
	vec3 v = normalize(-posicion);
	vec3 h, l;

	// Primera luz
	l = normalize(posicion - luzE1.posicion);
	LdotDirLuz = dot(l, normalize( luzE1.direccion));
	angulo = degrees(acos(LdotDirLuz));
	if ((angulo > luzI.angulo) || (! luzE1.prendida) )
		color += luzAmb;
	else{
		//Factor de decrecimiento
		k = pow(LdotDirLuz, luzI.k); 
		h = normalize(v - l);
		color += (luzAmb +
				k * ((luzDif * max( dot(-l, n), 0.0 )) +
					(luzEspec * pow(max(dot(h,n),0.0), material.brillo ))));
	}

	//Segunda luz
	l = normalize(posicion - luzE2.posicion);
	LdotDirLuz = dot(l, normalize( luzE2.direccion));
	angulo = degrees(acos(LdotDirLuz));
	if ((angulo > luzI.angulo) || (! luzE2.prendida) )
		color += luzAmb;
	else{
		//Factor de decrecimiento
		k = pow(LdotDirLuz, luzI.k); 
		h = normalize(v - l);
		color += (luzAmb +
				k * ((luzDif * max( dot(-l, n), 0.0 )) +
					(luzEspec * pow(max(dot(h,n),0.0), material.brillo ))));
	}
	//Tercera luz
	l = normalize(posicion - luzE3.posicion);
	LdotDirLuz = dot(l, normalize( luzE3.direccion));
	angulo = degrees(acos(LdotDirLuz));
	if ((angulo > luzI.angulo) || (! luzE3.prendida) )
		color += luzAmb;
	else{
		//Factor de decrecimiento
		k = pow(LdotDirLuz, luzI.k); 
		h = normalize(v - l);
		color += (luzAmb +
				k * ((luzDif * max( dot(-l, n), 0.0 )) +
					(luzEspec * pow(max(dot(h,n),0.0), material.brillo ))));
	}
	//Cuarta luz
	l = normalize(posicion - luzE4.posicion);
	LdotDirLuz = dot(l, normalize( luzE4.direccion));
	angulo = degrees(acos(LdotDirLuz));
	if ((angulo > luzI.angulo) || (! luzE4.prendida) )
		color += luzAmb;
	else{
		//Factor de decrecimiento
		k = pow(LdotDirLuz, luzI.k); 
		h = normalize(v - l);
		color += (luzAmb +
				k * ((luzDif * max( dot(-l, n), 0.0 )) +
					(luzEspec * pow(max(dot(h,n),0.0), material.brillo ))));
	}
	//Quinta luz
	l = normalize(posicion - luzE5.posicion);
	LdotDirLuz = dot(l, normalize( luzE5.direccion));
	angulo = degrees(acos(LdotDirLuz));
	if ((angulo > luzI.angulo) || (! luzE5.prendida) )
		color += luzAmb;
	else{
		//Factor de decrecimiento
		k = pow(LdotDirLuz, luzI.k); 
		h = normalize(v - l);
		color += (luzAmb +
				k * ((luzDif * max( dot(-l, n), 0.0 )) +
					(luzEspec * pow(max(dot(h,n),0.0), material.brillo ))));
	}
	//Sexta luz
	l = normalize(posicion - luzE6.posicion);
	LdotDirLuz = dot(l, normalize( luzE6.direccion));
	angulo = degrees(acos(LdotDirLuz));
	if ((angulo > luzI.angulo) || (! luzE6.prendida) )
		color += luzAmb;
	else{
		//Factor de decrecimiento
		k = pow(LdotDirLuz, luzI.k); 
		h = normalize(v - l);
		color += (luzAmb +
				k * ((luzDif * max( dot(-l, n), 0.0 )) +
					(luzEspec * pow(max(dot(h,n),0.0), material.brillo ))));
	}

	return color;
}

void main (void){   
	vec3 reflejo = textureCube(skyBoxTex, direccionDeReflejo).xyz;

	gl_FragColor = vec4( mix( BlinnPhong(), reflejo, 0.2), 1.0);
}