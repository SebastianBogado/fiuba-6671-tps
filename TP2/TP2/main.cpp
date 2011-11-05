///
/// 66.71 Sistemas Graficos
/// Framework de trabajo para el TP1
/// 2do Cuatrimestre 2011
///
/// info@sg6671.com.ar
///

#ifndef _DEBUG
#pragma comment(linker,"/subsystem:\"windows\" /entry:\"mainCRTStartup\"") //evitar consola en modo Release
#endif

#include <GL/glew.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <iostream>
using namespace std;
#include "HUD.h"
#include "ShaderManager.h"
#include "Emparchador.h"
#include "Esfera.h"
#include "Cubo.h"
#include "Toroide.h"
#include "Cilindro.h"
#include "AdministradorTexturas.h"


#include "TextureLoader.h"
//para la prueba de Texturas...
glTexture textura;
TextureLoader *texLoad;


// Tamaño de la ventana
GLfloat window_size[2];
#define W_WIDTH window_size[0]
#define W_HEIGHT window_size[1]

HUD* hud;
ShaderManager* shaderManager;


// Variables que controlan la ubicación de la cámara en la Escena 3D
float eye[3] = {3.0, 3.0, 2.0};
float at[3]  = { 0.0,  0.0, 0.0};
float up[3]  = { 0.0,  0.0, 1.0};

float anguloTheta=3.14/4.0;
float anguloPhi=3.14/4.0;
float difAnguloX=3.14/30.0;
float difAnguloY;
float RadioEsfera=5;
float deltaRadio=0.5;

//Variables de control
extern bool verEsfera;
extern bool verCubo;
extern bool verToroide;
extern bool verCilindro;

extern bool verMaterialSombreadoBrillante;
extern bool verMaterialSombreadoTexturado;
extern bool verMaterialReflectivo;
extern bool verMaterialSombreadoSemimate;

extern bool verRetorcer;
extern bool verRuido;
extern bool verDoblar;
extern bool verEsferizar;

extern bool usarShaders;

extern bool luzPrincipal;
extern bool luzSecundaria;

extern float tiempo;

//Efecto "retorcer"
extern float anguloDeRetorsion;

//Efecto de esferizar
extern float centro[];

//Efecto de "doblar"
extern float distanciaDeDoblado; 
extern float incrementoDeDistancia;

//Efecto de ruido
//Ondas
struct Onda{
	float longitud;
	float frecuencia;
	float amplitud;
};

extern float n;
extern Onda ondaEnX;
extern Onda ondaEnY;
extern Onda ondaEnZ;
extern float arista;

//Parámetro que se modifica al apretar las flechitas
float* parametroSeleccionado;
float variacion = 1.0;
bool modificandoOndaEnX = true;

// Variables de las luces

float luzPrincipalColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};
float luzPrincipalPosicion[3] = {-10.0f, -10.0f, 3.0f};
float luzPrincipalAmbiente[4] = {0.5f, 0.5f, 0.5f, 1.0f};

float luzSecundariaColor[4] = {0.5f, 0.5f, 0.5f, 0.5f};
float luzSecundariaPosicion[3] = {5.0f, 5.0f, 3.0f};
float luzSecundariaAmbiente[4] = {0.1f, 0.1f, 0.1f, 1.0f};

//Material sombreado brillante
GLfloat materialSombreadoBrillanteAmbiente[4] = {0.3, 0.8, 0.7, 1.0};
GLfloat materialSombreadoBrillanteDifusa[4] =  {0.3, 0.8, 0.7, 1.0};
GLfloat materialSombreadoBrillanteEspecular[4] = {0.3, 0.8, 0.7, 1.0};
GLfloat materialSombreadoBrillanteBrillo[] = {5};
GLfloat materialSombreadoBrillanteEmisiva[3] = {0.15,0.4,0.35};

