#include "ObjetoGraficoCubico.h"


vec2 ObjetoGraficoCubico::vText[4];


ObjetoGraficoCubico::ObjetoGraficoCubico(void)
{
	this->discretizacionPorDefecto  = true;

	this->definirMaterialAux();
}

void ObjetoGraficoCubico::graficarBase(){


	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glDisable(GL_LIGHTING);
		
		glTranslatef(posicionObjeto[0],posicionObjeto[1],posicionObjeto[2]);
		
	//	if(dibujarLineas)
			glBegin(GL_LINES);
//		else
	//		glBegin(GL_QUADS);
			
			glColor3f(1.0,0.0,0.0);
			glVertex3fv(vertices[1]);
			glVertex3fv(vertices[2]);
			glVertex3fv(vertices[6]);
			glVertex3fv(vertices[5]);

			glColor3f(0.0,1.0,0.0);
			glVertex3fv(vertices[2]);
			glVertex3fv(vertices[3]);
			glVertex3fv(vertices[7]);
			glVertex3fv(vertices[6]);

			glColor3f(0.0,0.0,1.0);
			glVertex3fv(vertices[3]);
			glVertex3fv(vertices[0]);
			glVertex3fv(vertices[4]);
			glVertex3fv(vertices[7]);

			//4ta tapa
			glColor3f(1.0,1.0,0.0);
			glVertex3fv(vertices[0]);
			glVertex3fv(vertices[4]);
			glVertex3fv(vertices[5]);
			glVertex3fv(vertices[1]);

			//5ta tapa
			glColor3f(1.0,0.0,1.0);
			glVertex3fv(vertices[6]);
			glVertex3fv(vertices[7]);
			glVertex3fv(vertices[4]);
			glVertex3fv(vertices[5]);

			//6ta tapa la del piso, que resultaria el piso
			glColor3f(0.8,0.8,0.8);
			glVertex3fv(vertices[0]);
			glVertex3fv(vertices[1]);
			glVertex3fv(vertices[2]);
			glVertex3fv(vertices[3]);

		glEnd();
	glPopMatrix();


}

void ObjetoGraficoCubico::inicializarVertices(){

	this->cantidadVertices = 8;

	this->vertices = new float*[cantidadVertices];

	for (int i=0; i < cantidadVertices ; i++)
		this->vertices[i] = new float[3]; 

	
	this->actualizarVertices();

}

void ObjetoGraficoCubico::definirParametros(float ancho,float largo,float alto){

	this->ancho = ancho;
	this->largo = largo;
	this->alto = alto;

	this->actualizarVertices();

}

float ObjetoGraficoCubico::valorAltura(){	return this->alto;}

float ObjetoGraficoCubico::valorLargo(){ return this->largo; }

float ObjetoGraficoCubico::valorAncho(){ return this->ancho;}


float ObjetoGraficoCubico::valorLargoEnX(){ return this->largo; }

float ObjetoGraficoCubico::valorLargoEnY(){ return this->ancho;}


void ObjetoGraficoCubico::posicionarObjeto()
{
	glTranslatef(	this->posicionObjeto[0] - this->valorLargoEnX() / 2.0, 
					this->posicionObjeto[1] - this->valorLargoEnY() / 2.0,
					this->posicionObjeto[2] );

}

void ObjetoGraficoCubico::actualizarVertices(){

	this->inicializarVector(vertices[0],0.0,0.0,0.0);
	this->inicializarVector(vertices[1],largo,0.0,0.0);
	this->inicializarVector(vertices[2],largo,ancho,0.0);
	this->inicializarVector(vertices[3],0.0,ancho,0.0);

	this->inicializarVector(vertices[4],0.0,0.0,alto);
	this->inicializarVector(vertices[5],largo,0.0,alto);
	this->inicializarVector(vertices[6],largo,ancho,alto);
	this->inicializarVector(vertices[7],0.0,ancho,alto);
}


void ObjetoGraficoCubico::dibujarPared(float* normal,int v1,int v2,int v3,int v4)
{	
	glBegin(GL_TRIANGLE_STRIP);
		glNormal3fv(normal);
		glVertex3fv(vertices[v1]);
		glVertex3fv(vertices[v2]);
		glVertex3fv(vertices[v3]);
		glVertex3fv(vertices[v4]);

	glEnd();


	/*
	//if(this->discretizacionPorDefecto)
		pasosDeDiscretizacion = 5;
	
	btVector3 x0 = btVector3(vertices[v1][0],vertices[v1][1],vertices[v1][2]);
	btVector3 x1 = btVector3(vertices[v2][0],vertices[v2][1],vertices[v2][2]);

	btVector3 y0 = btVector3(vertices[v3][0],vertices[v3][1],vertices[v3][2]); 
	btVector3 y1 = btVector3(vertices[v4][0],vertices[v4][1],vertices[v4][2]);

	//float dAlto = (x0 - y0).length() / pasosDeDiscretizacion; 

	btVector3 dir0 = (y0 - x0);
	btVector3 dir1 = (y1 - x1);
	//dir.normalize();
	dir0 /= pasosDeDiscretizacion;
	dir1 /= pasosDeDiscretizacion;

	y0 = x0 + dir0;
	y1 = x1 + dir1;
		

	for(int i=0; i < pasosDeDiscretizacion  ; i++)
	{
		this->dibujarFranja(normal,x0,x1,y0,y1);
		x0 = y0;
		x1 = y1;

		y0 += dir0;
		y1 += dir1;

	}

	*/

}

