#include "GLSLangShader.h"


GLSLangShader::GLSLangShader(){
	this->shaderHandle = 0;
	this->logString = "";
}

bool GLSLangShader::compileShaderFromFile( const char * fileName, GLSLShaderType type ){
	return compileShaderFromFile(string(fileName), type);
}

bool GLSLangShader::compileShaderFromFile( const string & fileName, GLSLShaderType type ){
	bool todoEnOrden = true;
	if (!fileExists(fileName))
		return !todoEnOrden;
	else{
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
		if (shaderHandle == 0) return !todoEnOrden;
		
		const char* aux = cargarArchivo(fileName);
		const GLchar* codeArray[] = {aux};
		glShaderSource(shaderHandle, 1, codeArray, NULL);
		glCompileShader(shaderHandle);
		
		GLint result;
		glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &result );
		if( GL_FALSE == result ){
			cout << "Falló la compilación" << endl;
			GLint logLen;
			glGetShaderiv( shaderHandle, GL_INFO_LOG_LENGTH, &logLen );
			if( logLen > 0 ){
				char * log = (char *)malloc(logLen);
				GLsizei written;
				glGetShaderInfoLog(shaderHandle, logLen, &written, log);
				cout << "Shader log: " << log << endl;
				logString = log;
				free(log);
				return !todoEnOrden;
			}
		}
		return todoEnOrden;	
	}
}

	


string GLSLangShader::log(){ return logString; }

int GLSLangShader::getShaderHandle(){ return shaderHandle; }

bool GLSLangShader::fileExists( const string & fileName ){
	ifstream ifile(fileName);
	return ifile;
}

const char* GLSLangShader::cargarArchivo(string fileName){
	std::fstream archivo;
	archivo.open(fileName.c_str(), std::fstream::in);
	if (!archivo.is_open()) 
		cout << "Problemas abriendo el archivo." << endl;
	else
		cout << "Se abrió el archivo" << endl;
	
	string archivoEntero;
	do{
		char linea[256];
		archivo.getline( (char*)&linea , 256 , '\n');
		string aux = linea;
		archivoEntero += aux;
	} while ( !archivo.eof() );

 	archivo.close();
	cout << archivoEntero.c_str() << endl;
	return archivoEntero.c_str();
}