#include "ShaderManager.h"

const string ShaderManager::NOMBRE_ARCHIVO_VERTEX_SHADER_RETORCER = "retorcer.vert";
const string ShaderManager::NOMBRE_ARCHIVO_VERTEX_SHADER_RUIDO = "ruido.vert";
const string ShaderManager::NOMBRE_ARCHIVO_VERTEX_SHADER_DOBLAR = "doblar.vert";
const string ShaderManager::NOMBRE_ARCHIVO_VERTEX_SHADER_ESFERIZAR = "esferizar.vert";

const string ShaderManager::NOMBRE_ARCHIVO_FRAGMENT_SHADER_MATERIAL_SOMBREADO_BRILLANTE = "materisalSombreadoBrillante.frag";
const string ShaderManager::NOMBRE_ARCHIVO_FRAGMENT_SHADER_MATERIAL_SOMBREADO_TEXTURADO = "materialSombreadoTexturado.frag";
const string ShaderManager::NOMBRE_ARCHIVO_FRAGMENT_SHADER_MATERIAL_REFLECTIVO = "materialReflectivo.frag";
const string ShaderManager::NOMBRE_ARCHIVO_FRAGMENT_SHADER_MATERIAL_SOMBREADO_SEMIMATE = "materialSombreadoSemimate.frag";

ShaderManager::ShaderManager(void){
	vertexShaderSeleccionado = -1;
	fragmentShaderSeleccionado = -1;
	programa;
	vertexShaders = new GLuint[4];
	fragmentShaders = new GLuint[4];
	cambioElVertexShader = false;
	cambioElFragmentShader = false;

	inicializarVertexShaders();
	inicializarFragmentShaders();
}


ShaderManager::~ShaderManager(void){
	delete [] vertexShaders;
	delete [] fragmentShaders;
}

void ShaderManager::setVertexShader(VertexShader tipo){
	switch (tipo){
	case RETORCER:
		usarVertexShaderRetorcer();
		break;
	case RUIDO:
		usarVertexShaderRuido();
		break;
	case DOBLAR:
		usarVertexShaderDoblar();
		break;
	case ESFERIZAR:
		usarVertexShaderEsferizar();
		break;
	default:
		break;
	}	
}

void ShaderManager::setFragmenShader(FragmentShader tipo){
	switch (tipo){
	case MATERIAL_SOMBREADO_BRILLANTE:
		usarFragmentShaderMaterialSombreadoBrillante();
		break;
	case MATERIAL_SOMBREADO_TEXTURADO:
		usarFragmentShaderMaterialSombreadoTexturado();
		break;
	case MATERIAL_REFLECTIVO:
		usarFragmentShaderMaterialReflectivo();
		break;
	case MATERIAL_SOMBREADO_SEMIMATE:
		usarFragmentShaderMaterialSombreadoSemimate();
		break;
	default:
		break;
	}	
}

void ShaderManager::usarPrograma(){
	//Si ya han sido seleccionados los shaders...
	if ( (vertexShaderSeleccionado != -1) && (fragmentShaderSeleccionado != -1) )
		//...y si cambi� alguno respecto del anterior...
		if (cambioElVertexShader || cambioElFragmentShader )
			//...y si lo puede linkear, entonces...
			if (programa.link(vertexShaderSeleccionado, fragmentShaderSeleccionado))
				//usa el programa
				programa.use();
}

void ShaderManager::usarVertexShaderRetorcer(){
	cambioElVertexShader = vertexShaderSeleccionado != vertexShaders[RETORCER];
	if (cambioElVertexShader)
		vertexShaderSeleccionado = vertexShaders[RETORCER];
}

void ShaderManager::usarVertexShaderRuido(){
	cambioElVertexShader = vertexShaderSeleccionado != vertexShaders[RUIDO];
	if (cambioElVertexShader)
		vertexShaderSeleccionado = vertexShaders[RUIDO];
}

void ShaderManager::usarVertexShaderDoblar(){
	cambioElVertexShader = vertexShaderSeleccionado != vertexShaders[DOBLAR];
	if (cambioElVertexShader)
		vertexShaderSeleccionado = vertexShaders[DOBLAR];
}

