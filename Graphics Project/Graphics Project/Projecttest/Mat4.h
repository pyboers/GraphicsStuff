#pragma once
#ifndef ___Matrix__
#include <wchar.h>
#include <malloc.h>
#include <string.h>
#include <math.h>
#define PI 3.14159265358979323846f
#define MAT4_BYTESIZE 16 * sizeof(float)
class Mat4 {
private:

public:

	float *mat;
	Mat4();
	
	Mat4 *initIdentity();
	Mat4 *initTranslation(float x, float y, float z);
	Mat4 *initRotation(float x, float y, float z);
	void copy(Mat4 *src);
	Mat4 *mul(Mat4 *dest, Mat4 *other);
	Mat4 *perspective(float fov, float aspect, float zNear, float zFar);
	Mat4 *initScale(float x, float y, float z);

	~Mat4();

	

};

#endif