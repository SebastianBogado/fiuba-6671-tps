#include "Camara.h"
#include <iostream>

using namespace std;
float Camara::posicionPorDefecto[3] = {15.0, 15.0, 5.0};
float Camara::atPorDefecto[3] = { 0.0,  0.0, 0.0};
float Camara::upPorDefecto[3] = { 0.0,  0.0, 1.0}; 
Camara* Camara::instancia = NULL;

Camara* Camara::getInstancia(){
	if (! instancia)
		Camara::instancia = new Camara();
	return Camara::instancia;
}
Camara::Camara()
{

                this->modoEspectador = false;
                this->incializarVectores();

                this->actual=this->panorama;

                this->atCamara = atPorDefecto ;
                this->ojoCamara = posicionPorDefecto;
                this->vectorArriba = upPorDefecto;


                this->actualizarVectores();

                this->calculadorMovMouse = new MovimientoCamaraMouse(&rotador,this->espectador->direccion);

}

void Camara::controladorBotonesMouse(int button,int state,int x,int y){

        if (!modoEspectador)
                return;

        this->calculadorMovMouse->botonesMouse(button,state,x,y);

}

void Camara::controladorMovMouse(int x, int y){

        if( !modoEspectador)
                return;

        //cout<<"X :"<<x<<"       "<<"Y: "<<y<<endl;

        this->calculadorMovMouse->movimientoMouse(x,y);

        float ejeRotacion[3];

        float dirPlana[3];

        this->proyectarDireccionPlana(&dirPlana[0]);

        this->rotador.obtenerOrtogonalPlano(&dirPlana[0],&ejeRotacion[0]);

        this->rotador.mult(&ejeRotacion[0],-1.0,&ejeRotacion[0]);

        float res[3];

        //
        //Se gira verticalmente
        //
        float phi = this->calculadorMovMouse->ultimoPhiCalculado();
        this->rotador.rotar(this->actual->direccion,phi,&ejeRotacion[0],&res[0]);
        this->rotador.copiar(&res[0],actual->direccion);

        this->rotador.rotar(actual->arriba,phi,&ejeRotacion[0],&res[0]);
        //this->rotador.copiar(&res[0],actual->arriba);


        //
        //Se gira Horizontalmente
        //
        float theta = this->calculadorMovMouse->ultimoThetaCalculado();

        float ejeZ[3]={0.0,0.0,1.0};

        this->rotador.rotar(actual->direccion,theta,&ejeZ[0],&res[0]);
        this->rotador.copiar(&res[0],actual->direccion);

        //this->rotador.rotar(actual->arriba,theta,&ejeZ[0],&res[0]);
        //this->rotador.copiar(&res[0],actual->arriba);


        //Calculo del vector arriba

        this->rotador.productoVectorial(actual->direccion,&ejeRotacion[0],actual->arriba);

        this->actualizarVectores();


}

void Camara::incializarVectores(){

        this->espectador = new VectoresCamara;

        this->rotador.copiar(&posicionInicialEspectador[0],this->espectador->posicionOjo);

        this->panorama = new VectoresCamara;
        this->rotador.copiar(&centroEscenaPanoramica[0], this->panorama->puntoDeVista );



}

void Camara::actualizarVectores(){

        this->rotador.copiar(this->actual->posicionOjo,this->ojoCamara);
        this->rotador.copiar(this->actual->arriba,this->vectorArriba);

        if(this->modoEspectador)
                this->calcularAtCamara();

        this->rotador.copiar(this->actual->puntoDeVista,this->atCamara);
}


