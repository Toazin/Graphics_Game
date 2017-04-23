#include <GL\glew.h>
#include <GL\freeglut.h>
#include <cmath>

#include "workspace.h"
#include "Planet.h"
#include "image_loader.h"
#include <time.h>
#include <string>
#include <iostream>
#include <typeinfo>

std::list<ObjectGL *> workScene;
ObjectGL * itemSelected;
int indexSelected = 0;
WorkSpace w;
GLUquadric *quadPlanets[9];
GLUquadric *quad;


WorkSpace::WorkSpace() 
{
	std::cout << " Me cree " << std::endl;
	//generatePlanets(10, 1);
}
WorkSpace::~WorkSpace()
{

}
void WorkSpace::generatePlanets(int n, int m)
{
	std::cout << " GeneratePlanets " << std::endl;
	ObjectGL * tmp;
	GLfloat x = 0;
	GLfloat y = 0;
	GLfloat z = 0;
	GLfloat xoffset = 2.5;
	GLfloat zoffset = 2.5;
	srand(time(NULL));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			Planet t = static_cast<Planet>(rand() %  PLUTON);
			//int t = static_cast <float> (rand() % 9);
			std::cout << " RANDOM: " << t << std::endl;
			tmp = new PlanetGL(t);
			tmp->traslate(x, y, z);
			workScene.push_back(tmp);
			x = xoffset*j;
			std::cout << " x: " << x << " z: " << z << std::endl;
		}
		std::cout << "LIENA"<< std::endl;
		z = zoffset*i;
	}
	if (itemSelected != NULL) {
		itemSelected->setColor(1.f, 1.f, 1.f);
	}
	indexSelected = workScene.size() - 1;
	itemSelected = tmp;

	return;
}

std::list<ObjectGL *> WorkSpace::getAll() {
	return workScene;
}

void WorkSpace::addFigure(int type, float x, float y) {
	ObjectGL * tmp;
	ObjectGL * tmp2;
	switch (type)
	{
	case 2:
		std::cout << "TEST 2 " << std::endl;
		generatePlanets(3, 3);
		return;
		break;
	case 3:
		std::cout << "TEST 1 " << std::endl;
		tmp = new PlanetGL(EARTH);
		tmp->traslate(x, y, 0.f);
		workScene.push_back(tmp);
		break;
	case 4:
		std::cout << "TEST 3 " << std::endl;
		tmp = new PlanetGL(MARS);
		tmp->traslate(x, y, 0.f);
		workScene.push_back(tmp);
		return;
		break;
	}
	if (itemSelected != NULL) {
		itemSelected->setColor(1.f, 1.f, 1.f);
	}
	indexSelected = workScene.size()-1;
	itemSelected = tmp;
	return;
}

ObjectGL * WorkSpace::getSelected() {
	return itemSelected;
}
void WorkSpace::setSelected(int index) {
	if (itemSelected != NULL) {
		itemSelected->setColor(1.f, 1.f, 1.f);
	}
	//Logica para el index.
	if (index < 0) {
		index = index * -1;
	}
	if (workScene.size() > 0)
	{
		if (index >= workScene.size()) {
			std::cout << "index1: " << index << std::endl;
			index = index % workScene.size();
		}
		std::cout << "index: " << index << std::endl;
		std::list<ObjectGL *>::iterator it = workScene.begin();
		std::advance(it, index);
		ObjectGL * tmp = (*it);
		itemSelected = tmp;
		indexSelected = index;
		
	}

}

int  WorkSpace::getIndex() {
	return indexSelected;
}

int WorkSpace::getType() {
	if (itemSelected != NULL) {
		return itemSelected->getType();
	}
	return 0;
}

void WorkSpace::deleteItem()
{
	workScene.remove(itemSelected);
}

void WorkSpace::flip()
{
	std::cout << "FLIP!" << std::endl;
	itemSelected->ObjectGL::flip();
}

int WorkSpace::getClosed()
{
	std::cout << "entre" << std::endl;
	if (itemSelected != NULL) {
		return itemSelected->ObjectGL::getClosed();
	}	
	return true;

}
