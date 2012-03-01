#pragma once
#include <GL\freeglut.h>
#include "../BulletPhysics/src/btBulletDynamicsCommon.h"

class ModeloFisica
{
public:
	ModeloFisica(void);

	void inicializar();

	void pasoDeSimulacion();

	void dibujar();

	void dibujarCubo();

	void reiniciar();

	~ModeloFisica(void);

private:

	void liberarMemoriaMundo();
	void dibujarRampa();

	void inicializarCubo();
	void inicializarRampa();
	void inicializarVerticesCubo();
	void inicializarVector(float *vector,float x,float y,float z);
	inline void copiarVectorMV(btScalar *m){ 		for(int i=0; i< 16; i++)	mMV[i] = m[i];	}
	void multMatriz(float* vector);

	double mMV[16];

	float **vertices;
	int cantidadVertices;
	float ladoCubo;


	btDiscreteDynamicsWorld *mundoDinamico;

	btAlignedObjectArray<btCollisionShape*> objetosDeColision;

	btBroadphaseInterface* faseGeneral;

	btCollisionDispatcher* despachadorDeColisiones;

	btConstraintSolver *solucionadorRestricciones;

	btDefaultCollisionConfiguration* configColision;

	btRigidBody** cubo;
	int cantCubos;

};

