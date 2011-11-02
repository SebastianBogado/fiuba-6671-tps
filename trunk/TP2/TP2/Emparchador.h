#ifndef __EMPARCHADOR_H__
#define __EMPARCHADOR_H__

#include "Superficie.h"
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtx/normal.hpp>
using glm::gtx::normal::triangleNormal;

extern bool esArista;

class Emparchador{
    public:
        void emparchar(Superficie* superficie);
    protected:
        void emparcharTapas(Superficie* superficie);
};

#endif // __EMPARCHADOR_H__
