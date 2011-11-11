//Fragment shader para tratar la luz principal.
//Tomado de http://www.opengl.org/sdk/docs/tutorials/ClockworkCoders/lighting.php
//La luz se define afuera de esto, pero ac� va c�mo se interpretan y esas cosas
// ��NO!! ponerle main.

varying vec3 N;
varying vec3 v;

uniform int primeraLuz;
uniform int ultimaLuz;


vec4 calcularColorPorLuz(){
	vec3 vN = normalize(N);
	vec4 finalColor = vec4(0.0, 0.0, 0.0, 0.0);
	
	int MAX_LIGHTS = ultimaLuz - primeraLuz + 1;

	for (int i=primeraLuz;i<MAX_LIGHTS+primeraLuz;i++){
		
		vec3 L = normalize(gl_LightSource[i].position.xyz - v); 
		vec3 E = normalize(-v); // we are in Eye Coordinates, so EyePos is (0,0,0) 
		vec3 R = normalize(-reflect(L,vN)); 
   
		//calculate Ambient Term: 
		vec4 Iamb = gl_FrontLightProduct[i].ambient;// * pow(max(dot(R,E),0.0),0.3*gl_FrontMaterial.shininess); 
		//calculate Diffuse Term: 
		vec4 Idiff = gl_FrontLightProduct[i].diffuse * max(dot(vN,L), 0.0);
		Idiff = clamp(Idiff, 0.0, 1.0); 
   
		// calculate Specular Term:
		vec4 Ispec = gl_FrontLightProduct[i].specular * pow(max(dot(R,E),0.0),0.3*gl_FrontMaterial.shininess)*2.0;
		Ispec = clamp(Ispec, 0.0, 1.0); 
   
		finalColor += Iamb + Idiff + Ispec;
		
	}
	
	return finalColor;   
}
