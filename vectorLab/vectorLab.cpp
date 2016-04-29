#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(linker, "/subsystem:console")

#include "windows.h"
#include "vector.h"
#include "glut.h"             // OpenGL utilties


using namespace MyOGLProg;

#include "stdlib.h"
#include <iostream>

//prototypes for our callback functions
void DisplayScene(void);    //our drawing routine
void idle(void);    //what to do when nothing is happening
void key(unsigned char k, int x, int y);  //handle key presses
void reshape(int width, int height);      //when the window is resized
void init_drawing(void);                  //drawing intialisation
void answerOne(void);
void answerTwo(void);
void answerThree(void);
void answerFour(void);
void answerFive(void);
void answerSix(void);
void answerSeven(void);
int displayAnswer = 1;

void DrawVector(Position& startPos, Vector& v1)
{
	//draw the vector v1 starting from position startPos
	//this function will only work as long as the z coordinate for both positions is zero
	float length = sqrt((v1.x * v1.x) + (v1.y * v1.y) + (v1.z * v1.z));
	Vector v;
	if (length > 0.0){ v.x = v1.x/length; v.y = v1.y/length; v.z = v1.z/length; }
	else return;
	float d = (v.x * 0.0) + (v.y * 1.0) + (v.z * 0.0);
	float a = RAD2DEG(acos(d));
	if (v.x > 0.0) a = -a;

	glPushMatrix();
	glTranslatef(startPos.x, startPos.y, startPos.z);
	glRotatef(a,0.0,0.0,1.0);
	float space = 0.25;
	glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, length, 0.0);

		glVertex3f(0.0, length, 0.0);
		glVertex3f(-space, length - (space * 1.5), 0.0);

		glVertex3f(0.0, length, 0.0);
		glVertex3f(space, length - (space * 1.5), 0.0);
	glEnd();
	glPopMatrix();
}

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
  glutDisplayFunc(DisplayScene);

  //request a window size of 600 x 600
  glutInitWindowSize(600,600);
  glutReshapeWindow(600,600);

  //go into the main loop
  //this loop won't terminate until the user exits the 
  //application
  glutMainLoop();

  return 0;
}



/*****************************************************************************
 DisplayScene()

 The work of the application is done here. This is called by glut whenever the 
//window needs to be redrawn
*****************************************************************************/

