varying vec3 normal;
varying vec3 posicion;
varying vec2 vTexCoord;


void main(void){
	vTexCoord = gl_MultiTexCoord0.st;
	normal = gl_NormalMatrix * gl_Normal;
	posicion = ( gl_ModelViewMatrix * gl_Vertex ).xyz;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}	