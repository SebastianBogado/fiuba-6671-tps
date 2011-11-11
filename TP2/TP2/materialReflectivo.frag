varying vec3 N; //normal
varying vec3 v; //vértice en coordenadas de vista

vec4 calcularColorPorLuz();

void main (void){
	vec4 finalColor = calcularColorPorLuz();
   gl_FragColor = gl_FrontLightModelProduct.sceneColor + finalColor; 
}