void DisplayScene(void)
{
  //clear the current window
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //make changes to the modelview matrix
  glMatrixMode(GL_MODELVIEW);
  //initialise the modelview matrix to the identity matrix
  glLoadIdentity();

  glTranslatef(-3.0,-3.0,-10.0);
  
  /*glColor3f(1.0,0.0,0.0);
  glBegin(GL_POINTS);
	glVertex3f(0.0,0.0,-5.0);
  glEnd();*/

  GLfloat yellow[4] = { 1.0f, 1.0f, 0.2f, 1.0f };
  GLfloat blue[4] = { 0.2f, 0.2f, 1.0f, 1.0f };
  GLfloat green[4] = { 0.2f, 1.0f, 0.2f, 1.0f };
Position origin;
origin.x = origin.y = origin.z = 0.0;

  //define a position and a vector
  Position p1;
  p1.x = 1.0; p1.y = 1.0; p1.z = 0.0;
  Vector v1(4.0, 4.0, 0.0);

  ////draw the vector at position
  //glDisable(GL_LINE_STIPPLE);
  //glLineWidth(1.0);
  //glColor3f(1.0,1.0,0.0);
  //DrawVector(p1,v1);

  //draw a red horizontal line, one unit long
  glLineWidth(3.0);
  glColor3f(1.0,0.0,0.0);
  glPushMatrix();
	  glTranslatef(0.0, 0.0, 0.0);
	  glBegin(GL_LINES);
		glVertex2f(0.0,0.0);
		glVertex2f(1.0,0.0);
	  glEnd();
  glPopMatrix();

  //draw a green vertical line, one unit high
  glLineWidth(3.0);
  glColor3f(0.0,0.0,1.0);
  glPushMatrix();
	  glBegin(GL_LINES);
		glVertex2f(0.0,0.0);
		glVertex2f(0.0,1.0);
	  glEnd();
  glPopMatrix();

  //draw a white point at the origin
  glPointSize(2.0);
  glColor3f(1.0,1.0,1.0);
  glPushMatrix();
	  glTranslatef(0.0, 0.0, 0.0);
	  glBegin(GL_POINTS);
		glVertex2f(0.0,0.0);
	  glEnd();
	glPopMatrix();

	switch (displayAnswer)
	{
	case 1: //27 is the ASCII code for the ESCAPE key
		answerOne();
		break;
	case 2: //27 is the ASCII code for the ESCAPE key
		answerTwo();
		break;
	case 3: //27 is the ASCII code for the ESCAPE key
		answerThree();
		break;
	case 4: //27 is the ASCII code for the ESCAPE key
		answerFour();
		break;
	case 5: //27 is the ASCII code for the ESCAPE key
		answerFive();
		break;
	case 6: //27 is the ASCII code for the ESCAPE key
		answerSix();
		break;
	case 7: //27 is the ASCII code for the ESCAPE key
		answerSeven();
		break;
	}

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
		case 49: //27 is the ASCII code for the ESCAPE key
			displayAnswer = 1;
			break;
		case 50: //27 is the ASCII code for the ESCAPE key
			displayAnswer = 2;
			break;
		case 51: //27 is the ASCII code for the ESCAPE key
			displayAnswer = 3;
			break;
		case 52: //27 is the ASCII code for the ESCAPE key
			displayAnswer = 4;
			break;
		case 53: //27 is the ASCII code for the ESCAPE key
			displayAnswer = 5;
			break;
		case 54: //27 is the ASCII code for the ESCAPE key
			displayAnswer = 6;
			break;
		case 55: //27 is the ASCII code for the ESCAPE key
			displayAnswer = 7;
			break;

	}
	DisplayScene();
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
  DisplayScene();
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
  //glDepthFunc(GL_LEQUAL);
  //glEnable(GL_DEPTH_TEST);

  //glClearColor(1.0,0.0,0.0,0.0);
}

void answerOne(void) {
	//define a position and a vector
	Position p1;
	p1.x = 1.0; p1.y = 2.0; p1.z = 0.0;
	Vector v1(4.0, 2.0, 0.0);

	//draw the vector at position
	glDisable(GL_LINE_STIPPLE);
	glLineWidth(1.0);
	glColor3f(1.0, 1.0, 0.0);
	DrawVector(p1, v1);
}

void answerTwo(void) {
	//define a position and a vector
	Position p1;
	p1.x = 0.0; p1.y = 0.0; p1.z = 0.0;
	Vector v1(4.0, 2.0, 0.0);

	Vector v2(-2.0, 3.0, 0.0);
	Position p2;
	p2.x = v1.x;
	p2.y = v1.y;
	p2.z = v1.z;

	Position p3;
	p3.x = 0.0; p3.y = 0.0; p3.z = 0.0;
	Vector v3 = v1.addTo(v2);

	//draw the vectors at position
	glDisable(GL_LINE_STIPPLE);
	glLineWidth(1.0);
	glColor3f(1.0, 1.0, 0.0);
	DrawVector(p1, v1);
	glColor3f(0.0, 1.0, 1.0);
	DrawVector(p2, v2);

	glColor3f(0.0, 1.0, 0.0);
	DrawVector(p3, v3);
}

void answerThree(void) {
	//define a position and a vector
	Position p1;
	p1.x = 0.0; p1.y = 0.0; p1.z = 0.0;
	Vector v1(0.0, 1.0, 0.0);
	Vector v2(0.707, 0.707, 0.0);

	v2.normalise();
	
	float dotProd = v1.getDotProduct(v2);
	float deg = RAD2DEG(acos(dotProd));

	//draw the vectors at position
	glDisable(GL_LINE_STIPPLE);
	glLineWidth(1.0);
	glColor3f(1.0, 1.0, 0.0);
	DrawVector(p1, v1);
	DrawVector(p1, v2);
}

