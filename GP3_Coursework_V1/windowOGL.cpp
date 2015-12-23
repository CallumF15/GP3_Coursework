#include "windowOGL.h"

windowOGL::windowOGL()
{

}

bool windowOGL::initOGL(int width, int height)
{
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); //Indicates the quality of color. The most correct, or highest quality.
	glEnable(GL_DEPTH_TEST); //depth comparisons and update the depth buffer
	glEnable(GL_LIGHTING);  // no vertex shader is active
	glClearStencil(0);                          // clear stencil buffer
	glClearDepth(1.0f);                         // 0 is near, 1 is far
	glDepthFunc(GL_LEQUAL);  //pass in incoming depth
	onResize(width, height); //resize render window

    //Return success
    return true;
}

void windowOGL::renderOGL(float rotAngle)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear depth/color matrix
    glLoadIdentity(); //reset matrix
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // select a polygon rasterization mode ( interior of the polygon is filled)
}

void windowOGL::shutdown()
{

}

void windowOGL::onResize(int width, int height)
{
    glViewport(0, 0, width, height);  //specifiy window viewport for rendering

    glMatrixMode(GL_PROJECTION); //Applies subsequent matrix operations to the projection matrix stack.
    glLoadIdentity(); //reset matrix

    gluPerspective(45.0f, float(width) / float(height), 1.0f, 100.0f); // set up a perspective projection matrix

    glMatrixMode(GL_MODELVIEW); //Applies subsequent matrix operations to the modelview matrix stack.

    glLoadIdentity();
}

void windowOGL::setOrtho2D(int width, int height)
{
	glDisable(GL_DEPTH_TEST); //disable depth comparisons
	glDisable(GL_LIGHTING); //disable no vertex shader
	glViewport(0, 0, width, height); 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); //reset matrix 
	glOrtho(0.0, width, height, 0.0, 0.0, -1.0);
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();
}

void windowOGL::setProjection3D(int width, int height)
{
	onResize(width, height);
}