//Fragment shader básico
uniform sampler2D textura;
varying vec2 vTexCoord;


vec4 calcularColorPorLuz();

void main(){

	vec4 finalColor = calcularColorPorLuz();
	gl_FragColor = texture2D(textura, vTexCoord).rgba + gl_FrontLightModelProduct.sceneColor + finalColor; 
}