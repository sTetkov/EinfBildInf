// standard includes
#include <cstdlib>
#include <iostream>
#include <vector>

// OpenGL includes
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <cmath>

typedef struct PointType{
  double x;
  double y;
  double z;
  PointType(double px,double py, double pz)
  {x=px; y=py; z=pz;}
};
typedef std::vector< PointType > PointListType;

PointListType points;

void transform(const double m[4*4])
{
 for (PointListType::iterator it = points.begin(); it != points.end(); ++it) {
     double x = it->x;            // get point coordinates
     double y = it->y;
     double z = it->z;

     double x1=x*m[0]+y*m[1]+z*m[2]+1*m[3];
     double y1=x*m[4]+y*m[5]+z*m[6]+1*m[7];
     double z1=x*m[8]+y*m[9]+z*m[10]+1*m[11];

     it->x = x1;                   // update point coordinates
     it->y = y1;
     it->z = z1;
  }
}

void translate(double dx,double dy, double dz)
{
  double m[4*4]={1.0, 0.0, 0.0, dx,
                 0.0, 1.0, 0.0, dy,
                 0.0, 0.0, 1.0, dz,
                 0.0, 0.0, 0.0, 1.0};
  transform(m);
}

void scale(double sx, double sy, double sz)
{
  double m[4*4]={ sx, 0.0, 0.0, 0.0,
                 0.0,  sy, 0.0, 0.0,
                 0.0, 0.0,  sz, 0.0,
                 0.0, 0.0, 0.0, 1.0};
  transform(m);
}

void shear(PointType a, PointType b)
{
  double m[4*4]={1.0, a.x, a.y, 0.0,
                 a.z, 1.0, b.x, 0.0,
                 b.y, b.z, 1.0, 0.0,
                 0.0, 0.0, 0.0, 1.0};
  transform(m);
}

void rotateXAxis(double angle)
{
  double m[4*4]={1.0,       0.0,          0.0, 0.0,
                 0.0,cos(angle),-(sin(angle)), 0.0,
                 0.0,sin(angle), cos(angle)  , 0.0,
                 0.0,       0.0,          0.0, 1.0};
  transform(m);
}

void rotateYAxis(double angle)
{
  double m[4*4]=   {cos(angle), 0.0, sin(angle), 0.0,
                           0.0, 1.0,        0.0, 0.0,
                 -(sin(angle)), 0.0, cos(angle), 0.0,
                           0.0, 0.0,        0.0, 1.0};
  transform(m);
}

void rotateZAxis(double angle)
{
  double m[4*4]={cos(angle), -(sin(angle)), 0.0, 0.0,
                 sin(angle),    cos(angle), 0.0, 0.0,
                        0.0,           0.0, 1.0, 0.0,
                        0.0,           0.0, 0.0, 1.0};
  transform(m);
}

/**
  * void drawScene ();
  * This function draws the simple scene required for the excercise
  */
void drawScene()
{
  glColor4f(0.0, 1.0, 0.0, 1.0);
  glBegin(GL_TRIANGLE_FAN);
  for (PointListType::iterator it = points.begin(); it != points.end(); ++it) {
    glVertex3f(it->x,it->y,it->z);
  }
  glEnd();
}

/**
  * void keyboard(unsigned char key, int x, int y);
  * This function implements the handling of keystrokes.
  */
void keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 'q':                           //move on x axis
      translate(1,0,0);
      break;
    case 'a':                           //move on x axis
      translate(-1,0,0);
      break;
    case 'w':                           //move on y axis
    translate(0,1,0);
      break;
    case 's':                           //move on y axis
    translate(0,-1,0);
      break;
    case 'e':                           //move on z axis
      translate(0,0,1);
      break;
    case 'd':                           //move on z axis
    translate(0,0,-1);
      break;
    case 'r':
    scale(1.1,1,1);
    break;
    case 'f':
    scale(0.9,1,1);
    break;
    case 't':
    scale(1,1.1,1);
    break;
    case 'g':
    scale(1,0.9,1);
    break;
    case 'z':
    scale(1,1,1.1);
    break;
    case 'h':
    scale(1,1,0.9);
    break;
    case 'u':
    shear(PointType(0.1,0,0),PointType(0,0,0));
    break;
    case 'j':
    shear(PointType(-0.1,0,0),PointType(0,0,0));
    break;
    case 'i':
    shear(PointType(0,0.1,0),PointType(0,0,0));
    break;
    case 'k':
    shear(PointType(0,-0.1,0),PointType(0,0,0));
    break;
    case 'o':
    shear(PointType(0,0,0.1),PointType(0,0,0));
    break;
    case 'l':
    shear(PointType(0,0,-0.1),PointType(0,0,0));
    break;
    case 'y':
    rotateXAxis(0.1);
    break;
    case 'x':
    rotateYAxis(0.1);
    break;
    case 'c':
    rotateZAxis(0.1);
    break;
    case 27:                            // Escape key
      exit(0);
      break;
    default:
      return;
  }
  glutPostRedisplay ();                 // re-render
}

/**
  * void reshape (int w, int h);
  * This function implements computation of the viewport and projection matrices and passes
  * them to the OpenGL engine.
  */
void reshape (int w, int h) {
  glViewport (0, 0, (GLsizei)w, (GLsizei)h);
  glClearColor(1.0, 1.0, 1.0, 0.0);     // background color
}

/**
  * void display(void);
  * This function contains the OpenGL drawing routines.
  */
void display() {
  glClear(GL_COLOR_BUFFER_BIT);         // clear buffers

  glMatrixMode(GL_PROJECTION);          // specify the current matrix mode;
                                        //   GL_PROJECTION applies subsequent matrix
                                        //   operations to the projection matrix stack
  glLoadIdentity ();                    // set matrix to identity
                                        // create a perspective projection matrix
  gluPerspective(45.0,                   //   FOV (y direction)
                 1.0,                   //   aspect ratio
                 1.0,                   //   near z plane
                 100.0);                //   far z plane
  glMatrixMode(GL_MODELVIEW);           // specify the current matrix mode;
                                        //   GL_MODELVIEW applies subsequent matrix
                                        //   operations to the modelview matrix stack

  glLoadIdentity();                     // set matrix to identity
                                        // define point of view
  gluLookAt (0.0, 0.0, 20.0,            // camera position
             0.0, 0.0, 0.0,             // loking at
             0.0, 1.0, 0.0);            // up vector of the camera
  glRotatef(0.0, 0.0, 1.0, 0.0);    // moving the camera = inverse moving the model
  glRotatef(0.0, 1.0, 0.0, 0.0);

  drawScene();

  glFlush();                            // drawing completed
  glutSwapBuffers();
}

int main(int argc, char** argv)
{
  std::cout << "**************************************************\n"
            << "*** Übung 03 Aufgabe 3                         ***\n"
            << "*** Sascha Tetkov                              ***\n"
            << "**************************************************\n"
            << "\n"
            << "Usage:\n"
            << "ESC :   Exit\n"
            << "\n";

  points.push_back(PointType(5.0,0.0,0.0));
  points.push_back(PointType(0.0,5.0,0.0));
  points.push_back(PointType(0.0,0.0,5.0));
  points.push_back(PointType(5.0,5.0,5.0));
  glutInit(&argc, argv);
  glutInitWindowSize(800, 800);         // resize window
  glutInitWindowPosition(0, 0);         // position window
                                        // create a titled drawing window (double buffered)
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutCreateWindow("Übung 03 Aufgabe 03");
  glutDisplayFunc(display);             // define the custom opengl function
  glutKeyboardFunc(keyboard);           // keyboard callback
  glutReshapeFunc(reshape);             // reshape callback
  glutMainLoop();                       // enter the GLUT event processing loop
  glutReshapeFunc(reshape);             // reshape callback
  glutMainLoop();                       // enter the GLUT event processing loop
  return 0;                             // everything's gone fine ;)
}
