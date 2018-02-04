#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>



/* Paramètres */
/* Parties du bras qui bougent */
#define TOP 0
#define MIDDLE 1
#define BOTTOM 2
int objectMoving = 2; /* quel morceau du bras on bouge   */

/*  méthods de tracés */
#define BareBones 0
#define JustFlesh 1
int drawingMethod = 0;


float rotations[3];
float length[3];

/* Pr interface utilisateur */
int beginx, beginy, width, height;
float beginAngle;
float tmin;

void drawFlesh(float tmin)
{
  float tmax = 1-tmin;
  float x,y;
  float x0, y0;
  int i;
  float radius = 0.1;
  float angle = 0;
  
  x0 = -1;
  y0 = -0.5;
  angle = 0;
  glLineWidth(2.0);
  glBegin(GL_LINES);
  for (i = 0; i < 3; i++) {
    angle += rotations[i];
    if (i != 0) {
      x = x0 + cos(angle)*length[i]*tmin + sin(-angle)*radius;
      y = y0 + sin(angle)*length[i]*tmin + cos(angle)*radius;
    } else {
      x = x0 + sin(-angle)*radius;
      y = y0 + cos(angle)*radius;
    }
    glVertex2f(x,y);
    if (i == 0) {
      x += cos(angle)*length[i]*tmax;
      y += sin(angle)*length[i]*tmax;
    } else if (i == 2) {
      x += cos(angle)*length[i]*(1.0-tmin);
      y += sin(angle)*length[i]*(1.0-tmin);
    } else {
      x += cos(angle)*length[i]*(tmax-tmin);
      y += sin(angle)*length[i]*(tmax-tmin);
    }
    glVertex2f(x,y);
    x0 += cos(angle)*length[i];
    y0 += sin(angle)*length[i];
  }
  glEnd();
  
  x0 = -1;
  y0 = -0.5;
  angle = 0;
  glBegin(GL_LINES);
  for (i = 0; i < 3; i++) {
    angle += rotations[i];
    if (i != 0) {
      x = x0 + cos(angle)*length[i]*tmin - sin(-angle)*radius;
      y = y0 + sin(angle)*length[i]*tmin - cos(angle)*radius;
    } else {
      x = x0 - sin(-angle)*radius;
      y = y0 - cos(angle)*radius;
    }
    glVertex2f(x,y);
    if (i == 0) {
      x += cos(angle)*length[i]*tmax;
      y += sin(angle)*length[i]*tmax;
    } else if (i == 2) {
      x += cos(angle)*length[i]*(1.0-tmin);
      y += sin(angle)*length[i]*(1.0-tmin);
    } else {
      x += cos(angle)*length[i]*(tmax-tmin);
      y += sin(angle)*length[i]*(tmax-tmin);
    }
    glVertex2f(x,y);
    x0 += cos(angle)*length[i];
    y0 += sin(angle)*length[i];
  }
  glEnd();
  
  x0 = -1;
  y0 = -0.5;
  angle = 0;
  glLineWidth(2.0);
  glBegin(GL_LINES);
  for (i = 0; i < 3; i++) {
    angle += rotations[i];
    if (i != 0) {
      x = x0 + cos(angle)*length[i]*tmin + sin(-angle)*radius;
      y = y0 + sin(angle)*length[i]*tmin + cos(angle)*radius;
    } else {
      x = x0 + sin(-angle)*radius;
      y = y0 + cos(angle)*radius;
    }
    glVertex2f(x,y);
    if (i != 0) {
      x = x0 + cos(angle)*length[i]*tmin - sin(-angle)*radius;
      y = y0 + sin(angle)*length[i]*tmin - cos(angle)*radius;
    } else {
      x = x0 - sin(-angle)*radius;
      y = y0 - cos(angle)*radius;
    }
    glVertex2f(x,y);
    if (i != 2) {
      x = x0 + cos(angle)*length[i]*tmax + sin(-angle)*radius;
      y = y0 + sin(angle)*length[i]*tmax + cos(angle)*radius;
    } else {
      x = x0 + cos(angle)*length[i] + sin(-angle)*radius;
      y = y0 + sin(angle)*length[i] + cos(angle)*radius;
    }
    glVertex2f(x,y);
    if (i!= 2) {
      x = x0 + cos(angle)*length[i]*tmax - sin(-angle)*radius;
      y = y0 + sin(angle)*length[i]*tmax - cos(angle)*radius;
    } else {
      x = x0 + cos(angle)*length[i] - sin(-angle)*radius;
      y = y0 + sin(angle)*length[i] - cos(angle)*radius;
    }
    glVertex2f(x,y);
    x0 += cos(angle)*length[i];
    y0 += sin(angle)*length[i];
  }
  glEnd();
}


