// transf_instance_main.cpp
// Transformación de Instancias

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string>
#include <iostream>
#include <list>
#include <cmath>

#include "workspace.h"

using namespace std;

// Geometries

list<ObjectGL *> scene;

//Rotaciones 

GLfloat deltaR = .01f;
GLfloat rot = 1.f;

GLfloat x = 0.f;
GLfloat z = 0.f;

// Tamaño de la ventana
GLint width = 800;
GLint height = 800;

// Parámetros de la cámara virtual
GLint mouseButton = 0;
GLboolean mouseRotate = false;
GLboolean mouseZoom = false;
GLboolean mousePan = false;
GLint xClick = 0;
GLint yClick = 0;
GLint xAux = 0;
GLint yAux = 0;
GLfloat rotX = 0.f;
GLfloat rotY = 312;
GLfloat panX = 0.f;
GLfloat panY = 0.f;
GLfloat zoomZ = -40.f;

//Camera
float eyeX = 0;
float eyeY = 50;//-50
float eyeZ = -20;
float centerX = 0;
float centerY = 0;
float centerZ = 0;
float upX = 0;
float upY = -10;
float upZ = 0;

//Workspace
WorkSpace *myWork;

//Scene
list<ObjectGL *> objectList;

//List Management
int index = 0;
ObjectGL * selectedItem;


//Displayed text----
int leftSelectType = 0;
int rightSelectType = 0;
int middleSelectType = 0;
int win = 0;

int positionFigure = 0;

//Actual Text Description
string esText = "";
string euText = "";

//Menu
static int window;
static int menu_id;
static int submenu_id;
static int value = 0;
float rightX = 0;
float rightY = 0;

// Función que inicializa el Contexto OpenGL y la geometría de la escena
void init()
{
	glClearColor(0.f, 0.f, 0.f, 0.f);
	glColor3f(1.f, 1.f, 1.f);
	myWork->restart();
}

// Función que se invoca cada vez que se redimensiona la ventana
void resize(GLint w, GLint h)
{
	if (h == 0)
	{
		h = 1;
	}
	width = w;
	height = h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.f, (float)width / height, 0.1f, 1000.f);		// Transf. de Proyección en Perspectiva
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, width, height);								// Transf. de Viewport (mapeo al área de dibujo)
}

// Geometría sistema coordenado
void geomCoordSys(GLfloat size)
{
	float currentColor[4];
	glGetFloatv(GL_CURRENT_COLOR, currentColor);

	// Eje X (Rojo)
	glColor3f(1., 0., 0.);
	glBegin(GL_LINES);
	glVertex3f(0., 0., 0.);
	glVertex3f(size, 0., 0.);
	glEnd();

	// Eje Y (Verde))
	glColor3f(0., 1., 0.);
	glBegin(GL_LINES);
	glVertex3f(0., 0., 0.);
	glVertex3f(0., size, 0.);
	glEnd();

	// Eje Z (Azul)
	glColor3f(0., 0., 1.);
	glBegin(GL_LINES);
	glVertex3f(0., 0., 0.);
	glVertex3f(0., 0., size);
	glEnd();

	glColor3f(currentColor[0], currentColor[1], currentColor[2]);
}

void getTypeDescription(int type)
{
	switch (type)
	{
	case 0:
		esText = "Sol";
		euText = "Sun";
		break;
	case 1:
		esText = "Mercurio";
		euText = "Mercury";
		break;
	case 2:
		esText = "Marte";
		euText = "Mars";
		break;
	case 3:
		esText = "Tierra";
		euText = "Earth";
		break;
	case 4:
		esText = "Venus";
		euText = "Venus";
		break;
	case 5:
		esText = "Jupiter";
		euText = "Jupiter";
		break;
	case 6:
		esText = "Saturno";
		euText = "Saturn";
		break;
	case 7:
		esText = "Urano";
		euText = "Uranus";
		break;
	case 8:
		esText = "Neptuno";
		euText = "Neptun";
		break;
	case 9:
		esText = "Pluton";
		euText = "Pluto";
		break;
	case 10:
		esText = "Luna";
		euText = "Moon";
		break;
	}
}

void displayText(string s, GLdouble x, GLdouble y, void * font)
{
	glDisable(GL_TEXTURE_2D); 
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, width, 0.0, height);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x, y);//GLUT_BITMAP_TIMES_ROMAN_24
	//void * font = GLUT_BITMAP_HELVETICA_18;
	for (string::iterator i = s.begin(); i != s.end(); ++i)
	{
		char c = *i;
		glColor3d(1.0, 0.0, 0.0);
		glutBitmapCharacter(font, c);
	}
	glMatrixMode(GL_MODELVIEW); 
	glPopMatrix();
	glMatrixMode(GL_PROJECTION); 
	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
	glutPostRedisplay();
}

