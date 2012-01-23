#ifndef TESTBSPLINE_H
#define TESTBSPLINE_H

#include "Test.h"
#include "BSpline.h"
#include <glm/glm.hpp>

using namespace glm;

class TestBSpline : public Test
{
    public:
        TestBSpline();
        void iniciar();

        void testInicializacion();
        void testEvaluar();
        void testTangente();
        void testCurvaGrande();
        void testTruncar();

        void inicializar(int cantPuntos,vec3* puntos);
        virtual ~TestBSpline();
    private:
        BSpline *curva;

};

#endif // TESTBSPLINE_H
