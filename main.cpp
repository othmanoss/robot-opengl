#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#include "robotopengl.h"

/************************
   Constantes, variables globales et initialisations
************************/

//Initialisation de la fenêtre
GLushort largeur_fenetre=600;
GLushort hauteur_fenetre=600;
GLushort pos_x_fenetre=100;
GLushort pos_y_fenetre=100;


char leftdown=0, middledown=0, rightdown=0;
char keyz=0, keyZ=0, keyx=0, keyX=0, keyy=0, keyY=0, keyleft=0, keydown=0, keyright=0, keyup=0;

GLfloat angle_twist=0.0;
GLfloat angle_elevation=30.0;
GLfloat angle_azimuth=-60.0;

GLfloat translatex=0, translatey=0;

GLfloat vitesse=1;

GLdouble theta_y=10,proportion=1,clipnear=0.1,clipfar=10000, distance=500;
GLdouble stepx=1, stepy=1, stepz=1;

int mousex, mousey;

char init=0;

///////////////////////////////
// Variables du robot;

ParametreRobot paramG, paramD, *paramSelect;;


unsigned char ancienkey;


int nbfichierseps=0;

int choixmenu=1;

///////////////////////////////////////////////////////////////
// FONCTIONS D'INITIALISATION
///////////////////////////////////////////////////////////////

void InitRobot()
{
  paramG.angle_tete=-10;
  paramG.angle_epaule=-10;
  paramG.angle_twistepaule=-10;
  paramG.angle_coude=10;
  paramG.angle_twistcoude=0;
  paramG.angle_poignet=0;
  paramG.angle_twistmain=120;
  paramG.angle_doigts=10;
  paramG.angle_jambe=10;
  paramG.angle_twistjambes=-10;
  paramG.angle_genoux=10;
  paramG.angle_pied=0;

  paramD.angle_tete=-10;
  paramD.angle_epaule=-10;
  paramD.angle_twistepaule=-30;
  paramD.angle_coude=20;
  paramD.angle_twistcoude=0;
  paramD.angle_poignet=10;
  paramD.angle_twistmain=120;
  paramD.angle_doigts=20;
  paramD.angle_jambe=30;
  paramD.angle_twistjambes=-15;
  paramD.angle_genoux=30;
  paramD.angle_pied=0;

  paramSelect=&paramG;
}


void InitZero()
{
  paramG.angle_tete=0;
  paramG.angle_epaule=0;
  paramG.angle_twistepaule=0;
  paramG.angle_coude=0;
  paramG.angle_twistcoude=0;
  paramG.angle_poignet=0;
  paramG.angle_twistmain=90;
  paramG.angle_doigts=0;
  paramG.angle_jambe=0;
  paramG.angle_twistjambes=0;
  paramG.angle_genoux=0;
  paramG.angle_pied=0;

  paramD.angle_tete=0;
  paramD.angle_epaule=0;
  paramD.angle_twistepaule=0;
  paramD.angle_coude=0;
  paramD.angle_twistcoude=0;
  paramD.angle_poignet=0;
  paramD.angle_twistmain=90;
  paramD.angle_doigts=0;
  paramD.angle_jambe=0;
  paramD.angle_twistjambes=0;
  paramD.angle_genoux=0;
  paramD.angle_pied=0;

  paramSelect=&paramG;
}







void InitView()
{
  angle_azimuth=angle_elevation=0;
  glutPostRedisplay();
}

void InitObjet()
{
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glutPostRedisplay();
}




//////////////////////////////////////////////////////////////
// EVENNEMENTS
//////////////////////////////////////////////////////////////

void Redimensionnement(int l,int h)
{

}

void Special(int key, int x, int y)
{


}

