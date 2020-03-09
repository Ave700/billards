#pragma once

#include <vector>
#include "glm/glm/vec3.hpp"
#include <windows.h>
#include <GL/GL.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include "pooltable.h"
#define BIL_MASS 0.170 //mass in kg of pool ball from wikipedia
#define BIL_RADIUS 0.0285 //radius in meters of pool ball from wikipedia
#define BIL_MOMENT_INTERTA ((double)2/5)* BIL_MASS * (BIL_RADIUS*BIL_RADIUS) //Following 2/5*mR^2

struct Billard
{
	GLUquadricObj* sphere;
	int id;
	double mass = BIL_MASS;
	double radius = BIL_RADIUS;
	//std::vector< glm::vec3 > position = (0.0f, 0.0f, 0.0f);
	glm::vec3 position = glm::vec3(0.0f, 0.0, 0.0f);
	glm::vec3 velocity = glm::vec3(0.0, 0.0, 0.0);
	//std::vector< glm::vec3 > velocity;
	glm::vec3 acceleration = glm::vec3(-0.0, 0.0, 0.0);
	void wallcollide(float deltaTime) {
		if (position.x + (velocity.x * deltaTime) + (((float)1 / 2) * acceleration.x * pow(deltaTime, 2)) > (TABLE_WIDTH / 2-BIL_RADIUS) || position.x + (velocity.x * deltaTime) + (((float)1 / 2) * acceleration.x * pow(deltaTime, 2)) < -TABLE_WIDTH / 2+BIL_RADIUS) {
			velocity.x = -1 * velocity.x;
		}
		if (position.y + (velocity.y * deltaTime) + (((float)1 / 2) * acceleration.y * pow(deltaTime, 2)) > (TABLE_HEIGHT/ 2-BIL_RADIUS) || position.y + (velocity.y * deltaTime) + (((float)1 / 2) * acceleration.y * pow(deltaTime, 2)) < -TABLE_HEIGHT / 2+BIL_RADIUS) {
			velocity.y = -1 * velocity.y;
		}

	}
	void timestep(float deltaTime) {

		//check collisions
		//checking wall collision
		wallcollide(deltaTime);
		//a = a
		//v =v0 + a*dt
		//s = s0 +v*dt + 1/2a*dt^2

		//update acceleration update velocity v0 update position s

		//updating velocity
		velocity.x = velocity.x + (acceleration.x * deltaTime);
		velocity.y = velocity.y + (acceleration.y * deltaTime);
		velocity.z = velocity.z + (acceleration.z * deltaTime);

		//updating position
		position.x = position.x + (velocity.x * deltaTime) + (((float)1 / 2) * acceleration.x * pow(deltaTime, 2));
		position.y = position.y + (velocity.y * deltaTime) + (((float)1 / 2) * acceleration.y * pow(deltaTime, 2));
		position.z = position.z + (velocity.z * deltaTime) + (((float)1 / 2) * acceleration.z * pow(deltaTime, 2));

	}
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