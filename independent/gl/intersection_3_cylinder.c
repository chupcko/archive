#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <GL/glut.h>

#define ENTRY printf("In %s:%d\n", __FUNCTION__, __LINE__)

#define WIDTH_DEFAULT 640
#define HEIGHT_DEFAULT 480
#define NEAR 1.0
#define FAR 10.0

#define TIMER_SLEEP_MSECONDS 40u

typedef enum
{
  FALSE = 0,
  TRUE = 1
} boolean;

int window_width;
int window_height;
GLdouble rotation_x;
GLdouble rotation_y;
GLdouble rotation_z;
boolean animation;
boolean orthogonal;
boolean wire;

void init(void)
{
  window_width = WIDTH_DEFAULT;
  window_height = HEIGHT_DEFAULT;
  rotation_x = 0.0;
  rotation_y = 0.0;
  rotation_z = 0.0;
  animation = FALSE;
  orthogonal = FALSE;
  wire = FALSE;
}

void init_view(void)
{
  glViewport(0, 0, window_width, window_height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if(orthogonal == TRUE)
  {
    if(window_width < window_height)
      glOrtho(-1.5, 1.5, -1.5*(GLdouble)window_height/(GLdouble)window_width, 1.5*(GLdouble)window_height/(GLdouble)window_width, NEAR, FAR);
    else
      glOrtho(-1.5*(GLdouble)window_width/(GLdouble)window_height, 1.5*(GLdouble)window_width/(GLdouble)window_height, -1.5, 1.5, NEAR, FAR);
  }
  else
    gluPerspective(45.0, (GLdouble)window_width/(GLdouble)window_height, NEAR, FAR);
}

void init_ligths(void)
{
  GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 0.15 };
  GLfloat mat_shininess[] = { 100.0 };
  GLfloat position[] = { 3.5, 3.5, 3.0, 0.0 };

  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
  glLightfv(GL_LIGHT0, GL_POSITION, position);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
}

void init_gl(void)
{
  glClearColor(0.0, 0.0, 0.0, 0.0);
  init_view();
  glEnable(GL_DEPTH_TEST);
  if(0 == 1)
    init_ligths();
}

inline double dabs(double x)
{
  if(x < 0.0)
    return -x;
  return x;
}

void display_part(void)
#define N 16
{
  int i;
  double t;
  double sin_t;
  double cos_t;

  glBegin(GL_QUAD_STRIP);
  for(i = 0; i <= 8*N; i++)
  {
    t = (double)i*M_PI/(4.0*(double)N);
    cos_t = cos(t);
    sin_t = sin(t);
    if((i/N+1)/2%2 == 0)
    {
      glVertex3d(cos_t, sin_t, -dabs(sin_t));
      glVertex3d(cos_t, sin_t, dabs(sin_t));
    }
    else
    {
      glVertex3d(cos_t, sin_t, -dabs(cos_t));
      glVertex3d(cos_t, sin_t, dabs(cos_t));
    }
  }
  glEnd();
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
  display_part();
  glRotated(90.0, 1.0, 0.0, 0.0);
  glColor3d(0.0, 1.0, 0.0);
  display_part();
  glRotated(90.0, 0.0, 1.0, 0.0);
  glColor3d(0.0, 0.0, 1.0);
  display_part();
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

inline boolean not(boolean x)
{
  if(x == TRUE)
    return FALSE;
  return TRUE;
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
    case 'm':
    case 'M':
      animation = not(animation);
      glutPostRedisplay();
      break;
    case 'o':
    case 'O':
      orthogonal = not(orthogonal);
      init_view();
      glutPostRedisplay();
      break;
    case 'w':
    case 'W':
      wire = not(wire);
      if(wire == TRUE)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      glutPostRedisplay();
      break;
    case 'q':
    case 'Q':
      exit(1);
      break;
  }
}

void callback_special(int key, int x, int y)
{
  ENTRY;
  printf("%d %d %d\n", key, x, y);
}

void callback_mouse(int button, int state, int x, int y)
{
  ENTRY;
  printf("%d %d %d %d\n", button, state, x, y);
}

void callback_motion(int x, int y)
{
  ENTRY;
  printf("%d %d\n", x , y);
}

void callback_timer(int value)
{
  if(animation == TRUE)
  {
    rotation_x += 1.1;
    if(rotation_x >= 360.0)
      rotation_x -= 360.0;
    rotation_y += 0.55;
    if(rotation_y >= 360.0)
      rotation_y -= 360.0;
    rotation_z += 0.63;
    if(rotation_z >= 360.0)
      rotation_z -= 360.0;
    glutPostRedisplay();
  }
  glutTimerFunc(TIMER_SLEEP_MSECONDS, &callback_timer, 0);
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
  glutSpecialFunc(&callback_special);
  glutMouseFunc(&callback_mouse);
  glutMotionFunc(&callback_motion);
  glutTimerFunc(TIMER_SLEEP_MSECONDS, &callback_timer, 0);

  init_gl();
  glutMainLoop();
  return 0;
}