void ObjetoGraficoCubico::definirCoordTextura(vec2 v1,vec2 v2,vec2 v3,vec2 v4)
{
	vText[0] = v1;
	vText[1] = v2;
	vText[2] = v3;
	vText[3] = v4;
	
}

void ObjetoGraficoCubico::dibujarParedTexturada(float* normal,int v1,int v2,int v3,int v4)
{
	glBegin(GL_TRIANGLE_STRIP);
		glNormal3fv(normal);
		glTexturaVec2(vText[0]);
		//glTexCoord2f(0.,0.);
		glVertex3fv(vertices[v1]);

		glTexturaVec2(vText[1]);
		//glTexCoord2f(1.,0.);
		glVertex3fv(vertices[v2]);

		glTexturaVec2(vText[2]);
		//glTexCoord2f(0.,1.);
		glVertex3fv(vertices[v3]);

		glTexturaVec2(vText[3]);
		//glTexCoord2f(1.,1.);
		glVertex3fv(vertices[v4]);

	glEnd();

	/*
	pasosDeDiscretizacion = 5;
	
	btVector3 x0 = btVector3(vertices[v1][0],vertices[v1][1],vertices[v1][2]);
	btVector3 x1 = btVector3(vertices[v2][0],vertices[v2][1],vertices[v2][2]);

	btVector3 y0 = btVector3(vertices[v3][0],vertices[v3][1],vertices[v3][2]); 
	btVector3 y1 = btVector3(vertices[v4][0],vertices[v4][1],vertices[v4][2]);


	btVector3 dir0 = (y0 - x0);
	btVector3 dir1 = (y1 - x1);


	vec2 dirTex0 = (vText[2] - vText[0]);
	vec2 ditTex1 = (vText[3] - vText[1]);
	

	dir0 /= pasosDeDiscretizacion;
	dir1 /= pasosDeDiscretizacion;

	y0 = x0 + dir0;
	y1 = x1 + dir1;
		

	for(int i=0; i < pasosDeDiscretizacion  ; i++)
	{	
		//cambiar a dibujarFranjaTexturada
		//this->dibujarFranja(normal,x0,x1,y0,y1);
		x0 = y0;
		x1 = y1;

		y0 += dir0;
		y1 += dir1;

	}
	*/
}

void ObjetoGraficoCubico::dibujarParedHueca(float* normal,int v1,int v2,int v3,int v4,float largoHoyo,float anchoHoyo,vec2 posHoyo,float profundidad)
{
	
	
	btVector3 x0 = btVector3(vertices[v1][0],vertices[v1][1],vertices[v1][2]);
	btVector3 x1 = btVector3(vertices[v2][0],vertices[v2][1],vertices[v2][2]);

	btVector3 y0 = btVector3(vertices[v3][0],vertices[v3][1],vertices[v3][2]); 
	btVector3 y1 = btVector3(vertices[v4][0],vertices[v4][1],vertices[v4][2]);


	btVector3 centroHoyo = x0 + posHoyo.x * (x1 - x0) + posHoyo.y * (y0 - x0);

	btVector3 dirPlana = x1 - x0; dirPlana /= dirPlana.length();
	btVector3 dirNoPlana = y0 - x0; dirNoPlana /= dirNoPlana.length();

	anchoHoyo /= 2.0;
	largoHoyo /= 2.0;

	btVector3 hx0 = centroHoyo - dirPlana * anchoHoyo - dirNoPlana * largoHoyo;
	btVector3 hx1 = centroHoyo + dirPlana * anchoHoyo - dirNoPlana * largoHoyo;

	btVector3 hy0 = centroHoyo - dirPlana * anchoHoyo + dirNoPlana * largoHoyo;
	btVector3 hy1 = centroHoyo + dirPlana * anchoHoyo + dirNoPlana * largoHoyo;


	this->discretizacionPorDefecto = false;

	pasosDeDiscretizacion = 3;
	this->dibujarFranja(normal,x0,x1,hx0,hx1);

	this->dibujarFranja(normal,x1,y1,hx1,hy1);

	this->dibujarFranja(normal,hy0,hy1,y0,y1);

	this->dibujarFranja(normal,y0,x0,hy0,hx0);


	this->dibujarHoyo(normal,hx0,hx1,hy0,hy1,profundidad);


	this->discretizacionPorDefecto = true;


}

