#include "BaseBSpline.h"


static const float nodo_0 = -1.0;
static const float nodo_1 = 0.0;
static const float nodo_2 = 1.0;
static const float nodo_3 = 2.0;
static const float valor_nulo = 10.0;

BaseBSpline::BaseBSpline(){}

BaseBSpline::BaseBSpline(float piso,float techo)
{
    this->redefinirIntervalo(piso,techo);

}

void BaseBSpline::redefinirIntervalo(float piso,float techo){

    if (piso < techo){
        this->piso = piso;
        this->techo = techo;
        this->difIntervalo = piso - nodo_0;

    }

}


float BaseBSpline::corregirValor(float x){

    float valorX;

   if ( x >= this->piso || x <= this->techo){

        valorX = x- this->difIntervalo;

    }else{

        valorX = valor_nulo;

    }

    return valorX;

}

float BaseBSpline::evaluar(float x){

    float res;

    float valorX = this->corregirValor(x);


    if ( valorX >= nodo_0 && valorX < nodo_1){

        res = this->func_0(valorX);

    }else if ( valorX >= nodo_1  && valorX < nodo_2){

        res = this->func_1(valorX);

    }else if (valorX >= nodo_2 && valorX <= nodo_3){

        res = this->func_2(valorX);

    }else{

        res = 0.0;
    }


    return res;

}


float BaseBSpline::derivada(float x){


    float res;

    float valorX = this->corregirValor(x);


    if ( valorX >= nodo_0 && valorX < nodo_1){

        res = this->func_0_prim(valorX);

    }else if ( valorX >= nodo_1  && valorX < nodo_2){

        res = this->func_1_prim(valorX);

    }else if (valorX >= nodo_2 && valorX <= nodo_3){

        res = this->func_2_prim(valorX);

    }else{

        res = 0.0;
    }


    return res;


}

float BaseBSpline::func_0(float x){

    float res,parcial;

    parcial = x + 1;

    res = 0.5 * ( parcial * parcial );

    return res;

}

float BaseBSpline::func_0_prim(float x){

    float res;

    res = x +1.0;

    return res;

}

float BaseBSpline::func_1(float x){

    float res, parcial;

    parcial = x - 0.5;

    res = 0.75 - (parcial * parcial);

    return res;

}

float BaseBSpline::func_1_prim(float x){

    float res;

    res = -2.0*x +1.0;

    return res;

}



float BaseBSpline::func_2(float x){

    float res,parcial;

    parcial = x - 2.0;

    res = 0.5 * (parcial * parcial);


    return res;

}

float BaseBSpline::func_2_prim(float x){

    float res;

    res = x - 2.0;

    return res;
}

BaseBSpline::~BaseBSpline()
{
    //dtor
}
