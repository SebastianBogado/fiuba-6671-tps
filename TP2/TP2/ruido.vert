//Vertex shader mnimo
varying vec3 N;
varying vec3 v;

struct Onda{
	float longitud;
	float frecuencia;
	float amplitud;
};

//uniform
Onda ondaEnX = Onda(0.3, 1.0, 0.1);Onda ondaEnY = Onda(0.3, 5.0, 0.1);
//Onda ondaEnY = Onda(0.2, 0.8, 0.04);
Onda ondaEnZ = Onda(0.01, 1.2, 0.5);

uniform float tiempo;

vec4 calcularRuido(vec4 posicion, vec3 normal){
	vec4 nuevaPos = posicion;
	const float DPI = 6.283185307;
	float Ax = ondaEnX.amplitud;
	float kx = DPI / ondaEnX.longitud; 
	float wx = DPI * ondaEnX.frecuencia;
	float Ay = ondaEnY.amplitud;
	float ky = DPI / ondaEnY.longitud; 
	float wy = DPI * ondaEnY.frecuencia;
	float Az = ondaEnZ.amplitud;
	float kz = DPI / ondaEnZ.longitud; 
	float wz = DPI * ondaEnZ.frecuencia;
	float t = tiempo;
	//float w = sqrt(kx*kx + ky*ky + kz*kz);
	float w = ondaEnX.frecuencia*ondaEnX.longitud*sqrt(kx*kx + ky*ky);
	float A = sqrt(Ax*Ax + Ay*Ay);
	
	//nuevaPos[0]=ondaEnY.amplitud * sin((ky*gl_Vertex.y) - wy*t) + ondaEnZ.amplitud * sin((kz*gl_Vertex.z) - wz*t);
	//nuevaPos[1]=ondaEnX.amplitud * sin((kx*gl_Vertex.x) - wx*t) + ondaEnZ.amplitud * sin((kz*gl_Vertex.z) - wz*t);
	//nuevaPos = nuevaPos + (Ax*Ay*Az* sin(ky*posicion.y +kz*posicion.z+kx*posicion.x- w*t))* normal;
	
	//para 1D frente de ondas
	//nuevaPos.z = Ax*sin(kx*posicion.x-wx*t);
	
	//para 2D prueba 1 pretendía ser que fuese como la gota cayendo en el agua
	//nuevaPos.z = A*sin(sqrt(pow(kx*posicion.x,2.0) + pow(ky*posicion.y,2.0)) - w*t);
	
	//para 2D prueba 2 sumar independientemente las ondas
	//nuevaPos.z = Ax*sin(kx*posicion.x-wx*t) + Ay*sin(ky*posicion.y-wy*t);;
	
	//para 2D prueba 3 va ganando este o el siguiente
	//nuevaPos.z= A*sin(posicion.x*posicion.y-w*t);

	//para 2D prueba 4 una mezcla de senoides de la prueba 3 porque me gustó
	//nuevaPos.z=A*sin(posicion.x*posicion.y-w*t) + 0.5*A*sin(0.9*posicion.x*posicion.y-1.5*w*t) + A*2.0*sin(1.8*posicion.x*posicion.y-0.3*w*t);
	
	//para 2D prueba 5
	//nuevaPos.z=A*(sin(pow(kx*posicion.x,2.0) + pow(ky*posicion.y, 2.0) - w*t))/(posicion.x*posicion.x + posicion.y*posicion.y);

	//if ((posicion.x == 0.0) && (posicion.y == 0.0))
	//	nuevaPos.z = A;

	//para 2D prueba 6
	nuevaPos.z = A*sin(pow(kx*posicion.x,2.0) + pow(ky*posicion.y,2.0)- w*t) ;//
	return nuevaPos;
}

vec3 calcularNormal(vec4 posicion, vec3 normal){
	vec3 normalNueva = normal;
	const float DPI = 6.283185307;
	float Ax = ondaEnX.amplitud;
	float kx = DPI / ondaEnX.longitud; 
	float wx = DPI * ondaEnX.frecuencia;
	float Ay = ondaEnY.amplitud;
	float ky = DPI / ondaEnY.longitud; 
	float wy = DPI * ondaEnY.frecuencia;
	float t = tiempo;
	float w = ondaEnX.frecuencia*ondaEnX.longitud*sqrt(kx*kx+ky*ky);
	float A = sqrt(Ax*Ax+Ay*Ay);
	float raiz = sqrt(pow(kx*posicion.x,2.0) + pow(ky*posicion.y,2.0));

	//para 1D
	//normalNueva = vec3(-kx*Ax*cos(kx*posicion.x-wx*t), 0.0 , 1.0);

	//para 2D prueba 1
	//normalNueva = vec3(-kx*kx*A*posicion.x*(cos(raiz-w*t))/raiz, -ky*ky*A*posicion.y*(cos(raiz-w*t))/raiz , 1.0);
	
	//para 2D prueba 2
	//normalNueva = vec3(-kx*Ax*cos(kx*posicion.x-wx*t), -ky*Ay*cos(ky*posicion.y-wy*t), 1.0);
	
	//para 2D prueba 3
	//normalNueva = vec3(-posicion.y*A*cos(posicion.x*posicion.y-w*t), -posicion.x*A*cos(posicion.x*posicion.y-w*t),1.0);
	
	//para 2D prueba 4
	//normalNueva = vec3(-A*posicion.y*sin(posicion.x*posicion.y-w*t)-0.45*posicion.y*A*sin(0.9*posicion.x*posicion.y-1.5*w*t)-3.6*posicion.y*A*sin(1.8*posicion.x*posicion.y-0.3*w*t), -A*posicion.x*sin(posicion.x*posicion.y-w*t)-0.45*posicion.x*A*sin(0.9*posicion.x*posicion.y-1.5*w*t)-3.6*posicion.x*A*sin(1.8*posicion.x*posicion.y-0.3*w*t), 1.0); 
	
	//para 2D prueba 5
	float argumento = pow(kx*posicion.x, 2.0) + pow(ky*posicion.y, 2.0);// - w*t;
	//normalNueva = vec3(-A*(kx*kx*posicion.x*(2.0*posicion.x*posicion.x + 2.0*posicion.y*posicion.y)*cos(argumento) - 2.0*posicion.x*sin(argumento))/(pow(posicion.x*posicion.x + posicion.y + posicion.y, 2.0)), -A*(ky*ky*posicion.y*(2.0*posicion.x*posicion.x + 2.0*posicion.y*posicion.y)*cos(argumento) - 2.0*posicion.y*sin(argumento))/(pow(posicion.x*posicion.x + posicion.y + posicion.y, 2.0)), 1.0);
	//if ((posicion.x == 0.0) && (posicion.y == 0.0))
		//normalNueva = vec3(0.0, 0.0, 1.0);

	//para 2D prueba 6
	normalNueva = vec3(-2.0*A*kx*kx*posicion.x*cos(argumento), -2.0*A*ky*ky*posicion.y*cos(argumento), 1.0);
	
	return normalNueva;
}

void main()
{	
	v = vec3(gl_ModelViewMatrix * gl_Vertex);   
	N = normalize(gl_NormalMatrix * calcularNormal(gl_Vertex, gl_Normal));
	vec4 aux = calcularRuido(gl_Vertex, gl_Normal);

	gl_Position = gl_ModelViewProjectionMatrix * aux;
}
