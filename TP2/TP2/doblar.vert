//Vertex shader mnimo
varying vec3 N;
varying vec3 v;
float angulo;
uniform float distancia;

float gradosARadianes(float grados) {

	const float PI = 3.141592653589;
	
	return grados * PI / 180.0;


}


vec3 direccionAVertice(vec4 vertice,vec3 puntoRef){
	

	vec3 resultado; 
		
	float radianes = angulo;//gradosARadianes(angulo * vertice.z / altura);	
	if(distancia>=0){
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
	
		parcial += pow(vector_distancia[i],2.0);
	
	}
	
	distancia = sqrt(parcial);
	
	return distancia;

}


vec3 transformarNormal(vec3 normal){

	vec3 normalTransformada=normal;
	if(distancia>0){
		normalTransformada.x=cos(angulo);
		}
	else {
		normalTransformada.x=-cos(angulo);
		}
	normalTransformada.z=sin(angulo);
	
	return normalTransformada;

}



void main()
{

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
	gl_Position = gl_ModelViewProjectionMatrix * vec4(resultado,gl_Vertex.w);
}
