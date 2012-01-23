#ifndef BASEBSPLINE_H
#define BASEBSPLINE_H


typedef float Flotante;

class BaseBSpline
{
    public:
        BaseBSpline();
        BaseBSpline(float piso,float techo);

        void redefinirIntervalo(float piso,float techo);
        float evaluar(float x);
        float derivada(float x);


        float func_0(float x);
        float func_1(float x);
        float func_2(float x);

        float func_0_prim(float x);
        float func_1_prim(float x);
        float func_2_prim(float x);

        virtual ~BaseBSpline();
    private:

        float corregirValor(float x);

        float piso,techo;
        float difIntervalo;

};

#endif // BASEBSPLINE_H
