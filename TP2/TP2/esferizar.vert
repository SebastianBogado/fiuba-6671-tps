//Vertex shader 
varying vec3 N;
varying vec3 v;
varying vec2 vTexCoord;
uniform float tiempo;
uniform vec3 centro;

void main()
{	
	vTexCoord = gl_MultiTexCoord0.xy;
	v = vec3(gl_ModelViewMatrix * gl_Vertex);       

	float parcial=0.0;
	float x = gl_Vertex.x;
	float y = gl_Vertex.y;
	float z = gl_Vertex.z;

	vec3 vectorDir = gl_Vertex.xyz-centro;

	for( int i=0; i < 3; i++){
		parcial+= vectorDir[i] * vectorDir[i];
	}
	
	float distancia = sqrt(parcial);
	

	float amplitud = 0.1*(sin(tiempo*2.0)+1.0)/2.0;


	//if (distancia > 1)
	vec3 vertice;
	if(distancia != 0.0)
		vertice = gl_Vertex.xyz + amplitud/pow(distancia,2.0)*normalize( vectorDir );	
	else
		vertice = gl_Vertex.xyz;
	N = normalize(gl_NormalMatrix * gl_Normal);
	//N= normalize(vectorDir);

	gl_Position = gl_ModelViewProjectionMatrix *vec4(vertice,1.0);
}
