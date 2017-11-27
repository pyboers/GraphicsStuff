#include "Camera.h"

Camera::Camera(float x, float y, float z, int width, int height, float fov, float znear, float zfar) 
	: movespeed(100), horizontalangle(0), verticalangle(0.0), width(width), height(height), 
	mousespeed(0.1), position(Vector3f(x, y, z)),  fov(fov), znear(znear), zfar(zfar) {
}

void Camera::update(float dt) {
	
	horizontalangle += mousespeed * dt * float(Input::getMouseDX());
	verticalangle -= mousespeed * dt * float(Input::getMouseDY());
	Vector3f dir= Vector3f(cos(verticalangle) * sin(horizontalangle), sin(verticalangle), cos(verticalangle) * cos(horizontalangle));
	dir.normalize();
	Vector3f right = Vector3f(sin(horizontalangle - 3.14f / 2.0f), 0, cos(horizontalangle - 3.14f / 2.0f));
	Vector3f up = right.cross(&dir);
	if (Input::getKeyState('w')) {
		position += &(dir * Input::getDT() * movespeed * dt);
	}
	if (Input::getKeyState('s')) {
		position -= &(dir * Input::getDT() * movespeed * dt);
	}
	if (Input::getKeyState('a')) {
		position += &(right * Input::getDT() * movespeed * dt);
	}
	if (Input::getKeyState('d')) {
		position -= &(right * Input::getDT() * movespeed * dt);
	}

	//printf("Position: %f %f %f Rotation: %f %f\n", position.getX(), position.getY(), position.getZ(), verticalangle, horizontalangle);
}
int Camera::getHeight() {
	return height;
}

int Camera::getWidth() {
	return width;
}

Mat4 *Camera::getViewMatrix(){
	Mat4 *view = new Mat4();
	Mat4 translationM = Mat4();
	Mat4 rotationM = Mat4();
	translationM.initTranslation(-position.getX(), -position.getY(), -position.getZ());
	rotationM.initRotation(verticalangle, horizontalangle, 0);
	rotationM.mul(view, &translationM);
	return view;
}

Mat4 *Camera::getProjectionMatrix(){
	Mat4 *projection = new Mat4();
	projection->perspective(fov, width / (float)height, znear, zfar);
	return projection;
}

Mat4 * Camera::getViewProjection() {
	Mat4 *view = getViewMatrix();
	Mat4 *projection = getProjectionMatrix();
	Mat4 *vp = new Mat4();
	return projection->mul(vp,view);
}


Camera::~Camera() {

}
