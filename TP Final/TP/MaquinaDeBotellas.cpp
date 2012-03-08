#include "MaquinaDeBotellas.h"


MaquinaDeBotellas::MaquinaDeBotellas(void)
{	

	this->posTramoEnCinta = -1.0;

	this->posicionObjeto = new float[3];

	this->inicializarVector(posicionObjeto,13.5,6.,0.);

	this->ancho = 6.0;
	this->largo = 4.0;
	this->alto = 5.0;

	this->alturaDeMaquina = alto;

	this->inicializarVertices();

	this->posDeObjetoAnimado = new float[3];
	//this->inicializarVector(this->posDeObjetoAnimado,posicionObjeto[0]+5,posicionObjeto[1],posicionObjeto[2]);
														

}

void MaquinaDeBotellas::definirMateriales()
{


}



void MaquinaDeBotellas::graficar(){

	//this->graficarBase();

	float normal[3];

	this->definirMateriales();

	glPushMatrix();
	//glTranslatef(posicionObjeto[0],posicionObjeto[1],posicionObjeto[2]);
	this->posicionarObjeto();

		this->inicializarVector(normal,0.0,-1.0,0.0);
		this->dibujarPared(normal,0,1,4,5);

		this->inicializarVector(normal,1.0,0.0,0.0);
		this->dibujarPared(normal,1,2,5,6);
	//	this->dibujarParedHueca(normal,1,2,5,6,1.6,2.2,vec2(0.5,0.5),0.8);

		this->inicializarVector(normal,0.0,1.0,0.0);
		this->dibujarParedHueca(normal,2,3,6,7,2.5,2.0,vec2(0.5,0.6),0.5);
	//	this->dibujarPared(normal,2,3,6,7);

		this->inicializarVector(normal,-1.0,0.0,0.0);
	//	this->dibujarPeredHueca(normal,3,0,7,4,1.6,2.2,vec2(0.5,0.5),0.8);
		this->dibujarPared(normal,3,0,7,4);

		this->inicializarVector(normal,0.0,0.0,1.0);
		this->dibujarPared(normal,4,5,7,6);

	glPopMatrix();

	if (this->AnimacionIniciada)
	{
		float color[3]={1.0,0.0,0.0};
		glPushMatrix();
		glTranslatef(this->posicionObjeto[0],this->posicionObjeto[1],this->posicionObjeto[2]+this->alto);
		this->dibujarPiramide(color);

		glPopMatrix();
	}

	/*
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glDisable(GL_LIGHTING);
		glTranslatef(posicionObjeto[0],posicionObjeto[1],posicionObjeto[2]);
		
		glBegin(GL_QUADS);
			
			//Se dibuja la MAquina
			glColor3f(1.0,0.0,0.0);
			glVertex3fv(vertices[1]);
			glVertex3fv(vertices[2]);
			glVertex3fv(vertices[6]);
			glVertex3fv(vertices[5]);

			glColor3f(0.0,1.0,0.0);
			glVertex3fv(vertices[2]);
			glVertex3fv(vertices[3]);
			glVertex3fv(vertices[7]);
			glVertex3fv(vertices[6]);

			glColor3f(0.0,0.0,1.0);
			glVertex3fv(vertices[3]);
			glVertex3fv(vertices[0]);
			glVertex3fv(vertices[4]);
			glVertex3fv(vertices[7]);

			//4ta tapa
			glColor3f(1.0,1.0,0.0);
			glVertex3fv(vertices[0]);
			glVertex3fv(vertices[4]);
			glVertex3fv(vertices[5]);
			glVertex3fv(vertices[1]);

			//5ta tapa
			glColor3f(1.0,0.0,1.0);
			glVertex3fv(vertices[6]);
			glVertex3fv(vertices[7]);
			glVertex3fv(vertices[4]);
			glVertex3fv(vertices[5]);

			//6ta tapa la del piso, no parece necesaria

		glEnd();
	glPopMatrix();*/

}

void MaquinaDeBotellas::aplicarShader(){


}

void MaquinaDeBotellas::detenerShader(){



}

void MaquinaDeBotellas::actualizarAtributos(){

	if (this->AnimacionIniciada)
	{
		this->_testAnimacion += this->_pasoTest;

		this->AnimacionIniciada = this->_testAnimacion > 100.0;
	}

}



void MaquinaDeBotellas::iniciarAnimacion(Botella* botella)
{
	this->AnimacionIniciada = true;


	//botella->etiquetar();

	this->_pasoTest = 1.0;
	this->_testAnimacion = 0.0;



}

bool MaquinaDeBotellas::animacionFinalizada()
{

	//return !this->AnimacionIniciada;
	return true;

}


MaquinaDeBotellas::~MaquinaDeBotellas(void)
{

	delete[] this->posicionObjeto;
	delete[] this->posDeObjetoAnimado;

}
