//Fragment shader básico

varying vec3 N; //normal
varying vec3 v; //vértice en coordenadas de vista


uniform sampler2D textura;
varying vec2 vTexCoord;


vec4 calcularColorPorLuz();

void main(){

	vec4 finalColor = calcularColorPorLuz();
	gl_FragColor = texture2D(textura, vTexCoord).rgba + 0.5*gl_FrontLightModelProduct.sceneColor + 0.5*finalColor; 
	//gl_FragColor = vec4(1.0,0.0,0.0,0.0);
}