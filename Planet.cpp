#include "Planet.h"
#include <iostream>

PlanetGL::PlanetGL(int p) : ObjectGL() {
	this->radius = 1.f;
	this->slices = 30.f;
	this->stacks = 30.f;
	this->type = p;
	this->rot = 0.0;
	this->deltaRot = 0.4;
	init(p);

}
PlanetGL::~PlanetGL() {
}

void PlanetGL::render() {
	glPushMatrix();
	glColor3f(this->color[0], this->color[1], this->color[2]);
	GLfloat *ptrM = glm::value_ptr(this->m);

	glMultMatrixf(ptrM);
	this->rot = this->rot + deltaRot;


	if (!this->closed) {
		renderbmp();
		glRotatef(-this->rot, 0, 1., 0);
		glRotatef(-90, 1., 0, 0);
		gluSphere(this->quad, this->radius, this->slices, this->stacks);
	}
	else
	{
		this->box->setColor(this->color[0], this->color[1], this->color[2]);
		if (this->timer >= this->limit)
		{
			this->box->render();
		}
		else {
			renderbmp();
			glRotatef(-this->rot, 0, 1., 0);
			glRotatef(-90, 1., 0, 0);
			gluSphere(this->quad, this->radius, this->slices, this->stacks);
		}
	}
	
	if (this->timer < this->limit) {
		this->timer++;
	}
	glPopMatrix();
}

void PlanetGL::renderbmp() {
	glClearColor(0.f, 0.f, 0.f, 0.f);
	//glColor3f(this->color[0], this->color[1], this->color[2]);
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
		//this->radius = 0.068250993f;
		break;
	case PlanetGL::MARS:
		this->bmpName = "mars.bmp";
		//this->radius = 0.095037207f;
		break;
	case PlanetGL::EARTH:
		this->bmpName = "earth.bmp";
		//this->radius = 0.178425558f;
		break;
	case PlanetGL::VENUS:
		this->bmpName = "venus.bmp";
		//this->radius = 0.169300062f;
		break;
	case PlanetGL::JUPITER:
		this->bmpName = "jupiter.bmp";
		//this->radius = 2.f;
		break;
	case PlanetGL::SATURN:
		this->bmpName = "saturnring.bmp";
		//this->radius = 1.686006826f;
		break;
	case PlanetGL::URANUS:
		this->bmpName = "uranus.bmp";
		//this->radius = 0.715017065f;
		break;
	case PlanetGL::NEPTUNE:
		this->bmpName = "neptune.bmp";
		//this->radius = 0.693392268f;
		break;
	case PlanetGL::PLUTON:
		this->bmpName = "pluto5.bmp";
		//this->radius = 0.033150562f;
		break;
	case PlanetGL::MOON:
		this->bmpName = "moon.bmp";
		//this->radius = 0.04859285f;
		break;
	}
}