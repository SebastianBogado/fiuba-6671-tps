#include "MovimientoCamaraMouse.h"

#include <iostream>

using namespace std;

MovimientoCamaraMouse::MovimientoCamaraMouse(float *direccionCamara)
{
        this->rotador = new Rotador();
        this->rotadorInstanciado = true;

        this->inicializar();
}

MovimientoCamaraMouse::MovimientoCamaraMouse(Rotador *rotador,float *direccionCamara)
{
        this->rotador = rotador;
        this->rotadorInstanciado = false;
        this->direccionCamara = direccionCamara;

        this->inicializar();

}

void MovimientoCamaraMouse::inicializar(){

        this->botonPresionado = false;
        xAnterior =0;
        yAnterior = 0;
}


void MovimientoCamaraMouse::movimientoMouse(int x,int y){

        float dX=0.0,dY=0.0;

        if (this->botonPresionado);
                dX = x - xAnterior;
                dY = y - yAnterior;

        //DEbug

     //   cout<<"x: "<<x<<"       Xant:"<<xAnterior<<"    dX:"<<dX<<endl;
      //  cout<<"y: "<<x<<"       Yant:"<<xAnterior<<"    dy:"<<dY<<endl<<endl;



        float dPhi = dY * pasoDeAngulo;
        theta = dX * pasoDeAngulo;

        float phiDir = this->rotador->determinarPhiEje(direccionCamara);

        float phiParcial =dPhi + phiDir;

        if (    phiParcial <= AnguloMaximoVertical && phiParcial >= AnguloMinimoVertical)
                phi = dPhi;

        xAnterior = x;
        yAnterior = y;


}

void MovimientoCamaraMouse::botonesMouse(int boton,int estado,int x,int y){


        if (boton == GLUT_LEFT_BUTTON) { //esto hace que sea s�lo para el bot�n izquierdo. En realidad no funciona, no s� por qu� :P, la c�mara la mov�s con el bot�n que quieras
                if (estado == GLUT_UP) { //cuando se levanta el bot�n me olvido de mover la c�mara
                   xAnterior = 0;
                    yAnterior = 0;
                    this->botonPresionado = false;
                }
                else  { //si se aprieta el bot�n, registro la posici�n actual del mouse para calcular m�s tarde la nueva posici�n
                    xAnterior = x;
                    yAnterior = y;
                    this->botonPresionado = true;
                }
            }

}

float MovimientoCamaraMouse::ultimoPhiCalculado(){
        float res = phi;

        phi = 0.0;

        return res;
}

float MovimientoCamaraMouse::ultimoThetaCalculado(){
        return -this->theta;

}

MovimientoCamaraMouse::~MovimientoCamaraMouse()
{
        if(this->rotadorInstanciado)
                delete rotador;
}