void Camara::controladorDeTeclado(char caracter){
    caracter = tolower( caracter);
	switch (caracter){
	  case '2':
		  ojoCamara[0] = 0.0;
		  ojoCamara[1] = 0.0;
		  ojoCamara[2] = 15.0;

		  atCamara[0] = 0.0;
		  atCamara[1] = 0.0;
		  atCamara[2] = 0.0;

		  vectorArriba[0] = 0.0;
		  vectorArriba[1] = 1.0;
		  vectorArriba[2] = 0.0;
		  glutPostRedisplay();
		  break;

	  case '3':
		  ojoCamara[0] = 15.0;
		  ojoCamara[1] = 15.0;
		  ojoCamara[2] = 5.0;

		  atCamara[0] = 0.0;
		  atCamara[1] = 0.0;
		  atCamara[2] = 0.0;

		  vectorArriba[0] = 0.0;
		  vectorArriba[1] = 0.0;
		  vectorArriba[2] = 1.0;
		  glutPostRedisplay();
		  break;
	  default: break;
	}

        if ( caracter == teclaCambioModo){

                this->modoEspectador = ! this->modoEspectador;

                if (this->actual == this->espectador){
                        actual = this->panorama;
                }else{
                        actual = this->espectador;
                }

        }else{

                if (this->modoEspectador){
                        this->movTecladoEspectador(caracter);
                }else{
                        this->movTecladoPanorama(caracter);
                }

        }

        this->actualizarVectores();


}


void Camara::movTecladoEspectador(char caracter){


        //caracter = tolower(caracter);


        switch ( caracter){

        case teclaAdelante : this->moverseAdelante(); break;

        case teclaAtras : this->moverseAtras(); break;

        case teclaDerecha :   this->girarDerecha();   break;

        case teclaIzquierda:  this->girarIzquierda();    break;

        default: break;

        }



}

void Camara::moverseAdelante(){

        float aux[3];

        this->proyectarDireccionPlana(&aux[0]);

        this->rotador.mult(&aux[0],pasoDeDesplazamiento,&aux[0]);

        this->rotador.sumar(&aux[0],this->actual->posicionOjo,this->actual->posicionOjo);

}

void Camara::moverseAtras(){

        float aux[3];

        this->proyectarDireccionPlana(&aux[0]);

        this->rotador.mult(&aux[0],-pasoDeDesplazamiento,&aux[0]);

        this->rotador.sumar(&aux[0],this->actual->posicionOjo,this->actual->posicionOjo);

}

void Camara::girarIzquierda(){

        float aux[3];

        if (this->modoEspectador){

                //this->rotador.rotarEnZ(this->actual->direccion,anguloRotacionHorizontal,this->actual->direccion);
                float direccion[3],dirTraslado[3];
                this->proyectarDireccionPlana(&direccion[0]);
                this->rotador.obtenerOrtogonalPlano(&direccion[0],&dirTraslado[0]);

                this->rotador.mult(&dirTraslado[0],-1.0 * pasoDeDesplazamiento,&dirTraslado[0]);

                this->rotador.sumar(&dirTraslado[0],actual->posicionOjo,actual->posicionOjo);


        }else{



                this->rotador.restar(this->actual->posicionOjo,this->actual->puntoDeVista,&aux[0]);

                this->rotador.rotarEnZ(&aux[0],-anguloRotacionHorizontal,&aux[0]);

                this->rotador.sumar(&aux[0],this->actual->puntoDeVista,this->actual->posicionOjo);

                float dir[3];


                this->rotador.restar(actual->puntoDeVista,actual->posicionOjo,actual->direccion);
                this->rotador.normalizar(actual->direccion);


        }

}

void Camara::girarDerecha(){

        if (this->modoEspectador){

                //this->rotador.rotarEnZ(this->actual->direccion,-anguloRotacionHorizontal,this->actual->direccion);

                float direccion[3],dirTraslado[3];
                this->proyectarDireccionPlana(&direccion[0]);
                this->rotador.obtenerOrtogonalPlano(&direccion[0],&dirTraslado[0]);

                this->rotador.mult(&dirTraslado[0], pasoDeDesplazamiento,&dirTraslado[0]);

                this->rotador.sumar(&dirTraslado[0],actual->posicionOjo,actual->posicionOjo);

        }else{

                float aux[3];

                this->rotador.restar(this->actual->posicionOjo,this->actual->puntoDeVista,&aux[0]);

                this->rotador.rotarEnZ(&aux[0],anguloRotacionHorizontal,&aux[0]);

                this->rotador.sumar(&aux[0],this->actual->puntoDeVista,this->actual->posicionOjo);

                this->rotador.restar(actual->puntoDeVista,actual->posicionOjo,actual->direccion);
                this->rotador.normalizar(actual->direccion);

        }
}


