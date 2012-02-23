varying vec2 vTexCoord;
varying vec3 normal;
varying vec3 posicion;

void main(void){
	vTexCoord = gl_MultiTexCoord0.st;
	normal = gl_Normal.xyz;
	posicion = ( gl_ModelViewMatrix * gl_Vertex ).xyz;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}