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


	this->textLoader.LoadTextureFromDisk("./Archivos de Recursos/Texturas de Objetos/LadrilloRustico.jpg",&this->textLadrillos);
	//this->textLoader.LoadTextureFromDisk("./Archivos de Recursos/Texturas de Objetos/sky_1.jpg",&this->textLadrillos);
	this->textLoader.LoadTextureFromDisk(  "./Archivos de Recursos/Texturas de Objetos/sky_1.jpg",&this->textCaja_Cielo);
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,this->textLadrillos.TextureID);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	
}



AdministradorTexturas* AdministradorTexturas::getInstancia(){

	if(!instanciado){
		instancia = new AdministradorTexturas;
		instanciado = true;
	}

	return instancia;

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

void AdministradorTexturas::generarCoordText(float* punto){

	this->aritmTrig.puntoActual(punto);

	float v = this->aritmTrig.calcularPhi() / this->aritmTrig.pi();;

	float u = this->aritmTrig.calcularTheta() / this->aritmTrig.dos_pi();

	glTexCoord2f(u,v);
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




void AdministradorTexturas::elegirTextura(TipoTextura tipo){

	switch (tipo){
	case Ladrillos:	glBindTexture(GL_TEXTURE_2D,this->textLadrillos.TextureID); 
		break;

	case Caja_Cielo: glBindTexture(GL_TEXTURE_2D,this->textCaja_Cielo.TextureID); 
		break;
	default: break;
	}
}


int AdministradorTexturas::getID(TipoTextura tipo){

	return this->textLadrillos.TextureID;

}

AdministradorTexturas::~AdministradorTexturas(void)
{
}