void Camara::calcularAtCamara(){

        this->rotador.sumar(this->actual->posicionOjo,this->actual->direccion,this->actual->puntoDeVista);

}

/////////////////////////////////////////////////////////
//Metodos para el movimiento en modo Panorama//
/////////////////////////////////////////////////////////

void Camara::movTecladoPanorama(char caracter){


        switch (caracter){

        case teclaZoomMas : this->zoomMas(); break;

        case teclaZoomMenos: this->zoomMenos(); break;

        case teclaAdelante : this->moverseArriba(); break;

        case teclaAtras: this->moverseAbajo(); break;

        case teclaIzquierda : this->girarIzquierda(); break;

        case teclaDerecha: this->girarDerecha(); break;

        default : break;

        }


}


void Camara::zoomMas(){

        float aux[3];

        this->rotador.restar(this->atCamara,this->actual->posicionOjo,this->actual->direccion);

        this->rotador.normalizar(this->actual->direccion);

        this->rotador.mult(this->actual->direccion,pasoDeZoom,&aux[0]);

        this->rotador.sumar(this->actual->posicionOjo,&aux[0],this->actual->posicionOjo);

}

void Camara::zoomMenos(){

        float aux[3];

        this->rotador.restar(this->atCamara,this->actual->posicionOjo,this->actual->direccion);

        this->rotador.normalizar(this->actual->direccion);

        this->rotador.mult(this->actual->direccion,-pasoDeZoom,&aux[0]);

        this->rotador.sumar(this->actual->posicionOjo,&aux[0],this->actual->posicionOjo);

}


void Camara::moverseAbajo(){

        float angulo = 2.0*pasoDeAngulo;

        this->moverseVerticalmentePanorama(angulo);

}

void Camara::moverseArriba(){

        float angulo = -2.0*pasoDeAngulo;

        this->moverseVerticalmentePanorama(angulo);

}


void Camara::moverseVerticalmentePanorama(float angulo){

        if ( rotador.abs(actual->posicionOjo[2] - actual->puntoDeVista[2]) <= 1.0 && angulo >= 0.0)
                return;

        if ( (rotador.abs(actual->posicionOjo[0] - actual->puntoDeVista[0]) < 1.0 &&  rotador.abs(actual->posicionOjo[1] - actual->puntoDeVista[1])< 1.0) && angulo <=0.0)
                return;

        float traslacion[3];

        this->rotador.restar(actual->posicionOjo,actual->puntoDeVista,&traslacion[0]);
        this->rotador.sumar(actual->posicionOjo,&traslacion[0],actual->posicionOjo);


        float dirPlana[3],ejeRotacion[3],ejeZ[3]={0.0,0.0,1.0},res[3];

        this->proyectarDireccionPlana(&dirPlana[0]);

        this->rotador.productoVectorial(&dirPlana[0],&ejeZ[0],&ejeRotacion[0]);

        this->rotador.rotar(actual->posicionOjo,angulo,&ejeRotacion[0],&res[0]);

        this->rotador.mult(&traslacion[0],-1.0,&traslacion[0]);

        this->rotador.sumar(&traslacion[0],&res[0],actual->posicionOjo);
        //this->rotador.sumar(&res[0],actual->puntoDeVista,actual->posicionOjo);

        //this->rotador.copiar(&res[0],this->actual->posicionOjo);

}

void Camara::proyectarDireccionPlana(float *proyeccion){

        proyeccion[0]=this->actual->direccion[0];
        proyeccion[1]=this->actual->direccion[1];
        proyeccion[2]=0.0;

        this->rotador.normalizar(proyeccion);

}

vec3 Camara::eye(){ return vec3(ojoCamara[0], ojoCamara[1], ojoCamara[2]); }
vec3 Camara::at(){ return vec3(atCamara[0], atCamara[1], atCamara[2]); }
vec3 Camara::up(){ return vec3(vectorArriba[0], vectorArriba[1], vectorArriba[2]); }

Camara::~Camara()
{
        delete espectador;
        delete panorama;
}
