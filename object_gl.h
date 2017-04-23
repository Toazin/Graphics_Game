#ifndef OBJECT_GL_H
#define OBJECT_GL_H

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ObjectGL
{
public:
	glm::mat4 m; //Matriz de glm de 4 x 4
	GLfloat color[4];
	int style, type;
public:
	ObjectGL();
	void setColor(GLfloat r, GLfloat g, GLfloat b);
	void setStyle(int style);
	void scale(GLfloat sx, GLfloat sy, GLfloat sz);
	void traslate(GLfloat tx, GLfloat ty, GLfloat tz);
	void rotate(GLfloat angle,GLfloat tx, GLfloat ty, GLfloat tz);
	int getType();
	void setType(int type);
	virtual void render() = 0;
	void flip();
	int closed;
	int getClosed();
};

#endif
