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


        if (boton == GLUT_LEFT_BUTTON) { //esto hace que sea sólo para el botón izquierdo. En realidad no funciona, no sé por qué :P, la cámara la movés con el botón que quieras
                if (estado == GLUT_UP) { //cuando se levanta el botón me olvido de mover la cámara
                   xAnterior = 0;
                    yAnterior = 0;
                    this->botonPresionado = false;
                }
                else  { //si se aprieta el botón, registro la posición actual del mouse para calcular más tarde la nueva posición
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
