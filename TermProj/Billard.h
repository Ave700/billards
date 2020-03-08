#pragma once

#include <vector>
#include "glm/glm/vec3.hpp"
#include <windows.h>
#include <GL/GL.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#define BIL_MASS 0.170 //mass in kg of pool ball from wikipedia
#define BIL_RADIUS 0.0285 //radius in meters of pool ball from wikipedia
#define BIL_MOMENT_INTERTA ((double)2/5)* BIL_MASS * (BIL_RADIUS*BIL_RADIUS) //Following 2/5*mR^2

struct Billard
{
	GLUquadricObj* sphere;
	int id;
	double mass = BIL_MASS;
	double radius = BIL_RADIUS;
	std::vector< glm::vec3 > position;
	std::vector< glm::vec3 > velocity;
	std::vector< glm::vec3 > acceleration;
	void draw(GLuint texture) {
		if (!(sphere = gluNewQuadric())) exit(1);
		gluQuadricDrawStyle(sphere, GLU_FILL);
		gluQuadricNormals(sphere, GLU_SMOOTH);
		//gluQuadricTexture(sphere, GL_TRUE);
		gluQuadricTexture(sphere, GLU_TRUE);
		//glMaterialfv(GL_FRONT, GL_SPECULAR, diffuse_surface);
		glColor3f(1.0, 1.0, 1.0);
		glBindTexture(GL_TEXTURE_2D, texture);

		//glCallList(mysphereID);
		//glMatrixMode(GL_MODELVIEW);
		//glLoadIdentity();
		//glTranslatef(10.0, 0.0, 10.0);
		gluSphere(sphere, .035, 50, 50);
	}

};