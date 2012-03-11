#include "LamparaDeTecho.h"

LamparaDeTecho::LamparaDeTecho(void)
{
	//this->posicionObjeto = new float[3];

	this->inicializarVertices();

}

LamparaDeTecho::LamparaDeTecho(ObjetoGraficoCubico *habitacion)
{
	//this->posicionObjeto = new float[3];

	//this->cuarto = habitacion;
	this->definirHabitacion(habitacion);
	
	this->inicializarVertices();
}

void LamparaDeTecho::graficar(){


	aplicarPhong();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glTranslatef(cuarto->vectorPosicion()[0],cuarto->vectorPosicion()[1],cuarto->vectorPosicion()[2]);
		

		if(rotarCamaras){

			//glTranslatef(cuarto->valorLargo() /2.0,);

			glRotatef(90.0,0.0,0.0,1.0);
			glTranslatef(0.0,-ladoMenorCuarto,0.0);

		}

		for (float i=1.0; i <= 3.1; i=i+1){
			glPushMatrix();

			glTranslatef(i*ladoMayorCuarto / 4.0 , ladoMenorCuarto / 3.0,cuarto->valorAltura());	
			this->graficarLamparaSimple();
		
			glTranslatef(0.0,ladoMenorCuarto / 3.0 ,0.0);	
			this->graficarLamparaSimple();

			glPopMatrix();
		}

	glPopMatrix();

}


void LamparaDeTecho::inicializarVertices(){

	this->largo = 1.3;
	this->ancho = 0.5;
	this->alturaCampana = 0.5;
	this->grosor = 0.2;

	this->cantVertices = 8;

	this->vertices = new float*[cantVertices];

	for (int i=0; i < cantVertices ; i++)
		vertices[i] = new float[3];

	this->actualizarVertices();

	this->definirMateriales();
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

	rotarCamaras = (cuarto->valorLargo() < cuarto->valorAncho());

	if (rotarCamaras){
		ladoMayorCuarto = cuarto->valorAncho();
		ladoMenorCuarto = cuarto->valorLargo();
	}else{
		ladoMayorCuarto = cuarto->valorLargo();
		ladoMenorCuarto = cuarto->valorAncho();

	}

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

vec3 LamparaDeTecho::posicionDeLuz(int indice)
{
	vec3 res(	cuarto->vectorPosicion()[0],
				cuarto->vectorPosicion()[1],
				cuarto->vectorPosicion()[2] + cuarto->valorAltura() - this->largo);

	vec3 parcial;

	if (rotarCamaras)
	{

		if ( indice < 3)
		{
			parcial = vec3 (cuarto->valorLargoEnX() / 3.0 ,	(indice + 1.0 ) * cuarto->valorLargoEnY() / 4.0 ,	0.0);
			
		}
		else if(indice < 6) 
		{
			parcial = vec3 (cuarto->valorLargoEnX()* 2.0 / 3.0 , (indice + - 2.0 ) * cuarto->valorLargoEnY() / 4.0 ,	0.0);
		}

	}
	else
	{
		if ( indice < 3)
		{
			parcial = vec3 ((indice + 1.0 ) * cuarto->valorLargoEnX() / 4.0 , cuarto->valorLargoEnY() / 3.0 ,	0.0);
		}
		else if(indice < 6) 
		{
			parcial = vec3 ((indice - 2.0 ) * cuarto->valorLargoEnX() / 4.0 , cuarto->valorLargoEnY() * 2.0/ 3.0 ,	0.0);
		}


	}

	res +=parcial;


	return res;	

	

}

int LamparaDeTecho::cantidadDeLuces()
{
	return 6;
}


LamparaDeTecho::~LamparaDeTecho(void)
{
	for (int i=0;i<this->cantVertices ; i++)
		delete[] vertices[i];

	delete[] vertices;

}

void LamparaDeTecho::definirMateriales(){
	material.colorAmb = vec3(0.8, 0.8, 0.8);		
	material.colorDif = vec3(0.8, 0.8, 0.8);
	material.colorEspec = vec3(0.2, 0.2, 0.2);
	material.brillo = 4.0;
}