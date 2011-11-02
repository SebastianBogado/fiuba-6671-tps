//Vertex shader escala en x e y
varying vec3 N;
varying vec3 v;
varying vec2 vTexCoord;
uniform float tiempo;

void main()
{	

	vTexCoord = gl_MultiTexCoord0.xy;

	//Luego esto tiene que ser un Uniform
	vec3 centro = vec3(0.0,0.0,0.5);
	
	v = vec3(gl_ModelViewMatrix * gl_Vertex);       
   
	
	vec3  vertice = gl_Vertex.xyz;
	
	float distancia = 0.0;
	float parcial=0.0;
	vec3 vectorDir = vertice - centro;
	for( int i=0; i < 3; i++){
		parcial+=pow(vertice[i] -centro[i],2.0 );
	}
	
	distancia = sqrt(parcial);
	

	float amplitud = (sin(tiempo*2.0)+1.0)/2.0;


	//if (distancia > 1)
	if(distancia != 0.0)
	vertice +=  amplitud*0.1/pow(distancia,2.0)*normalize( vectorDir );	
	
	N = normalize(gl_NormalMatrix * gl_Normal);
	//N= normalize(vectorDir);

	gl_Position = gl_ModelViewProjectionMatrix *vec4(vertice,1.0);
}
