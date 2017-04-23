#include "Box.h"
#include <iostream>

BoxGLU::BoxGLU() : ObjectGL() {
	this->size = 2;
	this->style == GL_FILL;
}
BoxGLU::~BoxGLU() {
}

void BoxGLU::render() {
	glPushMatrix();

	glColor3f(this->color[0], this->color[1], this->color[2]);

	GLfloat *ptrM = glm::value_ptr(this->m);
	glMultMatrixf(ptrM);
	glutSolidCube(this->size);

	glPopMatrix();
}