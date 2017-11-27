#pragma once
#ifndef ___SKYBOX__
#define ___SKYBOX__
#include "Mesh.h"
#include "Shader.h"
class SkyBox {
private:
	Shader *s;
	int tid;
public:
	SkyBox(Shader *s, int tid);
	
	void display(Mat4 *viewprojecection);

};

#endif