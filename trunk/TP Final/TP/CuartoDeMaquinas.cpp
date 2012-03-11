#include "CuartoDeMaquinas.h"


CuartoDeMaquinas::CuartoDeMaquinas(void)
{

	this->posicionObjeto = new float[3];

	posicionObjeto[0] = 0.0;
	posicionObjeto[1] = 0.0;
	posicionObjeto[2] = 0.0;

	this->ancho = 40.0;
	this->largo = 30.0;
	this->alto = 12.0;

	this->inicializarVertices();

	//this->rutaTextura = "..\\ShadersTest\\etiquetaCoca.png";
	this->rutaTextura = ".\\Recursos\\Piso.jpg";

	
	this->rutaShaderDeVertices = "..\\ShadersTest\\ObjetoTexturado.vert";
	this->rutaShaderDeFragmentos = "..\\ShadersTest\\ObjetoTexturado.frag";

	this->ini();


	char* rutaTexturaPared = ".\\Recursos\\Pared.jpg";

	texturaIDPared = SOIL_load_OGL_texture(rutaTexturaPared, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID,
										SOIL_FLAG_INVERT_Y | SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_TEXTURE_REPEATS);

	if (! texturaIDPared)
		cout << SOIL_last_result() << endl;

	

}

void CuartoDeMaquinas::graficar(){

	//this->graficarBase();

	this->aplicarPhongTexturado();

	float normal[3] = { 0.,1.,0.};

	glDisable(GL_LIGHTING);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texturaID);

	this->definirCoordTextura(vec2(0.0,0.0),vec2(2.0,0.0),vec2(0.0,2.0),vec2(2.0,2.0));
	this->dibujarParedTexturada(normal,0,1,3,2);

	glBindTexture(GL_TEXTURE_2D, texturaIDPared);

	//Pared 0
	this->definirCoordTextura(vec2(0.0,0.0),vec2(1.5,0.0),vec2(0.0,1.0),vec2(1.5,1.0));
	this->dibujarParedTexturada(normal,0,1,4,5);

	//Pared 1
	this->definirCoordTextura(vec2(0.0,0.0),vec2(1.5,0.0),vec2(0.0,1.0),vec2(1.5,1.0));
	this->dibujarParedTexturada(normal,1,2,5,6);

	
	this->definirCoordTextura(vec2(0.0,0.0),vec2(1.5,0.0),vec2(0.0,1.0),vec2(1.5,1.0));
	this->dibujarParedTexturada(normal,2,3,6,7);
	
	this->definirCoordTextura(vec2(0.0,0.0),vec2(1.5,0.0),vec2(0.0,1.0),vec2(1.5,1.0));
	this->dibujarParedTexturada(normal,3,0,7,4);

	this->detenerPhongTexturado();
}


void CuartoDeMaquinas::actualizarAtributos(){ }

void CuartoDeMaquinas::definirMateriales(){
	material.colorAmb = vec3(0.0);
	material.colorDif = vec3(0.0);
	material.colorEspec = vec3(0.2, 0.2, 0.2);
	material.brillo = 2.0;
}

btRigidBody* CuartoDeMaquinas::cuerpoRigido()
{


	float *posPiso = this->vectorPosicion();
	float largoX = this->valorLargoEnX();
	float largoY = this->valorLargoEnY();
	btScalar masaInfinita = 0.0;



	//btCollisionShape* formaDelPiso = new btBoxShape(btVector3(50.,50.,1.));
	btCollisionShape* formaDelPiso = new btStaticPlaneShape(btVector3(0,0,1),btScalar(0.));

	btCollisionShape* formaDePared1 = new btStaticPlaneShape(btVector3(-1,0,0),-btScalar(this->valorLargoEnX()+this->vectorPosicion()[0]));
	btCollisionShape* formaDePared2 = new btStaticPlaneShape(btVector3(1,0,0),btScalar(this->vectorPosicion()[0]));

	btCollisionShape* formaDePared3 = new btStaticPlaneShape(btVector3(0,-1,0),-btScalar(this->valorLargoEnY()+this->vectorPosicion()[1]));
	btCollisionShape* formaDePared4 = new btStaticPlaneShape(btVector3(0,1,0),btScalar(this->vectorPosicion()[1]));

	btCollisionShape* formaDelTecho = new btStaticPlaneShape(btVector3(0,0,-1),-btScalar(this->valorAltura()) );

//	this->objetosDeColision.push_back(formaDelPiso);

	btTransform transformador;
	transformador.setIdentity();
	transformador.setOrigin(btVector3(0,0,0));

	btCompoundShape* formaHabitacion = new btCompoundShape();

	formaHabitacion->addChildShape(transformador,formaDelPiso);
	formaHabitacion->addChildShape(transformador,formaDePared1);
	formaHabitacion->addChildShape(transformador,formaDePared2);
	formaHabitacion->addChildShape(transformador,formaDePared3);
	formaHabitacion->addChildShape(transformador,formaDePared4);
	formaHabitacion->addChildShape(transformador,formaDelTecho);



	btScalar masa(0.);

	btVector3 inerciaLocal(0,0,0);

	btDefaultMotionState* estadoMovPiso = new btDefaultMotionState(transformador);

	//btRigidBody::btRigidBodyConstructionInfo infoCuerpoRigido(masa,estadoMovPiso,formaDelPiso,inerciaLocal);
	btRigidBody::btRigidBodyConstructionInfo infoCuerpoRigido(masa,estadoMovPiso,formaHabitacion,inerciaLocal);

	btRigidBody *cuerpoRigidoDeHabitacion = new btRigidBody(infoCuerpoRigido);

	cuerpoRigidoDeHabitacion->setFriction(btScalar(0.35));

	return cuerpoRigidoDeHabitacion;

	//this->mundoDinamico->addRigidBody(cuerpoRigidoDelPiso);

}


CuartoDeMaquinas::~CuartoDeMaquinas(void)
{
	delete[] this->posicionObjeto;
}
