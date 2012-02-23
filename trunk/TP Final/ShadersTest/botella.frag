uniform sampler2D etiquetaText, tapaText;
uniform float porcentajeDeLiquido;
uniform bool tieneEtiqueta;
uniform bool tieneTapa;

varying vec2 vTexCoord;

void main (void){
	vec4 plastico = vec4(0.9, 0.9, 0.9, 0.2);
	vec4 liquido = vec4(0.1719, 0.0, 0.0, 0.95);
	vec4 etiqueta =  texture2D(etiquetaText, vTexCoord);
	vec4 tapa =  texture2D(tapaText, vTexCoord);
	if (vTexCoord.t > porcentajeDeLiquido)
		liquido.a = 0.0;
	vec4 color = mix(plastico, liquido, liquido.a);
	
	if ((tieneEtiqueta) && (etiqueta.a != 0.0))
		color = etiqueta;
	
	if ((tieneTapa) && (tapa.a != 0.0))
		color = tapa;
		
	gl_FragColor = color;
}