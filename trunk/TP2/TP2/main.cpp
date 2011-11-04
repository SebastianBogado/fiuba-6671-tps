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

extern bool luzPrincipal;
extern bool luzSecundaria;

extern float tiempo;

//Efector "retorcer"
extern float anguloDeRetorsion;
extern float arista;

//Efecto de "doblar"
extern float distanciaDeDoblado; 
extern float incrementoDeDistancia;

//Efecto de ruido
//Ondas
extern float arista;


// Variables asociadas a única fuente de luz de la escena
float light_color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
float light_position[3] = {-10.0f, -10.0f, 3.0f};
float light_ambient[4] = {0.5f, 0.5f, 0.5f, 1.0f};

//Material sombreado brillante
GLfloat materialSombreadoBrillanteAmbiente[4] = {0.3, 0.8, 0.7, 1.0};
GLfloat materialSombreadoBrillanteDifusa[4] =  {0.3, 0.8, 0.7, 1.0};
GLfloat materialSombreadoBrillanteEspecular[4] = {0.3, 0.8, 0.7, 1.0};
GLfloat materialSombreadoBrillanteBrillo[] = {5};
GLfloat materialSombreadoBrillanteEmisiva[3] = {0.15,0.4,0.35};

//Material sombreado semimate
GLfloat materialSombreadoSemimateAmbiente[4] = {1.0, 1.0, 1.0, 1.0};//{0.329412,0.223529, 0.027451, 1.0};
GLfloat materialSombreadoSemimateDifusa[4] =  {1.0, 1.0, 1.0, 1.0};//{0.780392, 0.568627, 0.113725, 1.0};
GLfloat materialSombreadoSemimateEspecular[4] = {1.0, 1.0, 1.0, 1.0};//{0.992157, 0.941176, 0.807843, 1.0};
GLfloat materialSombreadoSemimateBrillo[] = {32};//{27.8974};
GLfloat materialSombreadoSemimateEmisiva[3] = {1.0,1.0,1.0};
  		 	 	 

// Handle para el control de las Display Lists
GLuint dl_handle;
#define DL_ESFERA (dl_handle+0)
#define DL_CUBO (dl_handle+1)
#define DL_TOROIDE (dl_handle+2)
#define DL_CILINDRO (dl_handle+3)


void Set3DEnv()
{
	glViewport (10, -100, (GLsizei) W_WIDTH, (GLsizei) W_HEIGHT); 
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(60.0, (GLfloat) W_WIDTH/(GLfloat) W_HEIGHT, 1.0, 10.0);
}

void init(void) 
{	

	//Para la Prueba de Textura
	texLoad = new TextureLoader();
	char *p="C:\objEsfera.JPG";
	//texLoad->LoadTextureFromDisk(p,&textura);
	texLoad->LoadTextureFromDisk("./Archivos de Recursos/Texturas de Botones/objToroide.JPG",&textura);
	//texLoad->LoadTextureFromDisk("C:\o.jpg",&textura);
	//........


	AdministradorTexturas *adminText=AdministradorTexturas::getInstancia();
	adminText->CargarTexturas();

	Emparchador emparchador;
    Superficie* superficie;

	glClearColor (0.02f, 0.02f, 0.04f, 0.0f);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);

	dl_handle = glGenLists(4);

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


	glClearColor (0.2148f, 0.2305f, 0.2422f, 0.0f);
    glShadeModel (GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHT0);
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
			
			
		}else if(glm::abs(distanciaDeDoblado)<=1.2){
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
		shaderManager->setUniform("esCubo", verCubo);
		shaderManager->setUniform("esCilindro", verCilindro);
		shaderManager->setUniform("arista", arista);
		//setear uniforms y esas cosas
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
		//setear uniforms y esas cosas 
	}
	/*
	//selección de las luces
	if (luzPrincipal)
		shaderManager->setShaderLuz(LUZ_PRINCIPAL);
	if (luzSecundaria)
		shaderManager->setShaderLuz(LUZ_SECUNDARIA);
	*/
	//selección del material
	if (verMaterialSombreadoBrillante){
		shaderManager->setFragmenShader(MATERIAL_SOMBREADO_BRILLANTE);
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
	shaderManager->usar();
	
	//selección de primitiva
	if (verEsfera)
		glCallList(DL_ESFERA);
	if (verCubo)
		glCallList(DL_CUBO);
    if (verToroide)
		glCallList(DL_TOROIDE);
   	if (verCilindro)
		glCallList(DL_CILINDRO);

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

void mouse(int button, int state, int x, int y){
//mover cámara
}

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
void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
		
		case 'q':
			exit(0);
			break;
		case 'v':
			cout << anguloDeRetorsion << endl;
			anguloDeRetorsion -= 1;
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
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    //glutFullScreen();
   
	ventanaPrincipal = glutCreateWindow("66.71 - TP2");
    glutDisplayFunc(escena); 
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutIdleFunc(OnIdle);
	init ();

	hud = new HUD(ventanaPrincipal, ancho, alto);
	glewInit();

	shaderManager = new ShaderManager();
	
		
	//loop principal
	glutMainLoop();
    return 0;
}
