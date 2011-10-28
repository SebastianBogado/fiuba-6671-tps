#include "ShaderManager.h"

const string ShaderManager::NOMBRE_ARCHIVO_VERTEX_SHADER_RETORCER = "retorcer.vert";
const string ShaderManager::NOMBRE_ARCHIVO_VERTEX_SHADER_RUIDO = "ruido.vert";
const string ShaderManager::NOMBRE_ARCHIVO_VERTEX_SHADER_DOBLAR = "doblar.vert";
const string ShaderManager::NOMBRE_ARCHIVO_VERTEX_SHADER_ESFERIZAR = "esferizar.vert";

const string ShaderManager::NOMBRE_ARCHIVO_FRAGMENT_SHADER_MATERIAL_SOMBREADO_BRILLANTE = "materialSombreadoBrillante.frag";
const string ShaderManager::NOMBRE_ARCHIVO_FRAGMENT_SHADER_MATERIAL_SOMBREADO_TEXTURADO = "materialSombreadoTexturado.frag";
const string ShaderManager::NOMBRE_ARCHIVO_FRAGMENT_SHADER_MATERIAL_REFLECTIVO = "materialReflectivo.frag";
const string ShaderManager::NOMBRE_ARCHIVO_FRAGMENT_SHADER_MATERIAL_SOMBREADO_SEMIMATE = "materialSombreadoSemimate.frag";

ShaderManager::ShaderManager(void){
	vertexShaderSeleccionado;
	fragmentShaderSeleccionado;
	programa;
	vertexShaders = new GLSLangShader[4];
	fragmentShaders = new GLSLangShader[4];
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
	if ( (vertexShaderSeleccionado.getShaderHandle() != 0) && (fragmentShaderSeleccionado.getShaderHandle() != 0) )
		//...y si cambió alguno respecto del anterior...
		if (cambioElVertexShader || cambioElFragmentShader )
			//...y si lo puede linkear, entonces...
			if (programa.link(&vertexShaderSeleccionado, &fragmentShaderSeleccionado))
				//usa el programa
				programa.use();
}

void ShaderManager::usarVertexShaderRetorcer(){
	cambioElVertexShader = vertexShaderSeleccionado.getShaderHandle() != vertexShaders[RETORCER].getShaderHandle();
	if (cambioElVertexShader)
		vertexShaderSeleccionado = vertexShaders[RETORCER];
	if ( (!glIsShader(vertexShaderSeleccionado.getShaderHandle())))
		cout << "Se pierde la info del vertex shader en usarVertexShader" << endl;
}

void ShaderManager::usarVertexShaderRuido(){
	cambioElVertexShader = vertexShaderSeleccionado.getShaderHandle() != vertexShaders[RUIDO].getShaderHandle();
	if (cambioElVertexShader)
		vertexShaderSeleccionado = vertexShaders[RUIDO];
	if ( (!glIsShader(vertexShaderSeleccionado.getShaderHandle())))
		cout << "Se pierde la info del vertex shader en usarVertexShader" << endl;
}

void ShaderManager::usarVertexShaderDoblar(){
	cambioElVertexShader = vertexShaderSeleccionado.getShaderHandle() != vertexShaders[DOBLAR].getShaderHandle();
	if (cambioElVertexShader)
		vertexShaderSeleccionado = vertexShaders[DOBLAR];
	if ( (!glIsShader(vertexShaderSeleccionado.getShaderHandle())))
		cout << "Se pierde la info del vertex shader en usarVertexShader" << endl;
}

void ShaderManager::usarVertexShaderEsferizar(){
	cambioElVertexShader = vertexShaderSeleccionado.getShaderHandle() != vertexShaders[ESFERIZAR].getShaderHandle();
	if (cambioElVertexShader)
		vertexShaderSeleccionado = vertexShaders[ESFERIZAR];
	if ( (!glIsShader(vertexShaderSeleccionado.getShaderHandle())))
		cout << "Se pierde la info del vertex shader en usarVertexShader" << endl;
}


void ShaderManager::usarFragmentShaderMaterialSombreadoBrillante(){
	cambioElFragmentShader = fragmentShaderSeleccionado.getShaderHandle() != fragmentShaders[MATERIAL_SOMBREADO_BRILLANTE].getShaderHandle();
	if (cambioElFragmentShader)
		fragmentShaderSeleccionado = fragmentShaders[MATERIAL_SOMBREADO_BRILLANTE];
	if ( (!glIsShader(fragmentShaderSeleccionado.getShaderHandle())))
		cout << "Se pierde la info del vertex shader en usarFragmentShader" << endl;
}

void ShaderManager::usarFragmentShaderMaterialSombreadoTexturado(){
	cambioElFragmentShader = fragmentShaderSeleccionado.getShaderHandle() != fragmentShaders[MATERIAL_SOMBREADO_TEXTURADO].getShaderHandle();
	if (cambioElFragmentShader)
		fragmentShaderSeleccionado = fragmentShaders[MATERIAL_SOMBREADO_TEXTURADO];
	if ( (!glIsShader(fragmentShaderSeleccionado.getShaderHandle())))
		cout << "Se pierde la info del vertex shader en usarFragmentShader" << endl;
}

