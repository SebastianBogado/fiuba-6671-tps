varying vec2 vTexCoord;
varying vec3 normal;
varying vec3 posicion;

//agregada por Migue
uniform float desplazamientoDeCinta;

void main(void){
	float texS = gl_MultiTexCoord0.s + desplazamientoDeCinta;
	if (texS > 1.0)
		texS -= 1.0;
	vTexCoord = vec2(texS, gl_MultiTexCoord0.t);
	normal = gl_NormalMatrix * gl_Normal;
	posicion = ( gl_ModelViewMatrix * gl_Vertex ).xyz;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}