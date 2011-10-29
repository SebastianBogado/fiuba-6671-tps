//Vertex shader retorcer
varying vec3 N;
varying vec3 v;

float gradosARadianes(float angulo){
	const float DPI=6.283185307;
	angulo = angulo / 360.0;
	angulo = angulo * DPI;
	return angulo;
}

vec4 calcular(vec4 posicionOriginal){
	
	float angulo = gradosARadianes(90.0);
	angulo = angulo * posicionOriginal.z;
	angulo = angulo/2.0;
	float xAux;// = posicionOriginal.y;
	float yAux;// = posicionOriginal.x;
	float cosAngulo = cos (angulo);
	float tgAngulo = tan (angulo);
	
	//float aux = posicionOriginal.y/posicionOriginal.x;
	//float alfa = atan(aux);
	//alfa = alfa + angulo;
	//xAux = xAux / tan(alfa);
	xAux = cosAngulo*(posicionOriginal.x - tgAngulo * posicionOriginal.y);
	
	//yAux = yAux * tan(alfa);
	yAux = cosAngulo*(tgAngulo * posicionOriginal.x + posicionOriginal.y);

	vec4 posicionFinal = vec4(xAux, yAux, posicionOriginal.z, posicionOriginal.w);

	return posicionFinal;
}

vec3 calcularNormal(vec3 normal){
	
	float angulo = gradosARadianes(90.0);
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

   v = vec3(gl_ModelViewMatrix * gl_Vertex);       
   N = normalize(gl_NormalMatrix * calcularNormal(gl_Normal));
   //N = normalize(gl_NormalMatrix * gl_Normal);
	vec4 aux = calcular(gl_Vertex);

	gl_Position = gl_ModelViewProjectionMatrix * aux;
}
