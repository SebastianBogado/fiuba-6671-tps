#pragma once
#include "Curva.h"
#include <GL/glut.h>

class Delineador{
public:
	static void delinear(Curva* curva, int discretizacion);
};

