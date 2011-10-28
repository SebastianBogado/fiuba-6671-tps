//Vertex shader retorcer

float gradosARadianes(float angulo){
	const float DPI=6.283185307;
	angulo = angulo / 360.0;
	angulo = angulo * DPI;
	return angulo;
}

vec4 calcular(vec4 posicionOriginal){
	
	float angulo = gradosARadianes(30.0);
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


void main(){
	vec4 aux = calcular(gl_Vertex);

	gl_Position = gl_ModelViewProjectionMatrix * aux;
}