mat4 ObjetoGraficoCubico::calcularRealineacion(vec3 n){
	vec3 y = vec3(0.0, 1.0, 0.0);
	vec3 ejeDeRotacion = cross(n, y);
	mat4 I = mat4(1.0f);
	if ((ejeDeRotacion.x == 0) && (ejeDeRotacion.y == 0) && (ejeDeRotacion.z == 0))
		if (n == -y)
			return rotate(I, float(180), vec3(0.0, 0.0, 1.0));
		return I;
	n = normalize(n);

	float angulo = acos(dot(n, y));

	return rotate(I, degrees(angulo), ejeDeRotacion);
}
void ObjetoGraficoCubico::dibujarHoyo(float *n,btVector3 &x0,btVector3 &x1,btVector3 &y0,btVector3 &y1,float &profundidad)
{
	//Estas normales pertenecen a un hoyo cuyo hueco apunta hacia +Y, y puede que necesiten ser rotadas
	//En la máquina que arma los cajones, estas normales no sirven, hay que rotarlas
	vec4 normales[5] = {			
		vec4(  0.0,  0.0,  1.0,  0.0 ),
		vec4(  1.0,  0.0,  0.0,  0.0 ),
		vec4(  0.0,  0.0, -1.0,  0.0 ),
		vec4( -1.0,  0.0,  0.0,  0.0 ),
		vec4(  0.0,  1.0,  0.0,  0.0 )
	};
	mat4 rotadora = calcularRealineacion(vec3(n[0], n[1], n[2]));
	for (int i = 0; i < 5; i++)
		normales[i] = rotadora * normales[i];
	btVector3 normal = btVector3(n[0],n[1],n[2]);
	normal.normalize();

	normal = - profundidad * normal;

	glBegin(GL_QUADS);
		//Base
		glNormal3fv(&(vec3(normales[0])[0]));
		glVerticeVec3(x0);
		glVerticeVec3(x1);
		glVerticeVec3(x1 + normal);
		glVerticeVec3(x0 + normal);

		//Pared de la derecha mirando de frente al hueco
		glNormal3fv(&(vec3(normales[1])[0]));
		glVerticeVec3(x1);
		glVerticeVec3(y1);
		glVerticeVec3(y1 + normal);
		glVerticeVec3(x1 + normal);

		//Techo
		glNormal3fv(&(vec3(normales[2])[0]));
		glVerticeVec3(y0);
		glVerticeVec3(y0 + normal);
		glVerticeVec3(y1 + normal);
		glVerticeVec3(y1);

		//Pared de la izquierda mirando de frente al hueco
		glNormal3fv(&(vec3(normales[3])[0]));
		glVerticeVec3(y0);
		glVerticeVec3(x0);
		glVerticeVec3(x0 + normal);
		glVerticeVec3(y0 + normal);

	glEnd();

	glDisable(GL_LIGHTING);

	this->phong->setMaterial(this->materialAux);

	glBegin(GL_QUADS);
		//Fondo
		glColor3f(0.,0.,0.);
		glNormal3fv(&(vec3(normales[4])[0]));
		glVerticeVec3(x0 + normal);
		glVerticeVec3(x1 + normal);
		glVerticeVec3(y1 + normal);
		glVerticeVec3(y0 + normal);

	glEnd();
		
	this->phong->setMaterial(this->material);
	
	glEnable(GL_LIGHTING);


}


void ObjetoGraficoCubico::dibujarFranjaTexturada(float* normal,btVector3 &x0,btVector3 &x1,btVector3 &y0,btVector3 &y1)
{

}

void ObjetoGraficoCubico::dibujarFranja(float* normal,btVector3 &x0,btVector3 &x1,btVector3 &y0,btVector3 &y1)
{	

	glBegin(GL_TRIANGLE_STRIP);
			glNormal3fv(normal);
			glVerticeVec3(x0); 
			glVerticeVec3(x1);
			glVerticeVec3(y0);
			glVerticeVec3(y1);

	glEnd();

	//if(this->discretizacionPorDefecto)
		//pasosDeDiscretizacion = 15;
	/*
	float dX = (x1 - x0).length() / pasosDeDiscretizacion;
	float dY = (y1 - y0).length() / pasosDeDiscretizacion;

	btVector3 dirX = (x1 - x0);	dirX /= dirX.length();
	btVector3 dirY = (y1 - y0);	dirY /= dirY.length();

	btVector3 x = x0;
	btVector3 y = y0;

	glBegin(GL_TRIANGLE_STRIP);

		for(int i=0 ; i <= pasosDeDiscretizacion; i++)
		{	
			glNormal3fv(normal);
			glVerticeVec3(x); 

			glNormal3fv(normal);
			glVerticeVec3(y);

			x = x + dX * dirX;
			y = y + dY * dirY;

		}

	glEnd(); */

}


ObjetoGraficoCubico::~ObjetoGraficoCubico(void)
{
	for(int i=0;i < cantidadVertices;i++)
		delete[] this->vertices[i];

	delete[] this->vertices;

}


void ObjetoGraficoCubico::definirMaterialAux()
{

	materialAux.colorAmb = vec3(0.044, 0.057, 0.075);		
	materialAux.colorDif = vec3(0.044, 0.057, 0.075);
	materialAux.colorEspec = vec3(0.01, 0.015, 0.02);
	materialAux.brillo = 2.0;

}