#ifndef ROTADOR_H
#define ROTADOR_H

#include <math.h>

#ifndef M_PI
	#define M_PI	3.14159265358979323846
#endif

#ifndef M_PI_2
	#define M_PI_2	1.57079632679489661923
#endif

class Rotador
{
        public:
                Rotador();

                void rotar(float *vector,float angulo,float *eje,float *res);
                void normalizar(float *vector);
                float norma(float *vector);

                void rotarEnX(float *vector,float angulo,float* res);
                void rotarEnY(float *vector,float angulo,float* res);
                void rotarEnZ(float *vector,float angulo,float* res);

                void sumar(float *p1,float *p2, float *res);
                void sumar(float *p1,float p2, float * res);
                void restar(float *p1,float *p2,float *res);
                void mult(float *p1,float p2,float *res);

                void inicializarVec(float *v,float x,float y, float z);

                float abs(float);

                void productoVectorial(float *v1,float *v2,float *res);
                void obtenerOrtogonalPlano(float *v1,float *res);

                void copiar(float *p1,float *res);

                float determinarThetaEje(float *eje);
                float determinarPhiEje(float *eje);

                virtual ~Rotador();
        private:

                void comprobarAngulo(float &angulo);
                float anguloAnterior,cosAngulo,senoAngulo;



};

#endif // ROTADOR_H
