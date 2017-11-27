#pragma once
#ifndef ___SHADER__
#define ___SHADER__
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>
#include "Mat4.h"
#include "Vector3f.h"
class Shader{
private:
	GLuint programId;
	GLuint vsId;
	GLuint fsId;
	Shader(GLuint programId, GLuint vsId, GLuint fsId) 
		: programId(programId), vsId(vsId), fsId(fsId) {}

	~Shader();
public:
	static Shader *load(char *vsname, char *fsname);
	void bind();
	int getUniformLocation(char *name);
	void uniformMat4(char *name, Mat4 *m);
	void uniformVec3(char *name, Vector3f *v);
	void uniformVec2(char *name, float f1, float f2);
	void uniformVec4(char *name, float x, float y, float z, float w);
	void uniformf(char *name, float);
	void uniformi(char *name, int);
};

#endif