void obtainTexts()
{
	int left = myWork->getPair(0);
	int right = myWork->getPair(1);
	//First Selection
	if (left == 1)
	{
		leftSelectType = myWork->getPairType(0);
		getTypeDescription(leftSelectType);
		string s = "Este Planeta es: " + esText;
		displayText(s, width*.1, height*.1, GLUT_BITMAP_HELVETICA_18);
	}
	//Second Selection
	if (right == 1)
	{
		rightSelectType = myWork->getPairType(1);
		getTypeDescription(rightSelectType);
		string s = "This Planet is: " + euText;
		displayText(s, width*.8, height*.1, GLUT_BITMAP_HELVETICA_18);
	}
	//Actual selection
	if(selectedItem != NULL && selectedItem->ObjectGL::getClosed() == 0)
	{
		middleSelectType = myWork->getType();
		getTypeDescription(middleSelectType);
		string s = "Encontraste a : " + esText; 
		displayText(s, (width / 2) - (width * .05), height*.1, GLUT_BITMAP_HELVETICA_18);
	}

	//Score
	if (win == 1)
	{
		int cant = myWork->getIntentos();
		string sCant = to_string(cant);
		string s = "Has ganado en " + sCant + " intentos, da click derecho para reiniciar";
		displayText(s, (width / 2) - (width * .15), height / 2, GLUT_BITMAP_TIMES_ROMAN_24);
	}
	glutPostRedisplay();
}

void colorSelectedItem()
{
	if (selectedItem != NULL) {
		selectedItem->setColor(0.f, 0.f, 1.f);
	}
}

// Función que se invoca cada vez que se dibuja
void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//Se limpian los buffers con el color activo definido por glClearColor

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, -1, upZ);
	// Transformación de vista
	//glTranslatef(panX, panY, zoomZ);
	glRotatef(rotY, 1.0, 0.0, 0.0);
	glRotatef(rotX, 0.0, 1.0, 0.0);

	// Escena
	geomCoordSys(2.f);
	glPushMatrix();
	objectList = myWork->getAll();

	for (list<ObjectGL *>::iterator it = objectList.begin(); it != objectList.end(); it++)
	{
		//cout << "Render de: " << (*it) << endl;
		(*it)->render();
	}

	obtainTexts();
	selectedItem = myWork->getSelected();

	colorSelectedItem();
	glPopMatrix();

	glutSwapBuffers();			// Se intercambian buffers
}

void keyboardFunction(unsigned char key, int x, int y)
{
	if (key == 32) { //Barra Espaciadora
		cout << "Espacio perras" << endl;
		myWork->manageSelection();
		if (myWork->getScore() == 10) {
			win = 1;
		}
		//myWork->flip();
	}
	cout << key << " key press " << "x = " << x << " y = " << y << endl;
	
	if (selectedItem != NULL) {
		if (key == 'w') {
			selectedItem->traslate(0.f, .2f, 0.f);
			return;
		}
		else	if (key == 's') {
			selectedItem->traslate(0.f, -.2f, 0.f);
			return;
		}
		else	if (key == 'a') {
			selectedItem->traslate(-0.2f, 0.f, 0.f);

			return;
		}
		else	if (key == 'd') {
			selectedItem->traslate(0.2f, 0.f, 0.f);
			return;
		}
		else	if (key == 'q') {
			selectedItem->traslate(0.f, 0.f, 0.2f);
			return;
		}
		else	if (key == 'e') {
			selectedItem->traslate(0.f, 0.f, -0.2f);
			return;
		}
	}

	if (selectedItem != NULL) {
		if (key == 'o') {
			selectedItem->rotate(5, 1.f, 0.f, 0.f);
			return;
		}else if (key == 'l') {
			selectedItem->rotate(5, 0.f, 1.f, 0.f);
			return;
		}
		else if (key == 'i') {
			selectedItem->rotate(-5, 1.f, 0.f, 0.f);
			return;
		}
		else if (key == 'k') {
			selectedItem->rotate(-5, 0.f, 1.f, 0.f);
			return;
		}
	}

	if (selectedItem != NULL) {
		if (key == 'r') {
			myWork->deleteItem();
			return;
		}
	}

	if (selectedItem != NULL) {
		int ty = selectedItem->getType();
		cout << "Type: " << ty << endl;
		GLint deltaS = .2f;
		GLint sx = 1.f;
		GLint sy = 1.f;
		GLint sz = 1.f;
		if (key == 't') {
			selectedItem->scale(1.2f, 1.f, 1.f);
			return;
		}else if (key == 'y') {
			selectedItem->scale(.8f, 1.f, 1.f);
			return;
		}else if (key == 'g') {
			selectedItem->scale(1.f, 1.2f, 1.f);
			return;
		}else if (key == 'h') {
			selectedItem->scale(1.f, .8f, 1.f);
			return;
		}else if (key == 'b') {
			selectedItem->scale(1.f, 1.f, 1.2f);
			return;
		}else if (key == 'n') {
			selectedItem->scale(1.f, 1.f, .8f);
			return;
		}
	}

	if (key == 'c') {
		selectedItem->scale(1.f,2.f,1.f);
	}

	if (selectedItem != NULL) {
		if (key == 'x') {
			selectedItem->setStyle(GL_LINE);
			return;
		}
		else if (key == 'z') {
			selectedItem->setStyle(GL_FILL);
			return;
		}
	}
}

