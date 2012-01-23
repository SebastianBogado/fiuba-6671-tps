#ifndef VECTORESCAMARA_H
#define VECTORESCAMARA_H


class VectoresCamara
{
        public:
                VectoresCamara();
                virtual ~VectoresCamara();

                float *posicionOjo;
                float *direccion;
                float *arriba;
                float *puntoDeVista;

};

#endif // VECTORESCAMARA_H
