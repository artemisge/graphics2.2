#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <string>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>
#include <cmath>
#include <list>
#include <cstring>
#define M_PI 3.14159265358979323846
using namespace std;

int menuoption = 0; //default
float angle = 0;

GLfloat cam[] = {0, 20, 70};
GLfloat camAngle = M_PI / 180 * 270;

typedef struct treenode
{
  GLfloat m[16];
  void (*f)();
  struct treenode *sibling;
  struct treenode *child;
} treenode;
treenode torso_node, head_node, neck_node, flul_node, frul_node, blul_node, brul_node, flll_node, frll_node, blll_node, brll_node, flt_node, frt_node, blt_node, brt_node;
// legs: front/back, right/left, upper/lower, leg
// toes: front/back, right/left, toe

int theta[5] = {0};
int theta_ref[] = {90, 120, 40, 60, 45};

int torso_length = 15;
int torso_height = 5;
void torso()
{
  glPushMatrix();
  //glTranslatef(0, torso_height, -torso_length * 0.5);
  gluCylinder(gluNewQuadric(), torso_height, torso_height, torso_length, 20, 20);
  gluDisk(gluNewQuadric(), 0, torso_height, 20, 20);
  glTranslatef(0, 0, torso_length);
  gluDisk(gluNewQuadric(), 0, torso_height, 20, 20);
  glPopMatrix();
}
int neck_length = 5;
void neck()
{
  glPushMatrix();
  gluCylinder(gluNewQuadric(), 2, 2, 5, 20, 20);
  glPopMatrix();
}
int head_size = 3.5;
void head()
{
  glPushMatrix();
  gluSphere(gluNewQuadric(), head_size, 20, 20);
  glPopMatrix();
}

int leg_height = 5;
void flul()
{
  glPushMatrix();
  glRotatef(90, 1, 0, 0);
  gluCylinder(gluNewQuadric(), 1, 1, leg_height, 20, 20);
  glPopMatrix();
}
void flll()
{
  glPushMatrix();
  glRotatef(90, 1, 0, 0);
  gluCylinder(gluNewQuadric(), 1, 1, leg_height, 20, 20);
  glPopMatrix();
}

void frul()
{
  glPushMatrix();
  glRotatef(90, 1, 0, 0);
  gluCylinder(gluNewQuadric(), 1, 1, leg_height, 20, 20);
  glPopMatrix();
}
void frll()
{
  glPushMatrix();
  glRotatef(90, 1, 0, 0);
  gluCylinder(gluNewQuadric(), 1, 1, leg_height, 20, 20);
  glPopMatrix();
}

void blul()
{
  glPushMatrix();
  glRotatef(90, 1, 0, 0);
  gluCylinder(gluNewQuadric(), 1, 1, leg_height, 20, 20);
  glPopMatrix();
}
void blll()
{
  glPushMatrix();
  glRotatef(90, 1, 0, 0);
  gluCylinder(gluNewQuadric(), 1, 1, leg_height, 20, 20);
  glPopMatrix();
}

void brul()
{
  glPushMatrix();
  glRotatef(90, 1, 0, 0);
  gluCylinder(gluNewQuadric(), 1, 1, leg_height, 20, 20);
  glPopMatrix();
}
void brll()
{
  glPushMatrix();
  glRotatef(90, 1, 0, 0);
  gluCylinder(gluNewQuadric(), 1, 1, leg_height, 20, 20);
  glPopMatrix();
}

int toe_length = 4;
void flt()
{
  glPushMatrix();
  glTranslatef(0, 0, -1);
  gluCylinder(gluNewQuadric(), 1, 1, toe_length, 20, 20);
  gluDisk(gluNewQuadric(), 0, 1, 20, 20);
  glTranslatef(0, 0, toe_length);
  gluDisk(gluNewQuadric(), 0, 1, 20, 20);
  glPopMatrix();
}
void frt()
{
  glPushMatrix();
  glTranslatef(0, 0, -1);
  gluCylinder(gluNewQuadric(), 1, 1, toe_length, 20, 20);
  gluDisk(gluNewQuadric(), 0, 1, 20, 20);
  glTranslatef(0, 0, toe_length);
  gluDisk(gluNewQuadric(), 0, 1, 20, 20);
  glPopMatrix();
}
void blt()
{
  glPushMatrix();
  glTranslatef(0, 0, -1);
  gluCylinder(gluNewQuadric(), 1, 1, toe_length, 20, 20);
  gluDisk(gluNewQuadric(), 0, 1, 20, 20);
  glTranslatef(0, 0, toe_length);
  gluDisk(gluNewQuadric(), 0, 1, 20, 20);
  glPopMatrix();
}
void brt()
{
  glPushMatrix();
  glTranslatef(0, 0, -1);
  gluCylinder(gluNewQuadric(), 1, 1, toe_length, 20, 20);
  gluDisk(gluNewQuadric(), 0, 1, 20, 20);
  glTranslatef(0, 0, toe_length);
  gluDisk(gluNewQuadric(), 0, 1, 20, 20);
  glPopMatrix();
}

