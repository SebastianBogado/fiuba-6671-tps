//Vertex shader 
varying vec3 N;
varying vec3 v;
varying vec2 vTexCoord;
uniform float tiempo;
uniform vec3 centro;

float radioEsfera = 1.0;
float amplitud;

vec3 calcularDireccion(){

	vec3 resultado=gl_Vertex.xyz - centro;

	return resultado;
}

float calcDistAEsfera(vec3 vector){

	float resultado=0.0;
	for (int i=0; i < 3;i++)
		resultado += vector[i]*vector[i];

	resultado = sqrt (resultado);

	resultado = resultado - radioEsfera;

	return resultado;
}

vec3 calcularNormal(vec3 vector){

	vec3 resultado = mix(vector,gl_Normal.xyz,amplitud);

	return resultado;

}


void main()
{	
	vTexCoord = gl_MultiTexCoord0.xy;
	v = vec3(gl_ModelViewMatrix * gl_Vertex);     

	vec3 vecDir = calcularDireccion();
	
	//float distancia = sqrt(parcial);
	float distancia = calcDistAEsfera(vecDir);
	
	vecDir = normalize (vecDir);

	N = calcularNormal(vecDir);

	amplitud = (sin(tiempo*2.0)+1.0)/2.0;
		
	vec3 vertice;
	
	if(abs(distancia) >= 0.001)
	 vertice = gl_Vertex.xyz - amplitud * distancia * vecDir;
	else
		vertice = gl_Vertex.xyz;

	if (abs(gl_Vertex.x) > 10.0 || abs(gl_Vertex.y) > 10.0 ||abs(gl_Vertex.z) > 10.0){
		v = vec3(gl_ModelViewMatrix * gl_Vertex);
		gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	}
	else{
		v = vec3(gl_ModelViewMatrix * vec4(vertice,1.0));
		gl_Position = gl_ModelViewProjectionMatrix *vec4(vertice,1.0);
	}
}
