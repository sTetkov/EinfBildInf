#ifndef HELPERS
#define HELPERS

// standard includes
#include <limits>

// OpenGL includes
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#ifdef OPENGL_MODE
/**
  * void keyboard(unsigned char key, int x, int y);
  * This function implements the handling of keystrokes.
  */
void keyboard(unsigned char key, int x, int y) {
  switch (key) {
     case 27:                           // Escape key
       exit(0);
       break;
     default:
       return;
  }
  glutPostRedisplay ();                 // re-render
}

/**
  * void SpecialKey(int key, int x, int y);
  * This function implements the handling of special keystrokes (e.g. arrow keys).
  */
void SpecialKey(int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_DOWN:
      if (height > 0.0) height -= 1;
      break;
    case GLUT_KEY_UP:
      if (height < 90.0) height += 1;
      break;
    case GLUT_KEY_LEFT:
      if (azimuth > 0.0) azimuth -= 1;
      break;
    case GLUT_KEY_RIGHT:
      if (azimuth < 180.0)azimuth += 1;
      break;
    case GLUT_KEY_PAGE_UP:
      rotZ += 5;
      break;
    case GLUT_KEY_PAGE_DOWN:
      rotZ -= 5;
      break;
    case GLUT_KEY_HOME:
      zoom -= 1;
      break;
    case GLUT_KEY_END:
      zoom += 1;
      break;
    default:
      return;
  }
  glutPostRedisplay ();                 // re-render
}
#endif


#endif
