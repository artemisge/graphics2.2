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

GLfloat cam[] = {0, 20, 70};
GLfloat camAngle = M_PI / 180 * 270;

typedef struct particle
{
    //int color;
    GLfloat position[3];
    GLfloat velocity[3];
    GLfloat mass;
} particle;

const int MAX_NUM_PARTICLES = 50;
particle particles[MAX_NUM_PARTICLES];
// in all axis: 50/-50
GLfloat bounding_box = 50;

float dt = 0.1;        // time unit
float timecounter = 0; // time counter

int num_particles = 0;
float speed = 1;
void test()
{
    particle prt1;
    prt1.mass = 1;
    for (int j = 0; j < 3; j++)
    {
        prt1.position[j] = bounding_box * ((float)rand() / RAND_MAX) - bounding_box * 0.5;
        prt1.velocity[j] = speed * ((float)rand() / RAND_MAX);
    }
    particles[0] = prt1;
}

void generateParticle()
{
    // every x time units generate a particle
    // multiply * 10 giati einai dekadiko kai i (int) kanei floor, opote kanei generate polla particles mazi
    int time_modulo = (int)(timecounter * 10) % 30; // every 30 "seconds"
    if (time_modulo == 0)
    {
        // if array not full
        if (num_particles < MAX_NUM_PARTICLES)
        {
            particle prt;
            prt.mass = 1;
            for (int j = 0; j < 3; j++)
            {
                prt.position[j] = bounding_box * ((float)rand() / RAND_MAX) - bounding_box * 0.5;
                prt.velocity[j] = speed * ((float)rand() / RAND_MAX);
            }
            particles[++num_particles] = prt;
        }
    }
}

float coef = 1; // elastiki anapidisi
void collision(int n)
{
    int i;
    for (i = 0; i < 3; i++)
    {
        if (particles[n].position[i] >= bounding_box / 2)
        {
            particles[n].velocity[i] = -coef * particles[n].velocity[i];
            particles[n].position[i] = bounding_box / 2 - coef * (particles[n].position[i] - bounding_box / 2);
        }
        if (particles[n].position[i] <= -bounding_box / 2)
        {
            particles[n].velocity[i] = -coef * particles[n].velocity[i];
            particles[n].position[i] = -bounding_box / 2 - coef * (particles[n].position[i] + bounding_box / 2);
        }
    }
}

// theloume gravity mono ston y axis. (j=1)
float forces(int i, int j)
{
    if (j == 1)
        return (-1.0);
    else
        return (0.0);
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

void drawParticles()
{
    for (int i = 0; i < num_particles; i++)
    {
        glPointSize(20);
        glBegin(GL_POINTS);
        glVertex3fv(particles[i].position);
        glEnd();
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(cam[0], cam[1], cam[2], 0, 0, 0, 0, 1, 0);
    //printf(" %f|%f|%f\n", cam[0], cam[1], cam[2]);

    drawAxis();
    drawParticles();

    glutSwapBuffers();
    glFlush(); /* clear buffers */
}

void idleFunc()
{
    for (int i = 0; i < num_particles; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // State derivative: Y': (x, v)' -> (v, f/m)
            // Euler's method nomizo
            // Y(t+h) = Y(t) + h*Y'(t) + error
            // position += h * x' (=v)
            // velocity += h * v' (=f/m)
            particles[i].position[j] += dt * particles[i].velocity[j];
            particles[i].velocity[j] += dt * forces(i, j) / particles[i].mass;
        }
        collision(i);
    }
    timecounter += dt;
    cout << timecounter << endl;

    // generate a new particle with probability x
    // if array not full
    generateParticle();

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
    glutCreateWindow("Askisi 2.2");
    myinit();
    glutDisplayFunc(display);
    glutIdleFunc(idleFunc);
    glutSpecialFunc(SpecialKeyHandler);

    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}
