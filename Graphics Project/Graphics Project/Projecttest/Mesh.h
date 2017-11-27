#pragma once
#ifndef ___Mesh__
#define ___Mesh__
#define _CRT_SECURE_NO_WARNINGS
#include <GL/glew.h>
#include <vector>;
#include "Vector3f.h"

class Mesh {
	GLuint vaoID;
	GLuint vboID;
	GLuint iboID;
	GLuint size;
	GLenum target;

	static GLuint indexingvao;
public:
	~Mesh();
	void load(GLfloat vertices[], GLuint indices[], GLuint vsize, GLuint isize, GLenum target);
	void draw();
	void loadModel(char *filename);

	static Mesh * generateRectangularPrism();

	static void indexCall(int size); 
};
#endif