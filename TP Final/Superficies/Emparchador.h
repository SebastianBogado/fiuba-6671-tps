#ifndef __EMPARCHADOR_H__
#define __EMPARCHADOR_H__

#include "Superficie.h"
#include <GL/glut.h>

class Emparchador{
    public:
        static void emparchar(Superficie* superficie, int repeticionesDeLaTexturaS = 1, int repeticionesDeLaTexturaT = 1);

		/* Util�cese el siguiente s�lo para debuggear
		 * Nota: las normales est�n escaladas al 30% porque en esta aplicaci�n todas las figuras
		 * son de medidas peque�as, y se ve�an muy grandes las normales unitarias
		 */
		static void verNormales(Superficie* superficie);
    protected:
        void emparcharTapas(Superficie* superficie);
};

#endif // __EMPARCHADOR_H__