void Clavier(unsigned char key,int x,int y)
{

  char nomfichier[25];
  switch (key)
    {
    case '0':
      paramSelect = & paramG;
      break;
    case '1':
      paramSelect = & paramD;
      break;
    case 'a':break;
    case 'I':
      InitZero();
      InitObjet();
      break;
    case 'i':
      InitRobot();
      InitObjet();
      break;
    case 'x':
      keyx=1;
      break;
    case 'X':
      keyX=1;
      break;
    case 'y':
      keyy=1;
      break;
    case 'Y':
      keyY=1;
      break;
    case 'z':
      keyz=1;
      break;
    case 'Z':
      keyZ=1;
      break;
    case 'd':
      paramSelect->angle_doigts += vitesse;
      break;
    case 'D':
       paramSelect->angle_doigts -= vitesse;
      break;
    case 'p':
       paramSelect->angle_poignet += vitesse;
      break;
    case 'P':
       paramSelect->angle_poignet -= vitesse;
      break;
    case 'c':
       paramSelect->angle_coude += vitesse;
      break;
    case 'C':
       paramSelect->angle_coude -= vitesse;
      break;
  case 'u':
       paramSelect->angle_twistmain += vitesse;
      break;
    case 'U':
       paramSelect->angle_twistmain -= vitesse;
      break;
    case 'v':
       paramSelect->angle_twistcoude += vitesse;
      break;
    case 'V':
       paramSelect->angle_twistcoude -= vitesse;
      break;
    case 'e':
       paramSelect->angle_epaule += vitesse;
      break;
    case 'E':
       paramSelect->angle_epaule -= vitesse;
      break;
    case 'w':
       paramSelect->angle_twistepaule -= vitesse;
      break;
    case 'W':
       paramSelect->angle_twistepaule += vitesse;
      break;
    case 'g':
       paramSelect->angle_genoux += vitesse;
      break;
    case 'G':
       paramSelect->angle_genoux -= vitesse;
      break;
    case 'r':
       paramSelect->angle_pied += vitesse;
      break;
    case 'R':
       paramSelect->angle_pied -= vitesse;
      break;
    case 'j':
       paramSelect->angle_jambe += vitesse;
      break;
    case 'J':
      paramSelect-> angle_jambe -= vitesse;
      break;
    case 't':
       paramG.angle_tete -= vitesse;
       paramD.angle_tete -= vitesse;
      break;
    case 'T':
       paramG.angle_tete += vitesse;
       paramD.angle_tete += vitesse;
      break;
    case 'm':
       paramSelect->angle_twistjambes -= vitesse;
      break;
    case 'M':
       paramSelect->angle_twistjambes += vitesse;
      break;
    case 'h':case 'H':
      fprintf(stderr,"0 : sélectioner le coté gauche\n");
      fprintf(stderr,"1 : sélectioner le coté droit\n");
      fprintf(stderr,"d, D : angle des doigts\n");
      fprintf(stderr,"p, P : angle du poignet\n");
      fprintf(stderr,"u, U : twist du poignet\n");
      fprintf(stderr,"c, C : angle du coude\n");
      fprintf(stderr,"v, V : twist du coude\n");
      fprintf(stderr,"e, E : angle de l'épaule\n");
      fprintf(stderr,"w, W : twist du l'épaule\n");
      fprintf(stderr,"j, J : angle des jambes\n");
      fprintf(stderr,"g, G : angle des genoux\n");
      fprintf(stderr,"r, R : angle des pieds\n");
      fprintf(stderr,"t, T : angle de la tête\n");
      fprintf(stderr,"m, M : twist des jambes\n");

      break;
    case 'q':exit(0);
    default:fprintf(stderr,"Touche non gérée\n");break;
    }


 glutPostRedisplay();
}


void BougeSouris(int x, int y)
{

}


void PresseBouton(int button, int state, int x, int y)
{

}


/////////////////////////////////////////////////////////////
// MENU
/////////////////////////////////////////////////////////////

void FonctionMenu(int value)
{
  choixmenu=value;
}




//////////////////////////////////////////////////
// AFFICHAGE
//////////////////////////////////////////////////


void DessinAxes()
{


}



void DessinObjet()
{

  if (choixmenu != 1)
    DessinAxes();
  glLineWidth(1);
  glColor3f(0,0,0);

  switch(choixmenu)
    {
    case 1:
      DessineRobot(paramG, paramD);
      break;
    case 2:
      DessineBras(paramD);
      break;
    case 3:
      DessineBras(paramG);
      break;
    case 4:
      DessineJambe(paramD);
      break;
    case 5:
      DessineJambe(paramG);
      break;
    case 6:
      DessineAvantBras(paramD);
      break;
    case 7:
      DessineAvantBras(paramG);
      break;
    case 8:
      DessineMain(paramD);
      break;
    case 9:
      DessineMain(paramG);
      break;
    case 10:
      DessineDoigt(paramD);
      break;
    case 11:
      DessineDoigt(paramG);
      break;
    }
}




void Affichage(void)
{

}




/************************
   main
************************/

int main(void)
{

  int menu;
  glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
  glutInitWindowPosition(pos_x_fenetre,pos_y_fenetre);
  glutInitWindowSize(largeur_fenetre,hauteur_fenetre);
  glutCreateWindow("OpenGL et glut, TP 2 : glRotate et glTranslate");
  glEnable(GL_DEPTH_TEST);
  glutDisplayFunc(Affichage);
  glutKeyboardFunc(Clavier);
  glutSpecialFunc(Special);
  glutReshapeFunc(Redimensionnement);
  glutMotionFunc(BougeSouris);
  glutMouseFunc(PresseBouton);

  menu = glutCreateMenu(FonctionMenu);
  glutAddMenuEntry("Robot", 1);
  glutAddMenuEntry("Bras droit", 2);
  glutAddMenuEntry("Bras gauche", 3);
  glutAddMenuEntry("Jambe droite", 4);
  glutAddMenuEntry("Jambe gauche", 5);
  glutAddMenuEntry("Avant bras droit", 6);
  glutAddMenuEntry("Avant bras gauche", 7);
  glutAddMenuEntry("Main droite", 8);
  glutAddMenuEntry("Main gauche gauche", 9);
  glutAddMenuEntry("Doigt main droite", 10);
  glutAddMenuEntry("Doight main gauche", 11);
  glutAttachMenu(GLUT_RIGHT_BUTTON);


  InitRobot();



  glutMainLoop();
  return 0;
}