//Material sombreado semimate
GLfloat materialSombreadoSemimateAmbiente[4] = {0.5, 0.6, 0.7, 1.0};
GLfloat materialSombreadoSemimateDifusa[4] =  {7.0, 8.0, 9.0, 1.0};
GLfloat materialSombreadoSemimateEspecular[4] = {0.1, 0.1, 0.1, 0.1};
GLfloat materialSombreadoSemimateBrillo[] = {32};
GLfloat materialSombreadoSemimateEmisiva[3] = {1.0,1.0,1.0};
  		 	 	 

// Handle para el control de las Display Lists
GLuint dl_handle;
#define DL_ESFERA (dl_handle+0)
#define DL_CUBO (dl_handle+1)
#define DL_TOROIDE (dl_handle+2)
#define DL_CILINDRO (dl_handle+3)
#define DL_CAJA_CIELO (dl_handle+4)


float norma3(float* p){
    float resultado=0;

    resultado+=p[0]*p[0];
    resultado+=p[1]*p[1];
    resultado+=p[2]*p[2];

    resultado=sqrt(resultado);

    return resultado;
}

void redimensionar(){
	float norma=norma3(eye);

    eye[0]=cos(anguloPhi)*cos(anguloTheta)*norma;
    eye[1]=cos(anguloPhi)*sin(anguloTheta)*norma;
    eye[2]=sin(anguloPhi)*norma;

    RadioEsfera=norma;
}


void redimensionarRadio(){
	eye[0]=cos(anguloPhi)*cos(anguloTheta)*RadioEsfera;
    eye[1]=cos(anguloPhi)*sin(anguloTheta)*RadioEsfera;
    eye[2]=sin(anguloPhi)*RadioEsfera;
}

void Set3DEnv()
{
	glViewport (10, -100, (GLsizei) W_WIDTH, (GLsizei) W_HEIGHT); 
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(60.0, (GLfloat) W_WIDTH/(GLfloat) W_HEIGHT, 1.0, 10.0);
}

void init(void) 
{	

	AdministradorTexturas *adminText=AdministradorTexturas::getInstancia();
	adminText->CargarTexturas();

	Emparchador emparchador;
    Superficie* superficie;


	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);

	dl_handle = glGenLists(5);

	//DLs para las superficies
	glNewList(DL_ESFERA, GL_COMPILE);
	    superficie = new Esfera;
        emparchador.emparchar(superficie);
        delete superficie;
		/*glBegin(GL_TRIANGLES);
			for (float i=-1.5; i <= 1.5; i+=0.1){
				for (float j=-1.5; j <= 1.5; j+=0.1){
					glVertex3f(j,i,0);
					glVertex3f(j+0.1,i,0);
					glVertex3f(j,i+0.1,0);

					glVertex3f(j+0.1,i,0);
					glVertex3f(j+0.1,i+0.1,0);
					glVertex3f(j,i+0.1,0);
				}
			}
		glEnd();*/
	glEndList();
	
	glNewList(DL_CUBO, GL_COMPILE);
        superficie = new Cubo(arista, 16);
        emparchador.emparchar(superficie);
        delete superficie;
    glEndList();

	glNewList(DL_TOROIDE, GL_COMPILE);
        superficie = new Toroide;
		emparchador.emparchar(superficie);
		delete superficie;
	glEndList();
	

	glNewList(DL_CILINDRO, GL_COMPILE);
        superficie = new Cilindro(arista/2.0,arista,32);
        emparchador.emparchar(superficie);
        delete superficie;
	glEndList();


	glNewList(DL_CAJA_CIELO,GL_COMPILE);
		superficie = new Esfera(2.0,32);
       emparchador.emparchar2(superficie);
        delete superficie;

	glEndList();

	glClearColor (0.2148f, 0.2305f, 0.2422f, 0.0f);
    glShadeModel (GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzPrincipalColor);
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzPrincipalAmbiente);
    glLightfv(GL_LIGHT0, GL_POSITION, luzPrincipalPosicion);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, luzSecundariaColor);
    glLightfv(GL_LIGHT1, GL_AMBIENT, luzSecundariaAmbiente);
    glLightfv(GL_LIGHT1, GL_POSITION, luzSecundariaPosicion);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHTING);
	

}


