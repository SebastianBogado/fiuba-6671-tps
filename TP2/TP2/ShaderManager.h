#pragma once
#include "GLSLProgram.h"
#include "GLSLangShader.h"

enum VertexShader {
	RETORCER,
	RUIDO,
	DOBLAR,
	ESFERIZAR
};

enum FragmentShader{
	MATERIAL_SOMBREADO_BRILLANTE,
	MATERIAL_SOMBREADO_TEXTURADO,
	MATERIAL_REFLECTIVO,
	MATERIAL_SOMBREADO_SEMIMATE
};


class ShaderManager{
public:
	//crea todos los shaders de la aplicación
	ShaderManager(void);
	~ShaderManager(void);
	void setVertexShader(VertexShader tipo);
	void setFragmenShader(FragmentShader tipo);
	void usarPrograma();

private:
	GLuint vertexShaderSeleccionado;
	GLuint fragmentShaderSeleccionado;

	GLuint* vertexShaders;
	GLuint* fragmentShaders;
	
	//estas variables controlan si hubo algún cambio entre el shader anterior y el actual, para ahorra procesamiento
	bool cambioElFragmentShader;
	bool cambioElVertexShader;

	GLSLProgram programa;
	
	//ubicación de los archivos
	static const string NOMBRE_ARCHIVO_VERTEX_SHADER_RETORCER;
	static const string NOMBRE_ARCHIVO_VERTEX_SHADER_RUIDO;
	static const string NOMBRE_ARCHIVO_VERTEX_SHADER_DOBLAR;
	static const string NOMBRE_ARCHIVO_VERTEX_SHADER_ESFERIZAR;

	static const string NOMBRE_ARCHIVO_FRAGMENT_SHADER_MATERIAL_SOMBREADO_BRILLANTE;
	static const string NOMBRE_ARCHIVO_FRAGMENT_SHADER_MATERIAL_SOMBREADO_TEXTURADO;
	static const string NOMBRE_ARCHIVO_FRAGMENT_SHADER_MATERIAL_REFLECTIVO;
	static const string NOMBRE_ARCHIVO_FRAGMENT_SHADER_MATERIAL_SOMBREADO_SEMIMATE;

	void inicializarVertexShaders();
	void inicializarFragmentShaders();

	void usarVertexShaderRetorcer();
	void usarVertexShaderRuido();
	void usarVertexShaderDoblar();
	void usarVertexShaderEsferizar();

	void usarFragmentShaderMaterialSombreadoBrillante();
	void usarFragmentShaderMaterialSombreadoTexturado();
	void usarFragmentShaderMaterialReflectivo();
	void usarFragmentShaderMaterialSombreadoSemimate();
};

