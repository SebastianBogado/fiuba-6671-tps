varying vec2 vTexCoord;
varying vec3 normal;

void main(void){

	vTexCoord = vec2(gl_MultiTexCoord0.s, gl_MultiTexCoord0.t);
	normal = gl_NormalMatrix * gl_Normal;
	//posicion = ( gl_ModelViewMatrix * gl_Vertex ).xyz;

	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	//gl_Position = vec4 (1.0,0.0,0.0,1.0);

}