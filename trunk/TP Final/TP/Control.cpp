#include "Control.h"


float Control::posicionPorDefecto[3] = {15.0, 15.0, 5.0};
float Control::atPorDefecto[3] = { 0.0,  0.0, 0.0};
float Control::upPorDefecto[3] = { 0.0,  0.0, 1.0}; 

Camara* Control::camara = new Camara(&atPorDefecto[0], &posicionPorDefecto[0], &upPorDefecto[0]);

EscenaGrafica* Control::escena = new EscenaGrafica();

ManejadorDeBotellas *manejadorBotellas = new ManejadorDeBotellas();

Control::Control(bool debug){
	this->debug = debug;

	aplicacionCorriendo = true;

	this->inicializar();
	escena->agregarObjetosGraficos(this->cantObjetosTotales,this->objetosGraficos);


}
Control::~Control(){
	//delete camara;
}

void Control::teclado(unsigned char tecla, int x, int y){
	tecla = tolower(tecla);
	camara->controladorDeTeclado(tecla);
	//Cualquier otro control inherente al teclado va acá, 
	//junto con la discriminación entre release y debug mode
	switch (tecla){
	case 'q':	//liberarMemoria();
				exit(0); 
				break;
	default: break;
	}

	glutPostRedisplay();
}

void Control::mouse(int button, int state, int x, int y){
	camara->controladorBotonesMouse(button, state, x, y);
	//Cualquier otro control inherente al mouse va acá, 
	//junto con la discriminación entre release y debug mode

	glutPostRedisplay();
}

void Control::mouseMov(int x, int y){
	camara->controladorMovMouse(x, y);
	//Cualquier otro control inherente al mouse en movimiento va acá, 
	//junto con la discriminación entre release y debug mode

	glutPostRedisplay();
}

void Control::actualizarDatos(){

	if(aplicacionCorriendo){

		escena->actualizarEscena();
		manejadorBotellas->comprobarEstadoDeBotellas();
		glutPostRedisplay();	
	}
}


void Control::dibujarEscena(){


	if(aplicacionCorriendo)
		escena->graficar();

}


void Control::inicializar(){
	glewInit();
	this->cantObjetosTotales = 0;

	ObjetoGrafico** objetos = this->inicializarObjetosGraficos();
	ObjetoGrafico** maquinas = this->inicializarMaquinas();
	ObjetoGrafico** botellas = this->inicializarBotellas();

	this->objetosGraficos = new ObjetoGrafico*[this->cantObjetosTotales];

	int indice=0;

	for (int i = 0; i < this->cantObjetos ; i ++)
		this->objetosGraficos[indice + i] = objetos[i];
	indice += this->cantObjetos;


	for (int i = 0; i < this->cantMaquinas; i++)
		this->objetosGraficos[indice + i ] = maquinas[i];
	indice += this->cantMaquinas;

	for (int i = 0; i < this->cantBotellas ; i++)
		this->objetosGraficos[indice + i] = botellas[i];


}


ObjetoGrafico** Control::inicializarMaquinas()
{
	this->cantMaquinas = 5;
	this->cantObjetosTotales += this->cantMaquinas;

	ObjetoGrafico** maquinas= new ObjetoGrafico*[this->cantMaquinas];
	Maquina** _maquinas = new Maquina*[this->cantMaquinas];

	///////////////////////////////
	///Instanciacion de Maquinas///
	///////////////////////////////
	
	MaquinaDeBotellas *p1 = new MaquinaDeBotellas();
	maquinas[0] = p1;
	_maquinas[0] = p1;


	CintaTransportadora *p2 = new CintaTransportadora();
	maquinas[1] = p2;
	_maquinas[1] = p2;

	MaquinaEtiquetadora *p3 = new MaquinaEtiquetadora();
	maquinas[2] = p3;
	_maquinas[2] = p3;


	MaquinaEmbaladora *p4 = new MaquinaEmbaladora();
	maquinas[3] = p4;
	_maquinas[3] = p4;

	MaquinaDeLlenado *p5 = new MaquinaDeLlenado();
	maquinas[4] = p5;
	_maquinas[4] = p5;

	/*
	for (int i=0; i < this->cantMaquinas ; i++)
		_maquinas[i] =  reinterpret_cast<Maquina*>(maquinas[i]->devolverPuntero());
		//_maquinas[i] = (Maquina*) maquinas[i];
		*/

	manejadorBotellas->agregarMaquinas(this->cantMaquinas,_maquinas);

	return maquinas;

}

ObjetoGrafico** Control::inicializarObjetosGraficos()
{
	this->cantObjetos = 2;
	this->cantObjetosTotales += this->cantObjetos;

	ObjetoGrafico** objetos = new ObjetoGrafico*[this->cantObjetos];


	objetos[0] = new CuartoDeMaquinas;
	objetos[1] = new LamparaDeTecho((CuartoDeMaquinas*)objetos[0]);


	return objetos;

}

ObjetoGrafico** Control::inicializarBotellas()
{
	this->cantObjetosTotales++;
	this->cantBotellas = 3;

	ObjetoGrafico** botellas = new ObjetoGrafico*;

	ConjuntoDeBotellas *conjunBotellas = new ConjuntoDeBotellas(this->cantBotellas);
	botellas[0] = conjunBotellas;

//	for (int i=0; i < this->cantBotellas; i++)
//		botellas[i] = new Botella();


//	Botella** _botellas = new Botella*[this->cantBotellas];
	
//	for (int i = 0; i < this->cantBotellas ; i++ )
//		_botellas[i] = (Botella*)botellas[i];

	manejadorBotellas->agregarBotellas(conjunBotellas->cantidadDeBotellas(),conjunBotellas->devolverBotellas());


	return botellas;

}

void Control::liberarMemoria()
{	
	aplicacionCorriendo = false;

	delete escena;
	delete manejadorBotellas;
	delete camara;

}
