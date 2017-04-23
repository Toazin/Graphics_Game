#ifndef WORK_SPACE_H
#define WORK_SPACE_H

#include "object_gl.h"
#include <list>
#include <string>

class WorkSpace 
{
public:
	WorkSpace();
	~WorkSpace();
	enum Planet {
		SUN = 0,
		MERCURY = 1,
		MARS = 2,
		EARTH = 3,
		VENUS = 4,
		JUPITER = 5,
		SATURN = 6,
		URANUS = 7,
		NEPTUNE = 8,
		PLUTON = 9
	};
	std::list<ObjectGL *> getAll();
	void addFigure(int type, float x, float y);
	ObjectGL * getSelected();
	void setSelected(int index);
	int getIndex();
	int getType();
	void deleteItem();
	void generatePlanets(int n, int m);
	void flip();
	int getClosed();
};

#endif