void init_nodes()
{ // INITIALIZE TREE NODES AND MOVEMENT ANGLES
  // TORSO:
  glLoadIdentity();
  //glRotatef(50, 0, 1, 1);
  glGetFloatv(GL_MODELVIEW_MATRIX, torso_node.m);
  torso_node.f = torso;
  torso_node.sibling = NULL;
  torso_node.child = &neck_node;

  // NECK:
  glLoadIdentity();
  glTranslatef(0, torso_height / 2 - 1, torso_length);
  glRotatef(30, -1, 0, 0);
  glGetFloatv(GL_MODELVIEW_MATRIX, neck_node.m);
  neck_node.f = neck;
  neck_node.sibling = &flul_node;
  neck_node.child = &head_node;

  // HEAD:
  glLoadIdentity();
  glTranslatef(0, 0, neck_length + head_size / 2);
  //glTranslatef(0, torso_height / 2 - 1, torso_length);
  glGetFloatv(GL_MODELVIEW_MATRIX, head_node.m);
  head_node.f = head;
  head_node.sibling = NULL;
  head_node.child = NULL;

  // Front Left Upper Leg:
  glLoadIdentity();
  glTranslatef(-(torso_height / 2), -torso_height, torso_length - 2);
  glGetFloatv(GL_MODELVIEW_MATRIX, flul_node.m);
  flul_node.f = flul;
  flul_node.sibling = &frul_node;
  flul_node.child = &flll_node;

  // Front Left Lower Leg:
  glLoadIdentity();
  glTranslatef(0, -leg_height, 0);
  glGetFloatv(GL_MODELVIEW_MATRIX, flll_node.m);
  flll_node.f = flll;
  flll_node.sibling = NULL;
  flll_node.child = &flt_node;

  // Front Left Toe:
  glLoadIdentity();
  glTranslatef(0, -leg_height, 0);
  glGetFloatv(GL_MODELVIEW_MATRIX, flt_node.m);
  flt_node.f = flt;
  flt_node.sibling = NULL;
  flt_node.child = NULL;

  // Front Right Upper Leg:
  glLoadIdentity();
  // glTranslatef(13, -8, -2);
  // glRotatef(90, 1, 0, 0);
  glTranslatef((torso_height / 2), -torso_height, torso_length - 2);
  glGetFloatv(GL_MODELVIEW_MATRIX, frul_node.m);
  frul_node.f = frul;
  frul_node.sibling = &blul_node;
  frul_node.child = &frll_node;

  // Front Right Lower Leg:
  glLoadIdentity();
  // glTranslatef(0, -8, 0);
  glTranslatef(0, -leg_height, 0);
  glGetFloatv(GL_MODELVIEW_MATRIX, frll_node.m);
  frll_node.f = frll;
  frll_node.sibling = NULL;
  frll_node.child = &frt_node;

  // Front Right Toe:
  glLoadIdentity();
  glTranslatef(0, -leg_height, 0);
  glGetFloatv(GL_MODELVIEW_MATRIX, frt_node.m);
  frt_node.f = frt;
  frt_node.sibling = NULL;
  frt_node.child = NULL;

  // Back Left Upper Leg:
  glLoadIdentity();
  // glTranslatef(3, -4, 2);
  // glRotatef(90, 1, 0, 0);
  glTranslatef(-(torso_height / 2), -torso_height, 2);
  glGetFloatv(GL_MODELVIEW_MATRIX, blul_node.m);
  blul_node.f = blul;
  blul_node.sibling = &brul_node;
  blul_node.child = &blll_node;

  // Back Left Lower Leg:
  glLoadIdentity();
  // glTranslatef(0, -8, 0);  g
  glTranslatef(0, -leg_height, 0);
  glGetFloatv(GL_MODELVIEW_MATRIX, blll_node.m);
  blll_node.f = blll;
  blll_node.sibling = NULL;
  blll_node.child = &blt_node;

  // Back Left Toe:
  glLoadIdentity();
  glTranslatef(0, -leg_height, 0);
  glGetFloatv(GL_MODELVIEW_MATRIX, blt_node.m);
  blt_node.f = blt;
  blt_node.sibling = NULL;
  blt_node.child = NULL;

  // Back Right Upper Leg:
  glLoadIdentity();
  // glTranslatef(3, -4, -2);
  // glRotatef(90, 1, 0, 0);
  glTranslatef((torso_height / 2), -torso_height, 2);
  glGetFloatv(GL_MODELVIEW_MATRIX, brul_node.m);
  brul_node.f = brul;
  brul_node.sibling = NULL;
  brul_node.child = &brll_node;

  // Back Right Lower Leg:
  glLoadIdentity();
  // glTranslatef(0, -8, 0);
  glTranslatef(0, -leg_height, 0);
  glGetFloatv(GL_MODELVIEW_MATRIX, brll_node.m);
  brll_node.f = brll;
  brll_node.sibling = NULL;
  brll_node.child = &brt_node;

  // Back Right Toe:
  glLoadIdentity();
  glTranslatef(0, -leg_height, 0);
  glGetFloatv(GL_MODELVIEW_MATRIX, brt_node.m);
  brt_node.f = brt;
  brt_node.sibling = NULL;
  brt_node.child = NULL;
}

