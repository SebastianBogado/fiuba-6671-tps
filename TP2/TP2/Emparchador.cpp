#include "../include/Emparchador.h"
#include <iostream>

#include <windows.h>
#include <stdio.h>
using namespace std;
GLuint LoadTextureRAW( const char * filename )
{
    GLuint texture;
    int width, height;
    unsigned char * data;

    FILE * file;
    file = fopen( filename, "rb" );
    if ( file == NULL )
    {
        return 0;
    }

    width = 1024;
    height = 512;
    data = (unsigned char *)malloc( width * height * 3 );

    fread( data, width * height * 3, 1, file );
    fclose( file );

    glGenTextures( 1, &texture );
    glBindTexture( GL_TEXTURE_2D, texture );

    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data );

    free( data );

    return texture;
}


void Emparchador::emparchar(Superficie* superficie){
    float* puntoInferior;
    float* puntoSuperior;
    float* ultimoPuntoInferior;
    float* ultimoPuntoSuperior;
    for (int i = 0; i < superficie->cantidadDePuntosEnAlto(); i++){

 glBindTexture (GL_TEXTURE_2D, LoadTextureRAW( "earth.raw" ));

        glBegin(GL_TRIANGLE_STRIP);
            for (int j = 0; j < superficie->cantidadDePuntosBorde(); j++){
                puntoInferior = superficie->getPunto(j, j, i);
                puntoSuperior = superficie->getPunto(j, j, i+1);
                float random1=float(rand())/float(RAND_MAX);
                float random2=float(rand())/float(RAND_MAX);
                glTexCoord2f(puntoInferior[0]/1000,puntoInferior[0]/1000);
                glVertex3fv(puntoInferior);


                random1=float(rand())/float(RAND_MAX);
                random2=float(rand())/float(RAND_MAX);
                glTexCoord2f(puntoSuperior[0]/1000,puntoSuperior[0]/1000);
                glVertex3fv(puntoSuperior);
                delete []puntoInferior;
                delete []puntoSuperior;
            }
            ultimoPuntoInferior = superficie->getPunto(0, 0, i);
            ultimoPuntoSuperior = superficie->getPunto(0, 0, i+1);
            glVertex3fv(ultimoPuntoInferior);
            glVertex3fv(ultimoPuntoSuperior);
            delete []ultimoPuntoInferior;
            delete []ultimoPuntoSuperior;
        glEnd();
    }
    if (superficie->tieneTapas())
        this->emparcharTapas(superficie);
}


void Emparchador::emparcharTapas(Superficie* superficie){
    float* centroTapa;
    float* puntoBorde;
    float* ultimoPuntoBorde;
    for (int i = 0; i <= superficie->cantidadDePuntosEnAlto(); i += superficie->cantidadDePuntosEnAlto()){
        glBegin(GL_TRIANGLE_FAN);
            centroTapa = superficie->getPunto(0, 0, i);
            glVertex3f(0.0, 0.0, centroTapa[2]);
            for (int j = 0; j < superficie->cantidadDePuntosBorde(); j++){
                puntoBorde = superficie->getPunto(j, j, i);
                glVertex3fv(puntoBorde);
                delete []puntoBorde;
            }
            ultimoPuntoBorde = superficie->getPunto(0, 0, i);
            glVertex3fv(ultimoPuntoBorde);
            delete []centroTapa;
            delete []ultimoPuntoBorde;
        glEnd();
    }


}
