#include "GLSLangShader.h"


GLSLangShader::GLSLangShader(){
	this->shaderHandle = 0;
	this->logString = "";
}

bool GLSLangShader::compileShaderFromFile( const char * fileName, GLSLShaderType type ){
	switch (type){
		case VERTEX:
			shaderHandle = glCreateShader(GL_VERTEX_SHADER);
			break;
		case FRAGMENT:
			shaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
			break;
		case GEOMETRY:
			shaderHandle = glCreateShader(GL_GEOMETRY_SHADER);
			break;
		case TESS_CONTROL:
			shaderHandle = glCreateShader(GL_TESS_CONTROL_SHADER);
			break;
		case TESS_EVALUATION:
			shaderHandle = glCreateShader(GL_TESS_EVALUATION_SHADER);
			break;
		default:
			shaderHandle = 0;
			break;
	}
	if (shaderHandle == 0) return false;

	const GLchar* codeArray[] = {fileName};
	glShaderSource(shaderHandle, 1, codeArray, NULL);
	glCompileShader(shaderHandle);
	
	GLint result;
	glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &result );
	if( GL_FALSE == result ){
		cout << "Falló la compilación" << endl;
		return false;
		GLint logLen;
		glGetShaderiv( shaderHandle, GL_INFO_LOG_LENGTH, &logLen );
		if( logLen > 0 ){
			char * log = (char *)malloc(logLen);
			GLsizei written;
			glGetShaderInfoLog(shaderHandle, logLen, &written, log);
			cout << "Shader log: " << log << endl;
			logString = log;
			free(log);
		}
	}
	return true;
}

bool GLSLangShader::compileShaderFromString( const string & source, GLSLShaderType type ){
	if (fileExists(source)){
		switch (type){
			case VERTEX:
				shaderHandle = glCreateShader(GL_VERTEX_SHADER);
				break;
			case FRAGMENT:
				shaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
				break;
			case GEOMETRY:
				shaderHandle = glCreateShader(GL_GEOMETRY_SHADER);
				break;
			case TESS_CONTROL:
				shaderHandle = glCreateShader(GL_TESS_CONTROL_SHADER);
				break;
			case TESS_EVALUATION:
				shaderHandle = glCreateShader(GL_TESS_EVALUATION_SHADER);
				break;
			default:
				shaderHandle = 0;
				break;
		}

		if (shaderHandle == 0) return false;

		GLchar* aux = new GLchar[source.length()];
		for (int i = 0; i < source.length(); i++){
			aux[i] = source[i];
		}
		const GLchar* codeArray[] = {aux};
		glShaderSource(shaderHandle, 1, codeArray, NULL);
		glCompileShader(shaderHandle);
	
		GLint result;
		glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &result );
		if( GL_FALSE == result ){
			cout << "Falló la compilación" << endl;
			return false;
			GLint logLen;
			glGetShaderiv( shaderHandle, GL_INFO_LOG_LENGTH, &logLen );
			if( logLen > 0 ){
				char * log = (char *)malloc(logLen);
				GLsizei written;
				glGetShaderInfoLog(shaderHandle, logLen, &written, log);
				cout << "Shader log: " << log << endl;
				logString = log;
				free(log);
			}
		}
	}

	return true;
}

string GLSLangShader::log(){ return logString; }

int GLSLangShader::getShaderHandle(){ return shaderHandle; }

bool GLSLangShader::fileExists( const string & fileName ){
	ifstream ifile(fileName);
	return ifile;
}
