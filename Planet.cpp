#include "Planet.h"
#include <iostream>

PlanetGL::PlanetGL(int p) : ObjectGL() {
	this->radius = 1.f;
	this->slices = 30.f;
	this->stacks = 30.f;
	this->type = p;
	init(p);

}
PlanetGL::~PlanetGL() {
}

void PlanetGL::render() {
	glPushMatrix();
	glColor3f(this->color[0], this->color[1], this->color[2]);
	GLfloat *ptrM = glm::value_ptr(this->m);

	glMultMatrixf(ptrM);

	if (!this->closed) {
		renderbmp();
		gluSphere(this->quad, this->radius, this->slices, this->stacks);
	}
	else
	{
		this->box->setColor(this->color[0], this->color[1], this->color[2]);
		this->box->render();
	}
	

	glPopMatrix();
}

void PlanetGL::renderbmp() {
	glClearColor(0.f, 0.f, 0.f, 0.f);
	glColor3f(this->color[0], this->color[1], this->color[2]);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_RGB,
		this->image->width, this->image->height,
		0,
		GL_RGB,
		GL_UNSIGNED_BYTE,
		this->image->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	this->quad = gluNewQuadric();
	gluQuadricDrawStyle(this->quad, GLU_FILL);
	gluQuadricTexture(this->quad, true);
	gluQuadricNormals(this->quad, GLU_SMOOTH);
}

void PlanetGL::setQuad(GLUquadric* quad) 
{
	this->quad = quad;
}

void PlanetGL::init(int p) 
{
	this->box = new BoxGLU();
	PlanetGL::getType(p);
	glGenTextures(1, &this->textureId);
	glBindTexture(GL_TEXTURE_2D, this->textureId);
	this->image = loadBMP(this->bmpName);
}

void PlanetGL::getType(int p)
{
	//char *bmpName;
	switch (p)
	{
	case PlanetGL::SUN:
		this->bmpName = "sun.bmp";
		break;
	case PlanetGL::MERCURY:
		this->bmpName = "mercury.bmp";
		break;
	case PlanetGL::MARS:
		this->bmpName = "mars.bmp";
		break;
	case PlanetGL::EARTH:
		this->bmpName = "earth.bmp";
		break;
	case PlanetGL::VENUS:
		this->bmpName = "venus.bmp";
		break;
	case PlanetGL::JUPITER:
		this->bmpName = "jupiter.bmp";
		break;
	case PlanetGL::SATURN:
		this->bmpName = "saturn.bmp";
		break;
	case PlanetGL::URANUS:
		this->bmpName = "uranus.bmp";
		break;
	case PlanetGL::NEPTUNE:
		this->bmpName = "neptune.bmp";
		break;
	case PlanetGL::PLUTON:
		this->bmpName = "pluto.bmp";
		break;
	}
}