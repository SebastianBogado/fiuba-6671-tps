//Estos tres vectores en coordenadas modelView
varying vec3 normal;
varying vec3 posicion;
varying vec3 posicionDeLaLuz;
varying vec3 direccionDeLaLuz;

uniform vec3 luzposicion;
uniform vec3 luzdireccion;

void main(void){
	normal = vec3(gl_NormalMatrix*gl_Normal);
	posicion = ( gl_ModelViewMatrix * gl_Vertex ).xyz;
	posicionDeLaLuz = luzposicion;
	direccionDeLaLuz = normalize( luzdireccion );
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}