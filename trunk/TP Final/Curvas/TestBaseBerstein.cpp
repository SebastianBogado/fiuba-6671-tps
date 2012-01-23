#include "TestBaseBerstein.h"

TestBaseBerstein::TestBaseBerstein()
{
        this->base = new BaseBerstein;
}


void TestBaseBerstein::iniciar(){


        this->tituloInicio("BaseBerstein");

        this->testBaseCero();
        this->testBaseUno();
        this->testBaseDos();
        this->testBaseTres();

}

void TestBaseBerstein::testBaseCero(){

        this->tituloTest("BaseCero");

        float esperado,recivido;

        recivido = this->base->evaluar(0,0.0);
        esperado = 1.0;

        bool p1 = !(this->comparar(esperado,recivido));

        recivido = this->base->evaluar(0,1.0);
        esperado = 0.0;

        bool p2 = !(this->comparar(esperado,recivido));

        this->errorEncontrado = p1 || p2;

        this->errorEnMetodo(errorEncontrado,"BaseCero");

}

void TestBaseBerstein::testBaseUno(){

        this->tituloTest("BaseUno");


        float esperado,recivido;

        recivido = this->base->evaluar(1,0.0);
        esperado = 0.0;

        bool p1 = !(this->comparar(esperado,recivido));

        recivido = this->base->evaluar(1,1.0);
        esperado = 0.0;

        bool p2 = !(this->comparar(esperado,recivido));

        this->errorEncontrado = p1 || p2;



        this->errorEnMetodo(errorEncontrado,"BaseUno");

}


void TestBaseBerstein::testBaseDos(){


        this->tituloTest("BaseDos");

        float esperado,recivido;

        recivido = this->base->evaluar(2,0.0);
        esperado = 0.0;

        bool p1 = !(this->comparar(esperado,recivido));

        recivido = this->base->evaluar(2,1.0);
        esperado = 0.0;

        bool p2 = !(this->comparar(esperado,recivido));

        this->errorEncontrado = p1 || p2;

        this->errorEnMetodo(errorEncontrado,"BaseDos");

}

void TestBaseBerstein::testBaseTres(){

        this->tituloTest("BaseTres");

        float esperado,recivido;

        recivido = this->base->evaluar(3,0.0);
        esperado = 0.0;

        bool p1 = !(this->comparar(esperado,recivido));

        recivido = this->base->evaluar(3,1.0);
        esperado = 1.0;

        bool p2 = !(this->comparar(esperado,recivido));

        this->errorEncontrado = p1 || p2;

        this->errorEnMetodo(errorEncontrado,"BaseTres");

}

TestBaseBerstein::~TestBaseBerstein()
{
        delete this->base;
}
