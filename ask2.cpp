#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <string>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>
#include <cmath>
#include <list>
#define M_PI 3.14159265358979323846
using namespace std;

GLfloat cam[] = {0, 0, 70};
GLfloat camAngle = M_PI / 180 * 270;

typedef struct treenode
{
  GLfloat m[16];
  void (*f)();
  struct treenode *sibling;
  struct treenode *child;
} treenode;
treenode torso_node, head_node, neck_node, flul_node, frul_node, blul_node, brul_node, flll_node, frll_node, blll_node, brll_node;
// legs: front/back, right/left, upper/lower, leg

GLfloat theta[11] = {0};

int torso_length = 15;
int torso_height = 5;
void torso()
{
  glPushMatrix();
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
  glTranslatef(0, torso_height / 2 - 1, torso_length);
  gluCylinder(gluNewQuadric(), 3, 2, 5, 20, 20);
  glPopMatrix();
}
int head_size = 3.5;
void head()
{
  glPushMatrix();
  glTranslatef(0, 1, neck_length + head_size / 2);
  glTranslatef(0, torso_height / 2 - 1, torso_length);
  gluSphere(gluNewQuadric(), head_size, 20, 20);
  glPopMatrix();
}

int leg_height = 5;
void flul()
{
  glPushMatrix();
  glTranslatef(-(torso_height / 2), -torso_height, torso_length - 2);
  glRotatef(90, 1, 0, 0);
  gluCylinder(gluNewQuadric(), 1, 1, leg_height, 20, 20);
  glPopMatrix();
}
void flll()
{
  glPushMatrix();
  glTranslatef(0, -leg_height, 0);
  glTranslatef(-(torso_height / 2), -torso_height, torso_length - 2);
  glRotatef(90, 1, 0, 0);
  gluCylinder(gluNewQuadric(), 1, 1, leg_height, 20, 20);
  glPopMatrix();
}

void frul()
{
  glPushMatrix();
  glTranslatef(torso_height / 2, -torso_height, torso_length - 2);
  glRotatef(90, 1, 0, 0);
  gluCylinder(gluNewQuadric(), 1, 1, leg_height, 20, 20);
  glPopMatrix();
}
void frll()
{
  glPushMatrix();
  glTranslatef(0, -leg_height, 0);
  glTranslatef(torso_height / 2, -torso_height, torso_length - 2);
  glRotatef(90, 1, 0, 0);
  gluCylinder(gluNewQuadric(), 1, 1, leg_height, 20, 20);
  glPopMatrix();
}

void blul()
{
  glPushMatrix();
  glTranslatef(-torso_height / 2, -torso_height, 2);
  glRotatef(90, 1, 0, 0);
  gluCylinder(gluNewQuadric(), 1, 1, leg_height, 20, 20);
  glPopMatrix();
}
void blll()
{
  glPushMatrix();
  glTranslatef(0, -leg_height, 0);
  glTranslatef(-torso_height / 2, -torso_height, 2);
  glRotatef(90, 1, 0, 0);
  gluCylinder(gluNewQuadric(), 1, 1, leg_height, 20, 20);
  glPopMatrix();
}

void brul()
{
  glPushMatrix();
  glTranslatef(torso_height / 2, -torso_height, 2);
  glRotatef(90, 1, 0, 0);
  gluCylinder(gluNewQuadric(), 1, 1, leg_height, 20, 20);
  glPopMatrix();
}
void brll()
{
  glPushMatrix();
  glTranslatef(0, -leg_height, 0);
  glTranslatef(torso_height / 2, -torso_height, 2);
  glRotatef(90, 1, 0, 0);
  gluCylinder(gluNewQuadric(), 1, 1, leg_height, 20, 20);
  glPopMatrix();
}

