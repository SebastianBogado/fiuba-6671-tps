#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;
class Test
{
    public:
        Test();

        virtual void iniciar()=0;
        void tituloInicio(string clase);
        void tituloTest(string metodo);
        void errorEnMetodo(string metodo);
        void errorEnMetodo(bool hayErrores,string metodo);
        void testSinErrores(string metodo);
        bool comparar(float esperado,float recivido);
        bool comparar(vec3 esperado,vec3 recivido);
        bool comparar(float * esperado,float * recivido);
		vec3 normalizar(vec3 vector);

        virtual ~Test();
    protected:

		

        void comprobarErrores(string metodo);
        void inicializarVector(float x,float y,float z,float* vector);
        void inicializarVector(float *vector,float x,float y,float z);
        bool errorEncontrado;


        private:
        void registrarError(bool comparcion);
        void reiniciarErrores();


};

#endif // TEST_H
