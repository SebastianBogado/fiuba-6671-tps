#pragma once

#include "MenuDeCuatroBotones.h"
#include "MouseCallbacks.h"
#include "AdministradorTexturas.h"

//esta clase se encarga de armar los menúes y reposicionarlos
class HUD{
public:
	HUD( int ventanaPrincipal, int ancho, int alto);
	void resize(int nuevoAncho, int nuevoAlto);
	~HUD(void);
private:

	AdministradorTexturas *admintText;

	struct propiedades{
		int x;
		int y;
		int w;
		int h;
	};
	int ancho;
	int alto;
	int ventanaPrincipal;
	MenuDeCuatroBotones* menuFormas;
	MenuDeCuatroBotones* menuMateriales;
	MenuDeCuatroBotones* menuDeformaciones;
	MouseCallbacks mouseCallbacks;

	void inicializarMenuFormas();
	void inicializarMenuMateriales();
	void inicializarMenuDeformaciones();

	propiedades calcularTamanioDeMenuHorizontal();
	propiedades calcularTamanioDeMenuVertical(bool esElIzquierdo);	
};

