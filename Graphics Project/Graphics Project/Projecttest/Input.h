#pragma once
#ifndef ___Input__
#define ___Input__
#ifdef __APPLE__                        // if OS X
#include <glut/glut.h>                  // include freeglut libraries
#else                                   // if Windows
#include <gl/glut.h>                    // include freeglut libraries
#endif
class Input {

public:
	static void init();
	static void setMousePos(int x, int y);
	static int getMouseX();
	static int getMouseY();
	static float getDT();
	static void update();
	static int getMouseDX();
	static int getMouseDY();
	static void grabMouse(int, int);
	static void keyPressed(unsigned char, int, int);
	static void keyReleased(unsigned char, int, int);
	static bool getKeyState(unsigned char);
private:
	static int lasttime;
	static float dt;
	static int mousex;
	static int mousey;
	static int mdx;
	static int mdy;
	static bool warped;
	static bool keys[];
};
#endif