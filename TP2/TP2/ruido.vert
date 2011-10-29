//Vertex shader mnimo
varying vec3 N;
varying vec3 v;


void main()
{	

	vec4 nuevaPos = gl_Vertex;
	
	nuevaPos[0]=gl_Vertex.x * sin(gl_Vertex.z);
	nuevaPos[1]=gl_Vertex.x * sin(gl_Vertex.z);
	
	gl_Position = ftransform();
}
