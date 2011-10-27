//Clase extraida de "OpenGl 4.0 Shading Language Cookbook"
//Autor: David Wolff

#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
using glm::vec3;
using glm::vec4;
using glm::mat3;
using glm::mat4;

#include <iostream>
using std::string;
using std::cout;
using std::endl;

namespace GLSLShader {
	enum GLSLShaderType {
		VERTEX, 
		FRAGMENT, 
		GEOMETRY,
		TESS_CONTROL,
		TESS_EVALUATION};
};

class GLSLProgram{
private:
	int handle;
	bool linked;
	string logString;
	int getUniformLocation(const char * name );
	bool fileExists( const string & fileName );
public:
	GLSLProgram();
	bool compileShaderFromFile( const char * fileName, GLSLShader::GLSLShaderType type );
	bool compileShaderFromString( const string & source, GLSLShader::GLSLShaderType type );
	bool link();
	void use();
	string log();
	int getHandle();
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
