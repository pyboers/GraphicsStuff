#include "Vector3f.h"

Vector3f::Vector3f(float x, float y, float z) {
	val[0] = x;
	val[1] = y;
	val[2] = z;
	calcM = true;
}

Vector3f::Vector3f(float x, float y, float z, float mag) {
	val[0] = x;
	val[1] = y;
	val[2] = z;
	magnitude = mag;
	calcM = false;
}

Vector3f Vector3f::cross(Vector3f *v2) {
	return Vector3f(val[1] * v2->getZ() - val[2] * v2->getY(), 
		val[2]*v2->getX() - val[0]*v2->getZ(),
		val[0]*v2->getY() - val[1]*v2->getX());
}

Vector3f Vector3f::operator+(Vector3f *v2) {
	return Vector3f(val[0] + v2->getX(), val[1] + v2->getY(), val[2] + v2->getZ());
}


Vector3f Vector3f::operator-(Vector3f *v2) {
	return Vector3f(val[0] - v2->getX(), val[1] - v2->getY(), val[2] - v2->getZ());
}

void Vector3f::operator+=(Vector3f *v2) {
	val[0] += v2->getX();
	val[1] += v2->getY();
	val[2] += v2->getZ();
	calcM = true;
}

void Vector3f::operator-=(Vector3f *v2) {
	val[0] -= v2->getX();
	val[1] -= v2->getY();
	val[2] -= v2->getZ();
	calcM = true;
}

void Vector3f::operator*=(float f) {
	val[0] *= f;
	val[1] *= f;
	val[2] *=f;
	if (!calcM) {
		magnitude *= f;
	}
}

float Vector3f::operator*(Vector3f *v2) {
	return val[0] * v2->getX() + val[1] * v2->getY() + val[2] * v2->getZ();
}

Vector3f Vector3f::operator*(float f) {
	if (calcM) {
		return Vector3f(val[0] * f, val[1] * f, val[2] * f);
	}

	return Vector3f(val[0] * f, val[1] * f, val[2] * f, magnitude * f);
}

void Vector3f::normalize() {
	getLength();
	val[0] /= magnitude;
	val[1] /= magnitude;
	val[2] /= magnitude;
	magnitude = 1;
}


Vector3f Vector3f::normalized() {
	getLength();
	return Vector3f(val[0]/magnitude, val[1]/magnitude, val[2]/magnitude, 1);
}





float Vector3f::getLength() {
	if (calcM) {
		magnitude = sqrt(val[0]*val[0] + val[1]*val[1] + val[2]*val[2]);
	}
	return magnitude;
}




//Getters and Setters
void Vector3f::set(float x, float y, float z) {
	val[0] = x;
	val[1] = y;
	val[2] = z;
	calcM = true;
}

void Vector3f::set(Vector3f *v) {
	set(v->getX(), v->getY(), v->getZ());
}

float Vector3f::getX() {
	return val[0];
}

float Vector3f::getY() {
	return val[1];
}

float Vector3f::getZ() {
	return val[2];
}

void Vector3f::setX(float x) {
	val[0] = x;
	calcM = true;
}

void Vector3f::setY(float y) {
	val[1] = y;
	calcM = true;
}

void Vector3f::setZ(float z) {
	val[2] = z;
	calcM = true;
}