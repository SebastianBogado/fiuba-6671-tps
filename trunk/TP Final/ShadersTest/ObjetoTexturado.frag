uniform sampler2D textura;
uniform sampler2D texturaPared;
uniform bool esPiso;
uniform bool esPared;

varying vec2 vTexCoord;
varying vec3 normal;



void main(void)
{
	vec4 color;// =  texture2D(textura, vTexCoord);

//	if (esPiso == true)
		color = texture2D(textura, vTexCoord);
	




	gl_FragColor = vec4(color);

}