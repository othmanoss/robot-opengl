#include <GL/glut.h>
#include "robotopengl.h"


#define FACTEUR_JAMBE 1.1
#define FACTEUR_BRAS 0.8

void DessinePhalange(GLfloat longueur)
{


}


void DessineDoigt(ParametreRobot param)
{
     glPushMatrix();
     glColor3f(1.0f, 1.0f, 0.0f);
     glTranslatef(1, 1, 1);
     glScalef(1.0f, 5.0f, 1.0f);
     glutWireCube(1.0)
     glPopMatrix();
}

void DessineMain(ParametreRobot param)
{


}


void DessineAvantBras(ParametreRobot param)
{

}

void DessineBras(ParametreRobot param)
{


}


void DessineJambe(ParametreRobot param)
{


}

void DessineRobot(ParametreRobot paramG, ParametreRobot paramD)
{
    DessineDoigt();
}
