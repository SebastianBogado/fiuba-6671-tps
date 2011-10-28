//Vertex shader escala en x e y

void main()
{	
	//Luego esto tiene que ser un Uniform
	vec3 centro = (0.0,0.0,1.0);
	
	
	vec3  vertice = gl_Vertex.xyz;
	
	float distancia = 0.0;
	float parcial=0.0;
	
	for( int i=0; i < 3; i++){
		parcial+=pow(vertice[i] -centro[i],2.0 );
	}
	
	distancia = sqrt(parcial);
	
	//if (distancia > 1)
	if(distancia != 0)
	vertice = vertice * 1.0/distancia;	
	
	gl_Position = gl_ModelViewProjectionMatrix * vertice;
}