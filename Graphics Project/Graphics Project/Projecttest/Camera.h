#pragma once
#ifndef ___Camera__
#define ___Camera__
#include <GL/glew.h>
#include "Vector3f.h"
#include "Input.h"
#include <string>
#include "Mat4.h"

class Camera {
	int width, height;
	float fov;
	float znear;
	float zfar;
	float mousespeed;
	float movespeed;
	

public:	
	Vector3f position;
	void update(float dt);
	Camera(float, float, float, int, int, float ,float ,float);
	int getHeight();
	int getWidth();
	Mat4 *Camera::getViewMatrix();
	Mat4 *Camera::getProjectionMatrix();
	Mat4 *getViewProjection();
	~Camera();


private:
	float horizontalangle;
	float verticalangle;

};
#endif