void OnIdle (void)

{	
	
	tiempo += 0.01;
    glutPostRedisplay();


	if(verDoblar){
		distanciaDeDoblado+=incrementoDeDistancia;

		if (glm::abs(distanciaDeDoblado)>=15.0){
			distanciaDeDoblado=-distanciaDeDoblado;
			
			
		}else if(glm::abs(distanciaDeDoblado)<=2){
			incrementoDeDistancia=-incrementoDeDistancia;
			
		}
	}

}

void escena(void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Set3DEnv();
	gluLookAt (eye[0], eye[1], eye[2], at[0], at[1], at[2], up[0], up[1], up[2]);

	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_COLOR_MATERIAL);

	//selección de la deformación
	if (verRetorcer){
		shaderManager->setVertexShader(RETORCER);
		shaderManager->setUniform("anguloDeRetorsion", anguloDeRetorsion);
		shaderManager->setUniform("tiempo", tiempo);

		//setear uniforms y esas cosas
	}
	if (verRuido){
		shaderManager->setVertexShader(RUIDO);
		shaderManager->setUniform("tiempo", tiempo);
		shaderManager->setUniform("n", n);
		shaderManager->setUniform("ondaEnX.longitud", ondaEnX.longitud);
		shaderManager->setUniform("ondaEnX.frecuencia", ondaEnX.frecuencia);
		shaderManager->setUniform("ondaEnX.amplitud", ondaEnX.amplitud);
		shaderManager->setUniform("ondaEnY.longitud", ondaEnY.longitud);
		shaderManager->setUniform("ondaEnY.frecuencia", ondaEnY.frecuencia);
		shaderManager->setUniform("ondaEnY.amplitud", ondaEnY.amplitud);
		shaderManager->setUniform("ondaEnZ.longitud", ondaEnZ.longitud);
		shaderManager->setUniform("ondaEnZ.frecuencia", ondaEnZ.frecuencia);
		shaderManager->setUniform("ondaEnZ.amplitud", ondaEnZ.amplitud);
	}
    if (verDoblar){
		shaderManager->setVertexShader(DOBLAR);
		shaderManager->setUniform("distancia",distanciaDeDoblado);
		shaderManager->setUniform("tiempo", tiempo);
		//setear uniforms y esas cosas
	}
   	if (verEsferizar){
		shaderManager->setVertexShader(ESFERIZAR);
		shaderManager->setUniform("tiempo", tiempo);
		shaderManager->setUniform("centro", centro[0], centro[1], centro[2]);
		//setear uniforms y esas cosas 
	}

	//selección de las luces
	if (luzPrincipal){
		//Cuando esté implementado:	shaderManager->setShaderLuz(LUZ_PRINCIPAL);
		glEnable(GL_LIGHT0);
	}
	else
		glDisable(GL_LIGHT0);
		
	if (luzSecundaria){
		//Cuando esté implementado:	shaderManager->setShaderLuz(LUZ_SECUNDARIA);
		glEnable(GL_LIGHT1);
	}
	else
		glDisable(GL_LIGHT1);

	//selección del material
	if (verMaterialSombreadoBrillante){
		shaderManager->setFragmenShader(MATERIAL_SOMBREADO_BRILLANTE);
		AdministradorTexturas *adminTex = AdministradorTexturas::getInstancia();
		//shaderManager->setUniform("textura",0);//adminTex->getID(Ladrillos));
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSombreadoBrillanteEspecular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialSombreadoBrillanteAmbiente);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, materialSombreadoBrillanteBrillo);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialSombreadoBrillanteDifusa);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, materialSombreadoBrillanteEmisiva);
		//setear uniforms y esas cosas
	}
	if (verMaterialSombreadoTexturado){
		shaderManager->setFragmenShader(MATERIAL_SOMBREADO_TEXTURADO);
		//setear uniforms y esas cosas
	}
	if (verMaterialReflectivo){
		shaderManager->setFragmenShader(MATERIAL_REFLECTIVO);
		//setear uniforms y esas cosas
	}
   	if (verMaterialSombreadoSemimate){
		shaderManager->setFragmenShader(MATERIAL_SOMBREADO_SEMIMATE);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSombreadoSemimateEspecular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialSombreadoSemimateAmbiente);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, materialSombreadoSemimateBrillo);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialSombreadoSemimateDifusa);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, materialSombreadoSemimateEmisiva);
		//setear uniforms y esas cosas
	}
	
	
	//aplicar shaders
	if (usarShaders)
		shaderManager->usar();
	else
		shaderManager->cerrar();

	//selección de primitiva
	if (verEsfera)
		glCallList(DL_ESFERA);
	if (verCubo)
		glCallList(DL_CUBO);
    if (verToroide)
		glCallList(DL_TOROIDE);
   	if (verCilindro)
		glCallList(DL_CILINDRO);
	if (verMaterialReflectivo)
		glCallList(DL_CAJA_CIELO);

	#ifdef _DEBUG // no encontré cómo seguir variables globales :P
	if (verMaterialSombreadoBrillante){
		cout << "materialSombreadoBrillanteAmbiente = {";
		for (int i = 0; i < 4; i++)
			cout << materialSombreadoBrillanteAmbiente[i] << ", ";
		cout << "}" << endl;

		cout << "materialSombreadoBrillanteDifusa = {";
		for (int i = 0; i < 4; i++)
			cout << materialSombreadoBrillanteDifusa[i] << ", ";
		cout << "}" << endl;

		cout << "materialSombreadoBrillanteEspecular = {";
		for (int i = 0; i < 4; i++)
			cout << materialSombreadoBrillanteEspecular[i] << ", ";
		cout << "}" << endl;

			cout << "materialSombreadoBrillanteEmisiva = {";
		for (int i = 0; i < 3; i++)
			cout << materialSombreadoBrillanteEmisiva[i] << ", ";
		cout << "}" << endl;
	
		cout << "materialSombreadoBrillanteBrillo: " << materialSombreadoBrillanteBrillo[0] << endl;
		system("cls");
	}

	if (verMaterialSombreadoSemimate){
		cout << "materialSombreadoSemimateAmbiente = {";
		for (int i = 0; i < 4; i++)
			cout << materialSombreadoSemimateAmbiente[i] << ", ";
		cout << "}" << endl;

		cout << "materialSombreadoSemimateDifusa = {";
		for (int i = 0; i < 4; i++)
			cout << materialSombreadoSemimateDifusa[i] << ", ";
		cout << "}" << endl;

		cout << "materialSombreadoSemimateEspecular = {";
		for (int i = 0; i < 4; i++)
			cout << materialSombreadoSemimateEspecular[i] << ", ";
		cout << "}" << endl;
		
		cout << "materialSombreadoSemimateEmisiva = {";
		for (int i = 0; i < 3; i++)
			cout << materialSombreadoSemimateEmisiva[i] << ", ";
		cout << "}" << endl;

		cout << "materialSombreadoSemimateBrillo: " << materialSombreadoSemimateBrillo[0] << endl;
		system("cls");
	}

	if (verDoblar){
		cout << "distanciaDeDoblado = " << distanciaDeDoblado << endl;
		system("cls");
	}
	#endif

	glutSwapBuffers();
	glutPostRedisplay();
}

