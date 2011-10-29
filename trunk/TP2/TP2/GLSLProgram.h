//Clase inspirada en la homónima de "OpenGl 4.0 Shading Language Cookbook"
//Autor: David Wolff

#pragma once

#include "InterfazGLSLProgram.h"
#include <fstream>
#include <iostream>
using namespace std;

enum GLSLShaderType {
	VERTEX, 
	FRAGMENT, 
	GEOMETRY,
	TESS_CONTROL,
	TESS_EVALUATION
};


class GLSLProgram : public InterfazGLSLProgram{
private:
	int programHandle;
	GLuint vertexShaderActual;
	GLuint fragmentShaderActual;
	GLuint luzShaderActual;
	bool linked;
	string logString;
	
	bool fileExists( const string & fileName );
	//Devuelve una cadena con todo el contenido del archivo
	char* cargarArchivo(string fileName);

	int getUniformLocation(const char * name );

	//ubicación de los archivos
	static const string ARCHIVOS_VERTEX_SHADERS[];
	static const string NOMBRE_ARCHIVO_VERTEX_SHADER_RETORCER;
	static const string NOMBRE_ARCHIVO_VERTEX_SHADER_RUIDO;
	static const string NOMBRE_ARCHIVO_VERTEX_SHADER_DOBLAR;
	static const string NOMBRE_ARCHIVO_VERTEX_SHADER_ESFERIZAR;

	static const string ARCHIVOS_FRAGMENT_SHADERS[];
	static const string NOMBRE_ARCHIVO_FRAGMENT_SHADER_MATERIAL_SOMBREADO_BRILLANTE;
	static const string NOMBRE_ARCHIVO_FRAGMENT_SHADER_MATERIAL_SOMBREADO_TEXTURADO;
	static const string NOMBRE_ARCHIVO_FRAGMENT_SHADER_MATERIAL_REFLECTIVO;
	static const string NOMBRE_ARCHIVO_FRAGMENT_SHADER_MATERIAL_SOMBREADO_SEMIMATE;

	static const string ARCHIVOS_FRAGMENT_SHADERS_LUZ[];
	static const string NOMBRE_ARCHIVO_FRAGMENT_SHADER_LUZ_PRINCIPAL;
	static const string NOMBRE_ARCHIVO_FRAGMENT_SHADER_LUZ_SECUNDARIA;

public:
	GLSLProgram();

	bool compileShaderFromFile(int tShader, GLSLShaderType type, bool esLuz = false );
	//TODO : considerar hacer los métodos de renovar privados
	void renovar();
	void renovarVertexShader();
	void renovarFragmentShader();
	void renovarLuz();

	bool link();
	void usar();
	string log();
	int getProgramHandle();
	bool isLinked();
	
	void bindAttribLocation( GLuint location, const char * name);
	void bindFragDataLocation( GLuint location, const char * name);
	void setUniform(const char *name,float x,float y, float z);
	void setUniform(const char *name, const vec3 & v);
	void setUniform(const char *name, const vec4 & v);
	void setUniform(const char *name, const mat4 & m);
	void setUniform(const char *name, const mat3 & m);
	void setUniform(const char *name, float val );
	void setUniform(const char *name, int val );
	void setUniform(const char *name, bool val );
	void printActiveUniforms();
	void printActiveAttribs();
};
