#include "GLSLProgram.h"

GLSLProgram::GLSLProgram(){
	this->linked = false;
	this->handle = 0;
	this->logString = "";
}

bool GLSLProgram::compileShaderFromFile( const char * fileName, GLSLShader::GLSLShaderType type ){
	GLuint shader;
	switch (type){
		case GLSLShader::GLSLShaderType.VERTEX:
			shader = glCreateShader(GL_VERTEX_SHADER);
			break;
		case GLSLShader::GLSLShaderType.FRAGMENT:
			shader = glCreateShader(GL_FRAGMENT_SHADER);
			break;
		case GLSLShader::GLSLShaderType.GEOMETRY:
			shader = glCreateShader(GL_GEOMETRY_SHADER);
			break;
		case GLSLShader::GLSLShaderType.TESS_CONTROL:
			shader = glCreateShader(GL_TESS_CONTROL_SHADER);
			break;
		case GLSLShader::GLSLShaderType.TESS_EVALUATION:
			shader = glCreateShader(GL_TESS_EVALUATION_SHADER);
			break;
		default:
			shader = 0;
			break;
	}
	if (shader == 0) return false;

	const GLchar* codeArray[] = {fileName};
	glShaderSource(shader, 1, codeArray, NULL);
	glCompileShader(shader);
	
	GLint result;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result );
	if( GL_FALSE == result ){
		cout << "Falló la compilación" << endl;
		return false;
		GLint logLen;
		glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &logLen );
		if( logLen > 0 ){
			char * log = (char *)malloc(logLen);
			GLsizei written;
			glGetShaderInfoLog(shader, logLen, &written, log);
			cout << "Shader log: " << log << endl;
			logString = log;
			free(log);
		}
	}

	//si es el primer shader que se compila:
	if (handle == 0) handle = glCreateProgram();

	//si no se pudo crear el programa por alguna razón:
	if (handle == 0){
		cout << "Error creando el programa del shader" << endl;
		return false;
	}
	glAttachShader(handle, shader);
	return true;
}

bool GLSLProgram::compileShaderFromString( const string & source, GLSLShader::GLSLShaderType type ){
	if (fileExists(source)){
		GLuint shader;
		switch (type){
			case GLSLShader::GLSLShaderType.VERTEX:
				shader = glCreateShader(GL_VERTEX_SHADER);
				break;
			case GLSLShader::GLSLShaderType.FRAGMENT:
				shader = glCreateShader(GL_FRAGMENT_SHADER);
				break;
			case GLSLShader::GLSLShaderType.GEOMETRY:
				shader = glCreateShader(GL_GEOMETRY_SHADER);
				break;
			case GLSLShader::GLSLShaderType.TESS_CONTROL:
				shader = glCreateShader(GL_TESS_CONTROL_SHADER);
				break;
			case GLSLShader::GLSLShaderType.TESS_EVALUATION:
				shader = glCreateShader(GL_TESS_EVALUATION_SHADER);
				break;
			default:
				shader = 0;
				break;
		}

		if (shader == 0) return false;

		const GLchar* codeArray[] = {fileName};
		glShaderSource(shader, 1, codeArray, NULL);
		glCompileShader(shader);
	
		GLint result;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &result );
		if( GL_FALSE == result ){
			cout << "Falló la compilación" << endl;
			return false;
			GLint logLen;
			glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &logLen );
			if( logLen > 0 ){
				char * log = (char *)malloc(logLen);
				GLsizei written;
				glGetShaderInfoLog(shader, logLen, &written, log);
				cout << "Shader log: " << log << endl;
				logString = log;
				free(log);
			}
		}

		//si es el primer shader que se compila:
		if (handle == 0) handle = glCreateProgram();

		//si no se pudo crear el programa por alguna razón:
		if (handle == 0){
			cout << "Error creando el programa del shader" << endl;
			return false;
		}
		glAttachShader(handle, shader);
		return true;
	}
}


bool GLSLProgram::link(){
	glLinkProgram(handle);
	GLint status;
	linked = true;
	glGetProgramiv( handle, GL_LINK_STATUS, &status );
	if( GL_FALSE == status ) {
		cout << "Falló el linkeo al programa" << endl;
		linked = false;
		GLint logLen;
		glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &logLen);
		if( logLen > 0 ){
			char * log = (char *)malloc(logLen);
			GLsizei written;
			glGetProgramInfoLog(handle, logLen, &written, log);
			cout << "Program log: " << log << endl;
			logString = log;
			free(log);
		}
	}
	
	return linked;
}

void GLSLProgram::use(){
	if (linked) glUseProgram(handle);
}

string GLSLProgram::log(){ return logString; }

int GLSLProgram::getHandle(){ return handle; }

bool GLSLProgram::isLinked(){ return linked; }

void GLSLProgram::bindAttribLocation( GLuint location, const char * name){
	glBindAttribLocation(handle, location, name);
}

void GLSLProgram::bindFragDataLocation( GLuint location, const char * name ){
	glBindFragDataLocation(handle, location, name);
}

void GLSLProgram::setUniform(const char *name,float x,float y, float z){
	GLuint location = glGetUniformLocation(handle, name);
	if( location >= 0 ){
		glUniform3f(location, x, y, z);
	}
}

void GLSLProgram::setUniform(const char *name, const vec3 & v){
	GLuint location = glGetUniformLocation(handle, name);
	if( location >= 0 ){
		glUniform3fv(location, 1, &v[0]);
	}
}

void GLSLProgram::setUniform(const char *name, const vec4 & v){
	GLuint location = glGetUniformLocation(handle, name);
	if( location >= 0 ){
		glUniform4fv(location, 1, &v[0]);
}

void GLSLProgram::setUniform(const char *name, const mat4 & m){
	GLuint location = glGetUniformLocation(handle, name);
	if( location >= 0 ){
		glUniformMatrix4fv(location, 1, GL_FALSE, &m[0][0]);
	}
}

void GLSLProgram::setUniform(const char *name, const mat3 & m){
	GLuint location = glGetUniformLocation(handle, name);
	if( location >= 0 ){
		glUniformMatrix3fv(location, 1, GL_FALSE, &m[0][0]);
	}
}

void GLSLProgram::setUniform(const char *name, float val ){
	GLuint location = glGetUniformLocation(handle, name);
	if( location >= 0 ){
		glUniform1f(location, val);
	}
}

void GLSLProgram::setUniform(const char *name, int val ){
	GLuint location = glGetUniformLocation(handle, name);
	if( location >= 0 ){
		glUniform1i(location, val);
	}
}

void GLSLProgram::setUniform(const char *name, bool val ){
	GLuint location = glGetUniformLocation(handle, name);
	if( location >= 0 ){
		glUniform1i(location, val);
	}
}

void GLSLProgram::printActiveUniforms(){
	//implementar si se necesita debuggear
}

void GLSLProgram::printActiveAttribs(){
	//implementar si se necesita debuggear
}

int GLSLProgram::getUniformLocation(const char * name ){
	return glGetUniformLocation(handle, name);
}

bool GLSLProgram::fileExists( const string & fileName ){
	ifstream ifile(filename);
	return ifile;
}
