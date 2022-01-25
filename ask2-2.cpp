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

const int MAX_NUM_PARTICLES = 20;
particle particles[MAX_NUM_PARTICLES];
// in all axis: 20/-20
GLfloat bounding_box = 20; 

int num_particles = 1;
void test()
{
    particle prt1 = {{0, 1, 0}, {1, 0, 0}, 2};
    prt1.mass = 1;
    //cout << "mass " << prt1.mass;
    particles[0] = prt1;
}

// for (int i = 0; i < num_particles; i++)
// {
//     particles[i].mass = 1.0;
//     //particles[i].color = i % NUM_COLORS;
//     for (int j = 0; j < 3; j++)
//     {
//         particles[i].position[j] = 2.0 * ((float)rand() / RAND_MAX) - 1.0;
//         particles[i].velocity[j] = speed * 2.0 * ((float)rand() / RAND_MAX) - 1.0;
//     }
//     particles[i].position[3] = 1.0;
//     particles[i].velocity[3] = 0.0;
// }

float coef = 1; /* coefficient of restitution */
void collision(int n)
{
    int i;
    for (i = 0; i < 3; i++)
    {
        if (particles[n].position[i] >= 1.0)
        {
            particles[n].velocity[i] = -coef * particles[n].velocity[i];
            particles[n].position[i] = 1.0 - coef *
                                                 (particles[n].position[i] - 1.0);
        }
        if (particles[n].position[i] <= -1.0)
        {
            particles[n].velocity[i] = -coef * particles[n].velocity[i];
            particles[n].position[i] = -1.0 - coef *
                                                  (particles[n].position[i] + 1.0);
        }
    }
}

//bool gravity = TRUE;
float forces(int i, int j)
{
    // if (!gravity)
    //     return (0.0);
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
    test();
    drawParticles();

    glutSwapBuffers();
    glFlush(); /* clear buffers */
}

float dt = 0.1;        // time unit
float timecounter = 0; // time counter
void idleFunc()
{
    int i, j;
    //float dt;
    //present_time = glutGet(GLUT_ELAPSED_TIME); /* in milliseconds */
    //dt = 0.001 * (present_time - last_time);   /* in seconds */
    for (i = 0; i < num_particles; i++)
    {
        for (j = 0; j < 3; j++)
        {
            particles[i].position[j] += dt * particles[i].velocity[j];
            particles[i].velocity[j] += dt * forces(i, j) / particles[i].mass;
        }
        collision(i);
    }
    //last_time = present_time;
    timecounter += dt;

    // generate a new particle with probability x
    // if array not full
    // generateParticle()

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
    //glutIdleFunc(idleFunc);
    glutSpecialFunc(SpecialKeyHandler);

    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}
