#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(linker, "/subsystem:console")

#include "windows.h"
#include "stdlib.h"
#include <iostream>

#include <gl/gl.h>            // standard OpenGL include
#include <gl/glu.h>           // OpenGL utilties
#include <glut.h>             // OpenGL utilties

//#include "vector.h"
//#include "mymatrix.h"
#include "myQuat.h"

using namespace MyMathLab;


float rotation = 0.0;
float offsetX = 0.0;
float offsetY = 0.0;

//prototypes for our callback functions
void draw(void);    //our drawing routine
void idle(void);    //what to do when nothing is happening
void key(unsigned char k, int x, int y);  //handle key presses
void reshape(int width, int height);      //when the window is resized
void init_drawing(void);                  //drawing intialisation
void translateTest(void);
void draw_square(void);
void incrementRotation(void);
void rotateAroundVertex(void);
void taskTwoStuff(void);
void taskThreeStuff(void);
void taskThreeDotTwoDotTwo(void);
void taskThreeDotTwoDotThree(void);

//our main routine
int main(int argc, char *argv[])
{
  //Initialise Glut and create a window
  glutInit(&argc, argv);
  //sets up our display mode
  //here we've selected an RGBA display with depth testing 
  //and double buffering enabled
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
  //create a window and pass through the windows title
  glutCreateWindow("Basic Glut Application");

  //run our own drawing initialisation routine
  init_drawing();

  //tell glut the names of our callback functions point to our 
  //functions that we defined at the start of this file
  glutReshapeFunc(reshape);
  glutKeyboardFunc(key);
  glutIdleFunc(idle);
  glutDisplayFunc(draw);

  //request a window size of 600 x 600
  glutInitWindowSize(600,600);
  glutReshapeWindow(600,600);


  //go into the main loop
  //this loop won't terminate until the user exits the 
  //application
  glutMainLoop();

  return 0;
}

//draw callback function - this is called by glut whenever the 
//window needs to be redrawn
void draw(void)
{
  //clear the current window
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //make changes to the modelview matrix
  glMatrixMode(GL_MODELVIEW);
  //initialise the modelview matrix to the identity matrix
  glLoadIdentity();
  
  //***DO ALL YOUR DRAWING HERE****//
  glTranslatef(0.0, 0.0, -10.0);

  //taskTwoStuff();

  // Draw a point to see that things are set up right
  glColor3f(0.0, 1.0, 0.0);
  glPointSize(3.0);
  glPushMatrix();
	  glBegin(GL_POINTS);
		glVertex3f(0.0, 0.0, 0.0);
	  glEnd();
  glPopMatrix();

  taskThreeStuff();
  

  //flush what we've drawn to the buffer
  glFlush();
  //swap the back buffer with the front buffer
  glutSwapBuffers();
}

//idle callback function - this is called when there is nothing 
//else to do
void idle(void)
{
  //this is a good place to do animation
  //since there are no animations in this test, we can leave 
  //idle() empty
}

//key callback function - called whenever the user presses a 
//key
void key(unsigned char k, int x, int y)
{
  switch(k)
  {
    case 27: //27 is the ASCII code for the ESCAPE key
      exit(0);
      break;
	case 114: //114 is the ASCII code for the r key
		offsetX = 0;
		incrementRotation();
		break;
	case 116: //116 is the ASCII code for the t key
		rotateAroundVertex();
		incrementRotation();
		break;
  }
}

//reshape callback function - called when the window size changed
void reshape(int width, int height)
{
  //set the viewport to be the same width and height as the window
  glViewport(0,0,width, height);
  //make changes to the projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  //set up our projection type
  //we'll be using a perspective projection, with a 90 degree 
  //field of view
  gluPerspective(45.0, (float) width / (float) height, 1.0, 100.0);
  //redraw the view during resizing
  draw();
}

//set up OpenGL before we do any drawing
//this function is only called once at the start of the program
void init_drawing(void)
{
  //blend colours across the surface of the polygons
  //another mode to try is GL_FLAT which is flat shading
  glShadeModel(GL_SMOOTH);
  //turn lighting off
  glDisable(GL_LIGHTING);
  //enable OpenGL hidden surface removal
  glDepthFunc(GL_LEQUAL);
  glEnable(GL_DEPTH_TEST);
}

