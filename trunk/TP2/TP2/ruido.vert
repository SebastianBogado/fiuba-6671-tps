//Vertex shader ruido
//
varying vec3 N;
varying vec3 v;
varying vec2 vTexCoord;

struct Onda{
	float longitud;
	float frecuencia;
	float amplitud;
};



uniform float tiempo;

//Parámetros para forzar nodos en las aristas
//TODO : si hay tiempo, considerar manejar todo con VAOs
uniform float n;
uniform Onda ondaEnX;
uniform Onda ondaEnY;
uniform Onda ondaEnZ;

const float DPI = 6.283185307;

float calcularRuidoEnDireccionNormal(vec4 r){
	float diferencia;

	//Variables que ayudan a la notacion
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
	//Fin variables

	diferencia = Ax*sin(kx*r.x-wx*t)+ Ay*sin(ky*r.y-wy*t) + Az*sin(kz*r.z-wz*t);;
	return diferencia;
}

vec3 rotarEnX(float angulo, vec3 posicion){
	mat3 rotadoraEnX = mat3(1.0,		 0.0,		  0.0,
							0.0, cos(angulo),-sin(angulo),
							0.0, sin(angulo), cos(angulo) );
	return rotadoraEnX*posicion;
}

vec3 rotarEnY(float angulo, vec3 posicion){
	mat3 rotadoraEnY = mat3( cos(angulo),  0.0, sin(angulo),
									 0.0,  1.0,			0.0,
							-sin(angulo),  0.0, cos(angulo));
	return rotadoraEnY*posicion;
}

vec3 rotarEnZ(float angulo, vec3 posicion){
	mat3 rotadoraEnZ = mat3(cos(angulo), -sin(angulo), 0.0,
							sin(angulo),  cos(angulo), 0.0,
									0.0,		  0.0, 1.0);
	return rotadoraEnZ*posicion;
}

vec4 calcularRuido(vec4 r, vec3 n){
	vec4 posicionFinal = r;
	posicionFinal.x += calcularRuidoEnDireccionNormal(r);
	posicionFinal.y += calcularRuidoEnDireccionNormal(r);
	posicionFinal.z += calcularRuidoEnDireccionNormal(r);
	
	//Fin
	return posicionFinal;
}

vec3 calcularNormal(vec4 r, vec3 n){
	vec3 normalNueva;
	
	//Variables que ayudan a la notacion
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
	//Fin variables

	normalNueva = vec3(-kx*Ax*cos(kx*r.x-wx*t), -ky*Ay*cos(ky*r.y-wy*t), -kz*Az*cos(kz*r.z-wz*t));
	return normalNueva;
}

void main()
{	
	vTexCoord = gl_MultiTexCoord0.xy;
	vec4 aux = calcularRuido(gl_Vertex, gl_Normal);
	v = vec3(gl_ModelViewMatrix * aux);   
	N = normalize(gl_NormalMatrix * calcularNormal(gl_Vertex, gl_Normal));
	gl_Position = gl_ModelViewProjectionMatrix * aux;
}

