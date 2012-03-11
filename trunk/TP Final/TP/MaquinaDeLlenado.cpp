#include "MaquinaDeLlenado.h"
#include "EscenaGrafica.h"
#include "Control.h"

MaquinaDeLlenado::MaquinaDeLlenado(void)
{

		///solo para test
	this->_pasoTest = 0.01;

	this->posicionObjeto = new float[3];
	this->inicializarVector(posicionObjeto,5.5,15.5,0.0);

	this->posDeObjetoAnimado = new float [3];
	this->inicializarVector(posDeObjetoAnimado,23.0,6.5,0.0);
	
	this->AnimacionIniciada = false;
	rutaShaderDeVertices = "..\\ShadersTest\\tanqueDeCoca.vert";
	rutaShaderDeFragmentos = "..\\ShadersTest\\tanqueDeCoca.frag";
	ladoTextura = 256;
	ini();
}

void MaquinaDeLlenado::ini(){
	//GLSL
	shaders = new GLSLProgram(rutaShaderDeVertices, rutaShaderDeFragmentos);

	//Textura
	glGenTextures(1, &texturaID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texturaID);
	for (int i=0;i<6;++i)
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0, GL_RGB, ladoTextura, ladoTextura, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	GLclampf prioridad = 1.0;
	glPrioritizeTextures(1, &texturaID, &prioridad);
		
	//Materiales
	definirMateriales();

	//Superficies
	//Cuerpo del tanque
	vec3 bsplineP1 = vec3(-1.0, 0.0, 1.0); 
	vec3 bsplineP2 = vec3(1.0, 0.0, 1.0);
	vec3 bsplineP3 = vec3(1.0, 0.0, 2.5);
	vec3 bsplineP4 = vec3(1.0, 0.0, 4.0); 
	vec3 bsplineP5 = vec3(-1.0, 0.0, 4.0);
	alturaDelCentro = bsplineP5.z - bsplineP1.z;
	BSpline* perfilTanqueDeCoca = new BSpline(5);
	perfilTanqueDeCoca->incluirPunto(bsplineP1);
	perfilTanqueDeCoca->incluirPunto(bsplineP2);
	perfilTanqueDeCoca->incluirPunto(bsplineP3);
	perfilTanqueDeCoca->incluirPunto(bsplineP4);
	perfilTanqueDeCoca->incluirPunto(bsplineP5);
	SuperficieDeRevolucion* superficieTanqueDeCoca = new SuperficieDeRevolucion(perfilTanqueDeCoca);
	
	//Tubito que llena las botellas
	//Curva borde
	Circunferencia* borde = new Circunferencia(0.1, vec3(0.0, 0.0, 4.5));
	//Curva camino
	//vec3 caminoP1 = vec3( 0.0,  -0.25, 4.5);
	vec3 caminoP1 = vec3( 0.0,  -0.25, 4.5);
	vec3 caminoP2 = vec3( 0.0,   0.25, 4.5);
	vec3 caminoP3 = vec3( 0.0,   1.0, 4.5);
	vec3 caminoP4 = vec3( 0.0,   1.6, 4.5);

	//vec3 caminoP5 = vec3( 0.0,  1.75, 4.25) original
	vec3 caminoP5 = vec3( 0.0,  2.0, 4.25);

	//vec3 caminoP6 = vec3( 0.0,  1.75, 4.0); original
	vec3 caminoP6 = vec3( 0.0,  2.0, 3.75);
	BSpline* caminoTuboDelTanqueDeCoca = new BSpline(6);//6 original

	//caminoTuboDelTanqueDeCoca->incluirPunto(caminoP0);//migue
	caminoTuboDelTanqueDeCoca->incluirPunto(caminoP1);
	caminoTuboDelTanqueDeCoca->incluirPunto(caminoP2);
	caminoTuboDelTanqueDeCoca->incluirPunto(caminoP3);
	caminoTuboDelTanqueDeCoca->incluirPunto(caminoP4);
	caminoTuboDelTanqueDeCoca->incluirPunto(caminoP5);
	caminoTuboDelTanqueDeCoca->incluirPunto(caminoP6);
	SuperficieDeBarrido* superficieTuboDelTanqueDeCoca = new SuperficieDeBarrido(borde, caminoTuboDelTanqueDeCoca);

	//DL
	dl_handle = glGenLists(4);
	DL_TANQUE = dl_handle;
	DL_BASE = dl_handle+1;
	DL_SOPORTE_DEL_TUBITO = dl_handle+2;
	DL_TUBITO = dl_handle+3;

	glNewList(DL_TANQUE, GL_COMPILE);
		//Emparchador::emparchar(superficieTanqueDeCoca->discretizar(30, 36)); original
		Emparchador::emparchar(superficieTanqueDeCoca->discretizar(15, 18));
	glEndList();
	glNewList(DL_TUBITO, GL_COMPILE);
		Emparchador::emparchar(	superficieTuboDelTanqueDeCoca->discretizar(10, 10));
	glEndList();
	glNewList(DL_BASE, GL_COMPILE);
		glBegin(GL_QUADS);
			glNormal3f(1.0, 0.0, 0.0);
			glVertex3f(0.375, -0.375, 0.0);
			glVertex3f(0.375,  0.375, 0.0);	
			glVertex3f(0.375,  0.375, 1.25);
			glVertex3f(0.375, -0.375, 1.25);

			glNormal3f( 0.0,  1.0, 0.0);
			glVertex3f( 0.375, 0.375, 0.0);
			glVertex3f(-0.375, 0.375, 0.0);
			glVertex3f(-0.375, 0.375, 1.25);
			glVertex3f( 0.375, 0.375, 1.25);

			glNormal3f(-1.0,  0.0,  0.0);
			glVertex3f(-0.375, 0.375, 0.0);
			glVertex3f(-0.375, -0.375, 0.0);	
			glVertex3f(-0.375, -0.375, 1.25);
			glVertex3f(-0.375, 0.375, 1.25);	

			glNormal3f(0.0,  -1.0,  0.0);
			glVertex3f(-0.375, -0.375, 0.0);
			glVertex3f(0.375,  -0.375, 0.0);
			glVertex3f(0.375,  -0.375, 1.25);
			glVertex3f(-0.375, -0.375, 1.25);		

			glNormal3f(0.0,  0.0,  1.0);
			glVertex3f(0.375, -0.375, 1.25);
			glVertex3f(0.375,  0.375, 1.25);
			glVertex3f(-0.375,  0.375, 1.25);
			glVertex3f(-0.375, -0.375, 1.25);	

			glNormal3f(0.0,  0.0,  -1.0);
			glVertex3f(0.375, -0.375, 0.0);
			glVertex3f(0.375,  0.375, 0.0);
			glVertex3f(-0.375,  0.375, 0.0);
			glVertex3f(-0.375, -0.375, 0.0);	
		glEnd();
	glEndList();
	glNewList(DL_SOPORTE_DEL_TUBITO, GL_COMPILE);
		glBegin(GL_QUADS);
			glNormal3f(1.0, 0.0, 0.0);
			glVertex3f(0.2, -0.2, 3.75);
			glVertex3f(0.2,  0.2, 3.75);
			glVertex3f(0.2,  0.2, 4.75);
			glVertex3f(0.2, -0.2, 4.75);

			glNormal3f( 0.0,  1.0, 0.0);
			glVertex3f( 0.2, 0.2, 3.75);
			glVertex3f(-0.2, 0.2, 3.75);
			glVertex3f(-0.2, 0.2, 4.75);
			glVertex3f( 0.2, 0.2, 4.75);

			glNormal3f(-1.0,  0.0,  0.0);
			glVertex3f(-0.2, 0.2, 3.75);
			glVertex3f(-0.2, -0.2, 3.75);
			glVertex3f(-0.2, -0.2, 4.75);
			glVertex3f(-0.2, 0.2, 4.75);

			glNormal3f(0.0,  -1.0,  0.0);
			glVertex3f(-0.2, -0.2, 3.75);
			glVertex3f(0.2,  -0.2, 3.75);
			glVertex3f(0.2,  -0.2, 4.75);
			glVertex3f(-0.2, -0.2, 4.75);

			glNormal3f(0.0,   0.0, 1.0);
			glVertex3f( 0.2, -0.2, 4.75);
			glVertex3f( 0.2,  0.2, 4.75);
			glVertex3f(-0.2,   0.2, 4.75);
			glVertex3f(-0.2,  -0.2, 4.75);

			glNormal3f(0.0,   0.0, -1.0);
			glVertex3f( 0.2, -0.2, 3.75);
			glVertex3f( 0.2,  0.2, 3.75);
			glVertex3f(-0.2,   0.2, 3.75);
			glVertex3f(-0.2,  -0.2, 3.75);
		glEnd();
	glEndList();
}

