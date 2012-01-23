#include "TestBaseBSpline.h"

using namespace std;

TestBaseBSpline::TestBaseBSpline()
{
    this->base = new BaseBSpline(-1.0,2.0);
}

void TestBaseBSpline::tituloTest(string metodo){

    cout<<"Se inicia el Test para el metodo/s "<<metodo.c_str()<<endl;

}

void TestBaseBSpline::inicializar(float piso,float techo){

    delete this->base;

    base = new BaseBSpline(piso,techo);

}

void TestBaseBSpline::errorMetodo(string metodo){

    cout<<"Se encontro al menos un error en el metodo "<<metodo.c_str()<<endl<<endl;

}


void TestBaseBSpline::valorEsperado(float esperado,float recivido){


    cout <<"Se esperaba el valor: "<<esperado<<"    , y se recivio: "<<recivido<<endl;
}

bool TestBaseBSpline::comparar(float esperado,float recivido){

    bool esIgual = false;

    esIgual = (esperado == recivido);

    if (!esIgual)
        this->valorEsperado(esperado,recivido);

    return esIgual;

}

void TestBaseBSpline::iniciar(){

    this->testFuncionCero();
    this->testFuncionUno();
    this->testFuncionDos();

    this->testFuncionCeroPrima();
    this->testFuncionUnoPrima();
    this->testFuncionDosPrima();

    this->testGeneral();

}

void TestBaseBSpline::testGeneral(){

    this->tituloTest("Evaluar");

    bool error_encontrado=false;
    bool p1,p2,p3,p4,p5,p6,p7;

    float res=0.0;


    res = this->base->evaluar(0.0);
    p1 = !(0.5 == res);
    if (p1) this->valorEsperado(0.5,res);

    res = this->base->evaluar(1.0);
    p2 = !(0.5 == res);
    if (p2) this->valorEsperado(0.5,res);

    res = this->base->evaluar(0.5);
    p3 = !(0.75 == res);
    if (p3) this->valorEsperado(0.75,res);

    res = this->base->evaluar(-1.0);
    p4 = !(0.0 == res);
    if (p4) this->valorEsperado(0.0,res);

    res = this->base->evaluar(2.0);
    p5 = !(0.0 == res);
    if (p5) this->valorEsperado(0.0,res);

    res = this->base->evaluar(4.0);
    p6 = !(0.0 == res);
    if (p6) this->valorEsperado(0.0,res);

    res = this->base->evaluar(-2.0);
    p7 = !(0.0 == res);
    if (p7) this->valorEsperado(0.0,res);

    error_encontrado = p1 || p2 || p3 || p4 || p5 || p6 || p7;

    if (error_encontrado )
        this->errorMetodo("Evaluar");

}


void TestBaseBSpline::testFuncionCero(){

    bool error_encontrado=false;
    bool p1,p2,p3 = false;

    float res;

    this->tituloTest("FuncionCero");

    res = this->base->func_0(-1.0);
    p1 = !(res == 0.0);
    if(p1) this->valorEsperado(0.0,res);

    res = this->base->func_0(0.0);
    p2 = !(res == 0.5);
    if(p2) this->valorEsperado(0.5,res);

    error_encontrado = p1 || p2 || p3;

    if (error_encontrado)
        this->errorMetodo("FuncionCero desde evaluar");
}

void TestBaseBSpline::testFuncionUno(){

    bool error_encontrado=false;
    bool p1,p2,p3 = false;

    float res;

    this->tituloTest("FuncionUno");

    res = this->base->func_1(0.5);
    p1 = !(res == 0.75);
    if(p1) this->valorEsperado(0.75,res);

    res = this->base->func_1(0.0);
    p2 = !(res == 0.5);
    if(p2) this->valorEsperado(0.5,res);

    res = this->base->func_1(1.0);
    p3 = !(res == 0.5);
    if(p3) this->valorEsperado(0.5,res);

    error_encontrado = p1 || p2 || p3;

    if (error_encontrado)
        this->errorMetodo("FuncionUno desde evaluar");
}



void TestBaseBSpline::testFuncionDos(){

    bool error_encontrado=false;
    bool p1,p2,p3 = false;

    float res;

    this->tituloTest("FuncionDos");

    res = this->base->func_2(1.0);
    p1 = !(res == 0.5);
    if(p1) this->valorEsperado(0.5,res);

    res = this->base->func_2(2.0);
    p2 = !(res == 0.0);
    if(p2) this->valorEsperado(0.0,res);

    error_encontrado = p1 || p2 || p3;

    if (error_encontrado)
        this->errorMetodo("FuncionDos desde evaluar");
}

void TestBaseBSpline::testFuncionCeroPrima(){

    this->tituloTest("FuncionCeroPrima");

    bool error_encontrado= false;

    bool p1,p2,p3;

    float res;

    res = this->base->derivada(-1.0);
    p1 = !(this->comparar(0.0,res));

    res = this->base->derivada(0.0);
    p2 = !(this->comparar(1.0,res));

    res = this->base->derivada(-0.5);
    p3 = !(this->comparar(0.5,res));

    error_encontrado = p1 || p2 || p3;

    if (error_encontrado){
        this->errorMetodo("FuncionCeroPrima");
    }

}

void TestBaseBSpline::testFuncionUnoPrima(){

    this->tituloTest("FuncionUnoPrima");

    bool error_encontrado= false;

    bool p1,p2,p3;

    float res;

    res = this->base->derivada(0.0);
    p1 = !(this->comparar(1.0,res));

    res = this->base->derivada(0.5);
    p2 = !(this->comparar(0.0,res));

    res = this->base->derivada(1.0);
    p3 = !(this->comparar(-1.0,res));

    error_encontrado = p1 || p2 || p3;

    if (error_encontrado)
        this->errorMetodo("FuncionPrimaUno");

}

void TestBaseBSpline::testFuncionDosPrima(){

    this->tituloTest("FuncionDosPrima");

    bool error_encontrado= false;

    bool p1,p2,p3;

    float res;

    res = this->base->derivada(1.0);
    p1 = !(this->comparar(-1.0,res));

    res = this->base->derivada(1.5);
    p2 = !(this->comparar(-0.5,res));

    res = this->base->derivada(2.0);
    p3 = !(this->comparar(0.0,res));

    error_encontrado = p1 || p2 || p3;

    if( error_encontrado){
        this->errorMetodo("FuncionDosPrima");
    }

}

TestBaseBSpline::~TestBaseBSpline()
{
    delete this->base;
}