void ShaderManager::usarVertexShaderEsferizar(){
	cambioElVertexShader = vertexShaderSeleccionado != vertexShaders[ESFERIZAR];
	if (cambioElVertexShader)
		vertexShaderSeleccionado = vertexShaders[ESFERIZAR];
}


void ShaderManager::usarFragmentShaderMaterialSombreadoBrillante(){
	cambioElFragmentShader = fragmentShaderSeleccionado != fragmentShaders[MATERIAL_SOMBREADO_BRILLANTE];
	if (cambioElFragmentShader)
		fragmentShaderSeleccionado = fragmentShaders[MATERIAL_SOMBREADO_BRILLANTE];
}

void ShaderManager::usarFragmentShaderMaterialSombreadoTexturado(){
	cambioElFragmentShader = fragmentShaderSeleccionado != fragmentShaders[MATERIAL_SOMBREADO_TEXTURADO];
	if (cambioElFragmentShader)
		fragmentShaderSeleccionado = fragmentShaders[MATERIAL_SOMBREADO_TEXTURADO];
}

void ShaderManager::usarFragmentShaderMaterialReflectivo(){
	cambioElFragmentShader = fragmentShaderSeleccionado != fragmentShaders[MATERIAL_REFLECTIVO];
	if (cambioElFragmentShader)
		fragmentShaderSeleccionado = fragmentShaders[MATERIAL_REFLECTIVO];
}

void ShaderManager::usarFragmentShaderMaterialSombreadoSemimate(){
	cambioElFragmentShader = fragmentShaderSeleccionado != fragmentShaders[MATERIAL_SOMBREADO_SEMIMATE];
	if (cambioElFragmentShader)
		fragmentShaderSeleccionado = fragmentShaders[MATERIAL_SOMBREADO_SEMIMATE];
}


void ShaderManager::inicializarVertexShaders(){	
	GLSLangShader shaderAux;

	if ( shaderAux.compileShaderFromFile( NOMBRE_ARCHIVO_VERTEX_SHADER_RETORCER, VERTEX ) )
		vertexShaders[RETORCER] = shaderAux.getShaderHandle();

	if ( shaderAux.compileShaderFromFile( NOMBRE_ARCHIVO_VERTEX_SHADER_RUIDO, VERTEX ) )
		vertexShaders[RUIDO] = shaderAux.getShaderHandle();
	
	if ( shaderAux.compileShaderFromFile( NOMBRE_ARCHIVO_VERTEX_SHADER_DOBLAR, VERTEX ) )
		vertexShaders[DOBLAR] = shaderAux.getShaderHandle();
	
	if ( shaderAux.compileShaderFromFile( NOMBRE_ARCHIVO_VERTEX_SHADER_ESFERIZAR, VERTEX ) )
		vertexShaders[ESFERIZAR] = shaderAux.getShaderHandle();
}

void ShaderManager::inicializarFragmentShaders(){	
	GLSLangShader shaderAux;

	if ( shaderAux.compileShaderFromFile( NOMBRE_ARCHIVO_FRAGMENT_SHADER_MATERIAL_SOMBREADO_BRILLANTE, FRAGMENT ) )
		fragmentShaders[MATERIAL_SOMBREADO_BRILLANTE] = shaderAux.getShaderHandle();
	
	if ( shaderAux.compileShaderFromFile( NOMBRE_ARCHIVO_FRAGMENT_SHADER_MATERIAL_SOMBREADO_TEXTURADO, FRAGMENT ) )
		fragmentShaders[MATERIAL_SOMBREADO_TEXTURADO] = shaderAux.getShaderHandle();
	
	if ( shaderAux.compileShaderFromFile( NOMBRE_ARCHIVO_FRAGMENT_SHADER_MATERIAL_REFLECTIVO, FRAGMENT ) )
		fragmentShaders[MATERIAL_REFLECTIVO] = shaderAux.getShaderHandle();
	
	if ( shaderAux.compileShaderFromFile( NOMBRE_ARCHIVO_FRAGMENT_SHADER_MATERIAL_SOMBREADO_SEMIMATE, FRAGMENT ) )
		fragmentShaders[MATERIAL_SOMBREADO_SEMIMATE] = shaderAux.getShaderHandle();
}
