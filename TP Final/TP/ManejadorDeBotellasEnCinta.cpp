#include "ManejadorDeBotellasEnCinta.h"


ManejadorDeBotellasEnCinta::ManejadorDeBotellasEnCinta(void)
{
	this->inicializar();
}

void ManejadorDeBotellasEnCinta::agregarBotellas(vector<Botella*> &botellas)
{

	if(!this->botellasAgregadas)
	{
		this->botellas = botellas;
		this->botellasAgregadas = true;

		this->posDeTramosDeBotellas = new float[this->botellas.size()];

		for (int i=0; i < this->botellas.size() ; i++)
		{
			this->posDeTramosDeBotellas[i] = 0.0;
		}
		
		this->inicializarPoscionesDeBotellas();
	}
}

void ManejadorDeBotellasEnCinta::inicializarPoscionesDeBotellas()
{

	if (this->botellasAgregadas && this->cinta )
	{
		for (int i=0; i < this->botellas.size() ; i++)
		{
			this->cinta->nuevaPosicion(	this->posDeTramosDeBotellas[i],
										this->botellas[i]->vectorPosicion());

		}

	}

}

void ManejadorDeBotellasEnCinta::definirCintaTransportadora(CintaTransportadora* cinta)
{
	if (this->cinta == NULL)
	{
		this->cinta = cinta;
		this->inicializarPoscionesDeBotellas();
	}

}

void ManejadorDeBotellasEnCinta::inicializar()
{

	this->botellasAgregadas = false;
	//this->cintaEnMovimiento = false;
	this->distanciaMinimaEntreBotellas = 3.0;

	this->cinta = NULL;

}

void ManejadorDeBotellasEnCinta::actualizarPosicionesDeBotellas()
{
	if(this->cinta->cintaActiva())
	{	
		bool actualizacionFinalizada = false;
		float distanciaEntreBotellas;
		for(int i=0; i < this->botellas.size() && !actualizacionFinalizada ; i++)
		{	

			if ( i > 0)
			{
				distanciaEntreBotellas = this->calcularDistancia(this->posDeTramosDeBotellas[i],this->posDeTramosDeBotellas[i-1]);

				actualizacionFinalizada = (this->distanciaMinimaEntreBotellas > distanciaEntreBotellas );
			}

			if (!actualizacionFinalizada)
			{	

				float nuevaPosicion = this->cinta->nuevaPosicionDeTramo(this->posDeTramosDeBotellas[i]);
				//this->posDeTramosDeBotellas[i] = this->cinta->nuevaPosicionDeTramo(this->posDeTramosDeBotellas[i]);

				if (nuevaPosicion < this->posDeTramosDeBotellas[i])
					this->botellas[i]->reiniciarAtributos();

				this->cinta->nuevaPosicion(nuevaPosicion,this->botellas[i]->vectorPosicion());
				this->posDeTramosDeBotellas[i] = nuevaPosicion;

			}
			
		}

	}

}

float ManejadorDeBotellasEnCinta::calcularDistancia(float p1,float p2)
{

	float res = p1 - p2;

	if ( res < 0.0 )
		res = - res;

	return res;

}

void ManejadorDeBotellasEnCinta::desplazarCinta(){ 
	
	//this->cintaEnMovimiento = true;
	this->cinta->desplazarCinta();

}


void ManejadorDeBotellasEnCinta::detenerCinta(){

	//this->cintaEnMovimiento = false;
	this->cinta->detenerCinta();
}
ManejadorDeBotellasEnCinta::~ManejadorDeBotellasEnCinta(void)
{
}
