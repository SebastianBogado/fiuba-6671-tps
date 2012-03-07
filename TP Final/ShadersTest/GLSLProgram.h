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
//#include <dirent.h>
#include <direct.h>
using namespace std;
#include "..\TP\Iluminacion.h"
#include "..\TP\propMaterial.h"


enum GLSLShaderType {
	VERTEX, 
	FRAGMENT, 
	GEOMETRY,
	TESS_CONTROL,
	TESS_EVALUATION
};


class GLSLProgram{
public:
	GLSLProgram();
	//El siguiente constructor hace todos los pasos necesarios para crear el programa
	// pero sin linkear ni usar
	GLSLProgram(const char* vertexShader, const char* fragmentShader);
	bool compileShaderFromFile(const char* fileName, GLSLShaderType type);

	bool link();
	void usar();
	void cerrar();
	string log();
	int getHandle();
	bool isLinked();
	
	void bindAttribLocation( GLuint location, const char * name);
	void bindFragDataLocation( GLuint location, const char * name);
	void setUniform(const char *name, float x, float y, float z);
	void setUniform(const char *name, const vec3 & v);
	void setUniform(const char *name, const vec4 & v);
	void setUniform(const char *name, const mat4 & m);
	void setUniform(const char *name, const mat3 & m);
	void setUniform(const char *name, float val );
	void setUniform(const char *name, int val );
	void setUniform(const char *name, bool val );
	void setLuces(Iluminacion* iluminacion);
	void setMaterial(propMaterial material);
	void printActiveUniforms();
	void printActiveAttribs();
private:
	int handle;
	bool linked;
	string logString;
	
	int getUniformLocation(const char * name );
	bool fileExists( const string & fileName );
	//Devuelve una cadena con todo el contenido del archivo
	char* cargarArchivo(string fileName);
	static const string tiposDeShaders[];
};
