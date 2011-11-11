//Vertex shader 
varying vec3 N;
varying vec3 v;

varying vec2 vTexCoord;

float angulo;
uniform float distancia;
uniform float tiempo;

float gradosARadianes(float grados) {
	const float PI = 3.141592653589;
	
	return grados * PI / 180.0;
}

float animacion(float distancia){
	return distancia*sin(2.0*tiempo);
}


vec3 direccionAVertice(vec4 vertice,vec3 puntoRef){
	

	vec3 resultado; 
		
	float radianes = angulo;//gradosARadianes(angulo * vertice.z / altura);	
	if(distancia>=0.0){
		resultado.x=-cos(radianes);
	}
	else{
		resultado.x=cos(radianes);
	}
	resultado.y=0.0;
	resultado.z=sin(radianes);		
	
	return resultado;

}


float calcularDistanciaObjetiva(vec4 vertice,vec3 puntoRef){

	float distancia;
	
	vec3 vertPlano = vec3(vertice.xy,0.0);
	
	vec3 vector_distancia = vertPlano - puntoRef;
	
	float parcial=0.0;
	
	for (int i=0; i < 3 ; i++){
	
		parcial += vector_distancia[i] * vector_distancia[i];
	
	}
	
	distancia = sqrt(parcial);
	
	return distancia;

}


vec3 transformarNormal(vec3 normalEntrada){
	vec3 normal = normalize (normalEntrada);
	
	vec3 normalTransformada = vec3(0.0);
	
	float signo =distancia / abs (distancia);

	vec3 vecRotacion=vec3(0.0,1.0*signo,0.0);

	float coseno = dot(normal,vecRotacion);
	
	float cosAngulo = cos (angulo);
	float sinAngulo = sin (angulo);
	
	if ( coseno  == 1.0 || coseno == -1.0){
		normalTransformada = normal;
	}
	else{
		if(distancia>0.0)
			normalTransformada.x=normal.x*cosAngulo + sinAngulo*normal.z;
		else 
			normalTransformada.x=normal.x*(-cosAngulo)+ sinAngulo*normal.z;

		normalTransformada.y=normal.y;
		normalTransformada.z=-normal.x*sinAngulo + cosAngulo*normal.z; 
		
	}
	
	return normalTransformada;

}



void main()
{
	vTexCoord = gl_MultiTexCoord0.xy;
	float altura=1.0;
	
	vec4 vertice = gl_Vertex;

	//Solo sirve para Debuggear con el IDE
	//vertice.z+=0.5; 
	
	angulo = asin(vertice.z/abs(distancia));
	
	vec3 puntoReferencia = vec3(distancia,0.0,0.0);
	
	puntoReferencia.y = vertice.y;
	vec3 dirAVertice = direccionAVertice(vertice,puntoReferencia);
	
	
	vec3 resultado= vertice.xyz ;
	
	float distanciaObjetiva = calcularDistanciaObjetiva(vertice,puntoReferencia);
	
	resultado= puntoReferencia + dirAVertice*distanciaObjetiva;
	    
	N = normalize (gl_NormalMatrix * transformarNormal(gl_Normal));	

	if (abs(gl_Vertex.x) > 10.0 || abs(gl_Vertex.y) > 10.0 ||abs(gl_Vertex.z) > 10.0){
		v = vec3(gl_ModelViewMatrix * gl_Vertex);
		gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	}
	else{
		v = vec3(gl_ModelViewMatrix * vec4(resultado,gl_Vertex.w));
		gl_Position = gl_ModelViewProjectionMatrix * vec4(resultado,gl_Vertex.w);
	}
}
