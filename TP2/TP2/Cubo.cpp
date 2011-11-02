#include "Cubo.h"

Cubo::Cubo(){
    this->lado = 1;
	this->paso=16;
    this->construir();
}
Cubo::Cubo(float lado, int paso){
    this->lado = lado;
    this->paso = paso;
    this->construir();
}


void Cubo::construir(){
    this->tengoTapas = true;
    this->altura = lado;
    this->puntosEnAlto = paso;
    this->curvaBorde = new Cuadrado(lado, paso);
}
float* Cubo::getNormal(int Xn, int Yn, int Zn){
	/* Si bien el cálculo de la normal de la forma genérica funcionaría para
	 * los puntos que no son aristas, las direcciones normales con las aristas
	 * son compartidas en todos los casos. Es óptimo entonces reescribir el método
	 * Además, como las aristas se repiten (esto es transparente para el emparchador),
	 * la orientación de la normal depende de si es la primera vez o segunda que aparece.
	 * Esto es muy dependiente de la implementación, así que, es difícil de entender si,
	 * justamente, no se conoce cómo está escrito el cubito. Por ende, la mejor forma de 
	 * calcular la normal es en papel y lápiz, según el Xn (Xn = Yn)
	 */

	if (Xn >= cantidadDePuntosBorde())
        return getNormal(Xn-cantidadDePuntosBorde(), Yn-cantidadDePuntosBorde(), Zn);
	if (Xn < 0)
        return getNormal(Xn+cantidadDePuntosBorde(), Yn+cantidadDePuntosBorde(), Zn);
   	 
	float* normal = new float[3];
	
	for (int i = 0; i < 4; i++){
		switch(i){
            case 0:
				if ((i*(paso+1) <= Xn) && (Xn <= i*(paso+1) + paso)){
					normal[0] = 0.0;
					normal[1] = 1.0;
					normal[2] = 0.0;
					return normal;
				}
                break;
            case 1:
                if ((i*(paso+1) <= Xn) && (Xn <= i*(paso+1) + paso)){
					normal[0] = -1.0;
					normal[1] = 0.0;
					normal[2] = 0.0;
					return normal;
				}
                break;
            case 2:
                if ((i*(paso+1) <= Xn) && (Xn <= i*(paso+1) + paso)){
					normal[0] = 0.0;
					normal[1] = -1.0;
					normal[2] = 0.0;
					return normal;
				}
                break;
            case 3:
                if ((i*(paso+1) <= Xn) && (Xn <= i*(paso+1) + paso)){
					normal[0] = 1.0;
					normal[1] = 0.0;
					normal[2] = 0.0;
					return normal;
				}
                break;
            default:
                break;
		}
	}

	//NUNCA debería llegar acá
	return 0;
}

float* Cubo::getNormalArista(int Xn, int Yn, int Zn){
	return getNormal(Xn, Yn, Zn);
}

bool Cubo::esArista(int Xn, int Yn, int Zn){
	//Si es piso o techo, vuelve true

    if ( (Zn == 0) || (Zn == cantidadDePuntosEnAlto()) )
		return true;
	float* punto = getPunto(Xn, Yn, Zn);

	if ( ((punto[0] ==  lado/2.0) && (punto[1] ==  lado/2.0)) ||
		 ((punto[0] == -lado/2.0) && (punto[1] ==  lado/2.0)) ||
		 ((punto[0] == -lado/2.0) && (punto[1] == -lado/2.0)) ||
		 ((punto[0] ==  lado/2.0) && (punto[1] == -lado/2.0))){
			delete []punto;
			return true;
	}
	return false;
}