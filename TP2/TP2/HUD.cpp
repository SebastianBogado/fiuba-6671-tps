#include "HUD.h"

HUD::HUD(int ventanaPrincipal, int ancho, int alto){
	this->mouseCallbacks;
	this->ancho = ancho;
	this->alto = alto;
	this->ventanaPrincipal = ventanaPrincipal;

	this->admintText=AdministradorTexturas::getInstancia();

	this->inicializarMenuFormas();
	this->inicializarMenuMateriales();
	this->inicializarMenuDeformaciones();
}

HUD::~HUD(){
	delete this->menuDeformaciones;
	delete this->menuFormas;
	delete this->menuMateriales;
}

void HUD::inicializarMenuFormas(){
	
	
	Boton botonEsfera(BOTON_ESFERA, mouseCallbacks.getCallback(BOTON_ESFERA));
	
	Boton botonCubo(BOTON_CUBO, mouseCallbacks.getCallback(BOTON_CUBO));
	
	Boton botonToroide(BOTON_TOROIDE, mouseCallbacks.getCallback(BOTON_TOROIDE));

	Boton botonCilindro(BOTON_CILINDRO, mouseCallbacks.getCallback(BOTON_CILINDRO));

	Boton botones[4]={botonEsfera, botonCubo, botonToroide, botonCilindro};

	propiedades prop = calcularTamanioDeMenuVertical(true);

	this->menuFormas = new MenuDeCuatroBotones(this->ventanaPrincipal, prop.x, prop.y, prop.w, prop.h,botones);// botones);
}

void HUD::inicializarMenuMateriales(){

	Boton botonMaterialSombreadoBrillante(BOTON_MATERIAL_SOMBREADO_BRILLANTE, mouseCallbacks.getCallback(BOTON_MATERIAL_SOMBREADO_BRILLANTE));


	Boton botonMaterialSombreadoTexturado(BOTON_MATERIAL_SOMBREADO_TEXTURADO, mouseCallbacks.getCallback(BOTON_MATERIAL_SOMBREADO_TEXTURADO));


	Boton botonMaterialReflectivo(BOTON_MATERIAL_REFLECTIVO, mouseCallbacks.getCallback(BOTON_MATERIAL_REFLECTIVO));


	Boton botonMaterialSombreadoSemimate(BOTON_MATERIAL_SOMBREADO_SEMIMATE, mouseCallbacks.getCallback(BOTON_MATERIAL_SOMBREADO_SEMIMATE));

	Boton botones[4]={botonMaterialSombreadoBrillante, botonMaterialSombreadoTexturado, 
		botonMaterialReflectivo,botonMaterialSombreadoSemimate};

	propiedades prop = calcularTamanioDeMenuHorizontal();

	this->menuMateriales = new MenuDeCuatroBotones(this->ventanaPrincipal, prop.x, prop.y, prop.w, prop.h, botones);
}

void HUD::inicializarMenuDeformaciones(){
	
	Boton botonRetorcer(BOTON_RETORCER, mouseCallbacks.getCallback(BOTON_RETORCER));

	Boton botonRuido(BOTON_RUIDO, mouseCallbacks.getCallback(BOTON_RUIDO));

	Boton botonDoblar(BOTON_DOBLAR, mouseCallbacks.getCallback(BOTON_DOBLAR));

	Boton botonEsferizar(BOTON_ESFERIZAR, mouseCallbacks.getCallback(BOTON_ESFERIZAR));

	Boton botones[4]={botonRetorcer,botonRuido, botonDoblar, botonEsferizar};

	propiedades prop = calcularTamanioDeMenuVertical(false);

	this->menuDeformaciones = new MenuDeCuatroBotones(this->ventanaPrincipal, prop.x, prop.y, prop.w, prop.h, botones);
}

HUD::propiedades HUD::calcularTamanioDeMenuHorizontal(){
	propiedades prop;
	//constantes calculadas en papel y lápiz, no las voy a justificar
	prop.x = this->ancho * ((float)3/(float)16);
	prop.y = this->alto/24;

	prop.w = this->ancho * ((float)5/(float)8);
	prop.h = this->alto * ((float)5/(float)24);

	return prop;
}
HUD::propiedades HUD::calcularTamanioDeMenuVertical(bool esElIzquierdo){
	propiedades prop;
	//constantes calculadas en papel y lápiz, no las voy a justificar
	if (esElIzquierdo)
		prop.x = this->ancho / 32;
	else
		prop.x = this->ancho * ((float)13/(float)16);
	
	prop.y = this->alto/4;

	prop.w = this->ancho * ((float)5/(float)32);
	prop.h = this->alto * ((float)17/(float)24);

	return prop;
}

void HUD::resize(int nuevoAncho, int nuevoAlto){
	this->ancho = nuevoAncho;
	this->alto = nuevoAlto;
	//menú de formas
	propiedades prop = calcularTamanioDeMenuVertical(true);
	this->menuFormas->resize(prop.x, prop.y, prop.w, prop.h);

	//menú de materiales
	prop = calcularTamanioDeMenuHorizontal();
	this->menuMateriales->resize(prop.x, prop.y, prop.w, prop.h);

	//menú de deformaciones
	prop = calcularTamanioDeMenuVertical(false);
	this->menuDeformaciones->resize(prop.x, prop.y, prop.w, prop.h);
}