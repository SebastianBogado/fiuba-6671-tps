varying vec3 N; //normal
varying vec3 v; //vértice en coordenadas de vista
varying vec2 vTexCoord;

uniform vec3 posCamara;
uniform sampler2D texCajaDeCielo;

float PI = 3.1415926535897;


vec4 calcularColorPorLuz();

vec4 calcularReflexion(){

	vec3 vectorInc = v - posCamara;
	vectorInc = normalize (vectorInc);

	vec3 reflexion = reflect ( vectorInc, N);

	float coseno = dot(vectorInc , N);
	float seno = sqrt(1.0 - coseno * coseno);

	vec4 coordTex = texture2D(texCajaDeCielo, vTexCoord).rgba;

	return seno*coordTex;


}

vec2 calcularCoordTex(){

	vec3 vectorInc = v - posCamara;
	//vectorInc = normalize (vectorInc);

	vec3 reflexion = reflect ( vectorInc, N);

	reflexion = normalize (reflexion);

	float phi = acos(reflexion.z);

	float sinPhi = sin(phi);
	
	float acosAngulo,theta;

	if ( sinPhi > 0.0) {
			acosAngulo = acos( reflexion.x / sinPhi );
	}else{
			acosAngulo = 0.0;
	} 

	if (reflexion.y >=0.0)
		theta = acosAngulo;
	else 
		theta = 2.0*PI - acosAngulo;

	return vec2(theta/(2.0*PI),phi/PI);
}

void main (void){
	vec4 finalColor = calcularColorPorLuz();
	vec2 coordTex =calcularCoordTex();
	gl_FragColor = mix (gl_FrontLightModelProduct.sceneColor + finalColor, texture2D(texCajaDeCielo, coordTex).rgba, 0.5);
   //gl_FragColor = 0.7*gl_FrontLightModelProduct.sceneColor + 0.7*finalColor + texture2D(texCajaDeCielo, coordTex).rgba; 
}
