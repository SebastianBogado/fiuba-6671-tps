//Fragment shader básico
uniform sampler2D textura;
varying vec2 vTexCoord;

void main()
{
	gl_FragColor = texture2D(textura, vTexCoord).rgba; 
}