void myinit()
{
  //glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  glMatrixMode(GL_PROJECTION);
  glEnable(GL_DEPTH_TEST); // to see back of the cube, has to do with 3Dness
  glClearColor(0.5, 0.5, 0.5, 0);
  glOrtho(-50.0, 50.0, -50.0, 50.0, 0, 100); // αν ειναι αρνητικά, πάει πίσω από τον παρατηρητή

  glMatrixMode(GL_MODELVIEW); // peirazoume ton xoro kai ta simeia tora, oxi tin kamera
  gluLookAt(cam[0], cam[1], cam[2], 0, 0, 0, 0, 1, 0);
  // glulookat explanation: https://stackoverflow.com/questions/5717654/glulookat-explanation/5721110

  init_nodes();
}

void traverse(treenode *root)
{
  if (root == NULL)
    return;
  glPushMatrix();
  glMultMatrixf(root->m);
  root->f();
  if (root->child != NULL)
    traverse(root->child);
  glPopMatrix();
  if (root->sibling != NULL)
    traverse(root->sibling);
}

void drawAxis()
{
  glPushMatrix();
  glBegin(GL_LINE_STRIP);
  glColor3f(1, 0, 0);
  for (int x = -100; x <= 100; x++)
  {
    glVertex3f(x, 0, 0);
  }
  glEnd();
  glPopMatrix();
  glPushMatrix();
  glBegin(GL_LINE_STRIP);
  glColor3f(0, 0, 1);

  for (int x = -100; x <= 100; x++)
  {
    glVertex3f(0, x, 0);
  }
  glEnd();
  glPopMatrix();
  glPushMatrix();
  glBegin(GL_LINE_STRIP);
  glColor3f(0, 1, 0);

  for (int x = -100; x <= 100; x++)
  {
    glVertex3f(0, 0, x);
  }
  glEnd();
  glPopMatrix();
  glColor3f(1, 1, 1);
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt(cam[0], cam[1], cam[2], 0, 0, 0, 0, 1, 0);
  //printf(" %f|%f|%f\n", cam[0], cam[1], cam[2]);

  drawAxis();
  traverse(&torso_node);

  glutSwapBuffers();
  glFlush(); /* clear buffers */
}