void ShaderManager::usarFragmentShaderMaterialReflectivo(){
	cambioElFragmentShader = fragmentShaderSeleccionado.getShaderHandle() != fragmentShaders[MATERIAL_REFLECTIVO].getShaderHandle();
	if (cambioElFragmentShader)
		fragmentShaderSeleccionado = fragmentShaders[MATERIAL_REFLECTIVO];
	if ( (!glIsShader(fragmentShaderSeleccionado.getShaderHandle())))
		cout << "Se pierde la info del vertex shader en usarFragmentShader" << endl;
}

void ShaderManager::usarFragmentShaderMaterialSombreadoSemimate(){
	cambioElFragmentShader = fragmentShaderSeleccionado.getShaderHandle() != fragmentShaders[MATERIAL_SOMBREADO_SEMIMATE].getShaderHandle();
	if (cambioElFragmentShader)
		fragmentShaderSeleccionado = fragmentShaders[MATERIAL_SOMBREADO_SEMIMATE];
	if ( (!glIsShader(fragmentShaderSeleccionado.getShaderHandle())))
		cout << "Se pierde la info del vertex shader en usarFragmentShader" << endl;
}


void ShaderManager::inicializarVertexShaders(){	

	if ( vertexShaders[RETORCER].compileShaderFromFile( NOMBRE_ARCHIVO_VERTEX_SHADER_RETORCER, VERTEX ) )
		cout << "Se compiló bien el de retorcer" << endl;

	if ( vertexShaders[RUIDO].compileShaderFromFile( NOMBRE_ARCHIVO_VERTEX_SHADER_RUIDO, VERTEX ) )
		cout << "Se compiló bien el de ruido" << endl;
		
	if ( vertexShaders[DOBLAR] .compileShaderFromFile( NOMBRE_ARCHIVO_VERTEX_SHADER_DOBLAR, VERTEX ) )
		cout << "Se compiló bien el de doblar" << endl;
		
	if ( vertexShaders[ESFERIZAR].compileShaderFromFile( NOMBRE_ARCHIVO_VERTEX_SHADER_ESFERIZAR, VERTEX ) )
		cout << "Se compiló bien el de esferizar" << endl;
	if ( fragmentShaders[MATERIAL_SOMBREADO_BRILLANTE].compileShaderFromFile( NOMBRE_ARCHIVO_FRAGMENT_SHADER_MATERIAL_SOMBREADO_BRILLANTE, FRAGMENT ) )
		cout << "Se compiló bien el de material sombreado brillante" << endl;
	
	if ( fragmentShaders[MATERIAL_SOMBREADO_TEXTURADO].compileShaderFromFile( NOMBRE_ARCHIVO_FRAGMENT_SHADER_MATERIAL_SOMBREADO_TEXTURADO, FRAGMENT ) )
		cout << "Se compiló bien el de material sombreado texturado" << endl;
	
	if ( fragmentShaders[MATERIAL_REFLECTIVO].compileShaderFromFile( NOMBRE_ARCHIVO_FRAGMENT_SHADER_MATERIAL_REFLECTIVO, FRAGMENT ) )
		 cout << "Se compiló bien el de material reflectivo" << endl;
	
	if ( fragmentShaders[MATERIAL_SOMBREADO_SEMIMATE].compileShaderFromFile( NOMBRE_ARCHIVO_FRAGMENT_SHADER_MATERIAL_SOMBREADO_SEMIMATE, FRAGMENT ) )
		 cout << "Se compiló bien el de material sombreado semimate" << endl;
	if (programa.link(&vertexShaders[RETORCER], &fragmentShaders[MATERIAL_SOMBREADO_BRILLANTE]))
				//usa el programa
				programa.use();
}

void ShaderManager::inicializarFragmentShaders(){	/*

	if ( fragmentShaders[MATERIAL_SOMBREADO_BRILLANTE].compileShaderFromFile( NOMBRE_ARCHIVO_FRAGMENT_SHADER_MATERIAL_SOMBREADO_BRILLANTE, FRAGMENT ) )
		cout << "Se compiló bien el de material sombreado brillante" << endl;
	
	if ( fragmentShaders[MATERIAL_SOMBREADO_TEXTURADO].compileShaderFromFile( NOMBRE_ARCHIVO_FRAGMENT_SHADER_MATERIAL_SOMBREADO_TEXTURADO, FRAGMENT ) )
		cout << "Se compiló bien el de material sombreado texturado" << endl;
	
	if ( fragmentShaders[MATERIAL_REFLECTIVO].compileShaderFromFile( NOMBRE_ARCHIVO_FRAGMENT_SHADER_MATERIAL_REFLECTIVO, FRAGMENT ) )
		 cout << "Se compiló bien el de material reflectivo" << endl;
	
	if ( fragmentShaders[MATERIAL_SOMBREADO_SEMIMATE].compileShaderFromFile( NOMBRE_ARCHIVO_FRAGMENT_SHADER_MATERIAL_SOMBREADO_SEMIMATE, FRAGMENT ) )
		 cout << "Se compiló bien el de material sombreado semimate" << endl;
*/
}
