#include "object_gl.h"

ObjectGL::ObjectGL()
{
	this->color[0] = 1.f;
	this->color[1] = 1.f;
	this->color[2] = 1.f;
	this->color[3] = 1.f;
	this->style = GL_LINE;
	this->closed = 1;
	this->matched = 0;
	this->limit = 20;
	this->timer = this->limit + 1;

}

void ObjectGL::setColor(GLfloat r, GLfloat g, GLfloat b) {
	this->color[0] = r;
	this->color[1] = g;
	this->color[2] = b;

}

void ObjectGL::setStyle(int style) {
	this->style = style;
}

void ObjectGL::scale(GLfloat sx, GLfloat sy, GLfloat sz) {
	this->m = glm::scale(this->m, glm::vec3(sx, sy, sz));
}

void ObjectGL::traslate(GLfloat tx, GLfloat ty, GLfloat tz) {
	this->m = glm::translate(this->m, glm::vec3(tx, ty, tz));
}

void ObjectGL::rotate(GLfloat angle, GLfloat ux, GLfloat uy, GLfloat uz) {
	this->m = glm::rotate(this->m, glm::radians(angle), glm::vec3(ux, uy, uz));
}

int ObjectGL::getType() {
	return this->type;
}

void ObjectGL::setType(int type) {
	this->type = type;
}

void ObjectGL::flip()
{
	if (this->matched == 1) return;
	if (this->closed == 1)
	{
		this->closed = 0;
	}
	else
	{
		this->closed = 1;
	}
}

int ObjectGL::getClosed()
{
	return this->closed;
}

void ObjectGL::setMatched(int match)
{
	this->matched = match;
}

int ObjectGL::getMatched()
{
	return this->matched;
}

void ObjectGL::initTimmer()
{
	this->timer = 0;
}