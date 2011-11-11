//Vertex shader retorcer
varying vec3 N;
varying vec3 v;
varying vec2 vTexCoord;

uniform float anguloDeRetorsion;
uniform float tiempo;

float gradosARadianes(float angulo){
	const float DPI=6.283185307;
	angulo = angulo / 360.0;
	angulo = angulo * DPI;
	return angulo;
}

float animacion(float anguloDeRetorsion){
	return anguloDeRetorsion*sin(20.0*tiempo);
}

vec4 calcular(vec4 posicionOriginal){
	
	float angulo = gradosARadianes(animacion(anguloDeRetorsion));
	angulo = angulo * posicionOriginal.z;
	angulo = angulo/2.0;
	float xAux;
	float yAux;
	float cosAngulo = cos (angulo);
	float tgAngulo = tan (angulo);
	
	xAux = cosAngulo*(posicionOriginal.x - tgAngulo * posicionOriginal.y);
	
	yAux = cosAngulo*(tgAngulo * posicionOriginal.x + posicionOriginal.y);

	vec4 posicionFinal = vec4(xAux, yAux, posicionOriginal.z, posicionOriginal.w);

	return posicionFinal;
}

vec3 calcularNormal(vec3 normal){
	
	float angulo = gradosARadianes(anguloDeRetorsion);
	angulo = angulo * normal[2];
	angulo = angulo/2.0;
	float xAux;// = posicionOriginal.y;
	float yAux;// = posicionOriginal.x;
	float cosAngulo = cos (angulo);
	float tgAngulo = tan (angulo);
	
	xAux = cosAngulo*(normal[0] - tgAngulo * normal[1]);
	
	yAux = cosAngulo*(tgAngulo * normal[0] + normal[1]);

	vec3 posicionFinal = vec3(xAux, yAux, normal[2]);

	return posicionFinal;

}

void main(void)
{
	vTexCoord = gl_MultiTexCoord0.xy;
	N = normalize(gl_NormalMatrix * calcularNormal(gl_Normal));
	vec4 aux = calcular(gl_Vertex);
	if (abs(gl_Vertex.x) > 10.0 || abs(gl_Vertex.y) > 10.0 ||abs(gl_Vertex.z) > 10.0){
		v = vec3(gl_ModelViewMatrix * gl_Vertex); 
		gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	}
	else{
		v = vec3(gl_ModelViewMatrix * aux);
		gl_Position = gl_ModelViewProjectionMatrix * aux;
	}
}
