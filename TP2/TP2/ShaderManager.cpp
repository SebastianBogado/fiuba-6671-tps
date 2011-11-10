#include "ShaderManager.h"

const int ShaderManager::numeroDeVertexShaders = ESFERIZAR - RETORCER + 1;
const int ShaderManager::numeroDeFragmentShaders = MATERIAL_SOMBREADO_SEMIMATE - MATERIAL_SOMBREADO_BRILLANTE + 1;
const int ShaderManager::numeroDeLuces = LUZ_SECUNDARIA - LUZ_PRINCIPAL + 1;

ShaderManager::ShaderManager(void){
	vertexShaderSeleccionado = -1;
	fragmentShaderSeleccionado = -1;
	fragmentShaderLuzSeleccionado = -1;
	cambioElVertexShader = true;
	cambioElFragmentShader = true;
	cambioLaLuz = true;

	programa;

	shadersTriviales;
	if (!shadersTriviales.inicializarBasico())
		cout << shadersTriviales.log().c_str() << endl;
		
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

void ShaderManager::setShaderLuz(ShaderLuz tipo){
	switch (tipo){
	case LUZ_PRINCIPAL:
		usarShaderLuzPrincipal();
		break;
	case LUZ_SECUNDARIA:
		usarShaderLuzSecundaria();
		break;
	default:
		break;
	}	
}
void ShaderManager::usar(){
	if (programa.isLinked())
		programa.usar();
	else if (programa.link())
		programa.usar();
}

void ShaderManager::cerrar(){
	programa.cerrar();
	//puede ser necesario esto
	//shadersTriviales.usar();
}


void ShaderManager::usarVertexShaderRetorcer(){
	cambioElVertexShader = vertexShaderSeleccionado != RETORCER;
	if (cambioElVertexShader){
		vertexShaderSeleccionado = RETORCER;
		if ( (programa.compileShaderFromFile(vertexShaderSeleccionado, VERTEX)))
			cout << "Vertex Shader retorcer.vert: compilacion exitosa" << endl;
	}
}

void ShaderManager::usarVertexShaderRuido(){
	cambioElVertexShader = vertexShaderSeleccionado != RUIDO;
	if (cambioElVertexShader){
		vertexShaderSeleccionado = RUIDO;
		if ( (programa.compileShaderFromFile(vertexShaderSeleccionado, VERTEX)))
			cout << "Vertex Shader ruido.vert: compilación exitosa" << endl;
	}
}

void ShaderManager::usarVertexShaderDoblar(){
	cambioElVertexShader = vertexShaderSeleccionado != DOBLAR;
	if (cambioElVertexShader){
		vertexShaderSeleccionado = DOBLAR;
		if ( (programa.compileShaderFromFile(vertexShaderSeleccionado, VERTEX)))
			cout << "Vertex Shader doblar.vert: compilación exitosa" << endl;
	}
}

void ShaderManager::usarVertexShaderEsferizar(){
	cambioElVertexShader = vertexShaderSeleccionado != ESFERIZAR;
	if (cambioElVertexShader){
		vertexShaderSeleccionado = ESFERIZAR;
		if ( (programa.compileShaderFromFile(vertexShaderSeleccionado, VERTEX)))
			cout << "Vertex Shader esferizar.vert: compilación exitosa" << endl;
	}
}


void ShaderManager::usarFragmentShaderMaterialSombreadoBrillante(){
	cambioElFragmentShader = fragmentShaderSeleccionado != MATERIAL_SOMBREADO_BRILLANTE;
	if (cambioElFragmentShader){
		fragmentShaderSeleccionado = MATERIAL_SOMBREADO_BRILLANTE;
		if ( (programa.compileShaderFromFile(fragmentShaderSeleccionado, FRAGMENT)))
			cout << "Fragment Shader materialSombreadoBrillante.frag: compilación exitosa" << endl;
	}
}

void ShaderManager::usarFragmentShaderMaterialSombreadoTexturado(){
	cambioElFragmentShader = fragmentShaderSeleccionado != MATERIAL_SOMBREADO_TEXTURADO;
	if (cambioElFragmentShader){
		fragmentShaderSeleccionado = MATERIAL_SOMBREADO_TEXTURADO;
		if ( (programa.compileShaderFromFile(fragmentShaderSeleccionado, FRAGMENT)))
			cout << "Fragment Shader materialSombreadoTexturadofrag: compilación exitosa" << endl;
	}
}

void ShaderManager::usarFragmentShaderMaterialReflectivo(){
	cambioElFragmentShader = fragmentShaderSeleccionado != MATERIAL_REFLECTIVO;
	if (cambioElFragmentShader){
		fragmentShaderSeleccionado = MATERIAL_REFLECTIVO;
		if ( (programa.compileShaderFromFile(fragmentShaderSeleccionado, FRAGMENT)))
			cout << "Fragment Shader materialReflectivo.frag: compilación exitosa" << endl;
	}
}

void ShaderManager::usarFragmentShaderMaterialSombreadoSemimate(){
	cambioElFragmentShader = fragmentShaderSeleccionado != MATERIAL_SOMBREADO_SEMIMATE;
	if (cambioElFragmentShader){
		fragmentShaderSeleccionado = MATERIAL_SOMBREADO_SEMIMATE;
		if ( (programa.compileShaderFromFile(fragmentShaderSeleccionado, FRAGMENT)))
			cout << "Fragment Shader materialSombreadoSemimate.frag: compilación exitosa" << endl;
	}
}

void ShaderManager::usarShaderLuzPrincipal(){
	cambioLaLuz = fragmentShaderLuzSeleccionado != LUZ_PRINCIPAL;
	if (cambioLaLuz){
		fragmentShaderLuzSeleccionado = LUZ_PRINCIPAL;
		if ( (programa.compileShaderFromFile(fragmentShaderLuzSeleccionado, FRAGMENT, true)))
			cout << "Fragment Shader Luz luzPrincipal.vert: compilación exitosa" << endl;
	}
}

void ShaderManager::usarShaderLuzSecundaria(){
	cambioLaLuz = fragmentShaderLuzSeleccionado != LUZ_SECUNDARIA;
	if (cambioLaLuz){
		fragmentShaderLuzSeleccionado = LUZ_SECUNDARIA;
		if ( (programa.compileShaderFromFile(fragmentShaderLuzSeleccionado, FRAGMENT, true)))
			cout << "Fragment Shader Luz luzSecundaria.vert: compilación exitosa" << endl;
	}
}

void ShaderManager::bindAttribLocation( GLuint location, const char * name){
	programa.bindAttribLocation(location, name);
}

void ShaderManager::bindFragDataLocation( GLuint location, const char * name ){
	programa.bindFragDataLocation(location, name);
}

void ShaderManager::setUniform(const char *name, const vec3 & v){
	programa.setUniform(name, v);
}

void ShaderManager::setUniform(const char *name, float x, float y, float z){
	programa.setUniform(name, x, y, z);
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