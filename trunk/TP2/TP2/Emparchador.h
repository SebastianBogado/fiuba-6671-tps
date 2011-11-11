#ifndef __EMPARCHADOR_H__
#define __EMPARCHADOR_H__

#include "Superficie.h"
#include <GL/glut.h>

class Emparchador{
    public:
        void emparchar(Superficie* superficie);
		void emparchar2(Superficie* superficie);
		void verNormales(Superficie* superficie);
    protected:
        void emparcharTapas(Superficie* superficie);
};

#endif // __EMPARCHADOR_H__