void reshape (int w, int h)
{
   	W_WIDTH  = (float)w;
	W_HEIGHT = (float)h;
	
	hud->resize(W_WIDTH, W_HEIGHT);
}
int xOrigen, yOrigen;
void mouse(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_UP) {
			xOrigen = -1;
			yOrigen = -1;
		}
		else  {
			xOrigen = x;
			yOrigen = y;
		}
	}
}

void mouseEnMovimiento(int x, int y){
	if (xOrigen >= 0) {cout << "difAnguloX = " << difAnguloX << endl;
		float aux = asin(x/norma3(eye));
		float aux2 = asin(xOrigen/norma3(eye));
		difAnguloX = x - xOrigen;
	}
	if (yOrigen >= 0){cout << "difAnguloY = " << difAnguloY << endl;
		float aux = asin(y/norma3(eye));
		float aux2 = asin(yOrigen/norma3(eye));
		difAnguloY = y - yOrigen;
	}
	anguloTheta += (0.001* difAnguloX);
	anguloPhi += (0.001 * difAnguloY);
	redimensionar();
}

void rueditaDelMouse(int button, int dir, int x, int y){
	if (dir == 0) return;
	
	if (dir > 0){
		if(RadioEsfera-deltaRadio>0){
			RadioEsfera-=deltaRadio;
			redimensionarRadio();
        }
	}
    else{
		RadioEsfera+=deltaRadio;
        redimensionarRadio();
    }

	glutPostRedisplay();
}

