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
#include <vector>

std::list<ObjectGL *> workScene;
ObjectGL * itemSelected;
int indexSelected = 0;
GLUquadric *quadPlanets[9];
GLUquadric *quad;
ObjectGL *pairList[2];
int score, intentos;

WorkSpace::WorkSpace() 
{
	std::cout << " Me cree " << std::endl;
	//generatePlanets(10, 1);
	//WorkSpace::restart();
}
WorkSpace::~WorkSpace()
{
	score = 0;
	intentos = 0;
}
std::vector<int> generateRandomArray() {
	int randomIndex, temp;
	std::vector<int> vect;
	int array[] = { 6, 4, 10, 9, 7, 9, 1, 5, 5, 8, 2, 10, 7, 1, 8, 2, 3, 4, 6, 3 };
	for (int i = 0; i<19; i++) {
		randomIndex = (rand() % (20 - i)) + i;
		std::cout << "el indice random es: " << randomIndex << std::endl;
		temp = array[randomIndex];
		array[randomIndex] = array[i];
		vect.push_back(temp);
	}
	vect.push_back(array[19]);
	for (int i = 0; i<20; i++) {
		std::cout << vect.at(i) << ", ";
	}
	std::cout << std::endl;

	return vect;
}

std::vector<float> makecoordinates(int m, int size, int distance) {
	std::vector<float> vect;
	float ywidth = size / m;
	float yCord = ywidth - (ywidth / 2) - 10;
	vect.push_back(yCord);
	for (int i = 1; i < m; i++) {

		yCord += ywidth;
		vect.push_back(yCord);
	}
	return vect;
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
	workScene.clear();
	int counter = 0;
	std::vector<int> vect = generateRandomArray();
	std::vector<float> xcords = makecoordinates(n, 20, 0);
	std::vector<float> zcords = makecoordinates(m, 23, 0);

	for (int i = 0; i < 20; i++) {
		Planet t = static_cast<Planet>(vect.at(i));
		//int t = static_cast <float> (rand() % 9);
		std::cout << " RANDOM: " << t << std::endl;
		tmp = new PlanetGL(t);
		x = xcords.at(i%n);
		z = zcords.at(i / n);
		tmp->traslate(x, y, z);
		workScene.push_back(tmp);
		std::cout << " x: " << x << " z: " << z << std::endl;

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
		generatePlanets(5, 4);
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



void WorkSpace::manageSelection()
{
	if (itemSelected->ObjectGL::getMatched() == 1) return;
	//Esta en lista actual
	if (WorkSpace::inPair(itemSelected))
	{
		return;
	}
	//Esta llena la lista --> Reset y set
	/*if (WorkSpace::isFull())
	{
		WorkSpace::resetSelection();
		WorkSpace::addToList(itemSelected);
		return;
	}*/
	
	//Hay espacio --> agrega a lista
	WorkSpace::addToList(itemSelected);
	// lista 0 y 1 tienen algo--> siMatch?
	if (WorkSpace::isMatch())
	{
		score++;
		WorkSpace::setMatch();
		WorkSpace::resetSelection();
		return;
	}

	/*if (WorkSpace::isFull())
	{
		WorkSpace::resetSelection();
		return;
	}*/

}

void WorkSpace::fix()
{
	if (WorkSpace::isFull())
	{
		intentos++;
		WorkSpace::resetSelection();
		return;
	}
}

void WorkSpace::restart() {
	generatePlanets(5, 4);
}

bool WorkSpace::inPair(ObjectGL * item) {
	for (int i = 0; i < 2; i++) {
		std::cout << "Busco si exsite item: " << item << " igual a: " << pairList[i] << std::endl;
		if (pairList[i] == item) {
			std::cout << "Si existe!" << std::endl;
			pairList[i]->ObjectGL::flip();
			pairList[i] = NULL;
			return true;
		}
	}
	return false;
}

bool WorkSpace::isFull()
{
	for (int i = 0; i < 2; i++) {
		std::cout << "Busco si esta llena, item: " << pairList[i] << std::endl;
		if (pairList[i] == NULL) {
			return false;
		}
	}
	return true;
}

void WorkSpace::resetSelection()
{
	for (int i = 0; i < 2; i++) {
		std::cout << "Reseteo: " << pairList[i] << std::endl;
		if (pairList[i] != NULL)
		{
			pairList[i]->ObjectGL::flip();
			pairList[i]->ObjectGL::initTimmer();
			pairList[i] = NULL;
		}
	}
}



void WorkSpace::addToList(ObjectGL * item)
{
	if (pairList[0] == NULL)
	{
		//std::cout << "Agrego a pos 1: " << item << std::endl;
		pairList[0] = item;
	}
	else
	{
		//std::cout << "Agrego a pos 2: " << item << std::endl;
		pairList[1] = item;
	}
	for (int i = 0; i < 2; i++) {
		//std::cout << "Reviso Agregar: " << pairList[i] << std::endl;
	}
	itemSelected->ObjectGL::flip();
}

bool WorkSpace::isMatch()
{
	int pair1 = -1;
	int pair2 = -1;
	if (pairList[0] != NULL)
	{
		pair1 = pairList[0]->ObjectGL::getType();
	}
	if (pairList[1] != NULL)
	{
		pair2 = pairList[1]->ObjectGL::getType();
	}
	//std::cout << "IsMATCH: " << pair1 << " - " << pair2 << std::endl;
	return pair1 == pair2;
}


void WorkSpace::setMatch()
{
	for (int i = 0; i < 2; i++) {
		//std::cout << "Seteo MATCH: " << pairList[i] << std::endl;
		pairList[i]->ObjectGL::setMatched(1);
	}

}

int WorkSpace::getPair(int i)
{
	//std::cout << "getPair: " << i << pairList[i] << std::endl;
	if (pairList[i] != NULL) {
		//std::cout << "REGRESO 1" << std::endl;
		return 1;
	}
	return 0;
}

int WorkSpace::getPairType(int i) {
	if (pairList[i] != NULL) {
		return pairList[i]->getType();
	}
	return 0;
}

int  WorkSpace::getIntentos()
{
	return intentos;
}

int  WorkSpace::getScore() {
	return score;
}