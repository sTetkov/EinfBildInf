
// standard includes
#include <cstdlib>

#define OPENGL_MODE

#include <cstdio>
#include <vector>
#include <math.h>


// OpenGL includes
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

float rotX = 0.0;
float rotY = 0.0;
float rotZ = 0.0;
float zoom = 30.0;
float azimuth = 0.0;
float height = 0.0;

#include "./helpers.h"
#include "./geometry.h"

Object3DListType __objects3D;

void draw3DObject(const Object3DType object) {
  Point3DListType _points = object.first;
  EdgeListType    _edges  = object.second;
  
  glColor4f(1.0, 0.0, 0.0, 1.0);        // redefine pen color
  glBegin(GL_LINES);               // define rendering mode: lines
  for (EdgeListType::iterator itEdges = _edges.begin(); 
       itEdges != _edges.end(); 
       ++itEdges) {
    
       glVertex3f(_points[itEdges->first](0),
                  _points[itEdges->first](1),
                  _points[itEdges->first](2));
       glVertex3f(_points[itEdges->second](0),
                  _points[itEdges->second](1),
                  _points[itEdges->second](2));
  }
  glEnd();  
}

void draw3DObjects(const Object3DListType objects) {
  Object3DListType::const_iterator it = objects.begin();
  for (; it != objects.end(); ++it) {
    draw3DObject(*it);
  }
}

/**
  * void display(void);
  * This function contains the OpenGL drawing routines.
  */
void display(void) {
  glClear(GL_COLOR_BUFFER_BIT);         // clear buffers
  glLoadIdentity();                     // set projection matrix to identity
    
  glRotatef(rotX, 1.0, 0.0, 0.0);       // x rotation
  glRotatef(rotY, 0.0, 1.0, 0.0);       // y rotation
  glRotatef(rotZ, 0.0, 0.0, 1.0);       // z rotation

  gluLookAt(cos(height  * M_PI / 180.0) * cos(azimuth * M_PI / 180.0) * zoom, 
            sin(azimuth * M_PI / 180.0) * zoom,            // position of eye
            cos(height  * M_PI / 180.0) * sin(azimuth * M_PI / 180.0) * zoom, 
            0.0, 0.0, 1.0,             // at, where pointing at
            0.0, -1.0, 0.0);           // up vector of the camera 
  draw3DObjects(__objects3D);
//   drawObject(__objects[0]);
  
  glFlush();                            // drawing completed
}



/**
  * void reshape (int w, int h);
  * This function implements computation of the viewport and projection matrices and passes 
  * them to the OpenGL engine.
  */
void reshape (int w, int h) {
  glViewport (0, 0, (GLsizei)w, (GLsizei)h);
  glClearColor(1.0, 1.0, 1.0, 0.0);     // background color
  glMatrixMode(GL_PROJECTION);          // specify the current matrix mode;
                                        //   GL_PROJECTION applies subsequent matrix
                                        //   operations to the projection matrix stack
  glLoadIdentity ();                    // set matrix to identity
  gluPerspective(45.0, 1.0, 1.0, 100.0);// create a perspective projection matrix
  glMatrixMode(GL_MODELVIEW);           // specify the current matrix mode;
                                        //   GL_MODELVIEW applies subsequent matrix 
                                        //   operations to the modelview matrix stack
}

void demo(void) {
  glColor4f(0.0, 0.0, 0.0, 1.0);        // define pen color
  glBegin(GL_POINTS);                   // drawing points points
    glVertex3f(-1.0, 0.0, 3.0);         // vertex 1
    glVertex3f(-1.0, 0.0, -2.0);        // vertex 2
    glVertex3f(-2.0, 0.0, -1.0);        // vertex 3
  glEnd();  
  
  glColor4f(1.0, 0.0, 0.0, 1.0);        // redefine pen color
  glBegin(GL_LINE_STRIP);               // define rendering mode: lines
    glVertex3f(1.0, 0.0, 4.0);          // from vertex 1
    glVertex3f(1.0, 0.0, 2.0);          //   to vertex 2
    glVertex3f(2.0, 0.0, 1.0);          //   to vertex 3
    glVertex3f(1.0, 0.0, 4.0);          //   to vertex 1
  glEnd();
 
  glColor4f(0.0, 1.0, 0.0, 1.0);        // redefine pen color
  glBegin(GL_TRIANGLES);                // define rendering mode: triangles
    glVertex3f( 0.0, 0.0, 4.0);         // vertex 1
    glVertex3f( 0.0, 0.0, 2.0);         // vertex 2
    glVertex3f(-1.0, 0.0, 1.0);         // vertex 3
  glEnd();

  glColor4f(0.0, 0.0, 1.0, 1.0);        // redefine pen color
  glBegin(GL_QUADS);                    // define rendering mode: quadangles
    glVertex3f(2.0, 0.0,  0.0);         // vertex 1
    glVertex3f(0.0, 0.0,  0.0);         // vertex 2
    glVertex3f(0.0, 0.0, -2.0);         // vertex 3
    glVertex3f(2.0, 0.0, -2.0);         // vertex 4
  glEnd();
  
  glColor4f(1.0, 0.0, 1.0, 1.0);        // redefine pen color
  glBegin(GL_TRIANGLE_FAN);             // define rendering mode: quadangles
    glVertex3f(-4.0, 0.0, 3.0);         // center
    glVertex3f(-2.0, 0.0, 1.0);         // vertex 1
    glVertex3f(-1.0, 0.0, 5.0);         // vertex 2
    glVertex3f(-6.0, 0.0, 4.0);         // vertex 3
  glEnd();
}

// main function
int main(int argc, char **argv) {
  
  create3DObject(__objects3D);
  
	glutInit(&argc, argv);                // initialize opengl engine
	glutInitWindowSize(1024, 1024);       // resize window
	glutInitWindowPosition(0, 0);         // position window
                                        // create a titled drawing window
	glutCreateWindow("Introduction to Visual Computing - OpenGL Demo");
	glutDisplayFunc(display);             // define the custom opengl function
  glutKeyboardFunc(keyboard);           // keyboard callback
  glutSpecialFunc(SpecialKey);          // special keyboard callback
  glutReshapeFunc(reshape);             // reshape callback
	glutMainLoop();                       // enter the GLUT event processing loop
	return 0;                             // everything's gone fine ;)
}
