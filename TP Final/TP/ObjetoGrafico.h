#pragma once
class ObjetoGrafico
{
public:
	ObjetoGrafico(void);


	/*
		Funcion que dibuja al objeto en la escena
	*/

	virtual void graficar();

	/*
		Funciones para el manejo de shader del objeto
	*/
	
	virtual void aplicarShader()=0;
	virtual void detenerShader()=0;

	/*
		... y mas cosas que faltan definir (como texturas, etc)
	*/


	~ObjetoGrafico(void);
};

