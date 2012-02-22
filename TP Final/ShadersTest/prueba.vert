varying vec4 vColor;

void main(void){
	vColor = vec4(0.9, 0.9, 0.9, 0.3);
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}