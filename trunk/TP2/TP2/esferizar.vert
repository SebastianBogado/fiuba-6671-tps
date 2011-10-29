//Vertex shader escala en x e y
varying vec3 N;
varying vec3 v;

void main()
{	
	//Luego esto tiene que ser un Uniform
	vec3 centro = (0.0,0.0,0.0);
	
	v = vec3(gl_ModelViewMatrix * gl_Vertex);       
   N = normalize(gl_NormalMatrix * gl_Normal);
	
	vec3  vertice = gl_Vertex.xyz;
	
	float distancia = 0.0;
	float parcial=0.0;
	
	for( int i=0; i < 3; i++){
		parcial+=pow(vertice[i] -centro[i],2.0 );
	}
	
	distancia = sqrt(parcial);
	
	//if (distancia > 1)
	if(distancia != 0.0)
	vertice +=  0.1/pow(distancia,2.0)* gl_Normal;	
	
	gl_Position = gl_ModelViewProjectionMatrix *vec4(vertice,1.0);
}
