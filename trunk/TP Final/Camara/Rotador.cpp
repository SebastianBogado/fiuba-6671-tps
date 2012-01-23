#include "Rotador.h"

Rotador::Rotador()
{
        this->anguloAnterior = 0.0;
        this->cosAngulo=1.0;
        this->senoAngulo = 0.0;

}

void Rotador::comprobarAngulo(float &angulo){

        if (angulo != anguloAnterior){
                cosAngulo = cos(angulo);
                senoAngulo = sin(angulo);

                anguloAnterior = angulo;
        }
}

void Rotador::normalizar(float *vector){

        float Norma = this->norma(vector);

        if (Norma > 0.0){
                for( int i=0;i<3;i++)
                        vector[i] /=Norma;
        }

}


void Rotador::rotarEnX(float *vector,float angulo,float *res){

        this->comprobarAngulo(angulo);

        res[0] = vector[0];
        res[1] = vector[1]*cosAngulo  - vector[2]*senoAngulo;
        res[2] = vector[1]*senoAngulo + vector[2]*cosAngulo;

}

void Rotador::rotarEnY(float *vector,float angulo,float *res){
        this->comprobarAngulo(angulo);
        res[0] = vector[0]*cosAngulo  + vector[2]*senoAngulo;
        res[1] = vector[1];
        res[2] = -vector[0]*senoAngulo + vector[2]*cosAngulo;
}

void Rotador::rotarEnZ(float *vector,float angulo,float* res){

        this->comprobarAngulo(angulo);

        res[0] = vector[0]*cosAngulo  - vector[1]*senoAngulo;
        res[1] = vector[0]*senoAngulo + vector[1]*cosAngulo;
        res[2] = vector[2];

}

void Rotador::rotar(float *vector,float angulo,float *eje,float *res){

        float aux[3];


//        this->copiar(eje,&aux[0]);
//
//        this->normalizar(&aux[0]);
//
//        this->rotarEnX(vector,angulo * aux[0],res);
//        this->rotarEnY(res,angulo * aux[1],&parcial[0]);
//        this->rotarEnZ(&parcial[0],angulo * aux[2],res);

        /////////////////////
        ////"2do intento///
        /////////////////////

        float theta = this->determinarThetaEje(eje);
        float phi = this->determinarPhiEje(eje);

        phi = M_PI_2 - phi;

        rotarEnZ(vector,-theta ,res);
        rotarEnY(res,phi,&aux[0]);

        rotarEnX(&aux[0],angulo,res);

        rotarEnY(res, -phi,&aux[0]);
        rotarEnZ(&aux[0],theta,res);

}

void Rotador::inicializarVec(float *v,float x,float y,float z){

        v[0] = x;
        v[1] = y;
        v[2] = z;

}

float Rotador::abs(float x){

        if (x>=0.0)
                return x;
        else
                return -x;

}

float Rotador::norma(float *vector){

        float norma=0.0;

        for (int i = 0; i<3 ; i++)
                norma += vector[i] * vector[i] ;

        if (norma > 0.0)
                norma = pow(norma,(float)0.5); //Qué histérico que es el MSVC, que me hace castear a float el 0,5...

        return norma;

}

void Rotador::sumar(float *p1,float *p2, float *res){

        res[0] = p1[0] + p2[0] ;
        res[1] = p1[1] + p2[1] ;
        res[2] = p1[2] + p2[2] ;

}

 void Rotador::sumar(float *p1,float p2, float * res){

        res[0] = p1[0] + p2 ;
        res[1] = p1[1] + p2 ;
        res[2] = p1[2] + p2 ;

 }

void Rotador::restar(float *p1,float *p2,float *res){

        res[0] = p1[0] - p2[0];
        res[1] = p1[1] - p2[1];
        res[2] = p1[2] - p2[2];
}

void Rotador::mult(float *p1,float p2,float *res){

        res[0] = p1[0] * p2 ;
        res[1] = p1[1] * p2 ;
        res[2] = p1[2] * p2 ;

}

void Rotador::copiar(float *p1,float *res){

        res[0]=p1[0];
        res[1]=p1[1];
        res[2]=p1[2];

}


void Rotador::productoVectorial(float *v1,float *v2,float *res){


        res[0] = v1[1]*v2[2] - v1[2]*v2[1];
        res[1]=  v1[2]*v2[0] - v1[0]*v2[2];
        res[2]=  v1[0]*v2[1] - v1[1]*v2[0];

}


float Rotador::determinarPhiEje(float *eje){

        float Norma = this->norma(eje);

        if (Norma > 0.0){

                return acos(eje[2] / Norma);


        }else{

                return 0.0;
        }

}

float Rotador::determinarThetaEje(float *eje){
        /*
        float Norma = this->norma(eje);

        float sinPhi = sin(this->determinarPhiEje(eje));

        float acosAngulo;
        float theta;

        if ( sinPhi > 0.0) {
                        acosAngulo = acos(eje[0] / (sinPhi * Norma) );
        }else{

                if(eje[0]!=0.0){
                        acosAngulo = atan (eje[1]/eje[0]);
                }
                else{
                         acosAngulo= M_PI_2;
                }

        }*/


        float vecXY[3]={eje[0],eje[1],0.0};



        float angulo,theta;

        if (eje[0]!= 0.0 || eje[1]!=0.0){

                this->normalizar(&vecXY[0]);
                angulo = acos ( vecXY[0]);

        }else
                angulo = 0.0;

        if (eje[1]>=0.0)
                theta = angulo;
        else
                theta = 2*M_PI - angulo;


        return theta;

}

void Rotador::obtenerOrtogonalPlano(float *v1,float *res){


        float ejeZ[3]={0.0,0.0,1.0};

        this->productoVectorial(v1,&ejeZ[0],res);

        this->normalizar(res);

}

Rotador::~Rotador()
{
        //dtor
}
