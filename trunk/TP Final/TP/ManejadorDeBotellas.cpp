#include "ManejadorDeBotellas.h"


ManejadorDeBotellas::ManejadorDeBotellas(void)
{
	this->inicializar();
}

ManejadorDeBotellas::ManejadorDeBotellas(int cantBotellas, Botella** botellas,int cantMaquinas,Maquina **maquinas)
{
	this->inicializar();

	this->agregarBotellas(cantBotellas,botellas);
	this->agregarMaquinas(cantMaquinas,maquinas);

}

void ManejadorDeBotellas::inicializar()
{
	this->hayAnimacionesActivas = false;
	this->botellasAgregadas = false;
	this->maquinasAgregadas = false;

	this->botellas.clear();
	this->maquinas.clear();


	this->distanciaMaximaParaAnimacion = 0.1;

	this->manejadorDeCinta = new ManejadorDeBotellasEnCinta();

}


void ManejadorDeBotellas::agregarBotellas(int cantBotellas,Botella** botellas)
{
	if(!this->botellasAgregadas){

		for (int i=0; i < cantBotellas; i++)
			this->botellas.push_back(botellas[i]);

		this->botellasAgregadas = true;
	}

	this->manejadorDeCinta->agregarBotellas(this->botellas);
}


void ManejadorDeBotellas::agregarMaquinas(int cantMaquinas,Maquina** maquinas)
{

	if(!this->maquinasAgregadas && cantMaquinas >= 1){

		//No se toma en cuenta la CintaTransportadora
		this->indiceBotellasProximas = new  int[cantMaquinas-1];

		for (int i=0; i < cantMaquinas; i++)
		{
			if (maquinas[i]->tipo() == TipoMaquina::Transportadora)
			{
				this->manejadorDeCinta->definirCintaTransportadora((CintaTransportadora*)(maquinas[i]));
			}
			else
			{
				this->maquinas.push_back(maquinas[i]);
			}
			
			this->indiceBotellasProximas[i] = 0;
		}		

		this->maquinasAgregadas = true;
	}


}


void ManejadorDeBotellas::comprobarEstadoDeBotellas()
{

	this->comprobarAnimaciones();

	if( this->hayAnimacionesActivas){
		this->manejadorDeCinta->detenerCinta();
	}
	else
	{	this->manejadorDeCinta->actualizarPosicionesDeBotellas();
		this->manejadorDeCinta->desplazarCinta();
	}
}

void ManejadorDeBotellas::comprobarAnimaciones()
{

	float distanciaParaAnimacion;

	if (!this->hayAnimacionesActivas)
	{

		for (int i=0 ; i < this->maquinas.size() ; i++)
		{

			distanciaParaAnimacion = this->calcularDistanciaPlana(	this->maquinas[i]->posicionPlanaDeObjetoAnimado(),
																	this->botellas[indiceBotellasProximas[i]]->vectorPosicion());
																
			if (distanciaParaAnimacion <= this->distanciaMaximaParaAnimacion){
				this->hayAnimacionesActivas = true;

				this->maquinas[i]->iniciarAnimacion(this->botellas[indiceBotellasProximas[i]]);
				this->asignarProximaBotella(i);

			}

		}
	}
	else
	{
		bool AnimacionesFinalizadas = true;

		for (int i=0; i < this->maquinas.size(); i++)
			AnimacionesFinalizadas = AnimacionesFinalizadas && this->maquinas[i]->animacionFinalizada();

		this->hayAnimacionesActivas = !(AnimacionesFinalizadas);
		

	}
}


void ManejadorDeBotellas::asignarProximaBotella(int numMaquina){

	if (this->indiceBotellasProximas[numMaquina] < this->botellas.size()-1)
	{
		this->indiceBotellasProximas[numMaquina]++;
	}
	else
	{
		this->indiceBotellasProximas[numMaquina] = 0;
	}

}

float ManejadorDeBotellas::calcularDistanciaPlana(float* p1,float* p2)
{
	float res = 0.0;
	float parcial =0.0;

	for (int i=0; i < 2; i++)
	{
		parcial = p1[i] - p2[i];

		parcial = parcial * parcial;

		res += parcial;
	}

	return res;
}

ManejadorDeBotellas::~ManejadorDeBotellas(void)
{
	delete[] this->indiceBotellasProximas;
	delete this->manejadorDeCinta;

}
