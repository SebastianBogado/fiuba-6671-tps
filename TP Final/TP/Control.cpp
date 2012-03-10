#include "Control.h"

Camara* Control::camara = Camara::getInstancia();

EscenaGrafica* Control::escena = new EscenaGrafica();

ManejadorDeBotellas *manejadorBotellas = new ManejadorDeBotellas();

CintaTransportadora *cintaTransportadora;

ManejadorDeCajones *manejadorCajones = new ManejadorDeCajones();

InterfazMotorDeFisica *motorFisica = new InterfazMotorDeFisica();

static Control* instancia;

vec2 Control::tamañoVentana = vec2(0.0);



Control::Control(bool debug, vec2& tamañoVentana){
	this->debug = debug;

	aplicacionCorriendo = true;

	this->tamañoVentana = tamañoVentana;

	this->inicializar();
	
	instancia = this;

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

	case 'm':
		cintaTransportadora->aumentarDiscretizacionDeCinta(); 
		break;
	case 'n':
		cintaTransportadora->disminuirDiscretizacionDeCinta();
		break;

//	case 'r':
//		reiniciarAplicacion();
//		break;


	case 'r':
		escena->cambiarActualizarReflexion(); break;

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

		manejadorCajones->comprobarCajones();
		motorFisica->pasoDeSimulacion();
		//motorFisica->
		glutPostRedisplay();	
	}
}


void Control::dibujarEscena(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt (camara->eye()[0], camara->eye()[1], camara->eye()[2],
			   camara->at()[0], camara->at()[1], camara->at()[2],
			   camara->up()[0], camara->up()[1], camara->up()[2]);

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


	//Se Agregan los objetos
	escena->agregarObjetosGraficos(this->cantObjetosTotales,this->objetosGraficos);

}


ObjetoGrafico** Control::inicializarMaquinas()
{
	this->cantMaquinas = 6;
	this->cantObjetosTotales += this->cantMaquinas;

	ObjetoGrafico** maquinas= new ObjetoGrafico*[this->cantMaquinas];
	Maquina** _maquinas = new Maquina*[this->cantMaquinas];

	///////////////////////////////
	///Instanciacion de Maquinas///
	///////////////////////////////
	

	CintaTransportadora *p1 = new CintaTransportadora();
	maquinas[0] = p1;
	_maquinas[0] = p1;
	cintaTransportadora = p1;

	MaquinaDeBotellas *p2 = new MaquinaDeBotellas();
	maquinas[1] = p2;
	_maquinas[1] = p2;

	MaquinaEmbaladora *p3 = new MaquinaEmbaladora();
	maquinas[2] = p3;
	_maquinas[2] = p3;
	//SE AGREGA LA MAQUINA AL CAJON
	manejadorCajones->definirMaquina(p3);
	motorFisica->definirMaquinaEmbaladora(p3);
	

	MaquinaEtiquetadora *p4 = new MaquinaEtiquetadora();
	maquinas[3] = p4;
	_maquinas[3] = p4;
	
		

	MaquinaTapadora *p5 = new MaquinaTapadora();
	maquinas[4] = p5;
	_maquinas[4] = p5;

	MaquinaDeLlenado *p6 = new MaquinaDeLlenado();
	maquinas[5] = p6;
	_maquinas[5] = p6;
	escena->fijarObjetosReflectivos(p6);
	/*
//	for (int i=0; i < this->cantMaquinas ; i++)
	//	_maquinas[i] =  reinterpret_cast<Maquina*>(maquinas[i]->devolverPuntero());
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
	motorFisica->definirHabitacion((CuartoDeMaquinas*)objetos[0]);

	objetos[1] = new LamparaDeTecho((CuartoDeMaquinas*)objetos[0]);
	escena->posicionarLucesEnIluminacion((LamparaDeTecho*)objetos[1]);

	//Para Testear las posiciones de las Luces
	/*
	for (int i=0; i < 6 ; i++)
		vec3 posicion = ((LamparaDeTecho*)objetos[1])->posicionDeLuz(i);
	*/

	return objetos;

}

ObjetoGrafico** Control::inicializarBotellas()
{
	this->cantObjetosTotales += 2;
	this->cantBotellas = 7;

	ObjetoGrafico** botellas = new ObjetoGrafico*[2];

	ConjuntoDeBotellas *conjunBotellas = new ConjuntoDeBotellas(this->cantBotellas);
	botellas[0] = conjunBotellas;

	CajonesDeBotellas *cajones = new CajonesDeBotellas(conjunBotellas);
	botellas[1] = cajones;

	manejadorCajones->definirCajones(cajones);
	manejadorCajones->definirInterfaz(motorFisica);
	
	

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
	delete manejadorCajones;
	delete motorFisica;
	//delete camara;

}


void Control::reiniciarAplicacion()
{
	instancia->liberarMemoria();



	//Se intancia todo nuevamente

	Control::escena = new EscenaGrafica();

	manejadorBotellas = new ManejadorDeBotellas();

	manejadorCajones = new ManejadorDeCajones();

	motorFisica = new InterfazMotorDeFisica();

	aplicacionCorriendo = true;
	instancia->inicializar();

}


vec2 Control::getTamañoVentana(){ return tamañoVentana; }
