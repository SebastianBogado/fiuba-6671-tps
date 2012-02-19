#include "LamparaDeTecho.h"


LamparaDeTecho::LamparaDeTecho(void)
{
	//this->posicionObjeto = new float[3];

	this->inicializarVertices();

}

LamparaDeTecho::LamparaDeTecho(ObjetoGraficoCubico *habitacion)
{
	//this->posicionObjeto = new float[3];

	this->cuarto = habitacion;
	
	this->inicializarVertices();

}

void LamparaDeTecho::graficar(){

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glTranslatef(cuarto->vectorPosicion()[0],cuarto->vectorPosicion()[1],cuarto->vectorPosicion()[2]);

				
		glTranslatef(cuarto->valorLargo() / 3.0,cuarto->valorAncho() / 2.0,cuarto->valorAltura());	
		this->graficarLamparaSimple();
		
		glTranslatef(cuarto->valorLargo() / 3.0,0.0,0.0);	
		this->graficarLamparaSimple();

	glPopMatrix();

}


void LamparaDeTecho::inicializarVertices(){

	this->largo = 1.5;
	this->ancho = 0.5;
	this->alturaCampana = 0.5;
	this->grosor = 0.2;

	this->cantVertices = 8;

	this->vertices = new float*[cantVertices];

	for (int i=0; i < cantVertices ; i++)
		vertices[i] = new float[3];

	this->actualizarVertices();

}

void LamparaDeTecho::actualizarVertices(){

	this->inicializarVector(this->vertices[0],0.0,0.0,0.0);
	this->inicializarVector(this->vertices[1],grosor,0.0,0.0);
	this->inicializarVector(this->vertices[2],grosor,grosor,0.0);
	this->inicializarVector(this->vertices[3],0.0,grosor,0.0);
	
	this->inicializarVector(this->vertices[4],0.0,0.0,-largo);
	this->inicializarVector(this->vertices[5],grosor,0.0,-largo);
	this->inicializarVector(this->vertices[6],grosor,grosor,-largo);
	this->inicializarVector(this->vertices[7],0.0,grosor,-largo);

}

void LamparaDeTecho::definirHabitacion(ObjetoGraficoCubico *habitacion){

	this->cuarto= habitacion;

}

void LamparaDeTecho::graficarLamparaSimple(){

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glDisable(GL_LIGHTING);
		
		glBegin(GL_QUADS);
			
			glColor3f(0.5,0.5,0.5);
			glVertex3fv(vertices[1]);
			glVertex3fv(vertices[5]);
			glVertex3fv(vertices[6]);
			glVertex3fv(vertices[2]);

			//glColor3f(0.0,1.0,0.0);
			glVertex3fv(vertices[2]);
			glVertex3fv(vertices[6]);
			glVertex3fv(vertices[7]);
			glVertex3fv(vertices[3]);

			//glColor3f(0.0,0.0,1.0);
			glVertex3fv(vertices[3]);
			glVertex3fv(vertices[7]);
			glVertex3fv(vertices[4]);
			glVertex3fv(vertices[0]);

			//4ta tapa
			//glColor3f(1.0,1.0,0.0);
			glVertex3fv(vertices[0]);
			glVertex3fv(vertices[4]);
			glVertex3fv(vertices[5]);
			glVertex3fv(vertices[1]);

			//5ta tapa
			//glColor3f(1.0,0.0,1.0);
			glVertex3fv(vertices[6]);
			glVertex3fv(vertices[7]);
			glVertex3fv(vertices[4]);
			glVertex3fv(vertices[5]);


			//////////////////////////
			//Generacion de la Campana
			//////////////////////////

			//6ta tapa la del piso, que resultaria el piso
			//glColor3f(0.8,0.8,0.8);

			glVertex3fv(vertices[5]);
			glVertex3f(vertices[5][0]+ancho,vertices[5][1]-ancho,vertices[5][2]-alturaCampana);
			glVertex3f(vertices[6][0]+ancho,vertices[6][1]+ancho,vertices[6][2]-alturaCampana);
			glVertex3fv(vertices[6]);


			glVertex3fv(vertices[6]);
			glVertex3f(vertices[6][0]+ancho,vertices[6][1]+ancho,vertices[6][2]-alturaCampana);
			glVertex3f(vertices[7][0]-ancho,vertices[7][1]+ancho,vertices[7][2]-alturaCampana);
			glVertex3fv(vertices[7]);


			glVertex3fv(vertices[7]);
			glVertex3f(vertices[7][0]-ancho,vertices[7][1]+ancho,vertices[7][2]-alturaCampana);
			glVertex3f(vertices[4][0]-ancho,vertices[4][1]-ancho,vertices[4][2]-alturaCampana);
			glVertex3fv(vertices[4]);

			glVertex3fv(vertices[4]);
			glVertex3f(vertices[4][0]-ancho,vertices[4][1]-ancho,vertices[4][2]-alturaCampana);
			glVertex3f(vertices[5][0]+ancho,vertices[5][1]-ancho,vertices[5][2]-alturaCampana);
			glVertex3fv(vertices[5]);


		glEnd();
	glPopMatrix();
}

void LamparaDeTecho::actualizarAtributos(){ }

void LamparaDeTecho::aplicarShader(){}

void LamparaDeTecho::detenerShader(){}

LamparaDeTecho::~LamparaDeTecho(void)
{
	for (int i=0;i<this->cantVertices ; i++)
		delete[] vertices[i];

	delete[] vertices;

}
