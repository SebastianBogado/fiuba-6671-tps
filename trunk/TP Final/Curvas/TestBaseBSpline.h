#ifndef TESTBASEBSPLINE_H
#define TESTBASEBSPLINE_H


#include <iostream>
#include "BaseBSpline.h"
#include "Test.h"

using namespace std;

class TestBaseBSpline :
public Test
{
    public:
        TestBaseBSpline();
        void iniciar();
        void inicializar(float piso,float techo);
        void tituloTest(string metodo);
        void errorMetodo(string metodo);
        void valorEsperado(float esperado,float recivido);
        bool comparar(float esperado,float recivido);

        void testFuncionCero();
        void testFuncionUno();
        void testFuncionDos();

        void testFuncionCeroPrima();
        void testFuncionUnoPrima();
        void testFuncionDosPrima();

        void testGeneral();

        virtual ~TestBaseBSpline();
    private:
        BaseBSpline *base;
};

#endif // TESTBASEBSPLINE_H