void answerFour(void)
{
	//define a position and a vector
	Position p1;
	p1.x = 0.0; p1.y = 0.0; p1.z = 0.0;
	Vector v1(4.0, 4.0, 0.0);
	Vector v2(-2.0, 3.0, 0.0);

	//draw the vectors at position
	glDisable(GL_LINE_STIPPLE);
	glLineWidth(1.0);
	glColor3f(1.0, 1.0, 0.0);
	DrawVector(p1, v1);
	DrawVector(p1, v2);

	float dotProd = v1.getDotProduct(v2);
	// if positive dot product, they point in the same general direction (angle between is less than pi/2)
	if (dotProd >= 0.0) {
		std::cout << "The vectors point in the same general direction\n";
	}
	else {
		std::cout << "The vectors do NOT point in the same general direction\n";
	}
}

void answerFive(void) {
	Position p0;
	p0.x = 0.0; p0.y = 0.0; p0.z = 0.0;

	Position p2;
	p2.x = 3.0; p2.y = 9.0; p2.z = 0.0;

	//draw a red line
	glLineWidth(1.0);
	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
		glTranslatef(0.0, 0.0, 0.0);
		glBegin(GL_LINES);
			glVertex3f(p0.x, p0.y, p0.z);
			glVertex3f(3.0, 9.0, 0.0);
		glEnd();
	glPopMatrix();

	//draw a white point
	Position p1;
	p1.x = 5.0; p1.y = 4.0; p1.z = 0.0;

	glPointSize(5.0);
	glColor3f(0.0, 1.0, 0.0);
	glPushMatrix();
		glTranslatef(0.0, 0.0, 0.0);
		glBegin(GL_POINTS);
			glVertex3f(p1.x, p1.y, p1.z);
		glEnd();
	glPopMatrix();

	// calculate projection
	Vector p0p1(p0.x + p1.x, p0.y + p1.y, p0.z + p1.z);
	Vector p0p2(p0.x + p2.x, p0.y + p2.y, p0.z + p2.z);

	float dotProd = p0p1.getDotProduct(p0p2);
	float len = p0p2.getMagnitude();
	float scalarProj = dotProd / len;
	Vector normp0p2 = p0p2;
	normp0p2.normalise();
	normp0p2.setMagnitude(scalarProj);

	// make a point
	Position projPoint;
	projPoint.x = normp0p2.x; projPoint.y = normp0p2.y; projPoint.z = normp0p2.z;

	//draw the vectors at position
	glDisable(GL_LINE_STIPPLE);
	glLineWidth(1.0);
	glColor3f(0.0, 1.0, 0.0);
	DrawVector(p0, p0p1);
	glColor3f(1.0, 0.0, 0.0);
	DrawVector(p0, p0p2);
	//glColor3f(1.0, 1.0, 0.0);
	//DrawVector(p0, normp0p2);

	// draw the projection point
	glPointSize(8.0);
	glColor3f(0.0, 1.0, 0.0);
	glPushMatrix();
		glTranslatef(0.0, 0.0, 0.0);
		glBegin(GL_POINTS);
			glVertex3f(projPoint.x, projPoint.y, projPoint.z);
		glEnd();
	glPopMatrix();
	
}

