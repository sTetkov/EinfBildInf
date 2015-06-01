// standard includes
#include <cstdlib>
#include <iostream>

// OpenGL includes
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <cmath>

typedef double[3] PointType;
typedef std::vector< PointType > PointListType;

void transform(PointListType& points,const double m[4*4])
{
 for (PointListType::iterator it = points.begin(); it != points.end(); ++it) {
     double x = it[0];            // get point coordinates
     double y = it[1];
     double z = it[2];

     double x1=x*m[0]+y*m[1]+z*m[2]+1*m[3];
     double y1=x*m[4]+y*m[5]+z*m[6]+1*m[7];
     double z1=x*m[8]+y*m[9]+z*m[10]+1*m[11];

     it[0] = x1;                   // update point coordinates
     it[1] = y1;
     it[2] = z1;
  }
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
            << "*** Übung 03 Aufgabe 3                         ***\n"
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


