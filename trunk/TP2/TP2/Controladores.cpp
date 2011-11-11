//variables de control sobre lo que se ve en la escena
bool verEsfera = true;
bool verCubo = false;
bool verToroide = false;
bool verCilindro = false;

bool verMaterialSombreadoBrillante = true;
bool verMaterialSombreadoTexturado = false;
bool verMaterialReflectivo = false;
bool verMaterialSombreadoSemimate = false;

bool verRetorcer = true;
bool verRuido = false;
bool verDoblar = false;
bool verEsferizar = false;

bool usarShaders = true;

bool luzPrincipal = true;
bool luzSecundaria = true;

bool rotarEscena = false;

float tiempo = 0.0;

//Efecto retorcer
float anguloDeRetorsion = 90.0;

//Efecto de esferizar
float centro[3] = {0.0, 0.0, 0.5};

//Efecto de doblar
float distanciaDeDoblado = 3.0;
float incrementoDeDistancia = 0.15;

//Efecto de ruido
struct Onda{
	float longitud;
	float frecuencia;
	float amplitud;
};

float n = 0.5;
float arista = 1.4;
Onda ondaEnX = {arista/(2.0*n), 3.0, 0.07};
Onda ondaEnY = {arista/n, 4.0, 0.05};
Onda ondaEnZ = {arista/(4*n), 5.0, 0.04};



//Path de Archivos de Textura

int BotonTexturas=1;

char *pathObjEsfera=	"./Archivos de Recursos/Texturas de Botones/objEsfera.JPG";
char *pathObjCubo=		"./Archivos de Recursos/Texturas de Botones/objCubo.JPG";
char *pathObjToroide=	"./Archivos de Recursos/Texturas de Botones/objToroide.JPG";
char *pathObjCilindro=	"./Archivos de Recursos/Texturas de Botones/objCilindro.JPG";

char *pathMatBrillante=	"./Archivos de Recursos/Texturas de Botones/matBrillante.JPG";
char *pathMatTexturado=	"./Archivos de Recursos/Texturas de Botones/matTexturado.JPG";
char *pathMatSemimate=	"./Archivos de Recursos/Texturas de Botones/matSemimate.JPG";
char *pathMatReflectivo="./Archivos de Recursos/Texturas de Botones/matReflectivo.JPG";

char *pathEfecRetorcer=	"./Archivos de Recursos/Texturas de Botones/efecRetorcer.JPG";
char *pathEfecRuido=	"./Archivos de Recursos/Texturas de Botones/efecRuido.JPG";
char *pathEfecDoblar=	"./Archivos de Recursos/Texturas de Botones/efecDoblar.JPG";
char *pathEfecEsferizar="./Archivos de Recursos/Texturas de Botones/efecEsferizar.JPG";
