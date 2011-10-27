#include "GLSLProgram.h"

GLSLProgram::GLSLProgram(){
	this->linked = false;
}

bool GLSLProgram::compileShaderFromFile( const char * fileName, GLSLShaderType type ){
	GLuint shader;
	switch (type){
		case VERTEX:
			shader = glCreateShader(GL_VERTEX_SHADER);
			break;
		case FRAGMENT:
			shader = glCreateShader(GL_FRAGMENT_SHADER);
			break;
		case GEOMETRY:
			shader = glCreateShader(GL_GEOMETRY_SHADER);
			break;
		case TESS_CONTROL:
			shader = glCreateShader(GL_TESS_CONTROL_SHADER);
			break;
		case TESS_EVALUATION:
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
		cout << "Fall� la compilaci�n" << endl;
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
	if (programHandle == 0) programHandle = glCreateProgram();

	//si no se pudo crear el programa por alguna raz�n:
	if (programHandle == 0){
		cout << "Error creando el programa del shader" << endl;
		return false;
	}
	glAttachShader(programHandle, shader);
	return true;
}

bool GLSLProgram::compileShaderFromString( const string & source, GLSLShaderType type ){
	GLuint handle;
	if (fileExists(source)){
		switch (type){
			case VERTEX:
				handle = glCreateShader(GL_VERTEX_SHADER);
				break;
			case FRAGMENT:
				handle = glCreateShader(GL_FRAGMENT_SHADER);
				break;
			case GEOMETRY:
				handle = glCreateShader(GL_GEOMETRY_SHADER);
				break;
			case TESS_CONTROL:
				handle = glCreateShader(GL_TESS_CONTROL_SHADER);
				break;
			case TESS_EVALUATION:
				handle = glCreateShader(GL_TESS_EVALUATION_SHADER);
				break;
			default:
				handle = 0;
				break;
		}

		if (handle == 0) return false;

		GLchar* aux = new GLchar[source.length()];
		for (int i = 0; i < source.length(); i++){
			aux[i] = source[i];
		}
		const GLchar* codeArray[] = {aux};
		glShaderSource(handle, 1, codeArray, NULL);
		glCompileShader(handle);
	
		GLint result;
		glGetShaderiv(handle, GL_COMPILE_STATUS, &result );
		if( GL_FALSE == result ){
			cout << "Fall� la compilaci�n" << endl;
			return false;
			GLint logLen;
			glGetShaderiv( handle, GL_INFO_LOG_LENGTH, &logLen );
			if( logLen > 0 ){
				char * log = (char *)malloc(logLen);
				GLsizei written;
				glGetShaderInfoLog(handle, logLen, &written, log);
				cout << "Shader log: " << log << endl;
				logString = log;
				free(log);
			}
		}
	}

	//si es el primer shader que se compila:
	if (programHandle == 0) programHandle = glCreateProgram();

	//si no se pudo crear el programa por alguna raz�n:
	if (programHandle == 0){
		cout << "Error creando el programa del shader" << endl;
		return false;
	}
	glAttachShader(programHandle, handle);
	return true;
}


bool GLSLProgram::link(){
	glLinkProgram(programHandle);
	GLint status;
	linked = true;
	glGetProgramiv( programHandle, GL_LINK_STATUS, &status );
	if( GL_FALSE == status ) {
		cout << "Fall� el linkeo al programa" << endl;
		linked = false;
		GLint logLen;
		glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH, &logLen);
		if( logLen > 0 ){
			char * log = (char *)malloc(logLen);
			GLsizei written;
			glGetProgramInfoLog(programHandle, logLen, &written, log);
			cout << "Program log: " << log << endl;
			logString = log;
			free(log);
		}
	}
	
	return linked;
}

void GLSLProgram::use(){
	if (linked) glUseProgram(programHandle);
}

string GLSLProgram::log(){ return logString; }

int GLSLProgram::getProgramHandle(){ return programHandle; }

bool GLSLProgram::isLinked(){ return linked; }

bool GLSLProgram::link(GLuint vertexShader, GLuint fragmentShader){
	if (programHandle != 0)
		glDeleteProgram(programHandle);

	programHandle = glCreateProgram();
	if (programHandle == 0){
		cout << "Error creando el programa del shader" << endl;
		linked = false;
		return linked;
	}
	glAttachShader(programHandle, vertexShader);
	glAttachShader(programHandle, fragmentShader);
	glLinkProgram(programHandle);

	GLint status;
	linked = true;
	glGetProgramiv( programHandle, GL_LINK_STATUS, &status );
	if( GL_FALSE == status ) {
		cout << "Fall� el linkeo al programa" << endl;
		linked = false;
		GLint logLen;
		glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH, &logLen);
		if( logLen > 0 ){
			char * log = (char *)malloc(logLen);
			GLsizei written;
			glGetProgramInfoLog(programHandle, logLen, &written, log);
			cout << "Program log: " << log << endl;
			logString = log;
			free(log);
		}
	}
	
	return linked;
}


void GLSLProgram::bindAttribLocation( GLuint location, const char * name){
	glBindAttribLocation(programHandle, location, name);
}

void GLSLProgram::bindFragDataLocation( GLuint location, const char * name ){
	glBindFragDataLocation(programHandle, location, name);
}

int GLSLProgram::getUniformLocation(const char * name ){
	return glGetUniformLocation(programHandle, name);
}

void GLSLProgram::setUniform(const char *name,float x,float y, float z){
	GLuint location = getUniformLocation(name);
	if( location >= 0 ){
		glUniform3f(location, x, y, z);
	}
}

void GLSLProgram::setUniform(const char *name, const vec3 & v){
	GLuint location = getUniformLocation(name);
	if( location >= 0 ){
		glUniform3fv(location, 1, &v[0]);
	}
}

void GLSLProgram::setUniform(const char *name, const vec4 & v){
	GLuint location = getUniformLocation(name);
	if( location >= 0 ){
		glUniform4fv(location, 1, &v[0]);
	}
}

void GLSLProgram::setUniform(const char *name, const mat4 & m){
	GLuint location = getUniformLocation(name);
	if( location >= 0 ){
		glUniformMatrix4fv(location, 1, GL_FALSE, &m[0][0]);
	}
}

void GLSLProgram::setUniform(const char *name, const mat3 & m){
	GLuint location = getUniformLocation(name);
	if( location >= 0 ){
		glUniformMatrix3fv(location, 1, GL_FALSE, &m[0][0]);
	}
}

void GLSLProgram::setUniform(const char *name, float val ){
	GLuint location = getUniformLocation(name);
	if( location >= 0 ){
		glUniform1f(location, val);
	}
}

void GLSLProgram::setUniform(const char *name, int val ){
	GLuint location = getUniformLocation(name);
	if( location >= 0 ){
		glUniform1i(location, val);
	}
}

void GLSLProgram::setUniform(const char *name, bool val ){
	GLuint location = getUniformLocation(name);
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