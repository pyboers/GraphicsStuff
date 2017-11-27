#pragma once
#ifndef ___PENDULUM__
#define ___PENDULUM__
#include "SceneObject.h"
#include "Mesh.h"
class Pendulum  : public SceneObject{
private:
	int frame;
	Mesh *rectprism;
	Mesh *weight;
	void drawBase();

	void drawArm();

	void drawString();

	void drawWeight();
public:
	Pendulum(Shader *s);
	void draw();
	void update(float dt);
};
#endif