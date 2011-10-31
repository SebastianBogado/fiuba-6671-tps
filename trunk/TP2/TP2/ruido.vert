//Vertex shader ruido
//

varying vec3 N;
varying vec3 v;

struct Onda{
	float longitud;
	float frecuencia;
	float amplitud;
};

//uniform
Onda ondaEnX = Onda(0.09, 0.5, 0.1);
Onda ondaEnY = Onda(0.02, 0.8, 0.04);

uniform float tiempo;

float calcularRuidoEnDireccionNormal(vec4 r){
	float diferencia;

	//Variables que ayudan a la notacion
	const float DPI = 6.283185307;
	float Ax = ondaEnX.amplitud;
	float kx = DPI / ondaEnX.longitud; 
	float wx = DPI * ondaEnX.frecuencia;
	float Ay = ondaEnY.amplitud;
	float ky = DPI / ondaEnY.longitud; 
	float wy = DPI * ondaEnY.frecuencia;
	float t = tiempo;
	float k = sqrt(kx*kx + ky*ky);
	float w = sqrt(wx*wx + wy*wy);
	float A = sqrt(Ax*Ax + Ay*Ay);
	//Fin variables

	/*
	//suma independientemente de 2 ondas
	diferencia = Ax*sin(kx*r.x-wx*t)+ Ay*sin(ky*r.y-wy*t);

	//una mezcla de senoides de argumento x.y
	//diferencia = diferencia + A*sin(r.x*r.y-w*t) + 0.5*A*sin(0.9*r.x*r.y-1.5*w*t) + A*2.0*sin(1.8*r.x*r.y-0.3*w*t);
	diferencia = diferencia + A*sin(k*r.x*r.y-w*t) + 0.5*A*sin(0.9*k*r.x*r.y-1.5*w*t) + A*2.0*sin(1.8*k*r.x*r.y-0.3*w*t);
	*/

	diferencia = Ax*sin(kx*r.x-wx*t);
	return diferencia;
}

vec3 rotarEnY(float angulo, vec3 posicion){
	mat3 rotadoraEnY = mat3( cos(angulo),  0.0, sin(angulo),
									 0.0,  1.0,			0.0,
							-sin(angulo),  0.0, cos(angulo));
	return rotadoraEnY*posicion;
}

vec3 rotarEnX(float angulo, vec3 posicion){
	mat3 rotadoraEnX = mat3(1.0,		 0.0,		   0.0,
							0.0, cos(angulo), -sin(angulo),
							0.0, sin(angulo),  cos(angulo));
	return rotadoraEnX*posicion;
}

vec4 calcularRuido(vec4 r, vec3 n){
	//Calcular el ruido en la dirección normal
	float z = calcularRuidoEnDireccionNormal(r);

	//Alinear a la dirección normal
	float anguloDeRotacionEnY = atan(n.x/n.z);
	vec3 nuevaPosicion = rotarEnY(anguloDeRotacionEnY, vec3(0.0, 0.0, z));
	float anguloDeRotacionEnX = atan(n.z/n.y);
	nuevaPosicion = rotarEnX(anguloDeRotacionEnX, nuevaPosicion);

	//Trasladarlo al punto que pertenece
	vec4 posicionFinal = vec4(nuevaPosicion, 0.0) + r;

	//Fin
	return posicionFinal;
}

vec3 calcularNormal(vec4 r, vec3 n){
	vec3 normalNueva;
	
	//Variables que ayudan a la notacion
	const float DPI = 6.283185307;
	float Ax = ondaEnX.amplitud;
	float kx = DPI / ondaEnX.longitud; 
	float wx = DPI * ondaEnX.frecuencia;
	float Ay = ondaEnY.amplitud;
	float ky = DPI / ondaEnY.longitud; 
	float wy = DPI * ondaEnY.frecuencia;
	float t = tiempo;
	float k = sqrt(kx*kx + ky*ky);
	float w = sqrt(wx*wx + wy*wy);
	float A = sqrt(Ax*Ax+Ay*Ay);
	//Fin variables

	/*
	//normal de las dos senoides independientes
	normalNueva = vec3(-kx*Ax*cos(kx*r.x-wx*t), -ky*Ay*cos(ky*r.y-wy*t), 1.0);
	
	//normal de las senoides de argumento x.y
	normalNueva.x = normalNueva.x - A*k*r.y*sin(k*r.x*r.y-w*t) - 0.45*A*k*r.y*sin(0.9*k*r.x*r.y-1.5*w*t) - 3.6*A*k*r.y*sin(1.8*k*r.x*r.y-0.3*w*t);
	normalNueva.y = normalNueva.y - A*k*r.x*sin(k*r.x*r.y-w*t) - 0.45*A*k*r.x*sin(0.9*k*r.x*r.y-1.5*w*t) - 3.6*A*k*r.x*sin(1.8*k*r.x*r.y-0.3*w*t); 
	*/

	normalNueva = vec3(-kx*Ax*cos(kx*r.x-wx*t), 0.0, 1.0);

	/*
	//Alineación de normalNueva = (0, 0, 1) con n = (0, 0, 1)
	float anguloDeRotacionEnY = atan(n.x/n.z);
	normalNueva = rotarEnY(anguloDeRotacionEnY, normalNueva);
	float anguloDeRotacionEnX = atan(n.z/n.y);
	normalNueva = rotarEnX(anguloDeRotacionEnX, normalNueva);
	*/

	//No olvidar normalizar
	return normalize(normalNueva);
}

void main()
{	
	v = vec3(gl_ModelViewMatrix * gl_Vertex);   
	N = normalize(gl_NormalMatrix * calcularNormal(gl_Vertex, gl_Normal));
	vec4 aux = calcularRuido(gl_Vertex, gl_Normal);
	//v = vec3(aux.x, aux.y, aux.z);
	gl_Position = gl_ModelViewProjectionMatrix * aux;
}