void toe()
{
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

  // INITIALIZE TREE NODES
  // TORSO:
  glLoadIdentity();
  //glRotatef(90, 0, 1, 0);
  glGetFloatv(GL_MODELVIEW_MATRIX, torso_node.m);
  torso_node.f = torso;
  torso_node.sibling = NULL;
  torso_node.child = &neck_node;

  // NECK:
  glLoadIdentity();
  //glRotatef(90, 0, 1, 0);
  glGetFloatv(GL_MODELVIEW_MATRIX, neck_node.m);
  neck_node.f = neck;
  neck_node.sibling = &flul_node;
  neck_node.child = &head_node;

  // HEAD:
  glLoadIdentity();
  glGetFloatv(GL_MODELVIEW_MATRIX, head_node.m);
  head_node.f = head;
  head_node.sibling = NULL;
  head_node.child = NULL;

  // Front Left Upper Leg:
  glLoadIdentity();
  glGetFloatv(GL_MODELVIEW_MATRIX, flul_node.m);
  flul_node.f = flul;
  flul_node.sibling = &frul_node;
  flul_node.child = &flll_node;

  // Front Left Lower Leg:
  glLoadIdentity();
  glGetFloatv(GL_MODELVIEW_MATRIX, flll_node.m);
  flll_node.f = flll;
  flll_node.sibling = NULL;
  flll_node.child = NULL;

  // Front Right Upper Leg:
  glLoadIdentity();
  // glTranslatef(13, -8, -2);
  // glRotatef(90, 1, 0, 0);
  glGetFloatv(GL_MODELVIEW_MATRIX, frul_node.m);
  frul_node.f = frul;
  frul_node.sibling = &blul_node;
  frul_node.child = &frll_node;

  // Front Right Lower Leg:
  glLoadIdentity();
  // glTranslatef(0, -8, 0);
  glGetFloatv(GL_MODELVIEW_MATRIX, frll_node.m);
  frll_node.f = frll;
  frll_node.sibling = NULL;
  frll_node.child = NULL;

  // Back Left Upper Leg:
  glLoadIdentity();
  // glTranslatef(3, -4, 2);
  // glRotatef(90, 1, 0, 0);
  glGetFloatv(GL_MODELVIEW_MATRIX, blul_node.m);
  blul_node.f = blul;
  blul_node.sibling = &brul_node;
  blul_node.child = &blll_node;

  // Back Left Lower Leg:
  glLoadIdentity();
  // glTranslatef(0, -8, 0);
  glGetFloatv(GL_MODELVIEW_MATRIX, blll_node.m);
  blll_node.f = blll;
  blll_node.sibling = NULL;
  blll_node.child = NULL;

  // Back Right Upper Leg:
  glLoadIdentity();
  // glTranslatef(3, -4, -2);
  // glRotatef(90, 1, 0, 0);
  glGetFloatv(GL_MODELVIEW_MATRIX, brul_node.m);
  brul_node.f = brul;
  brul_node.sibling = NULL;
  brul_node.child = &brll_node;

  // Back Right Lower Leg:
  glLoadIdentity();
  // glTranslatef(0, -8, 0);
  glGetFloatv(GL_MODELVIEW_MATRIX, brll_node.m);
  brll_node.f = brll;
  brll_node.sibling = NULL;
  brll_node.child = NULL;
}

void idleFunc()
{

  //glutPostRedisplay();
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

int menuoption = 0; //default
void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt(cam[0], cam[1], cam[2], 0, 0, 0, 0, 1, 0);
  //printf(" %f|%f|%f\n", cam[0], cam[1], cam[2]);

  switch (menuoption)
  {
  case 0: // default dog position
    traverse(&torso_node);
    break;
  }

  glutSwapBuffers();
  glFlush(); /* clear buffers */
}

void menu(int option)
{
  menuoption = option;
  glutPostRedisplay();
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
  glutAddMenuEntry("Cubic Interpolation Curve", 0);
  glutAddMenuEntry("Bezier Curve: 1 part/6th degree", 1);

  glutAddMenuEntry("Bezier Curve: 2 cubic parts", 2);
  glutAddMenuEntry("Bicubic interpolation surface", 3);

  glutAttachMenu(GLUT_RIGHT_BUTTON);

  glutMainLoop();
  return 0;
}
