#include "Test.h"

using namespace std;

Test::Test()
{
    //ctor
}

void Test::tituloTest(string metodo){
    cout<<"***********************************"<<endl;
    cout<<"Se inicia el Test para el metodo/s "<<metodo.c_str()<<"."<<endl;
}

void Test::tituloInicio(string clase){

    cout<<"---------------------------------------------------------------------"<<endl;
    cout<<"--Se inician los tests para la clase "<<clase.c_str()<<endl;
    cout<<"---------------------------------------------------------------------"<<endl;

}

void Test::errorEnMetodo(string metodo){

    cout<<"Se encontro al menos un error en el metodo/s "<<metodo.c_str()<<endl;

}

void Test::errorEnMetodo(bool hayErrores,string metodo){

    if (hayErrores)
        this->errorEnMetodo(metodo);
    else
        this->testSinErrores(metodo);

}

bool Test::comparar(float esperado,float recivido){

    bool esIgual;

    esIgual = (esperado == recivido);

    if (!esIgual){

        cout<<"Se esperaba el valor: "<<esperado<<" y se recivio: "<<recivido<<endl;
    }

        registrarError(esIgual);

    return esIgual;
}

bool Test::comparar(vec3 esperado,vec3 recivido){

    bool esIgual;

    esIgual =   esperado.x == recivido.x &&
                    esperado.y == recivido.y &&
                    esperado.z == recivido.z ;

    if(!esIgual){

        cout<<"Se esperaba : ("<<esperado.x<<"; "<<esperado.y<<"; "<<esperado.z<<") ";
        cout<<" y se recivio : ("<<recivido.x<<"; "<<recivido.y<<"; "<<recivido.z<<")"<<endl;

    }

    registrarError(esIgual);

    return esIgual;

}

void Test::inicializarVector(float *vector,float x,float y,float z){

        this->inicializarVector(x,y,z,vector);
}

void Test::inicializarVector(float x,float y,float z,float *vector){

        vector[0]=x;
        vector[1]=y;
        vector[2]=z;

}

bool Test::comparar(float* esperado,float * recivido){

        vec3 esp(esperado[0],esperado[1],esperado[2]);
        vec3 rec(recivido[0],recivido[1],recivido[2]);

        return this->comparar(esp,rec);


}

void Test::registrarError(bool comparacion){

        errorEncontrado = errorEncontrado || !(comparacion);

}

void Test::testSinErrores(string metodo){

    cout<<"+++ El test para el metodo/s "<<metodo.c_str()<<" paso sin errores."<<endl;

}

void Test::reiniciarErrores(){

        errorEncontrado = false;
}

void Test::comprobarErrores(string metodo){

        this->errorEnMetodo(errorEncontrado,metodo);

        this->reiniciarErrores();

}

Test::~Test()
{
    //dtor
}