void specialKeyboard(int key, int x, int y) {
	cout << key << " Specialkey press " << "x = " << x << " y = " << y << endl;
	if (key == 100) {
		cout << "index: " << index << endl;
		if (objectList.size() > 0) {
			index = index + 1;
			myWork->fix();
			myWork->setSelected(index);
		}
		return;
	}
	if (key == 102) {
		cout << "index: " << index << endl;
		if (objectList.size() > 0) {
			index = index - 1;
			//myWork->manageClose();
			myWork->fix();
			myWork->setSelected(index);
		}
		return;
	}
}

void mouse(int button, int state, int x, int y)
{
	mouseButton = button;
	mouseRotate = false;
	mouseZoom = false;
	mousePan = false;
	xClick = x;
	yClick = y;
	if (button == GLUT_LEFT_BUTTON)
	{
		mouseRotate = true;
		xAux = rotX;
		yAux = rotY;
	}
	else if (button == GLUT_RIGHT_BUTTON)
	{
		//mouseZoom = true;
		//xAux = zoomZ;
	}
	else if (button == GLUT_MIDDLE_BUTTON)
	{
		mousePan = true;
		xAux = panX;
		yAux = panY;
	}
	//cout << "x: " << x << " y: " << y << endl;
}

void mouseMotion(int x, int y)
{
	if (mouseRotate == true)
	{
		if (mouseButton == GLUT_LEFT_BUTTON)
		{
			if ((x - xClick + xAux) > 360.0)
			{
				xAux = xAux - 360.0;
			}
			if ((x - xClick + xAux) < 0.0)
			{
				xAux = xAux + 360.0;
			}
			if ((y - yClick + yAux) > 360.0)
			{
				yAux = yAux - 360.0;
			}
			if ((y - yClick + yAux) < 0.0)
			{
				yAux = yAux + 360.0;
			}
			rotX = x - xClick + xAux;
			rotY = y - yClick + yAux;
		}
	}
	else if (mouseZoom == true)
	{
		if (mouseButton == GLUT_RIGHT_BUTTON)
		{
			
			//cout << " Value  " << ((x - xClick) / 10.0) + xAux << endl;
			//zoomZ = ((x - xClick) / 10.0) + xAux;
		}
	}
	else if (mousePan == true)
	{
		if (mouseButton == GLUT_MIDDLE_BUTTON)
		{
			panX = ((x - xClick) / 63.0) + xAux;
			panY = ((y - yClick) / (-63.0)) + yAux;
		}
	}
	glutPostRedisplay();
}

void mouseWheel(int button, int dir, int x, int y)
{
	if (dir > 0)
	{
		// Zoom in
		zoomZ = zoomZ + .3;
	}
	else
	{
		// Zoom out
		zoomZ = zoomZ - .3;
	}
	glutPostRedisplay();
	return;
}

//MENU
void menu(int num) {
	//cout << " Menu Press:  " << num << endl;
	float mouseX = (-(rightX - (width / 2)) / (1350 / zoomZ));
	float mouseY = ((rightY - (height / 2)) / (1350 / zoomZ));
	switch (num)
	{
	case 0:
		glutDestroyWindow(window);
		exit(0);
		break;
	case 1:
		//Restart
		cout << "Restart Press..." << endl;
		myWork->restart();
		win = 0;
		//myWork->deleteItem();
		break;
	default:
		cout << "Coordx: " << rightX << "Coordy: " << rightY << endl;
		cout << "Width: " << width << "Height: " << height << endl;
		float xa = (-(rightX - (width / 2)) / (1350 / zoomZ));
		float ya = ((rightY - (height / 2)) / (1350 / zoomZ));

		cout << "Posx: " << mouseX << "Posy: " << mouseY << endl;
		//	myWork->addFigure(num, 0, 0);
		myWork->addFigure(num, mouseX, mouseY);
		
		break;
	}
	glutPostRedisplay();
}

void status(int status, int x, int y) {
	cout << "status: " << status << " x: " << x << " y: " << y << endl;
	if (status == 1) {
		rightX = x;
		rightY = y;
	}
	
}

void createMenu(void) {
	menu_id = glutCreateMenu(menu);
	glutAddMenuEntry("Restart", 1);
	glutAddMenuEntry("Salir", 0);     
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMenuStatusFunc(status);
}

int main(GLint argc, GLchar **argv)
{
	// 1. Se crea una ventana y un contexto OpenGL usando GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow("3d Aplication - GLUT/OPENGL - 2nd Partial");

	// 1.2 Se definen las funciones callback para el manejo de eventos
	glutReshapeFunc(resize);
	glutDisplayFunc(render);
	//glutMouseFunc(mouse);
	//glutMotionFunc(mouseMotion);
	glutKeyboardFunc(keyboardFunction);
	glutSpecialFunc(specialKeyboard);
	glutMouseWheelFunc(mouseWheel);
	// 2. Se direcciona a las funciones correctas del API de OpenGL
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "GLEW Error");
		return false;
	}
	//Menu
	createMenu();

	// 3. Se inicializa el contexto de OpenGL y la geometría de la escena
	init();
	

	// 4. Se inicia el ciclo de escucha de eventos
	glutMainLoop();
	
	return 0;
}