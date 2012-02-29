varying vec3 normal;
varying vec3 posicion;

void main(void){
	normal = vec3(gl_NormalMatrix*gl_Normal);
	posicion = ( gl_ModelViewMatrix * gl_Vertex ).xyz;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}