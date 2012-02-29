varying vec3 direccionDeReflejo;
varying vec3 normal;
varying vec3 posicion;
uniform vec3 posicionDelOjo;

void main(void){
	posicion = vec3(gl_ModelViewMatrix * gl_Vertex);		//En coordenadas de mundo
	normal = normalize(vec3(gl_NormalMatrix * gl_Normal));	//En coordenadas de mundo
	vec3 posicionSegunEspectador = posicion - posicionDelOjo;	//En coordenadas de mundo, pero centrando el eje en la cámara
	
	direccionDeReflejo = reflect( posicionSegunEspectador, normal);
	direccionDeReflejo = (gl_ModelViewMatrixInverse * vec4(direccionDeReflejo, 0.0)).xyz;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}