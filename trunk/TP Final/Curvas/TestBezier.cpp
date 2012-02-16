#include "TestBezier.h"

TestBezier::TestBezier()
{
        this->curva = NULL;

        vec3 *puntos=new vec3[7];

        puntos[0]=vec3(1.0,0.0,0.0);
        puntos[1]=vec3(0.0,1.0,0.0);
        puntos[2]=vec3(0.0,0.0,1.0);
        puntos[3]=vec3(2.0,0.0,0.0);
        puntos[4]=vec3(2.0,1.0,0.0);
        puntos[5]=vec3(2.0,1.0,0.0);
        puntos[6]=vec3(0.0,2.0,2.0);

        this->inicializar(1,puntos);

        delete[] puntos;

}

void TestBezier::inicializar(int cantTramos,vec3* puntos){

        if(this->curva != NULL)
                delete this->curva;

        this->curva = new Bezier(cantTramos);

        for( int i=0; i < 3*cantTramos + 1 ; i++){

                this->curva->incluirPunto(puntos[i]);

        }

}

void TestBezier::iniciar(){

        this->tituloInicio("Bezier");

        this->testConstructor();
        this->testEvaluar();
		this->testTangente();


}

void TestBezier::testConstructor(){

        this->tituloTest("Constructor e inicializacion");

        vec3 *puntos=new vec3[7];

        puntos[0]=vec3(1.0,0.0,0.0);
        puntos[1]=vec3(0.0,1.0,0.0);
        puntos[2]=vec3(0.0,0.0,1.0);
        puntos[3]=vec3(2.0,0.0,0.0);
        puntos[4]=vec3(2.0,1.0,0.0);
        puntos[5]=vec3(2.0,1.0,0.0);
        puntos[6]=vec3(0.0,0.0,2.0);

        this->inicializar(2,puntos);

        bool p1= !(this->comparar(puntos[0],this->curva->verPunto(0)));

        bool p2= !(this->comparar(puntos[1],this->curva->verPunto(1)));

        bool p3= !(this->comparar(puntos[2],this->curva->verPunto(2)));

        bool p4= !(this->comparar(puntos[3],this->curva->verPunto(3)));

        bool p5= !(this->comparar(puntos[4],this->curva->verPunto(4)));

        bool p6= !(this->comparar(puntos[5],this->curva->verPunto(5)));

        bool p7= !(this->comparar(puntos[6],this->curva->verPunto(6)));


        errorEncontrado = p1 || p2 || p3 || p4 || p5 || p6 || p7;

		delete[] puntos;

        this->errorEnMetodo(errorEncontrado,"Constructor e inicializacion");

}

void TestBezier::testEvaluar(){

        this->tituloTest("Evaluar");

        vec3 ptoEsperado,ptoRecivido;

        ptoEsperado = vec3 (1.0, 0.0 , 0.0);
        ptoRecivido = this->curva->evaluar(0.0);

        bool p1 = !( comparar(ptoEsperado,ptoRecivido) );


        ptoEsperado = vec3 (2.0, 0.0 , 0.0);
        ptoRecivido = this->curva->evaluar(1.0);

        bool p2 = !( comparar(ptoEsperado,ptoRecivido) );


        ptoEsperado = vec3 (0.0, 0.0 , 2.0);
        ptoRecivido = this->curva->evaluar(2.0);

        bool p3 = !( comparar(ptoEsperado,ptoRecivido) );


        ptoEsperado = vec3 (0.0, 0.0 , 0.0);
        ptoRecivido = this->curva->evaluar(2.5);

        bool p4 = !( comparar(ptoEsperado,ptoRecivido) );


        this->errorEncontrado = p1 || p2 || p3 || p4;

        this->errorEnMetodo(errorEncontrado,"Evaluar");

}


void TestBezier::testTangente(){

	this->tituloTest("Tangente");

	vec3 *puntos=new vec3[7];

    puntos[0]=vec3(1.0,0.0,0.0);
    puntos[1]=vec3(0.0,1.0,0.0);
    puntos[2]=vec3(0.0,0.0,1.0);
    puntos[3]=vec3(2.0,0.0,0.0);
    puntos[4]=vec3(2.0,1.0,0.0);
    puntos[5]=vec3(2.0,1.0,0.0);
    puntos[6]=vec3(0.0,0.0,2.0);

    this->inicializar(2,puntos);


	vec3 ptoEsperado = puntos[1] - puntos[0];
	vec3 ptoRecivido = this->curva->tangente(0.0);
	
	ptoEsperado = vec3(this->normalizar(ptoEsperado)); 
	ptoRecivido = vec3(this->normalizar(ptoRecivido));

	bool p1 = !(comparar(ptoEsperado,ptoRecivido));
	/////////////////////////
	///////////////////////
	ptoEsperado = puntos[3] - puntos[2];
	ptoRecivido = this->curva->tangente(0.99999);
	
	ptoEsperado = vec3(this->normalizar(ptoEsperado)); 
	ptoRecivido = vec3(this->normalizar(ptoRecivido));

	bool p2 = !(comparar(ptoEsperado,ptoRecivido));

	/////////////////////////
	///////////////////////
	ptoEsperado = puntos[6] - puntos[5];
	ptoRecivido = this->curva->tangente(2);
	
	ptoEsperado = vec3(this->normalizar(ptoEsperado)); 
	ptoRecivido = vec3(this->normalizar(ptoRecivido));

	bool p3 = !(comparar(ptoEsperado,ptoRecivido));


	this->errorEncontrado= p1 || p2 || p3;

	this->errorEnMetodo(errorEncontrado,"Tangente");



}

TestBezier::~TestBezier()
{
        if(this->curva != NULL)
                delete this->curva;
}
