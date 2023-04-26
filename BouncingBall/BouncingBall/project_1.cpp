#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/glut.h>
#define _USE_MATH_DEFINES
#include <compgraphmath2020.h>
#include <math.h>



using namespace std;
GLsizei winWidth = 700, winHeight = 700; //creating the window in given properties
GLint line;
GLint framems = 10; //frame rate
GLint Xin = 3;// Speed up on X axis
GLint Yin = 1;// speed up on Y axis
GLdouble d = 50; //diameter of circle
vec2 o = { float(cos(20.0 * M_PI / 180.0) * 100.0), float(sin(30.0 * M_PI / 180.0) * 100.0) };//ball direction semi diagonal path
//else this path can be spesified as such 
char window_title[] = "Ball-e"; // Window title




int end1;
float middle = 350; //mid point



void init()
{
	glClearColor(1.0, 1.0, 0.0, 0.0); //color of the backgorund
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
	glMatrixMode(GL_PROJECTION);
	glShadeModel(GL_FLAT);
	glLoadIdentity();

}



//Creating the circle
void circle(vec2 o, GLdouble d) {

	glBegin(GL_POLYGON); // Starting the Polygon
	for (GLdouble t = 0; t < 2 * pi(); t += 0.01)
		glVertex2d(o.x + d * cos(t), o.y + d * sin(t)); //Making a single Vertex for each point in the Polygon
	glEnd();

}




void display()
{

	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_LINES); //Creating the Line
	glColor3f(1.0, 0.0, 0.0); // Line color
	glVertex2i(263, middle);// we wait 263 px to start the line
	glVertex2i(438, middle);//we end the line at 438px so that it's 175px in total
	//glutPostRedisplay(); // I removed this function to make the animation smoother, but it can be added again if required
	glutSwapBuffers();
	glEnd();


	//making a condition to change the color of the ball from the moment it touches the line ot the moment it stops touching it 
	//basically below formula applys idea from the diameter
	if ((o.x > 263 - 50 && o.x < 438 + 50) && (o.y < middle + 50 && o.y > middle - 50)) {
		glColor3f(0.8, 0.0, 0.0);//color chance of the ball applied in case of touching the line
	}
	else {
		glColor3f(0.6, 0.7, 0.0);//color of the ball as described in discription
	}

	circle(o, d); //making the circle with the starting coordinates o and diameter d
	glFlush();

}


//Moving the line
void specialkey(int key, int x, int y) {
	//if we click up then we cehck if there is space to move the line upwards, if yes, we change the value of middle with a +4 inc
	if (key == 101 && middle <= 695) {
		middle = middle + 4; //move by
		glutPostRedisplay();
	}
	else if (key == 103 && middle >= 5) {
		middle = middle - 4;//if we click down we decrement middle by 4
		glutPostRedisplay();
	}
	//this section speeds up or slows down the ball
	//else if (key == 100 && framems <= 15) {
	//	framems = framems + 1;
	//	glutPostRedisplay();
	//}
	//else if (key == 102 && framems >= 1) {
		//framems = framems - 1;
		//glutPostRedisplay();
	//}
}



void update(int n)
{
	o.x += Xin;//update X cordinates
	o.y += Yin;//update Y cordinate
	if (o.x + d > 700 || o.x - d < 0) { // if we get to the edges of the window, we will change the incremint to become negative and move to the other direction 700 and 0 is the points on window borders
		Xin *= -1;

	}
	if (o.y + d > 700 || o.y - d < 0) {//same thing for y axis
		Yin *= -1;

	}

	glutPostRedisplay();
	glutTimerFunc(framems, update, 4);//call the update function after 6ms and with 4ms wait
	//line = (1) * o.y;
}



int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(400, 20);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow(window_title);
	init();
	glutDisplayFunc(display);
	glutTimerFunc(framems, update, 4);
	glutSpecialFunc(specialkey);
	glutMainLoop();

	return 0;
}