void MaquinaDeLlenado::definirMateriales(){
	material.colorAmb = vec3(0.44, 0.57, 0.75);
	material.colorDif = vec3(0.44, 0.57, 0.75);
	material.colorEspec = vec3(0.1, 0.15, 0.2);
	material.brillo = 32.0;
			
	materialTubito.colorAmb = vec3(0.9, 0.9, 0.28);
	materialTubito.colorDif = vec3(0.9, 0.9, 0.28);
	materialTubito.colorEspec = vec3(0.3, 0.3, 0.1);
	materialTubito.brillo = 32.0;

	materialBase.colorAmb = vec3(0.3, 0.3, 0.3);
	materialBase.colorDif = vec3(0.3, 0.3, 0.3);
	materialBase.colorEspec = vec3(0.1, 0.1, 0.1);
	materialBase.brillo = 1.0; 
}

MaquinaDeLlenado::~MaquinaDeLlenado(void)
{
	delete[] this->posicionObjeto;
	delete[] this->posDeObjetoAnimado;

}


void MaquinaDeLlenado::graficar()
{
	glDisable(GL_LIGHTING);
	aplicarPhong();
	glPushMatrix();
		glTranslatef(posicionObjeto[0],posicionObjeto[1],posicionObjeto[2]);
		glRotatef(-90.0, 0.0, 0.0, 1.0);
		phong->setMaterial(materialBase);
		//Parte fija, la base
		glCallList(DL_BASE);

		//Parte móvil, el soporte del tubito y el tubito mismo
		//O sea, acá va un glTranslate según la animación
		glCallList(DL_SOPORTE_DEL_TUBITO);
		detenerPhong();

		aplicarShader();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, texturaID);
		shaders->setMaterial(materialTubito);
		shaders->setUniform("skyBoxTex", 0);
		glCallList(DL_TUBITO);

	glPopMatrix();

	detenerShader();
}