void translateTest(void)
{
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -6.0f);

	glBegin(GL_TRIANGLES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
	glEnd();

	glLoadIdentity();
	glRotatef(45, 0.0f, 0.0f, 1.0f);
	glTranslatef(-1.5f, 0.0f, -6.0f);

	glBegin(GL_TRIANGLES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
	glEnd();
}

void draw_square(void)
{
	glBegin(GL_POLYGON);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(-1.0f, 1.0f, 0.0f);
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(1.0f, -1.0f, 0.0f);
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(1.0f, 1.0f, 0.0f);
	glEnd();
}

void incrementRotation(void)
{
	rotation = rotation + 5;
	draw();
}

void rotateAroundVertex(void)
{
	offsetX = 1.0;
	offsetY = 1.0;
}

void taskTwoStuff(void)
{
	MyMatrix myMatrix;
	myMatrix.getGLModelviewMatrix();

	myMatrix.printMatrix();

	myMatrix.translate(0.0, 0.0, -10.0);
	//myMatrix.rotateZ(rotation);
	//myMatrix.multiplyGLMatrix();
	myMatrix.printMatrix();
	myMatrix.setGLMatrix();



	glPushMatrix();
	glTranslatef(1.0, 1.0, -5.0);
	if (offsetX == 0.0) {
		//glRotatef(rotation, 0.0f, 0.0f, 1.0f);
		myMatrix.rotateZ(rotation);
		myMatrix.setGLMatrix();
		draw_square();
	}
	else {
		glTranslatef(-offsetX, -offsetY, 0.0);
		//glRotatef(rotation, 0.0f, 0.0f, 1.0f);
		myMatrix.rotateZ(rotation);
		myMatrix.setGLMatrix();
		glTranslatef(offsetX, offsetY, 0.0);
		draw_square();
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.0, 1.0, -5.0);
	if (offsetX == 0.0) {
		//glRotatef(rotation, 0.0f, 0.0f, 1.0f);
		myMatrix.rotateZ(rotation);
		draw_square();
	}
	else {
		glTranslatef(-offsetX, -offsetY, 0.0);
		//glRotatef(rotation, 0.0f, 0.0f, 1.0f);
		myMatrix.rotateZ(rotation);
		glTranslatef(offsetX, offsetY, 0.0);
		draw_square();
	}
	glPopMatrix();
}

void taskThreeStuff(void)
{
	// draw basis vector
	glLineWidth(3.0);
	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.0, 1.0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(0.0, 0.0);
	glVertex2f(1.0, 0.0);
	glEnd();
	glPopMatrix();


	// 3.2.2
	taskThreeDotTwoDotTwo();

	// 3.2.3
	//taskThreeDotTwoDotThree();
	
}

void taskThreeDotTwoDotTwo()
{
	float rads = DEG2RAD(45);
	Position p1;

	p1.x = 1.0, p1.y = 1.0, p1.z = 0.0;
	MyQuat qvec(p1);
	MyQuat q1(rads, Vector(0.0, 0.0, 1.0));

	MyQuat q1Conj = q1.getConjugate();
	MyQuat qrA = qvec.multiplyBy(q1Conj);
	MyQuat qr = q1.multiplyBy(qrA);



	// TASK 3.2.2 draw initial point and rotated point
	glColor3f(1.0, 1.0, 0.0);
	glPointSize(3.0);
	glPushMatrix();
	glBegin(GL_POINTS);
	glVertex3f(p1.x, p1.y, p1.z);
	glVertex3f(qr.v.x, qr.v.y, qr.v.z);
	glEnd();
	glPopMatrix();
}

void taskThreeDotTwoDotThree()
{
	float rads = DEG2RAD(45);
	Position p2;

	p2.x = 0.0, p2.y = -10.0, p2.z = 0.0;
	MyQuat qvec2(p2);
	MyQuat q2(rads, Vector(10.0, 0.0, 0.0));

	MyQuat q2Conj = q2.getConjugate();
	MyQuat qrB = qvec2.multiplyBy(q2Conj);
	MyQuat qr2 = q2.multiplyBy(qrB);

	// TASK 3.2.3 draw initial point and rotated point
	glColor3f(1.0, 1.0, 0.0);
	glPointSize(3.0);
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -30.0f);
	glBegin(GL_POINTS);
	glVertex3f(p2.x, p2.y, p2.z); // origin
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(qr2.v.x, qr2.v.y, qr2.v.z);
	glEnd();
	glPopMatrix();
}