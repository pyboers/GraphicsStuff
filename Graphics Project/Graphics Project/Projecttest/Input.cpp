#include "Input.h"
#include <string>
int Input::lasttime;
float Input::dt;
int Input::mousex;
int Input::mousey;
int Input::mdx;
int Input::mdy;
bool Input::warped;
bool Input::keys[256];


void Input::init() {
	mousex = 0;
	mousey = 0;
	mdx = 0;
	mdy = 0;
	warped = true;
}


void Input::update() {
	int time = glutGet(GLUT_ELAPSED_TIME);
	dt = time - lasttime;
	dt /= 1000;
	lasttime = time;
	mdx = 0;
	mdy = 0;
}

int Input::getMouseDX() {
	return mdx;
}

int Input::getMouseDY() {
	return mdy;
}

int Input::getMouseX() {
	return mousex;
}

int Input::getMouseY() {
	return mousey;
}

float Input::getDT() {
	return dt;
}
static bool warped = false;
void Input::grabMouse(int x, int y) {
	glutWarpPointer(x, y);
	warped = true;
	mousex = x;
	mousey = y;
}

void Input::setMousePos(int x, int y) {
		mdx = x - mousex;
		mdy = y - mousey;
		mousex = x;
		mousey = y;
}

void Input::keyPressed(unsigned char key,int x,int y) {
	keys[key] = true;
}

void Input::keyReleased(unsigned char key, int x, int y) {
	keys[key] = false;
}


bool Input::getKeyState(unsigned char key) {
	return keys[key];
}