void MaquinaDeLlenado::actualizarAtributos()
{
		//solo para test

	if (this->AnimacionIniciada)
	{
		this->_testAnimacion += this->_pasoTest;

		//Seria como el tiempo de animacion

		this->AnimacionIniciada = _testAnimacion < 1.0;

	}

}


void MaquinaDeLlenado::iniciarAnimacion(Botella* botella)
{	


	//Solo para test
	botella->etiquetar();

	this->AnimacionIniciada = true;

	this->_testAnimacion = 0.0;
	
}


bool MaquinaDeLlenado::animacionFinalizada()
{
	return !(this->AnimacionIniciada);

}

void MaquinaDeLlenado::actualizarReflexion(EscenaGrafica* escena){
	float CubeMapRots[6][4] = {			
		{	-90.0f,		0.0f,	1.0f,	0.0f	},
		{	90.0f,		0.0f,	1.0f,	0.0f	},

		{	-90.0f,		1.0f,	0.0f,	0.0f	},
		{	90.0f,		1.0f,	0.0f,	0.0f	},

		{	180.0f,		1.0f,	0.0f,	0.0f	},
		{	180.0f,		0.0f,	0.0f,	1.0f	},
	};

	
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	
	glViewport(0, 0, ladoTextura, ladoTextura);
	gluPerspective (90, 1.0f, 1, 5000);

	glMatrixMode(GL_MODELVIEW);
	
	for(GLuint i = 0; i < 6; i++){
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		glRotatef(CubeMapRots[i][0], CubeMapRots[i][1], CubeMapRots[i][2], CubeMapRots[i][3]);
		if(i == 0  ||  i == 1)		glRotatef(180.0f, 0.0f, 0.0f, 1.0f);

		glRotatef(90.0, 0.0, 0.0, 1.0);
		glTranslatef(-posicionObjeto[0], -posicionObjeto[1], -alturaDelCentro);

		escena->graficarParaReflexion();
		glBindTexture(GL_TEXTURE_CUBE_MAP, texturaID); 
		glCopyTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0, 0, 0, 0, 0, ladoTextura, ladoTextura);
		glFlush();
	}

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, Control::getTamañoVentana().x, Control::getTamañoVentana().y);

}
void MaquinaDeLlenado::graficarParteReflectiva(){
	glDisable(GL_LIGHTING);
	aplicarShader();
	glPushMatrix();
		glTranslatef(posicionObjeto[0],posicionObjeto[1],posicionObjeto[2]);
		glRotatef(-90.0, 0.0, 0.0, 1.0);
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, texturaID);
		shaders->setMaterial(material);
		shaders->setUniform("skyBoxTex", 0);
		glCallList(DL_TANQUE);

	glPopMatrix();

	detenerShader();
}
