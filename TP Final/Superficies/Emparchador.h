#ifndef __EMPARCHADOR_H__
#define __EMPARCHADOR_H__

#include "Superficie.h"
#include <GL/glut.h>

class Emparchador{
    public:
        static void emparchar(Superficie* superficie, int repeticionesDeLaTexturaS = 1, int repeticionesDeLaTexturaT = 1);

		/* Utilícese el siguiente sólo para debuggear
		 * Nota: las normales están escaladas al 30% porque en esta aplicación todas las figuras
		 * son de medidas pequeñas, y se veían muy grandes las normales unitarias
		 */
		static void verNormales(Superficie* superficie);
    protected:
        void emparcharTapas(Superficie* superficie);
};

#endif // __EMPARCHADOR_H__
