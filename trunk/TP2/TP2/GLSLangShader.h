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

class GLSLangShader{
protected:
	int shaderHandle;
	string logString;

	bool fileExists( const string & fileName );
public:
	GLSLangShader();
	virtual bool compileShaderFromFile( const char * fileName, GLSLShaderType type );
	virtual bool compileShaderFromString( const string & source, GLSLShaderType type );

	string log();
	int getShaderHandle();
};


