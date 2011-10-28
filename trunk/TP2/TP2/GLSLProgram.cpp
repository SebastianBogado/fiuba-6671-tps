#include "GLSLProgram.h"

const string GLSLProgram::NOMBRE_ARCHIVO_VERTEX_SHADER_RETORCER = "retorcer.vert";
const string GLSLProgram::NOMBRE_ARCHIVO_VERTEX_SHADER_RUIDO = "ruido.vert";
const string GLSLProgram::NOMBRE_ARCHIVO_VERTEX_SHADER_DOBLAR = "doblar.vert";
const string GLSLProgram::NOMBRE_ARCHIVO_VERTEX_SHADER_ESFERIZAR = "esferizar.vert";

const string GLSLProgram::ARCHIVOS_VERTEX_SHADERS[4] = {
		NOMBRE_ARCHIVO_VERTEX_SHADER_RETORCER,
		NOMBRE_ARCHIVO_VERTEX_SHADER_RUIDO,
		NOMBRE_ARCHIVO_VERTEX_SHADER_DOBLAR,
		NOMBRE_ARCHIVO_VERTEX_SHADER_ESFERIZAR};

const string GLSLProgram::NOMBRE_ARCHIVO_FRAGMENT_SHADER_MATERIAL_SOMBREADO_BRILLANTE = "materialSombreadoBrillante.frag";
const string GLSLProgram::NOMBRE_ARCHIVO_FRAGMENT_SHADER_MATERIAL_SOMBREADO_TEXTURADO = "materialSombreadoTexturado.frag";
const string GLSLProgram::NOMBRE_ARCHIVO_FRAGMENT_SHADER_MATERIAL_REFLECTIVO = "materialReflectivo.frag";
const string GLSLProgram::NOMBRE_ARCHIVO_FRAGMENT_SHADER_MATERIAL_SOMBREADO_SEMIMATE = "materialSombreadoSemimate.frag";
const string GLSLProgram::ARCHIVOS_FRAGMENT_SHADERS[4] = {
	NOMBRE_ARCHIVO_FRAGMENT_SHADER_MATERIAL_SOMBREADO_BRILLANTE,
	NOMBRE_ARCHIVO_FRAGMENT_SHADER_MATERIAL_SOMBREADO_TEXTURADO,
	NOMBRE_ARCHIVO_FRAGMENT_SHADER_MATERIAL_REFLECTIVO,
	NOMBRE_ARCHIVO_FRAGMENT_SHADER_MATERIAL_SOMBREADO_SEMIMATE};

GLSLProgram::GLSLProgram(){
	this->linked = false;
	this->logString = "";
	this->programHandle = 0;
}

void GLSLProgram::use(){
	if (linked)
		glUseProgram(programHandle);
	else
		cout << "El programa no ha sido linkeado" << endl;
}

string GLSLProgram::log(){ return logString; }

int GLSLProgram::getProgramHandle(){ return programHandle; }

bool GLSLProgram::isLinked(){ return linked; }

bool GLSLProgram::compileShaderFromFile(int tShader, GLSLShaderType type ){
	bool todoEnOrden = true;
	GLuint shaderHandle;
	const char* aux;

	switch (type){
		case VERTEX:
			if (!fileExists(ARCHIVOS_VERTEX_SHADERS[tShader]))
				return !todoEnOrden;
			shaderHandle = glCreateShader(GL_VERTEX_SHADER);
			aux = cargarArchivo(ARCHIVOS_VERTEX_SHADERS[tShader]);
			break;
		case FRAGMENT:
			if (!fileExists(ARCHIVOS_FRAGMENT_SHADERS[tShader]))
				return !todoEnOrden;
			shaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
			aux = cargarArchivo(ARCHIVOS_FRAGMENT_SHADERS[tShader]);
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
	if (programHandle == 0)
		programHandle = glCreateProgram();

	glAttachShader(programHandle, shaderHandle);
	return todoEnOrden;	
}


bool GLSLProgram::link(){
	linked = true;
	glLinkProgram(programHandle);
		
	GLint status;
	glGetProgramiv( programHandle, GL_LINK_STATUS, &status );
	if( GL_FALSE == status ) {
		cout << "Falló el linkeo al programa" << endl;
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

void GLSLProgram::renovar(){
	if (programHandle == 0)
		return;
	glDeleteProgram(programHandle);
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

bool GLSLProgram::fileExists( const string & fileName ){
	ifstream ifile(fileName);
	return ifile;
}

char* GLSLProgram::cargarArchivo(string fileName){
	//De http://stackoverflow.com/questions/1938466/unable-to-link-compiled-shaders-glsl
	
	char* fn = new char[fileName.size() + 1];
	for (int i = 0; i < fileName.size(); i++)
		fn[i] = fileName[i];
	fn[fileName.size()] = NULL;

	FILE *fp;
	char *content = NULL;

	int count=0;

	if (fn != NULL) {
		fp = fopen(fn,"rt");

		if (fp != NULL) {

			fseek(fp, 0, SEEK_END);
			count = ftell(fp);
			rewind(fp);

			if (count > 0) {
				content = (char *)malloc(sizeof(char) * (count+1));
				count = fread(content,sizeof(char),count,fp);
				content[count] = '\0';
			}
			fclose(fp);
		}
	}
	return content;
}