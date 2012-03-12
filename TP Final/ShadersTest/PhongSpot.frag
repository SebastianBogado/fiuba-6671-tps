varying vec3 normal;
varying vec3 posicion;
varying vec2 vTexCoord;


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
		4.0,
		vec3(0.01), 
		vec3(0.8),
		vec3(0.9)
	);
uniform propMaterial material;
uniform sampler2D textura;
uniform sampler2D normalMap;
uniform bool texturado;
uniform bool tieneNormalMap;
vec3 colorTextura;

vec3 Phong(){
	vec3 color = vec3(0.0);
	vec3 luzAmb, luzDif, n;

	if (tieneNormalMap)
		n = texture2D(normalMap, vTexCoord).xyz;
	else
		n = normalize(normal);

	if (texturado){
		luzAmb = luzI.amb * colorTextura;
		luzDif = luzI.dif * colorTextura;
	}
	else{
		luzAmb = luzI.amb * material.colorAmb;
		luzDif = luzI.dif * material.colorDif;	
	}	
	vec3 luzEspec = luzI.espec * material.colorEspec;
	float k, LdotDirLuz, angulo;

	if (! gl_FrontFacing)
		n = -n;
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
	vec3 luzAmb, luzDif, n;

	if (tieneNormalMap)
		n = texture2D(normalMap, vTexCoord).xyz;
	else
		n = normalize(normal);

	if (texturado){
		luzAmb = luzI.amb * colorTextura;
		luzDif = luzI.dif * colorTextura;
	}
	else{
		luzAmb = luzI.amb * material.colorAmb;
		luzDif = luzI.dif * material.colorDif;	
	}	
	vec3 luzEspec = luzI.espec * material.colorEspec;
	float k, LdotDirLuz, angulo; 

	
	if (! gl_FrontFacing)
		n = -n;
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
	vec4 texturaRGBA = texture2D(textura, vTexCoord);
	colorTextura = texturaRGBA.xyz;
	if ( (texturado) && ( texturaRGBA.a == 0.0 )) 
		discard;
	gl_FragColor = vec4(BlinnPhong(), 1.0);
}