varying vec2 vTexCoord;

void main(void){
	vTexCoord = gl_MultiTexCoord0.st;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}