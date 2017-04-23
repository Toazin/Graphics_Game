#ifndef PLANET_H
#define PLANET_H

#include "object_gl.h"
#include "image_loader.h"
#include "box.h"

class PlanetGL : public ObjectGL {
public:
	enum Planet {	SUN = 0, 
					MERCURY = 1, 
					MARS = 2, 
					EARTH = 3, 
					VENUS = 4, 
					JUPITER = 5, 
					SATURN = 6, 
					URANUS = 7, 
					NEPTUNE = 8, 
					PLUTON = 9};
	PlanetGL(int p);
	~PlanetGL();
	void setQuad(GLUquadric *quad);
	void render();
private:
	ObjectGL * box;
	GLfloat radius, slices, stacks;
	GLUquadric *quad;
	Image *image;
	GLuint textureId;
	void renderbmp();
	const char* bmpName;
	void getType(int p);
	void init(int p);
};

#endif 
