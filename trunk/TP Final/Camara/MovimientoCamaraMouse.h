#ifndef MOVIMIENTOCAMARAMOUSE_H
#define MOVIMIENTOCAMARAMOUSE_H


#include "Rotador.h"
#include <gl/glut.h>
#define _USE_MATH_DEFINES
#include <math.h>

const float AnguloMinimoVertical = M_PI *1.0/6.0;
const float AnguloMaximoVertical = M_PI * 5.0/6.0;
const float pasoDeAngulo=0.01;

class MovimientoCamaraMouse
{
        public:
                MovimientoCamaraMouse(float* direccionCamara);
                MovimientoCamaraMouse(Rotador *rotador,float *direccionCamara);

                void movimientoMouse(int x,int y);
                void botonesMouse(int boton,int estado,int x,int y);

                float ultimoPhiCalculado();
                float ultimoThetaCalculado();

                virtual ~MovimientoCamaraMouse();
        private:
                void inicializar();

                Rotador *rotador; bool rotadorInstanciado;
                float phi,theta;
                float *direccionCamara;

                float difAngulo;

                int xAnterior,yAnterior;
                bool botonPresionado;

};

#endif // MOVIMIENTOCAMARAMOUSE_H
