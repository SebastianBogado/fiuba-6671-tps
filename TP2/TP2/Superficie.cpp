#include "Superficie.h"

Superficie::Superficie(){ this->paso = 64; }

Superficie::~Superficie(){ delete this->curvaBorde; }

float* Superficie::getPunto(int Xn, int Yn, int Zn){
    float* punto = new float[3];
    punto[0] = this->Xn(Xn);
    punto[1] = this->Yn(Yn);
    punto[2] = this->Zn(Zn);

    return punto;
}

float Superficie::Xn(int n){ return this->curvaBorde->Xn(n); }
float Superficie::Yn(int n){ return this->curvaBorde->Yn(n); }
float Superficie::Zn(int n){ return ((float)n * (this->altura / this->paso)); }

bool Superficie::tieneTapas(){ return this->tengoTapas; }

float Superficie::getAltura(){ return this->altura; }

int Superficie::getPaso(){ return this->paso; }

int Superficie::cantidadDePuntosBorde(){ return this->curvaBorde->cantDePuntos(); }
int Superficie::cantidadDePuntosEnAlto(){ return this->puntosEnAlto; }


float* Superficie::getNormal(int Xn, int Yn, int Zn){
    if (esArista(Xn, Yn, Zn))
        return getNormalArista(Xn, Yn, Zn);
    //Calcular cuatro normales según otras direcciones, respecto del punto en cuestión
    float* puntoCentral = getPunto(Xn, Yn, Zn);

    //Dirección arriba y derecha
    float* puntoUno = getPunto(Xn, Yn, Zn+1);
    float* puntoDos = getPunto(Xn+1, Yn+1, Zn);
    float* normal1 = calcularNormal(puntoCentral, puntoUno, puntoDos);
    delete [] puntoUno;
    delete [] puntoDos;

    //Dirección derecha y abajo
    puntoUno = getPunto(Xn+1, Yn+1, Zn);
    puntoDos = getPunto(Xn, Yn, Zn-1);
    float* normal2 = calcularNormal(puntoCentral, puntoUno, puntoDos);
    delete [] puntoUno;
    delete [] puntoDos;

    //Dirección abajo e izquierda
    puntoUno = getPunto(Xn, Yn, Zn-1);
    puntoDos = getPunto(Xn-1, Yn-1, Zn);
    float* normal3 = calcularNormal(puntoCentral, puntoUno, puntoDos);
    delete [] puntoUno;
    delete [] puntoDos;

    //Dirección izquierda y arriba
    puntoUno = getPunto(Xn, Yn, Zn+1);
    puntoDos = getPunto(Xn-1, Yn-1, Zn);
    float* normal4 = calcularNormal(puntoCentral, puntoUno, puntoDos);
    delete [] puntoUno;
    delete [] puntoDos;

    //Promediar entre las cuatro normales

    float* normal = new float[3];
	
    normal[0] = normal1[0] + normal2[0] + normal3[0] + normal4[0];
    normal[1] = normal1[1] + normal2[1] + normal3[1] + normal4[1];
    normal[2] = normal1[2] + normal2[2] + normal3[2] + normal4[2];

	float norma = sqrt(normal[0]*normal[0] + normal[1]*normal[1] + normal[2]*normal[2]);
    normal[0] /= norma;
    normal[1] /= norma;
    normal[2] /= norma;

    delete []normal1;
    delete []normal2;
    delete []normal3;
    delete []normal4;

    return normal;
}
float* Superficie::calcularNormal(float* p, float* q, float* r){
    float* normal = new float[3];

    //Calcular una aproximación a una dirección tangente
    float* tgUno = new float[3];
    tgUno[0] = q[0]-p[0];
    tgUno[1] = q[1]-p[1];
    tgUno[2] = q[2]-p[2];

    //Calcular una aproximación a la otra dirección tangente
    float* tgDos = new float[3];
    tgDos[0] = r[0]-p[0];
    tgDos[1] = r[1]-p[1];
    tgDos[2] = r[2]-p[2];

    //Producto vectorial para obtener la dirección normal
    normal[0] = tgDos[1]*tgUno[2] - tgDos[2]*tgUno[1];
    normal[1] = tgDos[2]*tgUno[0] - tgDos[0]*tgUno[2];
    normal[2] = tgDos[0]*tgUno[1] - tgDos[1]*tgUno[0];

    //Normalizar
    float norma = sqrt(normal[0]*normal[0] + normal[1]*normal[1] + normal[2]*normal[2]);
    normal[0] /= norma;
    normal[1] /= norma;
    normal[2] /= norma;

    delete []tgUno;
    delete []tgDos;

    return normal;
}

float* Superficie::getNormalArista(int Xn, int Yn, int Zn){
    float* normal = new float[3];
    normal[0] = 1;
    normal[1] = 0;
    normal[2] = 0;
    return normal;
}
bool Superficie::esArista(int Xn, int Yn, int Zn){
    return false;
}
