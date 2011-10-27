//Vertex shader retorcer

void calcular(float &x, float &y, float &z){
	float angulo = 30;
	angulo = angulo * (z/2);
	float xAux = x;
	float yAux = y;

	float alfa = atan(y/x);
	alfa = alfa + angulo;
	xAux = y/tan(alfa);
	yAux = x*tan(alfa);

	x = xAux;
	y = yAux;
}


void main(){
	float x = gl_Vertex.x;
	float y = gl_Vertex.y;
	float z = gl_Vertex.z;
	calcular(x, y, z);

	gl_Position = vec4(x, y, z, 1);
	gl_Position = ftransform();
}