void case1()
{
  glPushMatrix();
  glLoadIdentity();
  glTranslatef((torso_height / 2), -torso_height, torso_length - 2);

  glRotatef(theta[0], -1, 0, 0);
  glGetFloatv(GL_MODELVIEW_MATRIX, frul_node.m);
  glPopMatrix();

  glPushMatrix();
  glLoadIdentity();
  glTranslatef(0, -leg_height, 0);
  glRotatef(theta[1], 1, 0, 0);
  glGetFloatv(GL_MODELVIEW_MATRIX, frll_node.m);
  glPopMatrix();
}
void case2()
{ // rotate torso
  glPushMatrix();
  glLoadIdentity();
  glRotatef(theta[2], -1, 0, 0);
  glGetFloatv(GL_MODELVIEW_MATRIX, torso_node.m);
  glPopMatrix();
  // counter-rotate back legs
  glPushMatrix();
  glLoadIdentity();
  glTranslatef(-(torso_height / 2), -torso_height, 2);
  glRotatef(theta[2], 1, 0, 0);
  glGetFloatv(GL_MODELVIEW_MATRIX, blul_node.m);
  glPopMatrix();
  // and the other one
  glPushMatrix();
  glLoadIdentity();
  glTranslatef((torso_height / 2), -torso_height, 2);
  glRotatef(theta[2], 1, 0, 0);
  glGetFloatv(GL_MODELVIEW_MATRIX, brul_node.m);
  glPopMatrix();
  // rotate and bend front legs
  glPushMatrix();
  glLoadIdentity();
  glTranslatef(-(torso_height / 2), -torso_height, torso_length - 2);
  glRotatef(theta[3], -1, 0, 0);
  glGetFloatv(GL_MODELVIEW_MATRIX, flul_node.m);
  glPopMatrix();
  // and lower leg bend
  glPushMatrix();
  glLoadIdentity();
  glTranslatef(0, -leg_height, 0);
  glRotatef(theta[1], 1, 0, 0);
  glGetFloatv(GL_MODELVIEW_MATRIX, flll_node.m);
  glPopMatrix();
  // and other leg
  glPushMatrix();
  glLoadIdentity();
  glTranslatef((torso_height / 2), -torso_height, torso_length - 2);
  glRotatef(theta[3], -1, 0, 0);
  glGetFloatv(GL_MODELVIEW_MATRIX, frul_node.m);
  glPopMatrix();
  // and other lower leg bend
  glPushMatrix();
  glLoadIdentity();
  glTranslatef(0, -leg_height, 0);
  glRotatef(theta[1], 1, 0, 0);
  glGetFloatv(GL_MODELVIEW_MATRIX, frll_node.m);
  glPopMatrix();
}
void case3()
{
  // rotate neck
  glPushMatrix();
  glLoadIdentity();
  glTranslatef(0, torso_height / 2 - 1, torso_length);
  glRotatef(theta[4], 1, 0, 0);
  glGetFloatv(GL_MODELVIEW_MATRIX, neck_node.m);
  glPopMatrix();
}

void idleFunc()
{
  // increase angle for animation
  angle += 0.1;
  for (int i = 0; i < 5; i++)
  {
    theta[i] += angle;
    if (theta[i] > theta_ref[i])
      theta[i] = theta_ref[i];
  }
  switch (menuoption)
  {
  case 0:
    init_nodes();
    break;
  case 1:
    init_nodes();
    case1();
    break;
  case 2:
    init_nodes();
    case2();
    break;
  case 3:
    init_nodes();
    case3();
    break;
  default:
    break;
  }
  glutPostRedisplay();
}

void menu(int option)
{
  menuoption = option;
  angle = 0;
  memset(theta, 0, sizeof(theta));
}

void SpecialKeyHandler(int key, int x, int y)
{
  // CAMERA left-right
  if (key == GLUT_KEY_RIGHT)
    camAngle += M_PI / 180 * 0.45;
  if (key == GLUT_KEY_LEFT)
    camAngle -= M_PI / 180 * 0.45;

  if (camAngle > M_PI / 180 * 360)
    camAngle -= M_PI / 180 * 360;
  if (camAngle < 0)
    camAngle += M_PI / 180 * 360;

  // now calculate new (x,z) for camera
  cam[0] = cos(camAngle) * 70; // 70 = radius
  cam[2] = -sin(camAngle) * 70;

  glutPostRedisplay();
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(800, 800);
  glutInitWindowPosition(50, 150);
  glutCreateWindow("Askisi 2");
  myinit();
  glutDisplayFunc(display);
  glutIdleFunc(idleFunc);
  glutSpecialFunc(SpecialKeyHandler);

  glutCreateMenu(menu);
  glutAddMenuEntry("Default position", 0);
  glutAddMenuEntry("Raise and bend front leg", 1);

  glutAddMenuEntry("Up on back legs and bend front legs", 2);
  glutAddMenuEntry("Bend the neck", 3);

  glutAttachMenu(GLUT_RIGHT_BUTTON);

  glutMainLoop();
  return 0;
}
