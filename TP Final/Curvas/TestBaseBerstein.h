#ifndef TESTBASEBERSTEIN_H
#define TESTBASEBERSTEIN_H

#include "Test.h"
#include "BaseBerstein.h"

class TestBaseBerstein : public Test
{
        public:
                TestBaseBerstein();
                void iniciar();

                void testBaseCero();
                void testBaseUno();
                void testBaseDos();
                void testBaseTres();

                virtual ~TestBaseBerstein();
        private:

                BaseBerstein *base;
};

#endif // TESTBASEBERSTEIN_H
