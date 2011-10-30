#include "AdministradorTexturas.h"


AdministradorTexturas::AdministradorTexturas(void)
{
	this->numero_Punto=0;
	this->incremento=0.087;
	this->incX=this->incremento*2.0;
	this->incY=this->incremento;

	this->coordX=0.0;
	this->coordY=0.0;//this->incY;
}


void AdministradorTexturas::CargarTexturas(){


	//this->textLoader.LoadTextureFromDisk("./Archivos de Recursos/Texturas Objetos/ladrilloRustico.jpg",&this->textLadrillos);

	//Carga de Texturas para Botones de Objetos

	this->textLoader.LoadTextureFromDisk("./Archivos de recursos/Texturas de Botones/objEsfera.jpg",&this->objTexture[0]);
	/*this->textLoader.LoadTextureFromDisk("./Archivos de recursos/Texturas de Botones/objCubo.jpg",&this->objTexture[1]);
	this->textLoader.LoadTextureFromDisk("./Archivos de recursos/Texturas de Botones/objToroide.jpg",&this->objTexture[2]);
	this->textLoader.LoadTextureFromDisk("./Archivos de recursos/Texturas de Botones/objCilindro.jpg",&this->objTexture[3]);


	//Carga de Texturas para Botones de Materiales

	this->textLoader.LoadTextureFromDisk("./Archivos de recursos/Texturas de Botones/matBrillante.jpg",&this->matTexture[0]);
	this->textLoader.LoadTextureFromDisk("./Archivos de recursos/Texturas de Botones/matTexturado.jpg",&this->matTexture[1]);
	this->textLoader.LoadTextureFromDisk("./Archivos de recursos/Texturas de Botones/matReflectivo.jpg",&this->matTexture[2]);
	this->textLoader.LoadTextureFromDisk("./Archivos de recursos/Texturas de Botones/matSemimate.jpg",&this->matTexture[3]);


	//Carga de Texturas para Botones de Efectos

	this->textLoader.LoadTextureFromDisk("./Archivos de recursos/Texturas de Botones/efecRetorcer.jpg",&this->efecTexture[0]);
	this->textLoader.LoadTextureFromDisk("./Archivos de recursos/Texturas de Botones/efecRuido.jpg",&this->efecTexture[1]);
	this->textLoader.LoadTextureFromDisk("./Archivos de recursos/Texturas de Botones/efecDoblar.jpg",&this->efecTexture[2]);
	this->textLoader.LoadTextureFromDisk("./Archivos de recursos/Texturas de Botones/efecEsferizar.jpg",&this->efecTexture[3]);

	*/
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,this->textLadrillos.TextureID);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	
}


void AdministradorTexturas::generarCoordText(){

	float esc=1.0;


	if (this->numero_Punto==1)
		this->sumarVecSup();

	glTexCoord2f(this->coordX*esc,this->coordY*esc);

	this->numero_Punto++;

	if (this->numero_Punto > 1 ){
		this->numero_Punto=0;
		this->sumarVecInf();
	}

}

AdministradorTexturas* AdministradorTexturas::getInstancia(){

	if(!instanciado){
		instancia = new AdministradorTexturas;
		instanciado = true;
	}

	return instancia;

}

void AdministradorTexturas::sumarVecSup(){
	
	//this->coordX=+this->incX;
	this->coordY+=this->incY;

}

void AdministradorTexturas::sumarVecInf(){
	this->coordX+=this->incX;
	this->coordY-=this->incY;
}

void AdministradorTexturas::comprobarPuntos(){

	if(this->coordX > 1.0){
		this->coordX = 0.0;
		this->coordY+=this->incY;
	}


}


void AdministradorTexturas::elegirTexturaBoton(TipoTexturaBoton tipo){

	//Seleccion de Textura para Objetos

	if (tipo == objEsfera)
		glBindTexture(GL_TEXTURE_2D,this->objTexture[0].TextureID);

	if (tipo == objCubo)
		glBindTexture(GL_TEXTURE_2D,this->objTexture[1].TextureID);

	if (tipo == objToroide)
		glBindTexture(GL_TEXTURE_2D,this->objTexture[2].TextureID);

	if (tipo == objCilindro)
		glBindTexture(GL_TEXTURE_2D,this->objTexture[3].TextureID);

	//Seleccion de Textura de Materiales

	if(tipo == matBrillante)
		glBindTexture(GL_TEXTURE_2D,this->matTexture[0].TextureID);

	if(tipo == matTexturado)
		glBindTexture(GL_TEXTURE_2D,this->matTexture[1].TextureID);
	
	if(tipo == matReflectivo)
		glBindTexture(GL_TEXTURE_2D,this->matTexture[2].TextureID);

	if(tipo == matSemimate)
		glBindTexture(GL_TEXTURE_2D,this->matTexture[3].TextureID);


	//Seleccion para Textura de Efecto

	if(tipo == efecRetorcer)
		glBindTexture(GL_TEXTURE_2D,this->efecTexture[0].TextureID);

	if(tipo == efecRuido)
		glBindTexture(GL_TEXTURE_2D,this->efecTexture[1].TextureID);

	if(tipo == efecDoblar)
		glBindTexture(GL_TEXTURE_2D,this->efecTexture[2].TextureID);

	if(tipo == efecEsferizar)
		glBindTexture(GL_TEXTURE_2D,this->efecTexture[3].TextureID);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
}


void AdministradorTexturas::generarCoordTextBoton(float u,float v){

	glTexCoord2f(u,v);

}

AdministradorTexturas::~AdministradorTexturas(void)
{
}
