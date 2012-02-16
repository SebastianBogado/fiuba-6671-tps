#ifndef TESTBEZIER_H
#define TESTBEZIER_H


#include <glm/glm.hpp>
#include "Test.h"
#include "Bezier.h"

using namespace glm;

class TestBezier : public Test
{
        public:
                TestBezier();
                void iniciar();
                void inicializar(int cantTramos,vec3 *puntos);

                void testConstructor();
                void testEvaluar();
				void testTangente();

                virtual ~TestBezier();
        private:
                Bezier *curva;

};

#endif // TESTBEZIER_H
