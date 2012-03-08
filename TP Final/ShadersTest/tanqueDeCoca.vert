varying vec3 direccionDeReflejo;
varying vec3 normal;
varying vec3 posicion;

void main(void){
	posicion = vec3(gl_ModelViewMatrix * gl_Vertex);		//En coordenadas de mundo
	normal = normalize(gl_NormalMatrix * gl_Normal);		//En coordenadas de mundo
	
	direccionDeReflejo = reflect(posicion, normal);
	direccionDeReflejo = (gl_ModelViewMatrixInverse * vec4(direccionDeReflejo, 0.0)).xyz;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}