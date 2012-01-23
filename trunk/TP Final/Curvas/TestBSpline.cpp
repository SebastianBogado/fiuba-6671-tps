#include "TestBSpline.h"
#include <iostream>

using namespace std;

TestBSpline::TestBSpline()
{
    this->curva = new BSpline(3);
    this->curva->incluirPunto(vec3(1.0,0.0,0.0));
    this->curva->incluirPunto(vec3(0.0,0.0,1.0));
    this->curva->incluirPunto(vec3(-1.0,0.0,0.0));
}

void TestBSpline::iniciar(){

    this->tituloInicio("BSpline");

    this->testInicializacion();
    this->testEvaluar();
    this->testTangente();
    this->testCurvaGrande();
    this->testTruncar();


}

void TestBSpline::inicializar(int cantPuntos,vec3* puntos){


    delete this->curva;

    this->curva= new BSpline(cantPuntos);

    for(int i=0;i<cantPuntos;i++)
        this->curva->incluirPunto(puntos[i]);

}

void TestBSpline::testInicializacion(){

    bool p1,p2,p3;

    this->tituloTest("Constructor e inicializacion de Puntos");

    vec3 *puntos= new vec3[3];

    puntos[0]=vec3(1.0,0.0,0.0);
    puntos[1]=vec3(0.0,1.0,0.0);
    puntos[2]=vec3(0.0,0.0,1.0);

    this->inicializar(3,puntos);

    p1 = !(this->comparar(puntos[0],this->curva->verPunto(0)));
    p2 = !(this->comparar(puntos[1],this->curva->verPunto(1)));
    p3 = !(this->comparar(puntos[2],this->curva->verPunto(2)));

    bool error_encontrado = p1 || p2 || p3;

    this->errorEnMetodo(error_encontrado,"Constructor y relevantes al mismo");

    delete[] puntos;


}


void TestBSpline::testEvaluar(){

    bool error_encontrado;
    bool p1,p2,p3;

    this->tituloTest("Evaluar");

    vec3 *puntos= new vec3[3];

    puntos[0]=vec3(1.0,0.0,0.0);
    puntos[1]=vec3(0.0,1.0,0.0);
    puntos[2]=vec3(0.0,0.0,1.0);

    this->inicializar(3,puntos);

    vec3 puntoEvaluado,puntoEsperado;


    puntoEsperado = vec3(0.5,0.5,0.0);

    puntoEvaluado = this->curva->evaluar(0.0);

    p1 = !(this->comparar(puntoEsperado,puntoEvaluado));



    puntoEsperado = vec3(0.0,0.5,0.5);

    puntoEvaluado = this->curva->evaluar(1.0);

    p2 = !(this->comparar(puntoEsperado,puntoEvaluado));


    puntoEsperado = vec3(0.0,0.0,0.0);

    puntoEvaluado = this->curva->evaluar(3.0);

    p3 = !(this->comparar(puntoEsperado,puntoEvaluado));


    error_encontrado = p1 || p2 || p3;

    this->errorEnMetodo(error_encontrado,"Evaluar");

    delete[] puntos;
}

void TestBSpline::testTangente(){

    bool error_encontrado;
    bool p1,p2,p3;

    this->tituloTest("Tangente");

    vec3 *puntos= new vec3[3];

    puntos[0]=vec3(1.0,0.0,0.0);
    puntos[1]=vec3(0.0,1.0,0.0);
    puntos[2]=vec3(0.0,0.0,1.0);

    this->inicializar(3,puntos);

    vec3 puntoEvaluado,puntoEsperado;

    puntoEsperado = vec3(-1.0,1.0,0.0);

    puntoEvaluado = this->curva->tangente(0.0);

    p1 = !(this->comparar(puntoEsperado,puntoEvaluado));



    puntoEsperado = vec3(0.0,-1.0,1.0);

    puntoEvaluado = this->curva->tangente(1.0);

    p2 = !(this->comparar(puntoEsperado,puntoEvaluado));



    error_encontrado = p1 || p2;

    this->errorEnMetodo(error_encontrado,"Tangente");

}

void TestBSpline::testCurvaGrande(){

    bool error_encontrado;

    this->tituloTest("Curva Grande, con mucho puntos");

    vec3 *puntos= new vec3[8];

    puntos[0]=vec3(3.0,0.0,0.0);
    puntos[1]=vec3(0.0,1.0,0.0);
    puntos[2]=vec3(0.0,0.0,1.0);
    puntos[3]=vec3(0.0,5.0,0.0);
    puntos[4]=vec3(0.0,0.0,10.0);
    puntos[5]=vec3(1.0,0.0,5.0);
    puntos[6]=vec3(0.0,2.0,1.0);
    puntos[7]=vec3(10.0,0.0,1.0);

    this->inicializar(8,puntos);

    vec3 ptoEsperado,ptoEvaluado;


    ptoEvaluado = this->curva->evaluar(1.0);
    ptoEsperado = vec3(0.0,0.5,0.5);
    bool p1 = !(this->comparar(ptoEsperado,ptoEvaluado));


    ptoEvaluado = this->curva->evaluar(6.0);
    ptoEsperado = vec3(5.0,1.0,1.0);
    bool p2 = !(this->comparar(ptoEsperado,ptoEvaluado));

    ptoEvaluado = this->curva->evaluar(5.0);
    ptoEsperado = vec3(0.5,1.0,3.0);
    bool p3 = !(this->comparar(ptoEsperado,ptoEvaluado));

    ptoEvaluado = this->curva->evaluar(4.0);
    ptoEsperado = vec3(0.5,0.0,7.5);
    bool p4 = !(this->comparar(ptoEsperado,ptoEvaluado));

    ptoEvaluado = this->curva->evaluar(2.0);
    ptoEsperado = vec3(0.0,2.5,0.5);
    bool p5 = !(this->comparar(ptoEsperado,ptoEvaluado));

    error_encontrado = p1 || p2 || p3 || p4 || p5;
    this->errorEnMetodo(error_encontrado,"Curva con mucho puntos");

    delete[] puntos;
}

void TestBSpline::testTruncar(){


    this->tituloTest("Truncar");

    float esperado,recivido;

    recivido = this->curva->truncar(3.5);
    esperado = 3.0;
    bool p1 = !(this->comparar(esperado,recivido));


    recivido = this->curva->truncar(5.9);
    esperado = 5.0;
    bool p2 = !(this->comparar(esperado,recivido));

    recivido = this->curva->truncar(2.1);
    esperado = 2.0;
    bool p3 = !(this->comparar(esperado,recivido));

    recivido = this->curva->truncar(1.0);
    esperado = 1.0;
    bool p4 = !(this->comparar(esperado,recivido));

    errorEncontrado = p1 || p2 || p3 || p4;

    this->errorEnMetodo(errorEncontrado,"Truncar");

}

TestBSpline::~TestBSpline()
{
    delete this->curva;
}
