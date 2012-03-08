#include "MaquinaTapadora.h"


MaquinaTapadora::MaquinaTapadora(void)
{
	this->posTramoEnCinta = 0.872;

	this->curvaPiezaBrazoMovil = new Circunferencia(0.25);

	this->ancho = 1.5;
	this->largo = 1.5;
	this->alto = 5.0;

	this->alturaDeMaquina = alto;

	this->posicionObjeto = new float[3];
	this->inicializarVector(posicionObjeto,5.5,21.5,0.0);

	this->posDeObjetoAnimado = new float[3];
	this->pasoDeAnimacion = 0.1;
	this->acumuladorEnAnimacion = 0.0;
	this->desplazamientoBrazoMovil = 0.0;
	this->tiempoMaximoDeAnimacion = 3.5;
	this->pasoDesplazamientoDeBrazo = 0.065;

	this->botellaActual = NULL;

	this->sentidoDeBrazoMovilCambiado = false;

	this->inicializarVertices();
}


void MaquinaTapadora::definirMateriales()
{


}

void MaquinaTapadora::graficar()
{

	float anchoHoyo = 0.6,altoHoyo = 2.0;
	vec2 posHoyo(0.5,0.78);


	float normal[3];
	this->definirMateriales();

	glPushMatrix();
	//glTranslatef(posicionObjeto[0],posicionObjeto[1],posicionObjeto[2]);
	this->posicionarObjeto(); 
	glRotatef(-90.0,0.0,0.0,1.0);

	glEnable(GL_LIGHTING);

		this->inicializarVector(normal,0.0,-1.0,0.0);
		this->dibujarPared(normal,0,1,4,5);
	//	this->dibujarParedHueca(normal,0,1,4,5,altoHoyoEntrada,anchoHoyoEntrada,posHent,0.6);

		this->inicializarVector(normal,1.0,0.0,0.0);
		this->dibujarPared(normal,1,2,5,6);
	//	this->dibujarParedHueca(normal,1,2,5,6,altoHoyoSalida,anchoHoyoSalida,posHsal,0.8);


		this->inicializarVector(normal,0.0,1.0,0.0);
		this->dibujarParedHueca(normal,2,3,6,7,altoHoyo,anchoHoyo,posHoyo,0.3);
	//	this->dibujarPared(normal,2,3,6,7);

		this->inicializarVector(normal,-1.0,0.0,0.0);
	//	this->dibujarParedHueca(normal,3,0,7,4,altoHoyoEntrada,anchoHoyoEntrada,vec2(0.5,0.4),0.8);
		this->dibujarPared(normal,3,0,7,4);

		this->inicializarVector(normal,0.0,0.0,1.0);
		this->dibujarPared(normal,4,5,7,6);

		this->dibujarBrazoMovil();

	glPopMatrix();


}

void MaquinaTapadora::actualizarAtributos()
{
	if (this->AnimacionIniciada)
	{

		this->acumuladorEnAnimacion += this->pasoDeAnimacion;

		this->desplazamientoBrazoMovil += this->pasoDesplazamientoDeBrazo;

		//Seria como el tiempo de animacion
		if(acumuladorEnAnimacion > tiempoMaximoDeAnimacion)
		{
			this->AnimacionIniciada = false;
			this->acumuladorEnAnimacion = 0.0;
			this->sentidoDeBrazoMovilCambiado = false;
			this->pasoDesplazamientoDeBrazo =-this->pasoDesplazamientoDeBrazo;
			this->desplazamientoBrazoMovil = 0.0;

		}else if (this->acumuladorEnAnimacion >= tiempoMaximoDeAnimacion / 2.0 && !this->sentidoDeBrazoMovilCambiado){
			this->sentidoDeBrazoMovilCambiado = true;
			this->pasoDesplazamientoDeBrazo = -this->pasoDesplazamientoDeBrazo;
			if(this->botellaActual)
				this->botellaActual->tapar();
		}
			

	}

}

void MaquinaTapadora::iniciarAnimacion(Botella *botella)
{
	this->botellaActual = botella;

	this->AnimacionIniciada = true;

	this->acumuladorEnAnimacion = 0.0;

}

bool MaquinaTapadora::animacionFinalizada()
{
	return !this->AnimacionIniciada;

}

void MaquinaTapadora::dibujarBrazoMovil()
{
	
	glTranslatef(	this->valorLargoEnX() /2.0,
					this->valorLargoEnY() * 0.9,
					0.9 * this->alturaDeMaquina - this->desplazamientoBrazoMovil);
	//glRotatef(90.0,0.0,0.0,1.0);

	float largo = 1.4 ,ladoRectangulo=0.25;
	
	glBegin(GL_TRIANGLE_STRIP);

		glVertex3f( -ladoRectangulo,0.0,-ladoRectangulo);
		glVertex3f( -ladoRectangulo,largo,-ladoRectangulo);

		glVertex3f(-ladoRectangulo,0.0,ladoRectangulo);
		glVertex3f(-ladoRectangulo,largo,ladoRectangulo);

		glVertex3f(ladoRectangulo,0.0, ladoRectangulo);
		glVertex3f(ladoRectangulo,largo, ladoRectangulo);

		glVertex3f(ladoRectangulo,0.0,-ladoRectangulo);
		glVertex3f(ladoRectangulo,largo,-ladoRectangulo);

		glVertex3f(-ladoRectangulo,0.0,-ladoRectangulo);
		glVertex3f(-ladoRectangulo,largo,-ladoRectangulo);

	glEnd();

	float largoCilindro = 0.7;

	glTranslatef(0.0,largo,-largoCilindro /2.0);
	glRotatef(90,1.0,0.0,0.0);

	int cantTramos = this->curvaPiezaBrazoMovil->cantidadDeTramos();
	int cantDiscret = 8;

	vec3 altura(0.0,largoCilindro,0.0);

	vec3 vertice;

	//Se dibuja la tapa del cilindro
	glBegin(GL_TRIANGLE_FAN);

	this->glVerticeVec3(altura);

	for (int i=0; i <= cantDiscret; i++)
	{
		vertice = this->curvaPiezaBrazoMovil->evaluar((float)(i * cantTramos) /(float) (cantDiscret));
		this->glVerticeVec3(vertice);

	}
	glEnd();



	//Se dibujan los dos cilindros el chico y el grande, uno dentro del otro
//	for (int j=0; j < 2 ; j++)
//	{	
		glBegin(GL_TRIANGLE_STRIP);
		for (int i=0; i <= cantDiscret; i++)
		{
			vertice = this->curvaPiezaBrazoMovil->evaluar((float)(i * cantTramos) /(float) (cantDiscret));
			this->glVerticeVec3(vertice);
			this->glVerticeVec3(vertice + altura); 

		}
		glEnd();

//		glTranslatef(0.0,-largoCilindro /2.0 ,0.0);
//		glScalef(0.8,1.1,0.8);
		
//	}

}

MaquinaTapadora::~MaquinaTapadora(void)
{
	delete[] this->posDeObjetoAnimado;
	delete this->curvaPiezaBrazoMovil;
	delete[] this->posicionObjeto;
}
