#pragma once
#include "GLSLProgram.h"

enum VertexShader {
	RETORCER=0,
	RUIDO,
	DOBLAR,
	ESFERIZAR
};

enum FragmentShader{
	MATERIAL_SOMBREADO_BRILLANTE=0,
	MATERIAL_SOMBREADO_TEXTURADO,
	MATERIAL_REFLECTIVO,
	MATERIAL_SOMBREADO_SEMIMATE
};


class ShaderManager{
public:
	//crea todos los shaders de la aplicación
	ShaderManager(void);
	~ShaderManager(void);

	static const int numeroDeVertexShaders;
	static const int numeroDeFragmentShaders;

	void setVertexShader(VertexShader tipo);
	void setFragmenShader(FragmentShader tipo);
	void usarPrograma();

private:
	int vertexShaderSeleccionado;
	int fragmentShaderSeleccionado;
	
	//estas variables controlan si hubo algún cambio entre el shader anterior y el actual, para ahorrar procesamiento
	bool cambioElFragmentShader;
	bool cambioElVertexShader;
	
	GLSLProgram programa;

	void usarVertexShaderRetorcer();
	void usarVertexShaderRuido();
	void usarVertexShaderDoblar();
	void usarVertexShaderEsferizar();

	void usarFragmentShaderMaterialSombreadoBrillante();
	void usarFragmentShaderMaterialSombreadoTexturado();
	void usarFragmentShaderMaterialReflectivo();
	void usarFragmentShaderMaterialSombreadoSemimate();
};

