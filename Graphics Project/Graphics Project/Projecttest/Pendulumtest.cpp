#include "Pendulum.h"

Pendulum::Pendulum(Shader *s) : SceneObject(s){
	rectprism = Mesh::generateRectangularPrism();
}

void Pendulum::drawBase() {
	//This is simply to shape the prism correctly. 
	glPushMatrix();
	glScalef(1 , 0.125f, 1);
	rectprism->draw();
	glPopMatrix();
}

void Pendulum::drawArm() {
	//This is simply to shape the prism correctly. 
	glPushMatrix();
	glScalef(0.125f, 1, 0.125f);
	rectprism->draw();
	glPopMatrix();
}


void Pendulum::drawString() {
	//This is simply to shape the prism correctly. 
	glPushMatrix();
	glScalef(0.05f, 1, 0.05f);
	rectprism->draw();
	glPopMatrix();
}

void Pendulum::drawWeight() {
	//This is simply to shape the prism correctly. 
	glPushMatrix();
	glScalef(0.125f, 0.125f, 0.125f);
	rectprism->draw();
	glPopMatrix();
}
//This time the hierarchical modeling is done without the use of a tree structure. 
//This is to show an explicit example.
void Pendulum::draw() {
	drawBase();
	glPushMatrix();
	{
		glTranslatef(0, 0.625f, 0);
		drawArm();
		glPushMatrix();
		{
			glTranslatef(0, 0.5f, 0);
			glRotatef(45, 1, 0, 0);
			glTranslatef(0, 0.5f, 0);
			drawArm();
			glPushMatrix();
			{
				glTranslatef(0, 0.5f, 0);
				glRotatef(-45, 1, 0, 0);
				glRotatef(sin(frame/20.f) * 30, 0, 0, 1);
				glTranslatef(0, -0.5f, 0);
				drawString();
				glPushMatrix();
				{
					glTranslatef(0, -0.5f, 0);
					glTranslatef(0, -0.0625f, 0);
					drawWeight();
				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void Pendulum::update(float dt) {
	frame += dt;
}

