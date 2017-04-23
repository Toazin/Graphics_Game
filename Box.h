#ifndef BOX_H
#define BOX_H

#include "object_gl.h"

class BoxGLU : public ObjectGL {
private:
	GLfloat size;
public:
	BoxGLU();
	~BoxGLU();
	void render();
};

#endif 
