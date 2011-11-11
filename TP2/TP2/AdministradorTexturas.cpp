#include "AdministradorTexturas.h"

extern bool VerMaterialTexturado;


AdministradorTexturas::AdministradorTexturas(void)
{
	this->numero_Punto=0;
	this->incremento=0.087;
	this->incX=this->incremento*2.0;
	this->incY=this->incremento;

	this->coordX=0.0;
	this->coordY=0.0;//this->incY;

	this->primerPuntoTapa=true;
	this->primerPunto=true;
	this->puntoCentroTapa=vec2(0.0);
}


void AdministradorTexturas::CargarTexturas(){

	
	this->textLoader.LoadTextureFromDisk("./Archivos de Recursos/Texturas de Objetos/LadrilloRustico.jpg",&this->textLadrillos);
	
	//this->textLoader.LoadTextureFromDisk("./Archivos de Recursos/Texturas de Objetos/sky_1.jpg",&this->textLadrillos);
	
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,this->textLadrillos.TextureID);	

	this->cargarParametrosTextura();

	this->textLoader2.LoadTextureFromDisk(  "./Archivos de Recursos/Texturas de Objetos/sky_1.jpg",&this->textCaja_Cielo);
	
	this->cargarParametrosTextura();
}


void AdministradorTexturas::cargarParametrosTextura(){

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

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

	glTexCoord2f(u,1-v);
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

	glEnable(GL_TEXTURE_2D);

	switch (tipo){
	case Ladrillos:	glBindTexture(GL_TEXTURE_2D,this->textLadrillos.TextureID); 
		break;

	case Caja_Cielo: glBindTexture(GL_TEXTURE_2D,this->textCaja_Cielo.TextureID); 
		break;
	default:  glBindTexture(GL_TEXTURE_2D,this->textCaja_Cielo.TextureID); break;
	}

	this->cargarParametrosTextura();

}

int AdministradorTexturas::getID(TipoTextura tipo){

	return this->textLadrillos.TextureID;

}

void AdministradorTexturas::generarCoordTextTapa(float *punto){

	float u=0.0,v=0.0;
	float angulo=0.0;
	vec2 centro=vec2(0.5,0.5);
	vec2 dir=vec2(punto[0],punto[1]);

	//dir=normalize(dir);
	//dir*=3.0;
	
	dir-=centro;
	glTexCoord2f(dir.x,dir.y);
	/*
	return;

	if (!this->primerPunto && this->primerPuntoTapa || vec2(punto[0],punto[1]) == this->puntoCentroTapa){
		
		this->puntoCentroTapa=vec2(punto[0],punto[1]);
		u=0.5;
		v=0.5;

		this->primerPuntoTapa=false;
	}else if(this->primerPunto){
		u=0.5;
		v=0.0;
		this->primerPunto=false;
	}
	else
	{

		dir= vec2(punto[0],punto[1])-this->puntoCentroTapa;
		
		dir = dir/sqrt(dir.x*dir.x + dir.y*dir.y);

		if (dir.y >= 0.0)
			angulo= acos(dir.x);
		else
			angulo= this->aritmTrig.dos_pi() - acos(dir.x);


		float pi=this->aritmTrig.pi();
		


		if (dir.y !=0.0 && dir.x/ dir.y <= 1.0)
			dir/=dir.y;
		else if (dir.x!=0.0 && dir.y/dir.x <=1.0)
			dir/=dir.x;

		dir/=2;

		dir+=centro;

		u=dir.x;
		v=dir.y;


		/*
		if (angulo >= pi/4.0 && angulo < 3.0*pi/4.0){

			v=1.0;
			dir=dir/dir.y;
			dir+=centro;
			u = dir.x;
			

		}else if(angulo >=3.0*pi/4.0 && angulo < 5.0*pi/4.0){
			u=0.0;
			dir=dir/dir.x;
			dir+=centro;
			v=dir.y;

		}else if(angulo >= 5.0*pi/4.0 && angulo < 7.0*pi/4.0){

			v=0.0;
			dir=dir/dir.y;
			dir+=centro;
			u=dir.x;

		}else if (angulo >= 7.0*pi/4.0 && angulo <  pi/4.0){

			u=1.0;
			dir=dir/dir.x;
			dir+=centro;
			v=dir.y;

		}
		
	}*/

	//glTexCoord2f(u,v);


}


void AdministradorTexturas::reiniciar(){

	this->primerPuntoTapa=true;
	this->primerPunto=true;

}


AdministradorTexturas::~AdministradorTexturas(void)
{
}