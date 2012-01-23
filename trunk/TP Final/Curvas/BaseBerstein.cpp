#include "BaseBerstein.h"

BaseBerstein::BaseBerstein()
{
    //ctor
}

float BaseBerstein::evaluar(int base,float x){


    float res;

    if ( x >= 0.0  && x <= 1.0){
        switch ( base ){

            case 0: res = this->base0(x); break;

            case 1: res = this->base1(x); break;

            case 2: res = this->base2(x); break;

            case 3: res = this->base3(x); break;

            default: res = 0.0;  break;

        }
    }else{
        res = 0.0;
    }

    return res;
}

float BaseBerstein::base0(float x){

    float res,parcial;

    parcial = (1.0 - x);

    res = parcial * parcial * parcial;

    return res;

}

float BaseBerstein::base1(float x){

    float res,parcial;

    parcial = (1.0- x);

    res = 3.0 * x * parcial * parcial ;

    return res;

}

float BaseBerstein::base2(float x){

    float res,parcial;

    parcial = (1.0 - x);

    res = 3.0 * x * x * parcial ;

    return res;

}

float BaseBerstein::base3(float x){

    float res;

    res = x * x * x ;

    return res;

}

BaseBerstein::~BaseBerstein()
{
    //dtor
}