void drawObject()
{
  float x, y;
  float x0, y0;
  float radius = 0.1;
  float tmax = 1 - tmin; 
  float angle = 0;
  int i;

  glPushMatrix();
  x = -1.0;
  y = -0.5;

  // Drawing the skeletton:
  glColor3f(1.0, 0.0, 0.0);
  glLineWidth(4.0);
  glBegin(GL_LINES);
  for (i = 0; i < 3; i++) {
    glVertex2f(x,y);
    angle += rotations[i];
    x += cos(angle)*length[i];
    y += sin(angle)*length[i];
    glVertex2f(x,y);
  }
  glEnd();
  x = -1.0;
  y = -0.5;
  angle = 0;
  // And its articulations:
  glPointSize(10.0);
  glColor3f(1.0, 1.0, 0.0);
  glBegin(GL_POINTS);
  for (i = 0; i < 3; i++) {
    glVertex2f(x,y);
    angle += rotations[i];
    x += cos(angle)*length[i];
    y += sin(angle)*length[i];
  }
  glEnd();

  // The drawing of the "flesh"
  glColor3f(0.0, 0.0, 1.0);
  glLineWidth(2.0);
  
  if ((drawingMethod >= 1)) { 
    drawFlesh(tmin);
  }

}

void handle_main_menu(int item)
{
  switch(item) {
  case TOP:
    objectMoving = 0;
    glutPostRedisplay();
    break;
  case MIDDLE:
    objectMoving = 1;
    glutPostRedisplay();
    break;
  case BOTTOM:
    objectMoving = 2;
    break;
  }
}

void
mouse(int button, int state, int x, int y)
{
  if (state == GLUT_DOWN) {
    beginx = x;
    beginy = y;
    beginAngle = rotations[objectMoving];
  }
  glutPostRedisplay();
}

void
motion(int x, int y)
{
  rotations[objectMoving] = beginAngle + (y - beginy)/(float)width;
  glutPostRedisplay();
}

void parsekey(unsigned char key, int x, int y)
{
  switch (key)
    {
    case 27: exit(0);
    case ' ': 
      rotations[0] = 0.0;
      rotations[1] = 0.0;
      rotations[2] = 0.0;
      break;
    case 'a': objectMoving = TOP; break;
    case 'z': objectMoving = MIDDLE; break;
    case 'e': objectMoving = BOTTOM; break;
    case 'q': drawingMethod = BareBones; break;
    case 's': drawingMethod = JustFlesh; break;
    default:
      return;
    }
  glutPostRedisplay();
}

void parsekey_special(int key, int x, int y)
{
  switch (key)
    {
    case GLUT_KEY_UP: 
      rotations[objectMoving] += 0.02;
      break;
    case GLUT_KEY_DOWN:	 
      rotations[objectMoving] -= 0.02;
      break;
    case GLUT_KEY_RIGHT: 
      tmin += 0.02;
      if (tmin > 0.3) tmin = 0.3;
      break;
    case GLUT_KEY_LEFT:	
      tmin -= 0.02;
      if (tmin < 0) tmin = 0;
      break;
    default:
      return;
    }
  glutPostRedisplay();
}

void myReshape(int w, int h)
{
  int xmin, ymin;
  xmin = 0;
  ymin = 0;
  if (w > h) {
    xmin = (w-h)/2;
    w = h;
  } else {
    ymin = (h-w)/2;
    h = w;
  }
  width = w;
  height = h;
  glViewport(xmin, ymin, w, h);
  glutPostRedisplay();
}

void display(void)
{
  glPushMatrix();
  //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


  drawObject();

  glutSwapBuffers();
  glPopMatrix();
}

void myinit(void)
{
  glDepthRange (0.1, 20);

  glLoadIdentity();
  glClearColor(0.0, 0.0, 0.0, 1.0);
  rotations[0] = 0.0;
  rotations[1] = 0.0;
  rotations[2] = 0.0;
  length[0] = 0.7;
  length[1] = 0.5;
  length[2] = 0.5;
  objectMoving = TOP;
}

int main(int argc, char *argv[]) 
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB | GLUT_DOUBLE | GLUT_MULTISAMPLE |
		      GLUT_STENCIL);
  glutCreateWindow("Modélisation hiérarchique");
  glutDisplayFunc(display);
  glutInitWindowSize(1200, 1200);
  glutInitWindowPosition(200, 0);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
  glutKeyboardFunc(parsekey);
  glutSpecialFunc(parsekey_special);
  glutReshapeFunc(myReshape);
  myinit();
    
  glutCreateMenu(handle_main_menu);
  glutAddMenuEntry("Bouger tout le bras", TOP);
  glutAddMenuEntry("Bouger la partie médiane", MIDDLE);
  glutAddMenuEntry("Bouger la partie inférieure", BOTTOM);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
  glutSwapBuffers();
  glutMainLoop();
  return 0;
}

