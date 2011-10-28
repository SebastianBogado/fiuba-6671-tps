#include "ShaderManager.h"

const int ShaderManager::numeroDeVertexShaders = ESFERIZAR - RETORCER + 1;
const int ShaderManager::numeroDeFragmentShaders = MATERIAL_SOMBREADO_SEMIMATE - MATERIAL_SOMBREADO_BRILLANTE + 1;

ShaderManager::ShaderManager(void){
	vertexShaderSeleccionado = -1;
	fragmentShaderSeleccionado = -1;
	programa;
	cambioElVertexShader = true;
	cambioElFragmentShader = true;
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

void ShaderManager::usar(){
	//Si ya han sido seleccionados los shaders...
	if ( (vertexShaderSeleccionado != -1) && (fragmentShaderSeleccionado != -1) )
		//...y si cambió alguno respecto del anterior, renueva el programa...
		if (cambioElVertexShader || cambioElFragmentShader ){
			programa.renovar();
			//...y si puede compilar los nuevos shaders...
			if ( (programa.compileShaderFromFile(vertexShaderSeleccionado, VERTEX)) &&
				 (programa.compileShaderFromFile(fragmentShaderSeleccionado, FRAGMENT)) )
				//...y si lo puede linkear, entonces...
				if (programa.link())
					//usa el programa
					programa.usar();
		}
}

void ShaderManager::usarVertexShaderRetorcer(){
	cambioElVertexShader = vertexShaderSeleccionado != RETORCER;
	if (cambioElVertexShader)
		vertexShaderSeleccionado = RETORCER;
}

void ShaderManager::usarVertexShaderRuido(){
	cambioElVertexShader = vertexShaderSeleccionado != RUIDO;
	if (cambioElVertexShader)
		vertexShaderSeleccionado = RUIDO;
}

void ShaderManager::usarVertexShaderDoblar(){
	cambioElVertexShader = vertexShaderSeleccionado != DOBLAR;
	if (cambioElVertexShader)
		vertexShaderSeleccionado = DOBLAR;
}

void ShaderManager::usarVertexShaderEsferizar(){
	cambioElVertexShader = vertexShaderSeleccionado != ESFERIZAR;
	if (cambioElVertexShader)
		vertexShaderSeleccionado = ESFERIZAR;
}


void ShaderManager::usarFragmentShaderMaterialSombreadoBrillante(){
	cambioElFragmentShader = fragmentShaderSeleccionado != MATERIAL_SOMBREADO_BRILLANTE;
	if (cambioElFragmentShader)
		fragmentShaderSeleccionado = MATERIAL_SOMBREADO_BRILLANTE;
}

void ShaderManager::usarFragmentShaderMaterialSombreadoTexturado(){
	cambioElFragmentShader = fragmentShaderSeleccionado != MATERIAL_SOMBREADO_TEXTURADO;
	if (cambioElFragmentShader)
		fragmentShaderSeleccionado = MATERIAL_SOMBREADO_TEXTURADO;
}

void ShaderManager::usarFragmentShaderMaterialReflectivo(){
	cambioElFragmentShader = fragmentShaderSeleccionado != MATERIAL_REFLECTIVO;
	if (cambioElFragmentShader)
		fragmentShaderSeleccionado = MATERIAL_REFLECTIVO;
}

void ShaderManager::usarFragmentShaderMaterialSombreadoSemimate(){
	cambioElFragmentShader = fragmentShaderSeleccionado != MATERIAL_SOMBREADO_SEMIMATE;
	if (cambioElFragmentShader)
		fragmentShaderSeleccionado = MATERIAL_SOMBREADO_SEMIMATE;
}

void ShaderManager::bindAttribLocation( GLuint location, const char * name){
	programa.bindAttribLocation(location, name);
}

void ShaderManager::bindFragDataLocation( GLuint location, const char * name ){
	programa.bindFragDataLocation(location, name);
}

void ShaderManager::setUniform(const char *name,float x,float y, float z){
	programa.setUniform(name, x, y, z);
}

void ShaderManager::setUniform(const char *name, const vec3 & v){
	programa.setUniform(name, v);
}

void ShaderManager::setUniform(const char *name, const vec4 & v){
	programa.setUniform(name, v);
}

void ShaderManager::setUniform(const char *name, const mat4 & m){
	programa.setUniform(name, m);
}

void ShaderManager::setUniform(const char *name, const mat3 & m){
	programa.setUniform(name, m);
}

void ShaderManager::setUniform(const char *name, float val ){
	programa.setUniform(name, val);
}

void ShaderManager::setUniform(const char *name, int val ){
	programa.setUniform(name, val);
}

void ShaderManager::setUniform(const char *name, bool val ){
	programa.setUniform(name, val);
}

void ShaderManager::printActiveUniforms(){
	programa.printActiveUniforms();
}

void ShaderManager::printActiveAttribs(){
	programa.printActiveAttribs();
}