// standard includes
#include <cstdlib>
#include <iostream>

// OpenGL includes
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <cmath>

#define PI           3.14159265358979323846  /* pi */

int segmentAmount;
int polygonAmount;
float radius;

float x_coord;
float y_coord;
float z_coord;
/**
  * void drawCircle(float x, float y, float z, float radius, int segments)
  * this function draws an aproximated circle with center in (x,y,z), radius and aproximated
  * with segments number of lines
  */
void drawCircle(float x, float y, float z, float radius, int segments)
{
  float period=(2*PI)/segments;
  glBegin(GL_LINE_STRIP);   
  for(int i=0; i<segments;i++)
  {
    float x_offset=cos(period*i)*radius;     //compiler optimizes this away
    float y_offset=sin(period*i)*radius;
    glVertex3f(x+x_offset,y+y_offset,z);
  }
  glVertex3f(x+radius,y,z);
  glEnd();
}

/**
  * void fillCircle(float x, float y, float z, float radius, int polygons)
  * fills a circle with centre in (x,y,z), radius with polygons amount of polygons
  */
void fillCircle(float x, float y, float z, float radius, int polygons)
{
  float period=(2*PI)/(2+polygonAmount);
  glBegin(GL_TRIANGLE_FAN);
  glVertex3f(x+radius,y,z);   
  for(int i=1; i<polygons+2;i++)
  {
    float x_offset=cos(period*i)*radius;     //compiler optimizes this away
    float y_offset=sin(period*i)*radius;
    glVertex3f(x+x_offset,y+y_offset,z);
  }
  glEnd();
}

/**
  * void drawScene ();
  * This function draws the simple scene required for the excercise
  */
void drawScene()
{
  glColor4f(0.0, 1.0, 0.0, 1.0);
  fillCircle(0.0, 0.0, 0.0, radius, polygonAmount);

  glColor4f(0.0, 0.0, 0.0, 1.0);        // redefine pen color
  drawCircle(0.0, 0.0, 0.0, radius, segmentAmount);
}

/**
  * void keyboard(unsigned char key, int x, int y);
  * This function implements the handling of keystrokes.
  */
void keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 'q':                           // increase segment count
      segmentAmount++;
      break;
    case 'a':                           //decrease segment amount
      if (segmentAmount > 4) segmentAmount--;
      break;
    case 'w':                           // increase polygon amount
      polygonAmount++;
      break;
    case 's':                           // decrease polygon amount
      if(polygonAmount > 1) polygonAmount--;
      break;
    case 'e':                           //increase radius
      radius+=0.2;
      break;
    case 'd':                           //decrease radius
      if(radius > 0.5) radius-=0.2;
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
void display(void) {
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
            << "*** Übung 01 Aufgabe 5                         ***\n"
            << "*** Sascha Tetkov                              ***\n"
            << "**************************************************\n"
            << "\n"
            << "Usage:\n"
            << "q   :   Increase Circle segments\n"
            << "a   :   Decrease Circle segments\n"
            << "w   :   Increase Circle polygons\n"
            << "s   :   Decrease Circle polygons\n"
            << "e   :   Increase Circle radius\n"
            << "d   :   Decrease Circle radius\n"
            << "ESC :   Exit\n"
            << "\n";
  segmentAmount=4;
  polygonAmount=1;
  radius=4.0;

  x_coord=0.0;
  y_coord=0.0;
  z_coord=0.0;
  glutInit(&argc, argv);
  glutInitWindowSize(800, 800);         // resize window
  glutInitWindowPosition(0, 0);         // position window
                                        // create a titled drawing window (double buffered)
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutCreateWindow("Übung 01 Aufgabe 05");
  glutDisplayFunc(display);             // define the custom opengl function
  glutKeyboardFunc(keyboard);           // keyboard callback
  glutReshapeFunc(reshape);             // reshape callback
  glutMainLoop();                       // enter the GLUT event processing loop
  glutReshapeFunc(reshape);             // reshape callback
  glutMainLoop();                       // enter the GLUT event processing loop
  return 0;                             // everything's gone fine ;)
}


