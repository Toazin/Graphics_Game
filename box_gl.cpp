#include <GL\glew.h>
#include <GL\freeglut.h>
#include <cmath>

#include "box_gl.h"
#include "quad_gl.h"

BoxGL::BoxGL() : PolygonGL()
{
	this->type = 4;
	GLfloat size = 1.f;
	//Cara 1
	this->c1 = new QuadGL();
	this->c1->traslate(-size / 2, 0.f, 0.f);
	this->c1->rotate(-90, 0.f, 1.f, 0.f);
	//Cara 2
	this->c2 = new QuadGL();
	this->c2->traslate(0.f, 0.f, -size / 2);
	this->c2->rotate(0, 0.f, 1.f, 0.f);
	//Cara 3
	this->c3 = new QuadGL();
	this->c3->traslate(size / 2, 0.f, 0.f);
	this->c3->rotate(90, 0.f, 1.f, 0.f);
	//Cara 4
	this->c4 = new QuadGL();
	this->c4->traslate(0.f, 0.f, size / 2);
	this->c2->rotate(180, 0.f, 1.f, 0.f);
	//Cara 5
	this->c5 = new QuadGL();
	this->c5->traslate(0.f, size / 2, 0.f);
	this->c5->rotate(-90, 1.f, 0.f, 0.f);
	//Cara 6
	this->c6 = new QuadGL();
	this->c6->traslate(0.f, -size / 2, 0.f);
	this->c6->rotate(90, 1.f, 0.f, 0.f);
}
BoxGL::~BoxGL()
{

}
void BoxGL::render()
{
	/*
	glPolygonMode(GL_FRONT, this->frontFaceMode);
	glPolygonMode(GL_BACK, this->backFaceMode);
	glColor3f(this->color[0], this->color[1], this->color[2]);
	*/

	glColor3f(this->color[0], this->color[1], this->color[2]);
	glPushMatrix();
	//Hace una multiplicación del vector.
	GLfloat *ptrM = glm::value_ptr(this->m);
	glMultMatrixf(ptrM);

	//FrontFace
	this->c1->frontFaceMode = this->frontFaceMode;
	this->c2->frontFaceMode = this->frontFaceMode;
	this->c3->frontFaceMode = this->frontFaceMode;
	this->c4->frontFaceMode = this->frontFaceMode;
	this->c5->frontFaceMode = this->frontFaceMode;
	this->c6->frontFaceMode = this->frontFaceMode;
	//backFace
	this->c1->backFaceMode = this->backFaceMode;
	this->c2->backFaceMode = this->backFaceMode;
	this->c3->backFaceMode = this->backFaceMode;
	this->c4->backFaceMode = this->backFaceMode;
	this->c5->backFaceMode = this->backFaceMode;
	this->c6->backFaceMode = this->backFaceMode;
	//Color
	this->c1->setColor(this->color[0], this->color[1], this->color[2]);
	this->c2->setColor(this->color[0], this->color[1], this->color[2]);
	this->c3->setColor(this->color[0], this->color[1], this->color[2]);
	this->c4->setColor(this->color[0], this->color[1], this->color[2]);
	this->c5->setColor(this->color[0], this->color[1], this->color[2]);
	this->c6->setColor(this->color[0], this->color[1], this->color[2]);


	this->c1->render();
	this->c2->render();
	this->c3->render();
	this->c4->render();
	this->c5->render();
	this->c6->render();


	/*
	this->c1->traslate(1.f, 0.f, 0.f);
	this->c2->traslate(1.f, 0.f, 0.f);
	this->c3->traslate(1.f, 0.f, 0.f);
	this->c4->traslate(1.f, 0.f, 0.f);
	*/
	glPopMatrix();
}