// standard includes
#include <cstdlib>
#include <iostream>

// OpenGL includes
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

/**
  * void drawScene ();
  * This function draws the simple scene required for the excercise
  */
void drawScene()
{
  glColor4f(1.0, 0.0, 0.0, 1.0);        // redefine pen color
  glBegin(GL_LINE_STRIP);               // define rendering mode: lines
    glVertex3f(0.0, 0.0, 0.0);          // from vertex 1
    glVertex3f(0.0, 5.0, 0.0);          //   to vertex 2
    glVertex3f(2.5, 7.5, 0.0);          //   to vertex 3
    glVertex3f(5.0, 5.0, 0.0);          //   to vertex 4
    glVertex3f(5.0, 0.0, 0.0);          //   to vertex 5
    glVertex3f(0.0, 5.0, 0.0);          //   to vertex 6
    glVertex3f(5.0, 5.0, 0.0);          //   to vertex 7
    glVertex3f(0.0, 0.0, 0.0);          //   to vertex 8
    glVertex3f(5.0, 0.0, 0.0);          //   to vertex 9
  glEnd();

  //grass
  glColor4f(0.0, 1.0, 0.0, 1.0);        // redefine pen color
  glBegin(GL_LINE_STRIP);               // define rendering mode: lines
    glVertex3f(-10.0, 0.0, 0.0);          // from vertex 1
    glVertex3f(15.0, 0.0, 0.0);
  glEnd();
  
  glBegin(GL_LINE_STRIP);
    glVertex3f(-2.0,0.0,0.0);
    glVertex3f(-2.0,2.0,0.0);
    glVertex3f(-4.0,2.0,0.0);
    glVertex3f(-2.5,3.0,0.0);
    glVertex3f(-3.75,3.0,0.0);
    glVertex3f(-2.25,4.0,0.0);
    glVertex3f(-3.5,4.0,0.0);
    glVertex3f(-2.0,5.0,0.0);
    glVertex3f(-0.5,4.0,0.0);
    glVertex3f(-1.25,4.0,0.0);
    glVertex3f(-0.25,3.0,0.0);
    glVertex3f(-1.5,3.0,0.0);
    glVertex3f(-0.0,2.0,0.0);
    glVertex3f(-2.0,2.0,0.0);
  glEnd();
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
  gluLookAt (2.0, 5.0, 20.0,            // camera position
             2.0, 5.0, 0.0,             // loking at
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
            << "*** Übung 01 Aufgabe 4                         ***\n"
            << "*** Sascha Tetkov                              ***\n"
            << "**************************************************\n"
            << "\n";
   glutInit(&argc, argv);
   glutInitWindowSize(800, 800);         // resize window
   glutInitWindowPosition(0, 0);         // position window
                                        // create a titled drawing window (double buffered)
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
   glutCreateWindow("Übung 01 Aufgabe 04");
   glutDisplayFunc(display);             // define the custom opengl function
   glutReshapeFunc(reshape);             // reshape callback
   glutMainLoop();                       // enter the GLUT event processing loop
   return 0;                             // everything's gone fine ;)
}
