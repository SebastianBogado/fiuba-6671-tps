#include "GLSLProgram.h"

const string GLSLProgram::tiposDeShaders[5] = {"Vertex", "Fragment", "Geometry", "Tess control", "Tess evaluation"};
Iluminacion* GLSLProgram::iluminacion = Iluminacion::getInstancia();

GLSLProgram::GLSLProgram(){
	this->linked = false;
	this->logString = "";
	this->handle = 0;
}

GLSLProgram::GLSLProgram(const char* vertexShader, const char* fragmentShader){
	this->linked = false;
	this->logString = "";
	this->handle = 0;

	if (!compileShaderFromFile(vertexShader, VERTEX))
		return;
	if (!compileShaderFromFile(fragmentShader, FRAGMENT))
		return;
}


void GLSLProgram::usar(){
	if (linked)
		glUseProgram(handle);
	else
		cout << "El programa no ha sido linkeado" << endl;
}

void GLSLProgram::cerrar(){ glUseProgram(0); }

string GLSLProgram::log(){ return logString; }

int GLSLProgram::getHandle(){ return handle; }

bool GLSLProgram::isLinked(){ return linked; }

bool GLSLProgram::compileShaderFromFile(const char* fileName, GLSLShaderType type){
	bool todoEnOrden = true;
	GLuint shaderHandle;
	const char* aux;

	switch (type){
		case VERTEX:
			if (!fileExists(fileName)){
				logString = "Archivo inexistente: ";
				logString += (fileName);
				cout << logString.c_str() << endl;
				return !todoEnOrden;
			}
			shaderHandle = glCreateShader(GL_VERTEX_SHADER);
			break;
		case FRAGMENT:
			if (!fileExists(fileName)){
				logString = "Archivo inexistente: ";
				logString += (fileName);
				cout << logString.c_str() << endl;
				return !todoEnOrden;
			}
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
	
	aux = cargarArchivo(fileName);
	const GLchar* codeArray[] = {aux};
	glShaderSource(shaderHandle, 1, codeArray, NULL);
	glCompileShader(shaderHandle);
		
	GLint result;
	glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &result );
	if( GL_FALSE == result ){
		cout << "Falló la compilación del " <<  tiposDeShaders[type].c_str() << " Shader." << endl;
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
	if (handle == 0)
		handle = glCreateProgram();

	glAttachShader(handle, shaderHandle);
	return todoEnOrden;	
}

bool GLSLProgram::link(){
	linked = true;
	glLinkProgram(handle);
		
	GLint status;
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

void GLSLProgram::bindAttribLocation( GLuint location, const char * name){
	glBindAttribLocation(handle, location, name);
}

void GLSLProgram::bindFragDataLocation( GLuint location, const char * name ){
	glBindFragDataLocation(handle, location, name);
}

int GLSLProgram::getUniformLocation(const char * name ){
	GLint loc = glGetUniformLocation(handle, name);
	if( loc < 0 )
		cout << "No existe el parametro " << name << " como variable uniforme." << endl;

	return loc;
}

void GLSLProgram::setUniform(const char *name, float x, float y, float z){
		glUniform3f(getUniformLocation(name), x, y, z);
}
void GLSLProgram::setUniform(const char *name, const vec3 & v){
	glUniform3fv(getUniformLocation(name), 1, &v[0]);
}

void GLSLProgram::setUniform(const char *name, const vec4 & v){
	glUniform4fv(getUniformLocation(name), 1, &v[0]);
}

void GLSLProgram::setUniform(const char *name, const mat4 & m){
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &m[0][0]);
}

void GLSLProgram::setUniform(const char *name, const mat3 & m){
	glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, &m[0][0]);
}

void GLSLProgram::setUniform(const char *name, float val ){
	glUniform1f(getUniformLocation(name), val);
}

void GLSLProgram::setUniform(const char *name, int val ){
	glUniform1i(getUniformLocation(name), val);
}

void GLSLProgram::setUniform(const char *name, bool val ){
	glUniform1i(getUniformLocation(name), val);
}

void GLSLProgram::setLuces(){ 
	string l[] = { "luzE1", "luzE2", "luzE3", "luzE4", "luzE5", "luzE6"};
	int i= 0;
	for (int i = 0; i < iluminacion->cantidadDeLuces(); i++){
		std::string aux = l[i];

		this->setUniform(aux.append(".prendida").c_str(), iluminacion->luz(i).prendida);			aux = l[i];
		this->setUniform(aux.append(".posicion").c_str(), vec3(iluminacion->luz(i).posicion));		aux = l[i];
		this->setUniform(aux.append(".direccion").c_str(), vec3(iluminacion->luz(i).direccion));
	}
}

void GLSLProgram::setMaterial(propMaterial material){
	this->setUniform("material.colorAmb", material.colorAmb);
	this->setUniform("material.colorDif", material.colorDif);
	this->setUniform("material.colorEspec", material.colorEspec);
	this->setUniform("material.brillo", material.brillo);
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