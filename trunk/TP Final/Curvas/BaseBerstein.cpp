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

float BaseBerstein::evaluarDerivada(int base,float x){


    float res;

    if ( x >= 0.0  && x <= 1.0){
        switch ( base ){

            case 0: res = this->baseDer0(x); break;

            case 1: res = this->baseDer1(x); break;

            case 2: res = this->baseDer2(x); break;

            case 3: res = this->baseDer3(x); break;

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

float BaseBerstein::baseDer0(float x){

	float res,parcial;
	parcial = (1.0 - x);

	res = -3.0*parcial*parcial;

	return res;
}

float BaseBerstein::base1(float x){

    float res,parcial;

    parcial = (1.0- x);

    res = 3.0 * x * parcial * parcial ;

    return res;

}

float BaseBerstein::baseDer1(float x){
	float res,parcial;

	parcial = (1.0 -x);

	res = 3.0*parcial*parcial - 6.0*x*parcial;

	return res;

}

float BaseBerstein::base2(float x){

    float res,parcial;

    parcial = (1.0 - x);

    res = 3.0 * x * x * parcial ;

    return res;

}

float BaseBerstein::baseDer2(float x){
	float parcial,res;

	parcial = (1.0 - x);

	res = 6.0*x*parcial - 3.0 * x * x;

	return res;

}

float BaseBerstein::base3(float x){

    float res;

    res = x * x * x ;

    return res;

}

float BaseBerstein::baseDer3(float x){

	float res;

	res = 3.0* x * x ;

	return res;
}

BaseBerstein::~BaseBerstein()
{
    //dtor
}
