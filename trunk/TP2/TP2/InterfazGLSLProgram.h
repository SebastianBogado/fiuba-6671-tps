#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
using glm::vec3;
using glm::vec4;
using glm::mat3;
using glm::mat4;

class InterfazGLSLProgram{
public:
	virtual void bindAttribLocation( GLuint location, const char * name) = 0;
	virtual void bindFragDataLocation( GLuint location, const char * name ) = 0;

	virtual void setUniform(const char *name, const vec3 & v) = 0;
	virtual void setUniform(const char *name, const vec4 & v) = 0;
	virtual void setUniform(const char *name, const mat4 & m) = 0;
	virtual void setUniform(const char *name, const mat3 & m) = 0;
	virtual void setUniform(const char *name, float val ) = 0;
	virtual void setUniform(const char *name, int val ) = 0;
	virtual void setUniform(const char *name, bool val ) = 0;
	virtual void printActiveUniforms() = 0;
	virtual void printActiveAttribs() = 0;
};

