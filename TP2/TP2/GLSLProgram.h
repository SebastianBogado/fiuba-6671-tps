//Clase inspirada en la homónima de "OpenGl 4.0 Shading Language Cookbook"
//Autor: David Wolff

#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
using glm::vec3;
using glm::vec4;
using glm::mat3;
using glm::mat4;

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


class GLSLProgram{
private:
	int programHandle;
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
public:
	GLSLProgram();

	bool compileShaderFromFile(int tShader, GLSLShaderType type );
	void renovar();
	bool link();
	void use();
	string log();
	int getProgramHandle();
	bool isLinked();
	
	void bindAttribLocation( GLuint location, const char * name);
	void bindFragDataLocation( GLuint location, const char * name );
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
