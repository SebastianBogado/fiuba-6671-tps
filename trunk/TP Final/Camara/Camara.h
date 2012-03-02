#ifndef CAMARA_H
#define CAMARA_H

#include <math.h>
#include <gl/glut.h>
#include "VectoresCamara.h"
#include "Rotador.h"
#include "MovimientoCamaraMouse.h"

const float anguloRotacionHorizontal = 0.1;
const float anguloRotacionVertical = 0.1;
const float pasoDeDesplazamiento = 0.5;
const float pasoDeZoom = 0.5;

static float centroEscenaPanoramica[3] = {5.0,5.0,0.0};
static float posicionInicialEspectador[3] = {15.0,15.0,3.0};

const char teclaAdelante = 'w';
const char teclaAtras = 's';
const char teclaIzquierda = 'a';
const char teclaDerecha = 'd';

const char teclaCambioModo = 'c';

const char teclaZoomMas = '+';
const char teclaZoomMenos = '-';


class Camara
{
        public:
                Camara(float *atCamara,float * ojoCamara,float *vectorArriba);

                void controladorDeTeclado(char caracter);

                //Metodos para el manejo del Mouse

                void controladorBotonesMouse(int button, int state, int x, int y);
                void controladorMovMouse(int x, int y);

                virtual ~Camara();
        private:

                void incializarVectores();
                void actualizarVectores();

                //Metodos para el moviemiento en modo Espectador
                void movTecladoEspectador(char caracter);


                void moverseAdelante();
                void moverseAtras();



                void calcularAtCamara();

                //Metodos para el movimiento en modo Panorama

                void movTecladoPanorama(char caracter);

                void moverseArriba();
                void moverseAbajo();

                void zoomMas();
                void zoomMenos();

                void moverseVerticalmentePanorama(float angulo);

                //Metodos para ambos modos

                void girarIzquierda();
                void girarDerecha();

                void proyectarDireccionPlana(float *proyeccion);


                ///////////////////////
                //Variables de Clase//
                ///////////////////////

                VectoresCamara *espectador,*panorama,*actual;

                float *ojoCamara,*vectorArriba,*atCamara;
                //float *direccionCamara;

                MovimientoCamaraMouse *calculadorMovMouse;

                bool modoEspectador;

                Rotador rotador;

};

#endif // CAMARA_H