#ifdef _DEBUG
GLfloat* parametroAModificar;
int indice = 0;

void modificarAmbiente(){
	if (verMaterialSombreadoBrillante)
		parametroAModificar = &materialSombreadoBrillanteAmbiente[indice];
	if (verMaterialSombreadoSemimate)
		parametroAModificar = &materialSombreadoSemimateAmbiente[indice];
}
void modificarDifusa(){
	if (verMaterialSombreadoBrillante)
		parametroAModificar = &materialSombreadoBrillanteDifusa[indice];
	if (verMaterialSombreadoSemimate)
		parametroAModificar = &materialSombreadoSemimateDifusa[indice];
}
void modificarEspecular(){
	if (verMaterialSombreadoBrillante)
		parametroAModificar = &materialSombreadoBrillanteEspecular[indice];
	if (verMaterialSombreadoSemimate)
		parametroAModificar = &materialSombreadoSemimateEspecular[indice];
}
void modificarEmisiva(){
	if (verMaterialSombreadoBrillante)
		parametroAModificar = &materialSombreadoBrillanteEmisiva[indice];
	if (verMaterialSombreadoSemimate)
		parametroAModificar = &materialSombreadoSemimateEmisiva[indice];
}
void modificarNormalizado(float &parametro, float variacion){
	parametro += variacion;
	if (parametro > 1.0){
		parametro = 1.0;
		return;
	}
	if (parametro < 0.0){
		parametro = 0.0;
		return;
	}
}

void modificarBrillo(float &brillo, float variacion){
	brillo += variacion;
	if (brillo > 128.0){
		brillo = 128.0;
		return;
	}
	if (brillo < 0.0){
		brillo = 0.0;
		return;
	}
}
#endif

void aumentarParametroSeleccionado(){
	if (parametroSeleccionado == NULL)
		return;
	*parametroSeleccionado += variacion; 
}
void disminuirParametroSeleccionado(){
	if (parametroSeleccionado == NULL)
		return;
	*parametroSeleccionado -= variacion; 
}
void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
#ifdef _DEBUG
		case 'a':
			modificarAmbiente();
			break;
		case 'd':
			modificarDifusa();
			break;
		case 's':
		  modificarEspecular();
		  break;
		case 'e':
		  modificarEmisiva();
		  break;
		case '1':
		indice = 0;
		break;
	case '2':
		indice = 1;
		break;
	case '3':
		indice = 2;
		break;
	case '4':
		indice = 3;
		break;
	case 'p':
		modificarNormalizado(*parametroAModificar, 0.01);
		break;
	case 'l':
		modificarNormalizado(*parametroAModificar, -0.01);
		break;
	case 'o':
		if (verMaterialSombreadoBrillante)
			modificarBrillo(materialSombreadoBrillanteBrillo[0], 1);
		if (verMaterialSombreadoSemimate)
			modificarBrillo(materialSombreadoSemimateBrillo[0], 1);
		break;
	case 'k':
		if (verMaterialSombreadoBrillante)
			modificarBrillo(materialSombreadoBrillanteBrillo[0], -1);
		if (verMaterialSombreadoSemimate)
			modificarBrillo(materialSombreadoSemimateBrillo[0], -1);
		break;
