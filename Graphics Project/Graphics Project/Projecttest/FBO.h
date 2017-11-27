#pragma once
#ifndef ___FBO__
#define ___FBO__
#include "GL/glew.h"
class FBO {
private:
	GLuint id;
	int width;
	int height;

	GLuint depthid;
public:
	FBO(int width, int height);
	~FBO();

	void bind();
	int colorTextureAttachment(int slot);
	void depthBufferAttachment();

	static void bindWindow(int width, int height);


};
#endif