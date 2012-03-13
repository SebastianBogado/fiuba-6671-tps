#include "MaquinaDeLlenado.h"
#include "EscenaGrafica.h"
#include "Control.h"

MaquinaDeLlenado::MaquinaDeLlenado(void)
{

	this->posTramoEnCinta = 0.655;


	this->pasoDeAnimacion = 0.1;
	this->acumuladorEnAnimacion = 0.0;
	this->tiempoMaximoDeAnimacion = 2.0;

	//atributos de liquido
	this->estLiquido = EstadoLiquido::iniciando;
	this->nivSupLiquido = 1.0;
	this->nivInfLiquido = 0.0;
	this->pasoNivLiquido = 0.15;

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
	dl_handle = glGenLists(5);
	DL_TANQUE = dl_handle;
	DL_BASE = dl_handle+1;
	DL_SOPORTE_DEL_TUBITO = dl_handle+2;
	DL_TUBITO = dl_handle+3;
	DL_LIQUIDO = dl_handle+4;

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


	glNewList(DL_LIQUIDO, GL_COMPILE);
		this->dibujarLiquido();
	glEndList();
}

void MaquinaDeLlenado::definirMateriales(){
	material.colorAmb = vec3(0.44, 0.57, 0.75);
	material.colorDif = vec3(0.44, 0.57, 0.75);
	material.colorEspec = vec3(0.2, 0.315, 0.42);
	material.brillo = 32.0;
			
	materialTubito.colorAmb = vec3(0.9, 0.9, 0.28);
	materialTubito.colorDif = vec3(0.9, 0.9, 0.28);
	materialTubito.colorEspec = vec3(0.3, 0.3, 0.1);
	materialTubito.brillo = 32.0;

	materialBase.colorAmb = vec3(0.3, 0.3, 0.3);
	materialBase.colorDif = vec3(0.3, 0.3, 0.3);
	materialBase.colorEspec = vec3(0.1, 0.1, 0.1);
	materialBase.brillo = 1.0; 


	materialLiquido.colorAmb = vec3(0.1719, 0.0, 0.0);
	materialLiquido.colorDif = vec3 (0.1719, 0.0, 0.0);
	materialLiquido.colorEspec = vec3(0.1719, 0.0, 0.0);
	materialLiquido.brillo = 0.1;
}

MaquinaDeLlenado::~MaquinaDeLlenado(void)
{
	delete[] this->posicionObjeto;
	delete[] this->posDeObjetoAnimado;

}


void MaquinaDeLlenado::graficar()
{
	glDisable(GL_LIGHTING);
	
	glPushMatrix();
		
	glTranslatef(posicionObjeto[0],posicionObjeto[1],posicionObjeto[2]);
	glRotatef(-90.0, 0.0, 0.0, 1.0);
	//this->dibujarLiquido();

		

		aplicarShader();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, texturaID);
		shaders->setMaterial(materialTubito);
		shaders->setUniform("skyBoxTex", 0);
		glCallList(DL_TUBITO);


		detenerShader();

		aplicarPhong();
		
		phong->setMaterial(materialBase);
		//Parte fija, la base
		
		glCallList(DL_BASE);

		//Parte móvil, el soporte del tubito y el tubito mismo
		//O sea, acá va un glTranslate según la animación
		//this->dibujarLiquido();
		
		glCallList(DL_SOPORTE_DEL_TUBITO);

		this->dibujarLiquido();

		detenerPhong();

		
		//glCallList(DL_LIQUIDO);

	glPopMatrix();

	//glScalef(20.,20.,20.);
	//this->dibujarCuboUnitario();
	
}

void MaquinaDeLlenado::actualizarAtributos()
{
		//solo para test

	if (this->AnimacionIniciada)
	{
		
		if (estLiquido == EstadoLiquido::iniciando)
		{

			nivInfLiquido += pasoNivLiquido;

			if (nivInfLiquido >= 1.0)
			{	
				nivInfLiquido = 1.0;
				estLiquido = EstadoLiquido::intermedio;
			}

		}
		else if (estLiquido == EstadoLiquido::intermedio)
		{	

			this->botellaActual->llenar();

			if (this->botellaActual->llenada())
			{
				estLiquido = EstadoLiquido::terminando;
			}

		}
		else if (estLiquido == EstadoLiquido::terminando)
		{

			nivSupLiquido -= 2.0*pasoNivLiquido;

			if (nivSupLiquido <= 0.0 )
			{	
				this->AnimacionIniciada = false;
				estLiquido = EstadoLiquido::iniciando;
				nivSupLiquido = 1.0;
				nivInfLiquido = 0.0;
			}

		}

	}

}


void MaquinaDeLlenado::iniciarAnimacion(Botella* botella)
{	

	this->AnimacionIniciada = true;

	//Solo para test
	//botella->etiquetar();
	this->botellaActual = botella;  
	
	this->estLiquido = EstadoLiquido::iniciando;
	this->acumuladorEnAnimacion = 0.0;

	//this->_testAnimacion = 0.0;
	
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


void MaquinaDeLlenado::dibujarLiquido()
{	


	if (!this->AnimacionIniciada)
		return;
	
	float color[3] = {0.1719, 0.0, 0.0};

	float alturaLiquido = 2.0;
	float lado = 0.1;

	btVector3 v1(0.0 , 0.0 , 0.0);
	btVector3 v2(lado , 0.0 , 0.0);
	btVector3 v3(0.0 , lado , 0.0);

	btVector3 altoLiquido(0.0,0.0,alturaLiquido);

	btVector3 nSup =  ( nivSupLiquido - 1.0) * altoLiquido ;

	btVector3 nInf = nivInfLiquido *(- altoLiquido );

	//Aqui se tralada hasta la punta de
	glTranslatef(0.0 - lado /3.0,2.0 - lado / 3.0,4.1);
	
	glBegin(GL_TRIANGLE_STRIP);
		
		//glVertex3f(0.,0.,0.);
		//glVertex3f(10.,0.,0.);
		//glVertex3f(0.,10.,0.);

		
		glVerticeVec3(v1 + nSup);
		glVerticeVec3(v1 + nInf);
		
		
		glVerticeVec3(v2 + nSup);
		glVerticeVec3(v2 + nInf);

		
		glVerticeVec3(v3 + nSup);
		glVerticeVec3(v3 + nInf);

		
		glVerticeVec3(v1 + nSup);
		glVerticeVec3(v1 + nInf);

	glEnd();
	
	//this->dibujarCuboUnitario();
	//glScalef(10.,10.,10.);
	//this->dibujarCuboUnitario();
}