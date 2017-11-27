#pragma once
#ifndef ___MyScene__
#define ___MyScene__
#include "Camera.h"
#include <GL/glew.h>
#include <stdio.h>


#include <iostream>
#include "Texture.h"
#include "CubeTexture.h"
#include "SkyBox.h"
#include "Shader.h"
#include "Mat4.h"
#include "Light.h"
#include "FBO.h"

class MyScene {
	public:

	static Shader *normalshader;
	static Shader *noiseshader;
	static Shader *postshader;
	static Texture *texture;
	static Camera *cam;
	static FBO *post1;
	static FBO *post2;
	static bool tex;
	static int prevtime;
	static int screentexture1;
	static int screentexture2;
	static void setup();
	static void draw();

	static void reshape(int, int);
	static void checkGLError();                        // Prints any OpenGL errors to console
	static void mouseexit(int);
	static void setMousePos(int, int);
	static void close();
	static void windowSetup();
	static void initObjects();
};
#endif