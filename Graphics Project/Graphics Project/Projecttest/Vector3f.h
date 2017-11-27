		#pragma once
#ifndef ___Vector3f__
#define ___Vector3f__
#include <cmath>
class Vector3f {
	bool calcM;
	float magnitude;
	float val[3];
public:
	Vector3f(float, float, float);
	Vector3f(float, float, float, float);

	float getX();
	void setX(float);
	float getY();
	void setY(float);
	float getZ();
	void setZ(float);
	float getLength();
	void set(float, float, float);
	void set(Vector3f *);
	Vector3f operator+(Vector3f*);
	Vector3f operator-(Vector3f*);
	void operator+=(Vector3f*);
	void operator-=(Vector3f*);
	float operator*(Vector3f*);
	Vector3f operator*(float);
	void operator*=(float);
	Vector3f cross(Vector3f *);
	void normalize();
	Vector3f normalized();


private:
};
#endif