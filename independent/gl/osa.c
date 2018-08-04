#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <GL/glut.h>

#define WIDTH_DEFAULT 640
#define HEIGHT_DEFAULT 480
#define NEAR 1.0
#define FAR 10.0

int window_width;
int window_height;
GLdouble rotation_x;
GLdouble rotation_y;
GLdouble rotation_z;

void init(void)
{
  window_width = WIDTH_DEFAULT;
  window_height = HEIGHT_DEFAULT;
  rotation_x = 0.0;
  rotation_y = 0.0;
  rotation_z = 0.0;
}

void init_view(void)
{
  glViewport(0, 0, window_width, window_height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, (GLdouble)window_width/(GLdouble)window_height, NEAR, FAR);
}

void init_gl(void)
{
  glClearColor(0.0, 0.0, 0.0, 0.0);
  init_view();
  glEnable(GL_DEPTH_TEST);
}

void callback_display(void)
{
  int i;
  double t;
  double sin_t;
  double cos_t;

  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslated(0.0, 0.0, -4.0);
  glRotated(rotation_x, 1.0, 0.0, 0.0);
  glRotated(rotation_y, 0.0, 1.0, 0.0);
  glRotated(rotation_z, 0.0, 0.0, 1.0);
  glColor3d(1.0, 0.0, 0.0);
  glBegin(GL_LINES);
  glVertex3d(0.0, 0.0, 0.0);
  glVertex3d(1.0, 0.0, 0.0);
  glEnd();
  glColor3d(0.0, 1.0, 0.0);
  glBegin(GL_LINES);
  glVertex3d(0.0, 0.0, 0.0);
  glVertex3d(0.0, 1.0, 0.0);
  glEnd();
  glColor3d(0.0, 0.0, 1.0);
  glBegin(GL_LINES);
  glVertex3d(0.0, 0.0, 0.0);
  glVertex3d(0.0, 0.0, 1.0);
  glEnd();
  glColor3d(1.0, 1.0, 1.0);
  glBegin(GL_TRIANGLES);
  glVertex3d(0.5, 0.0, 0.0);
  glVertex3d(0.0, 0.5, 0.0);
  glVertex3d(0.0, 0.0, 0.5);
  glEnd();
  glFlush();
  glutSwapBuffers();
}

void callback_reshape(int width, int height)
{
  window_width = width;
  window_height = height;
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  init_view();
  glutPostRedisplay();
}

void callback_keyboard(unsigned char key, int x, int y)
{
  switch(key)
  {
    case ' ':
      rotation_x = 0.0;
      rotation_y = 0.0;
      rotation_z = 0.0;
      glutPostRedisplay();
      break;
    case 'a':
    case 'A':
      rotation_x += 1.0;
      if(rotation_x >= 360.0)
        rotation_x -= 360.0;
      glutPostRedisplay();
      break;
    case 'z':
    case 'Z':
      rotation_x -= 1.0;
      if(rotation_x < 0.0)
        rotation_x += 360.0;
      glutPostRedisplay();
      break;
    case 's':
    case 'S':
      rotation_y += 1.0;
      if(rotation_y >= 360.0)
        rotation_y -= 360.0;
      glutPostRedisplay();
      break;
    case 'x':
    case 'X':
      rotation_y -= 1.0;
      if(rotation_y < 0.0)
        rotation_y += 360.0;
      glutPostRedisplay();
      break;
    case 'd':
    case 'D':
      rotation_z += 1.0;
      if(rotation_z >= 360.0)
        rotation_z -= 360.0;
      glutPostRedisplay();
      break;
    case 'c':
    case 'C':
      rotation_z -= 1.0;
      if(rotation_z < 0.0)
        rotation_z += 360.0;
      glutPostRedisplay();
      break;
    case 'q':
    case 'Q':
      exit(1);
      break;
  }
}

int main(int argument_count, char *argument_value[])
{
  init();
  glutInit(&argument_count, argument_value);
  glutInitWindowSize(window_width, window_height);
  glutInitWindowPosition(0, 0);
  glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
  glutCreateWindow("sample");
  glutSetCursor(GLUT_CURSOR_CYCLE);

  glutDisplayFunc(&callback_display);
  glutReshapeFunc(&callback_reshape);
  glutKeyboardFunc(&callback_keyboard);

  init_gl();
  glutMainLoop();
  return 0;
}