#endif
		case 'q':
			exit(0);
			break;
		case 'c':
			luzPrincipal = !luzPrincipal;
			glutPostRedisplay();
			break;
		case 'v':
			luzSecundaria = !luzSecundaria;
			glutPostRedisplay();
			break;
	  case '5':
		  eye[0] = 0.0;
		  eye[1] = 0.0;
		  eye[2] = 3.0;

		  at[0] = 0.0;
		  at[1] = 0.0;
		  at[2] = 0.0;

		  up[0] = 0.0;
		  up[1] = 1.0;
		  up[2] = 0.0;
		  glutPostRedisplay();
		  break;

	  case '6':
		  eye[0] = 3.0;
		  eye[1] = 3.0;
		  eye[2] = 2.0;

		  at[0] = 0.0;
		  at[1] = 0.0;
		  at[2] = 0.0;

		  up[0] = 0.0;
		  up[1] = 0.0;
		  up[2] = 1.0;
		  glutPostRedisplay();
		  break;
     default:
         break;
   }

	if (verRetorcer)
		variacion = 1.0;
   if (verRuido)
	switch (key){
	case 'x':
		parametroSeleccionado = &n; 
		modificandoOndaEnX = true;
		variacion = 1.0;
		break;
	case 'y':
		parametroSeleccionado = &n; 
		modificandoOndaEnX = false; 
		variacion = 1.0;
		break;
	case 'l':
		parametroSeleccionado = &n; 
		variacion = 1.0;
		break;
	case 'a':
		variacion = 0.01;
		if (modificandoOndaEnX)
			parametroSeleccionado = &ondaEnX.amplitud;
		else
			parametroSeleccionado = &ondaEnY.amplitud;
		break;
	case 'f':
		variacion = 0.01;
		if (modificandoOndaEnX)
			parametroSeleccionado = &ondaEnX.frecuencia;
		else
			parametroSeleccionado = &ondaEnY.frecuencia;
		break;
	default:
		break;
   }

   if (verDoblar)
	   variacion = 0.0005;

   if (verEsferizar){
	   variacion = 0.005;
		switch (key){
		case 'x':
			parametroSeleccionado = &centro[0]; break;
		case 'y':
			parametroSeleccionado = &centro[1]; break;
		case 'z':
			parametroSeleccionado = &centro[2]; break;
		default: break;
		}
	}
}

void teclasParticulares(int key, int x, int y){
	switch(key) {
		case GLUT_KEY_UP :
			aumentarParametroSeleccionado();
			break;
		case GLUT_KEY_DOWN :
			disminuirParametroSeleccionado();
			break;
		case GLUT_KEY_F1 :
			usarShaders = !usarShaders;
			break;
		default:
			break;
	}
}

int main(int argc, char** argv){	
	int ancho = 800;
	int alto = 600;
	int ventanaPrincipal;

	glutInit(&argc, argv);
    glutInitWindowPosition (10, 10);
    glutInitWindowSize (ancho, alto); 
	if (!GLEW_NV_copy_image)
		glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	else
		glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	ventanaPrincipal = glutCreateWindow("66.71 - TP2");
    glutDisplayFunc(escena); 
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(teclasParticulares);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseEnMovimiento);
	glutMouseWheelFunc(rueditaDelMouse);
	glutIdleFunc(OnIdle);
	init ();

	hud = new HUD(ventanaPrincipal, ancho, alto);
	glewInit();

	shaderManager = new ShaderManager();
	
		
	//loop principal
	glutMainLoop();
    return 0;
}
