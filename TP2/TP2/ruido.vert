//Vertex shader ruido
//

//TODO : revisar las normales de z negativo. Pueden ser el origen del problema de que se parta en dos las figuras
// que tienen puntos de z<0
//TODO 2 : encontrar una manera de pasarle al shader si un vértice es normal. Por ahora, temo que voy a tener
// que pasarle un array con todos los vértices arista :S
varying vec3 N;
varying vec3 v;
varying vec2 vTexCoord;

struct Onda{
	float longitud;
	float frecuencia;
	float amplitud;
};

//uniform
Onda ondaEnX = Onda(1.9, 2.5, 0.01);
Onda ondaEnY = Onda(1.6, 2.8, 0.02);

uniform float tiempo;

uniform bool esArista;

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
	float t = tiempo;
	float k = sqrt(kx*kx + ky*ky);
	float w = sqrt(wx*wx + wy*wy);
	float A = sqrt(Ax*Ax + Ay*Ay);
	//Fin variables

	
	//suma independientemente de 2 ondas
	diferencia = Ax*sin(kx*r.x-wx*t)+ Ay*sin(ky*r.y-wy*t);

	//una mezcla de senoides de argumento x.y
	diferencia = diferencia + A*sin(k*r.x*r.y-w*t) + 0.5*A*sin(0.9*k*r.x*r.y-1.5*w*t) + A*2.0*sin(1.8*k*r.x*r.y-0.3*w*t);
	

/*  diferencia = Ax*sin(kx*r.x-wx*t); */
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
	//Calcular el ruido en la dirección normal
	float z = calcularRuidoEnDireccionNormal(r);

	//Alinear a la dirección normal
	vec3 nuevaPosicion;
	if  (n.x == 0.0){
		float anguloDeRotacionEnX =  atan(n.z, n.y);
		nuevaPosicion = rotarEnX(anguloDeRotacionEnX, vec3(0.0,0.0,z));
	}
	else{
		float anguloDeRotacionEnY =  atan(n.x, n.z);
		nuevaPosicion = rotarEnY(anguloDeRotacionEnY, vec3(0.0,0.0,z));
	
		float anguloDeRotacionEnZ = atan(n.y, n.x);
		nuevaPosicion = rotarEnZ(anguloDeRotacionEnZ, nuevaPosicion);
	}

	//Trasladarlo al punto que pertenece
	vec4 posicionFinal = vec4(nuevaPosicion, 0.0) + r;

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
	float t = tiempo;
	float k = sqrt(kx*kx + ky*ky);
	float w = sqrt(wx*wx + wy*wy);
	float A = sqrt(Ax*Ax+Ay*Ay);
	//Fin variables


	//normal de las dos senoides independientes
	normalNueva = vec3(-kx*Ax*cos(kx*r.x-wx*t), -ky*Ay*cos(ky*r.y-wy*t), 1.0);
	
	//normal de las senoides de argumento x.y
	normalNueva.x = normalNueva.x - A*k*r.y*sin(k*r.x*r.y-w*t) - 0.45*A*k*r.y*sin(0.9*k*r.x*r.y-1.5*w*t) - 3.6*A*k*r.y*sin(1.8*k*r.x*r.y-0.3*w*t);
	normalNueva.y = normalNueva.y - A*k*r.x*sin(k*r.x*r.y-w*t) - 0.45*A*k*r.x*sin(0.9*k*r.x*r.y-1.5*w*t) - 3.6*A*k*r.x*sin(1.8*k*r.x*r.y-0.3*w*t); 
	
/*
	normalNueva = vec3(-kx*Ax*cos(kx*r.x-wx*t), 0.0, 1.0);
*/
	//Alineación de normalNueva (calculada según (0,0,1)) con n
	if  (n.x == 0.0){
		float anguloDeRotacionEnX =  atan(n.z, n.y);
		normalNueva = rotarEnX(anguloDeRotacionEnX, normalNueva);
	}
	else{
		float anguloDeRotacionEnY =  atan(n.x, n.z);
		normalNueva = rotarEnY(anguloDeRotacionEnY, normalNueva);
	
		float anguloDeRotacionEnZ = atan(n.y, n.x);
		normalNueva = rotarEnZ(anguloDeRotacionEnZ, normalNueva);
	}

	return normalNueva;
}

void main()
{	

	vTexCoord = gl_MultiTexCoord0.xy;
	v = vec3(gl_ModelViewMatrix * gl_Vertex);   
	N = normalize(gl_NormalMatrix * calcularNormal(gl_Vertex, gl_Normal));
	vec4 aux = calcularRuido(gl_Vertex, gl_Normal);
	//v = vec3(aux.x, aux.y, aux.z);
	//if (esArista)
		//gl_Position = gl_ModelViewProjectionMatrix * vec4 (gl_Vertex);

	gl_Position = gl_ModelViewProjectionMatrix * aux;
}
