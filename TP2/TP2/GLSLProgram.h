//Clase extraida de "OpenGl 4.0 Shading Language Cookbook"
//Autor: David Wolff

#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "GLSLangShader.h"
using glm::vec3;
using glm::vec4;
using glm::mat3;
using glm::mat4;

#include <iostream>
using std::string;
using std::cout;
using std::endl;

class GLSLProgram: public GLSLangShader{
private:
	int programHandle;
	bool linked;
	string logString;
	int getUniformLocation(const char * name );

public:
	GLSLProgram();
	bool compileShaderFromFile( const char * fileName, GLSLShaderType type );
	bool compileShaderFromFile( const string & fileName, GLSLShaderType type );

	//Recibe los handles de un vertex shader y frag shader y los linkea. 
	//Desprecia todo shader que podría tener linkeado anteriormente, porque lo hace con un programa nuevo
	bool link(GLuint vertexShader, GLuint fragmentShader);
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