void answerSix(void) {
	//define a position and a vector
	Position p1;
	p1.x = 1.0; p1.y = 8.0; p1.z = 0.0;
	Position p2;
	p2.x = 5.0; p2.y = 4.0; p2.z = 0.0;

	Position p3;
	p3.x = 3.0; p3.y = 0.0; p3.z = 0.0;
	Position p4;
	p4.x = -6.0; p4.y = 0.0; p4.z = 0.0;

	//draw a red line
	glLineWidth(1.0);
	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
		glTranslatef(0.0, 0.0, 0.0);
		glBegin(GL_LINES);
			glVertex3f(p1.x, p1.y, p1.z);
			glVertex3f(p2.x, p2.y, p2.z);
		glEnd();
	glPopMatrix();

	//draw a red line
	glLineWidth(1.0);
	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
		glTranslatef(0.0, 0.0, 0.0);
		glBegin(GL_LINES);
			glVertex3f(p3.x, p3.y, p3.z);
			glVertex3f(p4.x, p4.y, p4.z);
		glEnd();
	glPopMatrix();

	Vector v1(p1.x, p1.y, p1.z);
	Vector v2(p2.x, p2.y, p2.z);
	Vector v3(p3.x, p3.y, p3.z);
	Vector v4(p4.x, p4.y, p4.z);

	Vector firstVector = v2.subtractFrom(v1);
	Vector secondVector = v4.subtractFrom(v3);

	firstVector.normalise();
	secondVector.normalise();

	float dotProd = firstVector.getDotProduct(secondVector);
	float deg = RAD2DEG(acos(dotProd));

	std::cout << deg << " degrees\n";

	//draw the vectors at position
	glDisable(GL_LINE_STIPPLE);
	glLineWidth(1.0);
	glColor3f(1.0, 1.0, 0.0);
	DrawVector(p1, v1);
	DrawVector(p1, v2);
}


void answerSeven(void) {
	//define a position and a vector
	Position p0;
	p0.x = -2.5; p0.y = -2.0; p0.z = 0.0;
	Position p1;
	p1.x = 5.0; p1.y = -2.0; p1.z = 0.0;
	Position p2;
	p2.x = 8.0; p2.y = 3.0; p2.z = 0.0;

	// calculate projection
	Vector p0p1(p1.x - p0.x, p1.y - p0.y, p1.z - p0.z);
	Vector p0p2(p2.x - p0.x, p2.y - p0.y, p2.z - p0.z);

	float dotProd = p0p1.getDotProduct(p0p2);
	float len = p0p1.getMagnitude();
	float scalarProj = dotProd / len;
	Vector normp0p1 = p0p1;
	normp0p1.normalise();
	normp0p1.setMagnitude(scalarProj);

	// make a point
	Position projPoint;
	projPoint.x = normp0p1.x + p0.x; projPoint.y = normp0p1.y + p0.y; projPoint.z = normp0p1.z + p0.z;

	// check if point exceeds limits of the line
	if (projPoint.x < p0.x) {
		projPoint.x = p0.x;
	}
	else if (projPoint.x > p1.x) {
		projPoint.x = p1.x;
	}

	if (projPoint.y < p0.y) {
		projPoint.y = p0.y;
	}
	else if (projPoint.y > p1.y) {
		projPoint.y = p1.y;
	}

	if (projPoint.z < p0.z) {
		projPoint.z = p0.z;
	}
	else if (projPoint.z > p1.z) {
		projPoint.z = p1.z;
	}
	
	//draw a red line
	glLineWidth(1.0);
	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
		glTranslatef(1.0, 4.0, 0.0);
		glBegin(GL_LINES);
			glVertex3f(p0.x, p0.y, p0.z);
			glVertex3f(p1.x, p1.y, p1.z);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f(p0.x, p0.y, p0.z);
			glColor3f(1.0, 1.0, 0.0); // super sweet color interpolation
			glVertex3f(p2.x, p2.y, p2.z);
		glEnd();
	glPopMatrix();

	//draw point
	glPointSize(5.0);
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
		glTranslatef(3.0, 4.0, 0.0);
		glBegin(GL_POINTS);
			glVertex3f(p2.x, p2.y, p2.z);
		glEnd();
	glPopMatrix();

	//draw projected point
	glPointSize(5.0);
	glPushMatrix();
		glTranslatef(3.0, 4.0, 0.0);
		glBegin(GL_POINTS);
			glColor3f(0.0, 1.0, 0.0);
			glVertex3f(projPoint.x, projPoint.y, projPoint.z);
		glEnd();
	glPopMatrix();
}