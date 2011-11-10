varying vec3 N;
varying vec3 v;


vec4 calcularColorPorLuz();

void main (void){
	vec4 finalColor = calcularColorPorLuz(); 
   
   gl_FragColor = gl_FrontLightModelProduct.sceneColor + finalColor;
   }
