#ifndef BOX_GL_H
#define BOX_GL_H

#include "polygon_gl.h"

class BoxGL : public PolygonGL
{
private:
	PolygonGL *c1, *c2, *c3, *c4, *c5, *c6;
public:
	BoxGL();
	~BoxGL();
	void render();
};

#endif
